# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#define BUFFER_SIZE 2048


void die(const char *s){
  perror(s);
  exit(0);
}

void do_wcl(const char *path){
  int fd;
  char buf[BUFFER_SIZE];
  int n;

  fd=open(path, O_RDONLY);
  if (fd<0) die(path);
  int tmp=0;
  for (;;){
    n=read(fd, buf, sizeof buf);
    if (n<0) die(path);
    else if (n==0) break;
    else{
      int num=0;
      for (num=0;num<n;num++){
        if (buf[num]=='\n') tmp++;
      }
    }
  }
  printf("num of \"\\n\" %d\n", tmp);
  if (close(fd)<0) die(path);
}



int main(int argc, char *argv[]){
  if (argc<2){
    char path[100];
    printf("input file name\n");
    char *buf[BUFFER_SIZE];
    scanf("%s", path);
    do_wcl(path);
  }
  else{
    int i;
    for (i=1; i<argc; i++)
      do_wcl(argv[i]);
  }
  exit(1);
}
