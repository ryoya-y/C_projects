# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <regex.h>
# include <dirent.h>
# include <time.h>

#define INIT_BUF 1

int main(){
  char *buf, *tmp;
  int size=INIT_BUF;
  fprintf(stdout, "first size: %d\n", size);
  buf=malloc(size);


  for (;;){
    if ((getcwd(buf, size))!=NULL){
      fprintf(stdout, "Now, buf size is %d\n", size);
      fprintf(stdout, "%s\n", buf); break;
    }
    else{
      size*=2;
      tmp=realloc(buf, size);
      buf=tmp;
    }
  }
  free(buf);6
  exit(0);
}
