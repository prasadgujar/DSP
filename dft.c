

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Pi 3.141592653589
#define SWAP(a,b) tempr=(a); (a)=(b); (b)=tempr

void pause()
{ int k;
  printf("paused, enter 1 to continue...\n");
  scanf("%d",&k);
}

fft(xr,xi,N,inverse)
float *xr, *xi;
int N,inverse;
{ int mmax,step,i,j,k,j1,m,n;
  float arg,s,c,w,tempr,tempi;
/*
  if (inverse) printf("IFFT of size %d \n",N);
  else printf("FFT of size %d \n",N);
*/
  m=log((float)N)/log(2.0);

  for (i=0; i<N; ++i) {       /* bit reversal */
    j=0;
    for (k=0; k<m; ++k)
      j=(j << 1) | (1 & (i >> k));
    if (j < i) 
      { SWAP(xr[i],xr[j]);  SWAP(xi[i],xi[j]); }
  }
  for (i=0; i<m; i++) {         /* for log N stages */
    n=w=pow(2.0,(float)i);  w=Pi/n; if (inverse) w=-w;
    k=0;
    while (k<N-1) {             /* for N components */
      for (j=0; j<n; j++) {     /* for each section */
	arg=-j*w; c=cos(arg); s=sin(arg); 
	j1=k+j;
	tempr=xr[j1+n]*c-xi[j1+n]*s;
	tempi=xi[j1+n]*c+xr[j1+n]*s;
	xr[j1+n]=xr[j1]-tempr;
	xi[j1+n]=xi[j1]-tempi;
	xr[j1]=xr[j1]+tempr;
	xi[j1]=xi[j1]+tempi;
      }
      k+=2*n;
    }
  }
  arg=1.0/sqrt((float)N);
  for (i=0; i<N; i++) 
    { xr[i]*=arg; xi[i]*=arg; }
}

void dft(xr,xi,N,inverse)
     float *xr, *xi;
     int N,inverse;
{ int i,j,k,m,n;
 float arg,s,c,*yr,*yi;

 if (inverse) printf("IDFT of size %d \n",N);
 else printf("DFT of size %d \n",N);
  
 yr = (float *) malloc(N*sizeof(float));
 yi = (float *) malloc(N*sizeof(float));

 for (k=0; k<N; k++) {          // for all N frequency components 
   yr[k]=yi[k]=0;
   for (m=0; m<N; m++) {
     arg=-2*Pi*m*k/N;
     if (inverse) arg=-arg;
     c=cos(arg);
     s=sin(arg);
     yr[k]+=xr[m]*c-xi[m]*s;
     yi[k]+=xi[m]*c+xr[m]*s;
   }
 }
 for (k=0; k<N; k++) {
   if (inverse) 
     { xr[k]=yr[k]/N; xi[k]=yi[k]/N; }
   else 
     { xr[k]=yr[k]; xi[k]=yi[k]; }
 }
 free(yr); free(yi);
}



main()
{
  int i,j,k, m=3, n, l;
  float xr[8],xi[8];

  n=pow(2,m);

  printf("%d-point DFT: use FFT algorithm? Yes (0), or No (1) ",n);
  scanf("%d",&l);

  for (i=0; i<n; i++) { xr[i]=0; xi[i]=0;}
  for (i=2; i<5; i++) { xr[i]=i; }

  printf("X in time domain:\n");
  for (i=0; i<n; i++) {
    printf("%4.1f   %4.1f\n",xr[i], xi[i]);
  }

  if (l) dft(xr,xi,n,0);     // forward dft  
  else   fft(xr,xi,n,0);     // forward fft  

  printf("X in frequency domain:\n");
  for (i=0; i<n; i++) {
    printf("%4.1f   %4.1f\n",xr[i], xi[i]);
  }

  // This is where you can insert your 1D filtering codes. 

  if (l) dft(xr,xi,n,1);     // inverse dft 
  else   fft(xr,xi,n,1);     // inverse fft  

  printf("X back to time domain:\n");
  for (i=0; i<n; i++) {
    printf("%4.1f   %4.1f\n",xr[i], xi[i]);
  }
}   