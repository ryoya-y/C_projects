# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

# define LEN 4


void make_digits(int x[], int len){
  int i, j, val;
  for (i=0; i<len; i++){
    val=rand()%10;
    for (j=0; j<i; j++){
      if (val==x[j]){
        i-=1;
        break;
      }
      else x[i]=val;
    }
  }
}

int judge(char *s, int x[],int *hit,int *blow){
  int i,j;
  *hit=*blow=0;
  for (i=0; i<LEN; i++){
    char tmp;
    tmp=s[i];
    for (j=0; j<LEN; j++){
      if (tmp==x[j]+'0'){
        (*blow)++;
        if (i==j) (*hit)++;
      }
    }
  }
  if (*hit==4 && *blow==4)
    return 0;
  else
    return 1;
}


int main(){
  int flag;
  flag=1;
  int x[LEN];
  int i;
  make_digits(x, LEN);
  while (flag!=0) {

    //標準入力より回答を取得

    printf("回答を入力してください\n");
    char *s;
    s=(char *)malloc(LEN+1);
    scanf("%s", s);
    printf("input is %s\n", s);

    // 入力が数字か判定
    for (i=0; i<LEN; i++){
      if (isdigit(s[i])==0){
        fprintf(stderr, "input error: can not use string \'%c\'\n", s[i]);
        exit(1);
      }
    }

    int hit, blow;
    if ((flag=judge(s, x, &hit, &blow))==0) break;
    printf("hit: %d\nblow: %d\n", hit, blow);
    free(s);
  }
  printf("congrat!\n");
  exit(0);
}
