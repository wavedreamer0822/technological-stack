// example1_2_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

void main( )
{
  double *x,*a,*b,*c,*d,*rhs,*ans,*u;
  double A,B,h,Pi,alpha,beta,lambda,mu;
  int i,j,N;
  double * f(double * x, int N);
  double q(double x);
  double *chase_algorithm(double *a, double *b, double *c, int n, double *d);
  m=640;
  Pi=3.14159265359;
  A=0;
  B=Pi;
  h=(B-A)/m;
  alpha=1.0;
  beta=-exp(Pi);
  lambda=mu=0;
 
  x=(double *)malloc(sizeof(double)*(m+1));
  for(i=0;i<=m;i++)
    x[i]=A+i*h;
 
  rhs=f(x,m+1);
  for(i=1;i<m;i++)
	  rhs[i]=rhs[i]*h*h;
  rhs[0]=h*alpha;
  rhs[m]=-h*beta;

  a=(double *)malloc(sizeof(double)*(m+1));
  b=(double *)malloc(sizeof(double)*(m+1));
  c=(double *)malloc(sizeof(double)*(m+1));
  d=(double *)malloc(sizeof(double)*(m+1));
  for(i=0;i<=m;i++)
  {
	  d[i]=rhs[i];
	  a[i]=1.0;
	  b[i]=h*h*q(x[i])-2;
	  c[i]=a[i];
  }
  b[0]=lambda*h-1.0;
  b[m]=-(mu*h+1.0);
  free(rhs);
  ans=(double *)malloc(sizeof(double)*(m+1));
  ans=chase_algorithm(a,b,c,m+1,d);
  free(a);
  free(b);
  free(c);
  free(d);
  
  u=(double *)malloc(sizeof(double)*(m+1));   //u为数值解
  for(i=0;i<=m;i++)
	  u[i]=ans[i];
  free(ans);

  i=m/5;
  for(j=1;j<=4;j++)
	 printf("x=%f==%d*Pi/5, u=%f\n",A+j*i*h,j,u[i*j]);
  free(u);
}


double * f(double  * x, int N)
{
	int i;
	double *ans;
	ans=(double *)malloc(sizeof(double)*(N+1));
	for(i=0;i<=N;i++)
		ans[i]=exp(x[i])*(2*cos(x[i])-sin(x[i]));
	return ans;
}

double q(double x)
{
	double z;
	z=-1.0;
	return z;
}

double * chase_algorithm(double *a, double *b, double *c, int n, double *d)
{
  double * ans,*g,*w,p;
  int i;
  ans=(double *)malloc(sizeof(double)*n);
  g=(double *)malloc(sizeof(double)*n);
  w=(double *)malloc(sizeof(double)*n);
  g[0]=d[0]/b[0];
  w[0]=c[0]/b[0];
  
  for(i=1;i<n;i++)
  {
	  p=b[i]-a[i]*w[i-1];
	  g[i]=(d[i]-a[i]*g[i-1])/p;
	  w[i]=c[i]/p;
  }
  ans[n-1]=g[n-1];
  i=n-2;
   do
	 {
		ans[i]=g[i]-w[i]*ans[i+1];
		i=i-1;
		//printf("i=%d, Now it's OK!\n",i);
	 }
  while(i>=0);
  free(g);
  free(w);
  return ans;
}

