//
// dft.c - Simple brute force DFT
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
#define Ni 1024
#define PI2 6.2832

//Generates the Array - I wrote this
void arrayGen(double* ptr){
    
    double l[1024];
    int i,k,n,N = 0;

    double pi= 3.14;
    double v1,v2,v3,noise;
    for (int i = 0; i < 1024 - 1; ++i) {
  	    v1 = (1024 * sin(2*pi*(int)i /1024));
        v2 = (500 * sin(6*pi*(int)i / 1024));
        v3 = (512 * sin(20*2*pi*(int)i /1024));
    	noise =   (rand() % (1000 + 1));

        
        l[i]= (double)v1 + (double)v2 + (double)v3 + (double)noise;
        *(ptr + i) = l[i];
        
  }
}
 
int main()
{
    double* ptr;

    ptr = (double*) malloc(1024 * sizeof(double));

    arrayGen(ptr);



    // time and frequency domain data arrays
    int n, k;             // indices for time and frequency domains
    float x[Ni];           // discrete-time signal, x
    float Xre[Ni], Xim[Ni]; // DFT of x (real and imaginary parts)
    float P[Ni];           // power spectrum of x
    float FFT[Ni];
    float phase[Ni];
     

    for (n = 0;n<1024;++n){
        x[n] = *(ptr+n);
        //printf("%f",*(ptr+n));
    }
     
    // Calculate DFT of x using brute force
    for (k=0 ; k<Ni ; ++k)
    {
        // Real part of X[k]
        Xre[k] = 0;
        for (n=0 ; n<Ni ; ++n) Xre[k] += x[n] * cos(n * k * PI2 / Ni);
         
        // Imaginary part of X[k]
        Xim[k] = 0;
        for (n=0 ; n<Ni ; ++n) Xim[k] -= x[n] * sin(n * k * PI2 / Ni);
         
        // Power at kth frequency bin 
        P[k] = Xre[k]*Xre[k] + Xim[k]*Xim[k];
        P[k] = sqrt(P[k])/(1024); P[0] = 0;


        //FFT
        FFT[k] = 0;
        FFT[k] = (Xre[k],Xim[k]);
        
        //Denoise
         if(P[k] < 50){
             Xre[k] = 0;
             Xim[k] = 0;
         }
    }
    // IDFT
    float IXre[Ni],IXim[Ni];
    float IP[Ni];
    float IFFT[Ni];

    for (k=0 ; k<Ni ; ++k)
    {
        // Real part
        IXre[k] = 0;
        for (n=0 ; n<Ni ; ++n) IXre[k] += Xre[n] * cos(n * k * PI2 / Ni);
         
        // Imaginary part
        IXim[k] = 0;
        for (n=0 ; n<Ni ; ++n) IXim[k] += Xim[n] * sin(n * k * PI2 / Ni);

        //IP
        IP[k] =  IXre[k]*IXre[k] + IXim[k]*IXim[k];

        //IFFT
        IFFT[k] = 0;
        IFFT[k] = (IXre[k],IXim[k]);
        }
        
        

     
    // Output results to MATLAB / Octave M-file for plotting
    FILE *f = fopen("dftplots.m", "w");
    fprintf(f, "n = [0:%d];\n", Ni-1);
    fprintf(f, "x = [ ");
    for (n=0 ; n<Ni ; ++n) fprintf(f, "%f ", x[n]);
    fprintf(f, "];\n");
    fprintf(f, "Xre = [ ");
    for (k=0 ; k<Ni ; ++k) fprintf(f, "%f ", Xre[k]);
    fprintf(f, "];\n");
    fprintf(f, "Xim = [ ");
    for (k=0 ; k<Ni ; ++k) fprintf(f, "%f ", Xim[k]);
    fprintf(f, "];\n");
    fprintf(f, "P = [ ");
    for (k=0 ; k<Ni ; ++k) fprintf(f, "%f ", P[k]);
    fprintf(f, "];\n");
    fprintf(f, "IP = [ ");
    for (k=0 ; k<Ni ; ++k) fprintf(f, "%f ", (float)(sqrt(IP[k])/1024));
    fprintf(f, "];\n");
    fprintf(f, "subplot(2,2,1)\nplot(n,x)\n");
    fprintf(f, "xlim([0 %d])\n", Ni-1);
    fprintf(f, "subplot(2,2,2)\nplot(n,Xre,n,Xim)\n");
    fprintf(f, "xlim([0 %d])\n", Ni-1);
    fprintf(f, "subplot(2,2,3)\nstem(n,P)\n");
    fprintf(f, "xlim([0 %d])\n", Ni-1);
    fprintf(f, "subplot(2,2,4)\nplot(n,IP)\n");
    fprintf(f, "xlim([0 %d])\n", Ni-1);
    fclose(f);
     
    // exit normally
    return 0;
}