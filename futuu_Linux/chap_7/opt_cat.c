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


void do_cat(FILE *f, int n_flag){
  char c;
  while((c=fgetc(f))!=EOF){
    if (n_flag==1){
      if (c=='\n') {
        putchar('$');
        putchar('\n');
      }
      else putchar(c);
    }
    else {
       putchar(c);
    }
  }
}


int main(int argc, char *argv[]){
  int opt;
  int n_flag=0;

  while((opt=getopt(argc, argv, "n"))!=-1){
    switch(opt){
      case 'n':
        n_flag=1; break;
      case '?':
        fprintf(stderr, "Usage error: %s\n", argv[0]); break; exit(1);
    }
  }

  if (optind==argc){
    do_cat(stdin, n_flag);
  }
  else{
    int i;
    for (i=optind; i<argc; i++){
      FILE *f;
      if ((f=fopen(argv[i], "r"))==NULL) die(argv[i]);
      do_cat(f, n_flag);
      if (fclose(f)<0) die(argv[i]);
    }
  exit(1);
  }
}

