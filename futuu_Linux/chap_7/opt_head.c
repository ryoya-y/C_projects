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
  int opt;
  int nlines;
  while ((opt=getopt(argc, argv, "n:h"))!=-1){
    switch(opt){
      case 'n':
        nlines=atol(optarg); break;
      case 'h':
        fprintf(stdout, "Usage: help help help\n"); break;
      case '?':
        fprintf(stderr, "Usage error: %s\n", argv[0]); break; exit(0);
    }
  }

  if (optind==argc) do_head(stdin, nlines);
  else{
    int i;
    for (i=optind; i<argc; i++){
      fprintf(stdout, "%s:\n", argv[i]);
      printf("-----------------------------------\n");
      FILE *f;
      f=fopen(argv[i], "r");
      do_head(f, nlines);
      printf("-----------------------------------\n");
    }
  }
  exit(1);
}
