#include "stdlib.h"
#include "stdio.h"
#include "math.h"
int main(){
 FILE *fp;
 fp = fopen("output.txt","w");
    int l[1024];
  int i = 0;
  double pi= 3.14;
  double value;
  for (i = 0; i <= 1023; ++i) {
  	value = (2048 * sin(4*pi*(int)i /1024)+2048);
  l[i]= (int)value;
  //printf( "p[%d] = %d\n", i, l[i]);
  //printf("%d , ",l[i]);
  fprintf(fp,"%d\t %d\n",i,l[i]);
  }
  printf("\n");
  printf("%x",&fp);
        
    }
