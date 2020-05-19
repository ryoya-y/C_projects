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

void stdio_cat(char *path){
  FILE *fd;
  fd=fopen(path, "r");
  if (fd==NULL) die(path);
  int c;
  while ((c=fgetc(fd))!=EOF){
    if (c=='\t'){
      printf("\\t");
    }
    else if (c=='\n') printf("$\n");
    else {
     if (putchar(c)<0) die(path);
    }
  }
  if (fclose(fd)) die(path);
}


int main(int argc, char *argv[]){
  if (argc<2){
    printf("input file name\n");
  }
  else{
    int i;
    for (i=1; i<argc; i++){
      stdio_cat(argv[i]);
    }
  }
  exit(0);
}
