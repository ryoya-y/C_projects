# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <regex.h>
# include <dirent.h>
# include <stdarg.h>
# include <signal.h>
# include <string.h>
# include <time.h>

# define LINE_BUF_SIZE 100
# define MAX_REQUEST_BODY_LENGTH 100
# define TIME_BUF_SIZE 100
# define HTTP_MINOR_VERSION 1
# define SERVER_NAME "ORIGINAL WEB"
# define SERVER_VERSION "1.1"

typedef void (*sighandler_t)(int);

// HTTP構造体関連

struct HTTPHeaderField{
  char *name;
  char *value;
  struct HTTPHeaderField *next;
};

struct HTTPRequest{
  int protocol_minor_version;
  char *method;
  char *path;
  struct HTTPHeaderField *header;
  char *body;
  long length;
};

// ファイル構造体関連

struct FileInfo{
  char *path;
  long size;
  int ok;
};

// エラーとログに関する関数

void log_exit(char *fmt, ...){
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
  exit(1);
}

// メモリ管理

void* xmalloc(size_t sz){
  void *p;
  p=malloc(sz);
  if (!p) log_exit("failed to allocate memory");
  return p;
}

// 接続が切れた時のシグナル処理

static void signal_exit(int sig){
  log_exit("exit by signal: %d", sig);
}

void trap_signal(int sig, sighandler_t handler){
  struct sigaction act;
  act.sa_handler=handler;
  sigemptyset(&act.sa_mask);
  if (sigaction(sig, &act, NULL)<0){
    log_exit("sigaction failed");
  }
}

void install_signal_handlers(void){
  trap_signal(SIGPIPE, signal_exit);
}

// エンティティボディを確認

static char *lookup_header_field_value(struct HTTPRequest *req, char *name){
  struct HTTPHeaderField *h;

  for (h=req->header; h; h=h->next){
    if (strcasecmp(h->name, name)==0)
      return h->value;
  }
  return NULL;
}

static long content_length(struct HTTPRequest *req){
  char *val;
  long len;
  val=lookup_header_field_value(req, "Content-Length");
  if (!val) return 0;
  len=atol(val);
  if (len<0) log_exit("negative Content Length value");
  return len;
}

// headerの読み取り

static struct HTTPHeaderField *read_header_field(FILE *in){
  struct HTTPHeaderField *h;
  char *p;
  char buf[LINE_BUF_SIZE];
  if (!fgets(buf, LINE_BUF_SIZE, in)) log_exit("request size error: %s", in);
  if ((buf[0]=='\n') || (strcmp(buf, "\r\n")==0))
    return NULL;
  p=strchr(buf, ':');
  if (!p) log_exit("parse error on request header field: %s", in);
  *p++='\0';
  h=xmalloc(sizeof(struct HTTPHeaderField));
  h->name=xmalloc(p-buf);
  strcpy(h->name, buf);

  p+=strspn(p, "\t");
  h->value=xmalloc(strlen(p)+1);
  strcpy(h->value, p);

  return h;
}

// requestを読む

static void read_request_line(struct HTTPRequest *req, FILE *in){
  char buf[LINE_BUF_SIZE];
  char *p, *path;
  if (!fgets(buf, LINE_BUF_SIZE, in)){
    log_exit("failed to parse request: %s", in);
  }
  p=strchr(buf, ' ');
  if (!p) log_exit("parse error : %s", in);
  *p++='\0';
  req->method=xmalloc(p-buf);
  strcpy(req->method, buf);
  // upcase(req->method);
  path=p;
  p=strchr(path, ' ');
  if (!p) log_exit("parse error: %s", in);
  *p++='\0';
  req->path=xmalloc(p-path);
  strcpy(req->path, path);
  if (strncasecmp(p, "HTTP/1.", strlen("HTTP/1."))!=0){
    log_exit("parse error: %s", in);
  }

  p+=strlen("HTTP/1.");
  req->protocol_minor_version=atoi(p);
}

// リクエストをHTTPRequestに格納

static struct HTTPRequest *read_request(FILE *in){
  struct HTTPRequest *req;
  struct HTTPHeaderField *h;
  req=xmalloc(sizeof(struct HTTPRequest));
  read_request_line(req, in);
  req->header=NULL;
  while ((h=read_header_field(in))){
    h->next=req->header;
    req->header=h;
  }

  req->length=content_length(req);
  if (req->length!=0){
    if (req->length>MAX_REQUEST_BODY_LENGTH){
      log_exit("too long request");
    }
    req->body=xmalloc(req->length);
    if (fread(req->body, req->length, 1, in)<1){
      log_exit("failed to read request body");
    }
  }
  else{
    req->body=NULL;
  }
  return req;
}

// HTTP Requestのメモリ領域を解放

static void free_request(struct HTTPRequest *req){
  struct HTTPHeaderField *h, *head;
  head=req->header;
  while(head){
    h=head;
    head=head->next;
    free(h->name);
    free(h->value);
    free(h);
  }
  free(req->method);
  free(req->path);
  free(req->body);
}

// ファイル情報の処理


char *build_fspath(char *docroot, char *urlpath){
  char *path;
  path=xmalloc(strlen(docroot)+1+strlen(urlpath)+1);
  sprintf(path, "%s/%s", docroot, urlpath);
  return path;
}

static struct FileInfo *get_fileinfo(char *docroot, char *urlpath){
  struct FileInfo *info;
  struct stat st;

  info=xmalloc(sizeof(struct FileInfo));
  info->path=build_fspath(docroot, urlpath);
  info->size=0;
  if (lstat(info->path, &st)<0) return info;
  if (!S_ISREG(st.st_mode)) return info;
  info->ok=1;
  info->size=st.st_size;
  return info;
}

// ファイル情報の解放

static void free_fileinfo(struct FileInfo *info){
  free(info->path);
}

// common headerの関数

static void output_common_header_field(struct HTTPRequest *req, FILE *out, char *status){
  time_t t;
  struct tm *tm;
  char buf[TIME_BUF_SIZE];

  t=time(NULL);
  tm=gmtime(&t);
  if(!tm) log_exit("gmtime() failed");
  strftime(buf, TIME_BUF_SIZE, "%a, %d %b %Y %H:%M:%S GMT", tm);
  fprintf(out,"HTTP/1.%d %s\r\n", HTTP_MINOR_VERSION, status);
  fprintf(out, "Date: %s\n", buf);
  fprintf(out, "Server: %s%s\r\n", SERVER_NAME, SERVER_VERSION);
  fprintf(out, "Connection Close\n");
}

static void do_file_response(struct HTTPRequest *req, FILE *out, char *docroot){
  struct FileInfo *info;
  info=get_fileinfo(docroot, req->path);
  if (info->ok==0){
    free_fileinfo(info);
    fprintf(stderr, "file info error: not OK\n");
    // not_found(req, out);
    return;
  }
  output_common_header_field(req, out, "200 OK");
  fprintf(out, "Content-Length: %ld\r\n", info->size);
  // fprintf(out, "Content-type: %s\r\n", guess_content_type(info));
  fprintf(out, "\r\n");
  if (strcmp(req->method, "GET")==0){
    FILE *fd;
    int c;
    fd=fopen(req->path, "r");
    while((c=fgetc(fd))!=EOF){
      putchar(c);
    }
    fclose(fd);
  }
  fflush(out);
  free_fileinfo(info);
}


// methodごとの処理わけ
static void respond_to(struct HTTPRequest *req, FILE *out, char *docroot){
  if (strcmp(req->method, "GET")==0){
    do_file_response(req, out, docroot);
  }
  else if (strcmp(req->method, "HEAD")==0){
    do_file_response(req, out, docroot);
  }
  else if (strcmp(req->method, "POST")==0){
    // method_not_allowed(req, out);
  }
  else{
    // not_implemented(req, out);
  }
}


// service処理

static void service(FILE* in, FILE* out, char* docroot){
  struct HTTPRequest *req;
  req=read_request(in);
  respond_to(req, out, docroot);
  // fprintf(stdout, "Request is correct\n");
  free_request(req);
}

int main(int argc, char *argv[]){
  if (argc!=2){
    fprintf(stderr, "Usage error: %s <docroot>\n", argv[0]);
    exit(1);
  }

  install_signal_handlers();
  service(stdin, stdout, argv[1]);
  exit(0);
}



