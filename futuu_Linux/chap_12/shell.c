# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <regex.h>
# include <dirent.h>
# include <time.h>
#define BUFFER_SIZE 2048

void die(char *path){
  perror(path);
  exit(0);
}

int main(void){
  char command[100];
  while(1){
    fprintf(stdout, "shell original$\t");
    fgets(command, sizeof(command), stdin);
    pid_t pid;
    pid=fork();
    if (pid<0){
      fprintf(stderr, "Proc Error\n");
    }

    if (pid==0){
      execl(command, command, NULL);
      die(command);
    }

    else{
      int status;
      waitpid(pid, &status, 0);
      break;
    }
  }
}
