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
    fprintf(stderr, "Usage error: %s\n", argv[0]);
    exit(0);
  }
  else{
    DIR *dir;
    struct dirent *ent;
    dir=opendir(argv[1]);
    if (dir==0) die(argv[1]);
    while((ent=readdir(dir))!=NULL){
      printf("%s\n", ent->d_name);
    }
    closedir(dir);
  }
}
