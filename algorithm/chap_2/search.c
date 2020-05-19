# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define N 10
# define NOT_FOUND -1

int sort[N];
int buffer[N];


int linear_search(int i, int data[], int size){

  int num=0;

  while(data[num]!=i){
    num++;
  }

  if (num<size){
    return num;
  }else{
    return NOT_FOUND;
  }
}

int search(int i, int data[], int size){
  int num=0, temp;

  // 番兵を代入
  temp=data[size-1];
  data[size-1]=i;

  while(num<size && data[num]!=i){
    num++;
  }

  if (num<size-1){
    return num;
  }

  // 番兵より先にtargetがいればそちらを返すため、最初に判定をしない

  if (temp==i){
    return size-1;
  }

  return NOT_FOUND;
}

int binary_search(int i, int data[], int left, int right){
  int mid;

  while(left<right){
    mid=(left+right)/2;
    if(data[mid]<i){
      left=mid+1;
    }else{
      right=mid;
    }
    if (data[left]==i){
      return left;
    }
  }

  return NOT_FOUND;
}

void bubble_sort(void){
  int i, j, tmp;

  for (i=N-1; i>0; i--){
    for (j=0; j<i; j++){
      if (sort[j]>sort[j+1]){
        tmp=sort[j+1];
        sort[j+1]=sort[j];
        sort[j]=tmp;
      }
    }
  }
}

int main(void){
  srand((unsigned)time(NULL));
  int i;
  for (i=0; i<N; i++){
    sort[i]=rand()%10;
    if (i==0) sort[i]=0;
    printf("%d ", sort[i]);
  }
  printf("\n");
  // sortをソート
  bubble_sort();
  for (i=0; i<N; i++){
    printf("%d ", sort[i]);
  }
  int input, out;
  printf("数を入力してください\n");
  scanf("%d", &input);

  out=binary_search(input, sort, 0, N-1);

  if (out!=NOT_FOUND){
    printf("%d番目にあります\n", out+1);
  }else{
    printf("ありません\n");
  }
}
