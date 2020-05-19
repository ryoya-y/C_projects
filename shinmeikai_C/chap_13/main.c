# include <stdio.h>

int main(void){
  FILE *fp, *fp_;
  char fname_r[FILENAME_MAX], fname_w[FILENAME_MAX];

  printf("ファイル名を入力してください\n");
  scanf("%s", fname_r);
  scanf("%s", fname_w);

  if ((fp=fopen(fname_r, "r"))==NULL){
    printf("readファイルを開けませんでした\n");
  }
  else{
    if ((fp_=fopen(fname_w,"w"))==NULL){
      printf("writeファイルを開けませんでした\n");
    }
    else{
      char ch;
      while ((ch=fgetc(fp))!=EOF){
        fprintf(fp_, "%c", ch);
      }
    }
  }
}
