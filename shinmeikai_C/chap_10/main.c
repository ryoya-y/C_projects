#include <stdio.h>
#include <string.h>

void diff(int x, int y, int *pointer){
  *pointer=x-y;
}

void swap(int *pa, int *pb){
  int tmp;
  tmp=*pa;
  *pa=*pb;
  *pb=tmp;
}

void sort(int *n1, int*n2){
  if (*n1>*n2){
    swap(n1, n2);
  }
}

void set_ary(int *v, int n){
  int i;
  for (i=0; i<n; i++){
    v[-i]=i;
  }
}


size_t str_length(char *v){
  size_t len=0;
  while (*v++){
    len++;
  }
  return len;
}

void str_put(const char *v){
  int i=0;
  while (*(v+i)!=0){
    printf("%c", *(v+i));
    i++;
  }
  printf("\n");

}

int str_chnum(char *v, int c){
  int len=0;
  int i=0;
  while (v[i]!=0){
    if (v[i]==c){
      len++;
    }
    i++;
  }
  return len;
}

char *str_chr(char *v, int c){
  int i=0;
  while (v[i]!=0){
    if (v[i]==c){
      return v+i;
    }
    i++;
  }
  return NULL;
}

int main(void){
  char str[]="aaaaaaafdddddddwedfafdeqf";
  printf("%p\n", str_chr(str, 'd'));
}
