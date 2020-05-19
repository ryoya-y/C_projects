# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define N 10

int sort[N];
int buffer[N];


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


void quick_sort(int bottom, int top, int *data){
  // bottom>=topの場合、return
  if (bottom>=top) return;

  int lower, upper, div, temp;

  div=data[bottom];

  for (lower=bottom, upper=top; lower<upper;){
    while(lower<=upper && data[lower]<=div){
      lower++;
    }
    while(lower<=upper && data[upper]>=div){
      upper--;
    }

    if (lower<upper){
      temp=data[lower];
      data[lower]=data[upper];
      data[upper]=temp;    }
  }

  temp=data[bottom];
  data[bottom]=data[upper];
  data[upper]=temp;

  int i;
  for (i=0; i<N; i++){
    printf("%d ", data[i]);
  }
  printf("\n");
  quick_sort(bottom, upper-1, data);
  quick_sort(upper+1, top, data);

}


void merge_sort(int n, int x[]){
  if (n<=1) return;
  int m,j,k,i, temp;
  m=n/2;

  merge_sort(m, x);
  merge_sort(n-m, x+m);

  // マージ作業

  // 前半をbufferに保持

  for (i=0; i<m; i++){
    buffer[i]=x[i];
  }

  j=m;
  i=k=0;

  while(i<m && j<n){
    if (buffer[i]>x[j]){
      x[k++]=x[j++];
    }else{
      x[k++]=buffer[i++];
    }
  }

  while(i<m){
    x[k++]=buffer[i++];
  }

}

void insert_sort(int n, int x[]){
  int i,j, bottom, insert, temp;

  for (i=1; i<n-1; i++){
    for (bottom=0; bottom<i+1; bottom++){
      if (x[bottom]>x[i+1]) break;
    }
    insert=x[i+1];
    while(bottom<=i+1){
      temp=x[bottom];
      x[bottom++]=insert;
      insert=temp;
    }

    for(j=0; j<n; j++){
      printf("%d ", x[j]);
    }
  printf("\n");
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
  insert_sort(N, sort);
  printf("\n");
  printf("ソート完了\n");

  for (i=0; i<N; i++){
    printf("%d ", sort[i]);
  }
  printf("\n");
}
