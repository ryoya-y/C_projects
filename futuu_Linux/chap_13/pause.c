# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <regex.h>
# include <dirent.h>
# include <time.h>
# include <signal.h>

void msg(){
  printf("signal call\n");
}


int main(){
  struct sigaction act;
  act.sa_handler=msg;
  sigemptyset(&act.sa_mask);
  act.sa_flags=0;

  sigaction(SIGINT, &act, NULL);

  printf("before pause...\n");

  pause();

  printf("after pause...\n");

}
