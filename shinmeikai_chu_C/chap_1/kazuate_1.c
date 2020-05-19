# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# define MAX_TRY_NUM 10

int main(void){
  int ans;
  int input;
  int try_num;
  int input_list[MAX_TRY_NUM];


  srand(time(NULL));
  ans=rand()%1000;
  for(try_num=0; try_num<MAX_TRY_NUM; try_num++){
    printf("数を入力してください\n");
    scanf("%d", &input);
    input_list[try_num]=input;
    if (ans<input) printf("もっと小さい数字です 残り:%d回\n", MAX_TRY_NUM-try_num-1);
    else if (ans>input) printf("もっと大きい数字です 残り:%d回\n", MAX_TRY_NUM-try_num-1);
    else {
      printf("正解です\n");
      break;
    }
  }
  if (input!=ans)
    printf("正解は%dでした\n",ans);
  printf("-----------入力履歴--------------\n");

  int i;
  for (i=0; i<MAX_TRY_NUM; i++){
    printf("%d回目: 入力%d 差%d\n", i, input_list[i], input_list[i]-ans);
  }
  exit(0);
}
