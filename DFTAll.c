#include "math.h"
#include "stdio.h"
#include <stdlib.h>
 
//Generates the Array
void arrayGen(double* ptr){
    
    double l[1024];
    int i,k,n,N = 0;

    double pi= 3.14;
    double v1,v2;
    for (int i = 0; i < 1024 - 1; ++i) {
  	    v1 = (1024 * sin(2*pi*(int)i /1024) + 1024);
        v2 = (500 * sin(6*pi*(int)i / 1024) + 1024);

        
        l[i]= (double)v1 + (double)v2;
        //printf( "l[%d] = %d\n", i, l[i]);
        *(ptr + i) = l[i];
        
  }
}

//Calculate the DFT
void calcDFT(double* ptrR, double*ptrI, double* ptr){
    double l[1024];
    double Xr[1024];
    double Xi[1024];
    int k,t, n = 1024;
 

    for (size_t k = 0; k < n; k++) {  
		double sumreal = 0;
		double sumimag = 0;
		for (size_t t = 0; t < n; t++) {  
			double angle = 2 * 3.14 * t * k / n;
			sumreal +=  t * cos(angle) + l[t] * sin(angle);
			sumimag += -t * sin(angle) + l[t] * cos(angle);
		}
		Xr[k] = sumreal;
		Xi[k] = sumimag;
        //printf("(%f) + j(%f)\n", Xr[k], Xi[k]);
        *(ptrR + k) = Xr[k];
        *(ptrI + k) = Xi[k];
	}
    

}

 
// Driver Code
int main()
{
    double* ptr;
    ptr = (double*) malloc(1024 * sizeof(double));

    double* ptrR;
    double* ptrI;
    ptrR = (double*) malloc(1024 * sizeof(double));
    ptrI = (double*) malloc(1024 * sizeof(double));

    arrayGen(ptr);
    calcDFT(ptrR,ptrI,ptr);

    FILE * fp;
    fp = fopen("Real.txt","w");
    for (int i = 0;i < 1024; ++i){
        printf("Xr[%d] = %f , Xi[%d] = %f\n",i+1, *(ptrR + i),i+1, *(ptrI + i));
        fprintf(fp,"%d\t%f\n",i ,*(ptrR + i));
    }
    free(ptr);
    free(ptrR);
    free(ptrI);
 
    return 0;
}