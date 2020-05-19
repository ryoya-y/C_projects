#include <stdio.h>

#include <limits.h>

/* 配列の要素数を求める*/


int count_bits(unsigned x){
  int bits=0;
  while(x){
    if (x & 1U) bits++;
    x>>=1;
  }
  return bits;
}

int int_bits(void){
  return count_bits(~0U);
}


void print_bits(unsigned x){
  int max;
  max=int_bits();
  int i;
  for (i=0; i<max; i++){
    unsigned tmp;
    tmp=x>>(max-1);
    putchar((tmp & 1U) ? '1':'0');
    x=x<<1;
    // printf("%i\n", x);
  }
}

// bitの1の最高位の位置を調べる
int top_check(unsigned x){
  int max;
  max=int_bits();
  int i;
  for (i=1; i<=max; i++){
    int tmp;
    int shift;
    shift=max-i;
    tmp=x>>shift;
    if (tmp & 1U)
      return i-1;
  }
  return -1;
}

int tail_check(unsigned x){
  int max;
  max=int_bits();
  int i;
  for (i=1; i<=max; i++){
    int tmp;
    int shift;
    shift=max-i;
    tmp=x<<shift;
    tmp=tmp>>(max-1);
    if (tmp & 1U)
      return i-1;
  }
  return -1;
}


// 2のn乗を返す関数
int two_pow(int n){
  int i;
  int tmp=1;
  for (i=0; i<n; i++){
    tmp*=2;
  }
  return tmp;
}

int rrotate(unsigned x, int n){
  int max=int_bits();
  int tmp;
  tmp=x>>n;

  // rotateするn桁の移動後の値
  int rotate_value=0;
  int i;
  int check_tmp;
  unsigned rank_value;
  for (i=0; i<n; i++){
    check_tmp=x<<(max-i-1);
    check_tmp=check_tmp>>(max-1);
    rank_value=(check_tmp & 1U) ? 1:0;
    rotate_value+=(rank_value)*two_pow(max-n+i);
  }
  return tmp+rotate_value;
}

int main(void){
  unsigned num;
  printf("数字を入力してください\n");
  scanf("%u", &num);
  printf("top is %d, tail is %d\n", top_check(num), tail_check(num));

  printf("シフトする数を入力してください\n");
  unsigned shift;
  scanf("%u", &shift);

  printf("シフト後は%dです\n", rrotate(num, shift));
  print_bits(num);
  putchar('\n');
  print_bits(rrotate(num, shift));
  putchar('\n');


}
