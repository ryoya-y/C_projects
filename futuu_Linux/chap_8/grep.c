# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <regex.h>
#define BUFFER_SIZE 2048

void die(char *path){
  perror(path);
  exit(0);
}


void do_grep(regex_t *pat, FILE *f){
  char buf[4096];
  while(fgets(buf, sizeof buf, f)){
    if (regexec(pat, buf, 0, NULL, 0)==0){
      fputs(buf, stdout);
    }
  }

}


int main(int argc, char *argv[]){
  regex_t pat;
  int err;
  int i;

  // ptternの正規処理

  if (argc<2){
    fprintf(stderr, "Usage error: %s\n", argv[0]);
    exit(1);
  }

  err=regcomp(&pat, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);

  if (err!=0){
    char buf[1024];
    regerror(err, &pat, buf, sizeof buf);
    puts(buf);
    exit(1);
  }

  else{
    FILE *f;
    f=fopen(argv[2], "r");
    if (f==NULL){
      die(argv[2]);
    }
    do_grep(&pat, f);
  }
  exit(1);

}
