#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "METHODS.H"


double delta,c,d;

double Round (double X,double Delta){   
 if (delta <= 1E-9) {puts("No okruglenue--\n");exit(1);}
 if (X>0.0) return (delta*(long((X/delta)+0.5)));
    else    return (delta*(long((X/delta)-0.5)));
}

double F(double x){ // f(x ) = (1+cos(x))/(3 - sin(x)) - x
  double s;
  long int S; 
  s = (1+cos(x))/(3 - sin(x)) -x;

  if( s/delta < 0 )
    S = s/delta - 0.5;
  else
    S = s/delta + 0.5;
  s = S*delta;

  s = Round(s,delta);
  return s;
}

double BISECT(double Left,double Right,double Eps,int &N){
  double E = fabs(Eps)*2.0;
  double FLeft = F(Left);
  double FRight = F(Right);
  double X = (Left+Right)/2.0;
  double Y;

  if (FLeft*FRight>0.0) {puts("Not interval\n");exit(1);}
  if (Eps<=0.0) {puts("Not tochoct\n");exit(1);}

  N=0;
  if (FLeft==0.0)  return Left;
  if (FRight==0.0) return Right;

  while ((Right-Left)>=E){
    X = 0.5*(Right + Left);   
    Y = F(X); 
    if (Y == 0.0) return (X);
    if (Y*FLeft < 0.0)
      Right=X;
    else{ 
      Left=X; 
      FLeft=Y; 
    }
    N++;
  };
  return X;
}


int main () {
  int k ;
  long int s;
  double a,b,eps,x;
  double F(double);

  printf("eps:");
  scanf("%f",&eps1);
  eps = eps1;

  a = 0.0;
  b = 1.0;
  delta = 0.000001;

  x = BISECT(a,b,eps,k);
  printf("x=%lf k=%d\n",x,k);
  return 0;
}  