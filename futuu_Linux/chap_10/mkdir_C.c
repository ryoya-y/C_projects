# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <regex.h>
# include <dirent.h>
#define BUFFER_SIZE 2048

void die(char *path){
  perror(path);
  exit(0);
}


int main(int argc, char *argv[]){
  if (argc!=2){
    fprintf(stderr, "Usage error:%s\n", argv[0]);
  }
  else{
    if(mkdir(argv[1], 0777)<0){
      die(argv[1]);
    }
  }
  exit(0);
}
