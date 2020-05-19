# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# define BUF_SIZE 100

int sleep(unsigned long x){
  clock_t c1=clock(), c2;
  do{
    if ((c2=clock())==(clock_t)-1)
      return 0;
  }while(1000*(c2-c1)/CLOCKS_PER_SEC<x);
  return 1;
}

int main(void){
  char buf[BUF_SIZE];
  printf("文字を入力してください\n");
  fgets(buf, BUF_SIZE, stdin);
  int buf_length, out_length;
  buf_length=strlen(buf);
  buf[buf_length-1]='\0';
  out_length=20;
  while(1){
    if (out_length>buf_length){
      int i;
      char *p;
      for (i=0; i<out_length+buf_length+1; i++){
        if (i<buf_length){
          p=buf+buf_length-i-1;
          fprintf(stdout, "%s", p);
          printf("\r");
          fflush(stdout);
          sleep(500);
        }
        else if (i<out_length){
          int j;
          for (j=0; j<i-buf_length+1; j++){
            putc(' ', stdout);
          }
          printf("%s", buf);
          printf("\r");
          fflush(stdout);
          sleep(500);
        }
        else{
          int k;
          for (k=0; k<i-buf_length+1; k++){
            putchar(' ');
          }
          int l;
          for (l=0; l<buf_length-i+out_length; l++){
            putchar(buf[l]);
          }
          printf("\r");
          fflush(stdout);
          sleep(500);
        }
      }
    }
  }
}
