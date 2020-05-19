# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <limits.h>
# include <ctype.h>

void strdump(char *s){
  while(*s){
    unsigned char x=(unsigned char)*s;
    printf("%c:", isprint(x)? x:' ');
    int i;
    for (i=CHAR_BIT-1; i>=0; i--){
      putchar((x>>i) & 1U ? '1': '0');
    }
    printf("\n");
    s++;
  }
}

int main(void){
  char p[][6]={"supre", "fight", "man"};
  char *s[]={"supre", "fight", "man"};

  printf("p size: %lu\n", sizeof(p));
  printf("s size: %lu\n", sizeof(s));
  printf("char pointer size: %lu\n", sizeof(char *));
}
