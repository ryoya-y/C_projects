# include <stdio.h>


typedef struct{
  char name[200];
  double height;
  double weight;
}Student;

void height_bsort(Student v[], int num){
  int i;
  for (i=0; i<num; i++){
    int j;
    for (j=num-1; j>i; j--){
      Student key_1, key_2;
      key_1=v[j];
      key_2=v[j-1];
      if (v[j].height<v[j-1].height){
        v[j]=key_2;
        v[j-1]=key_1;
      }
    }
  }
}


int main(void){
  FILE *fp;
  char name[100];
  double height, weight;

  fp=fopen("hw.dat", "r");
  if (fp==NULL)
    printf("ファイルを開けませんでした\n");
  else{
    double hsum, wsum;
    int p_num;
    p_num=0;
    Student list[7];
    while (fscanf(fp, "%s%lf%lf", name, &height, &weight)==3){
      Student tmp;
      int name_len;
      int i;
      name_len=sizeof(name)/sizeof(name[0]);
      for (i=0; i<name_len; i++){
        tmp.name[i]=name[i];
      }
      tmp.height=height;
      tmp.weight=weight;
      list[p_num]=tmp;
      hsum+=height;
      wsum+=weight;
      p_num++;
    }

    height_bsort(list, p_num);
    // int i;
    // for (i=0; i<p_num; i++){
    //   printf("%s %lf %lf\n", list[i].name, list[i].height, list[i].weight);
    // }
    // fclose(fp);

    if ((fp=fopen("sort_dat", "w"))==NULL)
      printf("ファイルを開けませんでした\n");
    else{
      int j;
      for (j=0; j<p_num; j++){
        fprintf(fp, "%s %lf %lf\n", list[j].name, list[j].height, list[j].weight);
      }
    }
    fprintf(fp, "height average is %lf\n", hsum/p_num);
    fprintf(fp, "weight average is %lf\n", wsum/p_num);
    fclose(fp);
  }
}
