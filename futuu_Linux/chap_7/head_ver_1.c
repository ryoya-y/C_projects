# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#define BUFFER_SIZE 2048

void die(char *path){
  perror(path);
  exit(0);
}

int do_head(FILE *f, long num){
  int p_flag;
  char c;
  while((c=fgetc(f))!=EOF){
    if (putchar(c)<0) exit(0);
    if (c=='\n')p_flag++;
    if (p_flag==num) break;
  }
  return EOF;
}

int main(int argc, char *argv[]){
  if (argc<2){
    fprintf(stderr, "Usage error: %s\n", argv[0]);
    exit(0);
  }
  else if (argc==2) do_head(stdin, atol(argv[1]));
  else{
    int i;
    for (i=2; i<argc; i++){
      FILE *f;
      if ((f=fopen(argv[i], "r"))==NULL) die(argv[i]);
      do_head(f, atol(argv[1]));
      if (fclose(f)<0) die(argv[i]);
    }
  }
  exit(1);
}
