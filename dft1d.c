#include <math.h>
void FFT1D( float a[], float b[], int n, int sign )
{
int l,l1,l2,j,jj,i,ii,k,nh,nm;
float *cr, *ci;
float den,p,q;
float ur,ui,vr,vi,wr,wi,urtemp;
double pi,x;
/***********************/
/* FUNCTION: This function computes the DFT of a complex array whose
real and imaginary parts are a and b respectively using
the successive doubling method.
NOTES: The function returns the real (a) and imaginary (b) parts
of the DFT.
The size of the arrays n must be an int power of 2.
Zero frequency occurs at 1+n/2.
By convention, the forward Fourier transform is obtained
when sign=-1 and the inverse Fourier transform is obtained
when sign=1.
If input is purely real then the imaginary part
(i.e. array b) must be set to be a null vector.
PARAMETERS
Input: a - real part of signal/spectrum
b - imaginary part of signal/spectrum
n - size of signal
Output: a - real part of spectrum/signal
b - imaginary part of spectrum/signal
EXTERNAL MODULES: None
INTERNAL MODULES: None */
/***********************/
/* Allocate n+1 words of memory to internal arrays. */
cr = (float *) calloc( n+1, sizeof( float ) );
ci = (float *) calloc( n+1, sizeof( float ) );
/* Compute scaling parameter (den) */
if ( sign < 0 )
den=1.0;
else
den=n;
/* Setup constants required for computation. */
pi = 4.0 * atan( 1.0 );
p = n;
q = log( p ) / log( 2.0 );
k = q;
nh = n * 0.5;
nm = n-1;
/* Generate switched arrays - switch positive/negative
half spaces to negative/positive half spaces respectively. */
for ( i=nh+1, j=1; i<=n; i++, j++ )
{
cr[j] = a[i];
ci[j] = b[i];
}
for ( i=1; i<=nh; i++, j++ )
{
cr[j] = a[i];
ci[j] = b[i];
}
/* Reorder data, i.e. perform ’bit-reversal’. */
for ( i=1, j=1; i<=nm; i++ )
{
if ( i < j )
{
vr = cr[j];
vi = ci[j];
cr[j] = cr[i];
ci[j] = ci[i];
cr[i] = vr;
ci[i] = vi;
}
jj = nh;
while ( jj<j)
{
j -= jj;
jj = jj * 0.5;
}
j += jj;
}
/* Do fast transform computations. */
for ( l=1; l<=k; l++ )
{
l1 = ldexp( 1.0, l );
x = (2 * pi * (double) sign) / l1;
wr = cos( x );
wi = sin( x );
l2 = l1 * 0.5;
ur = 1.0;
ui = 0.0;
for ( j=1; j<=l2; j++ )
{
for ( i=j; i<=n; i+=l1 )
{
ii = i + l2;
vr = (cr[ii] * ur) - (ci[ii] * ui);
vi = (cr[ii] * ui) + (ci[ii] * ur);
cr[ii] = cr[i] - vr;
ci[ii] = ci[i] - vi;
cr[i] = cr[i] + vr;
ci[i] = ci[i] + vi;
}
urtemp = ur;
ur = (ur * wr) - (ui * wi);
ui = (urtemp * wi) + (ui * wr);
}
}
/* Scale */
for ( i=1; i<=n; i++ )
{
cr[i] = cr[i] / den;
ci[i] = ci[i] / den;
}
/* Reverse half-spaces - write out data in ’optical form’. */
for ( i=nh+1, j=1; i<=n; i++, j++ )
{
a[j] = cr[i];
b[j] = ci[i];
}
for ( i=1; i<=nh; i++, j++ )
{
a[j] = cr[i];
b[j] = ci[i];
}
/* Free space from work arrays. */
free( cr );
free( ci );
}