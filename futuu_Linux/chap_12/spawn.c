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

int main(int argc, char *argv[]){
  if (argc!=3){
    fprintf(stderr, "Usage error: %s\n", argv[0]);
  }

  pid_t pid;
  pid=fork();

  if (pid<0){
    fprintf(stderr, "fork(2) errored\n");
    exit(0);
  }
  // 子プロセスの処理
  if (pid==0){
    execl(argv[1], argv[1], argv[2], NULL);
    die(argv[1]);
  }

  else{
    int status;
    waitpid(pid, &status,0);
    if (WIFEXITED(status)){
      fprintf(stdout, "exit, status=%d\n", status);
    }
    else if (WIFSIGNALED(status)){
      fprintf(stdout, "signaled, status=%d\n", status);
    }
    else{
      fprintf(stdout, "abnormal exit\n");
    }
  }

}
