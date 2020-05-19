# include <stdio.h>

void bsort(int v[], int length){

  int i;
  for (i=0; i<length; i++){
    // i番目の値を決定する
    int j;
    for (j=length-1; j>i; j--){
      int key_1, key_2;
      key_1=(v[j]>v[j-1]) ? v[j]:v[j-1];
      key_2=(v[j]>v[j-1]) ? v[j-1]:v[j];
      v[j]=key_1;
      v[j-1]=key_2;
    }
  };
}


int combination(int n, int r){
  if (n>r && r>0)
    return combination(n-1, r-1)+combination(n-1, r);
  else
    return 1;
}

int gcd(int x, int y){
  if (x!=y){
    int big, small;
    big=(x>y) ? x:y;
    small=(x>y) ? y:x;
    int diff;
    diff=big-small;
    return gcd(diff, small);
  }
  else
    return x;
}

void rev_str(char v[]){
  int end;
  end=0;
  while(v[end])
    end++;

  int i;
  for (i=0; i<(float)(end/2); i++){
    char key_1, key_2;
    key_1=v[i];
    key_2=v[end-i-1];
    v[i]=key_2;
    v[end-i-1]=key_1;
  }
}

void all_rev_str(char v[][128], int num){
  int i;
  for (i=0; i<num; i++){
    rev_str(v[i]);
  }
}

int main(void){
  char str[][128]={"DEFGFFDE", "ABC", "CDE"};
  int num=3;
  all_rev_str(str, num);
  int i;
  for (i=0; i<num; i++)
    printf("%s\n", str[i]);
}
