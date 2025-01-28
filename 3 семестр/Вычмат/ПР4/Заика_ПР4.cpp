#include<iostream>
#include<cmath>
#define MYCONST 1
double Round(double X, double Delta);

double Round_Truncation(double Y) {
   if (Y >= 0) {
   	return floor(Y);//round down
   } else {
   	return ceil(Y);//round up
   }
}

//c*cosh(x)-6
double F(double x, double c = 1) {
	return Round_Truncation((c*cosh(x)-6)*100)/100;
}


double Derivative(double c, double x) {
	return c*sinh(x);
}

double SecondDerivative(double c, double x) {
	return c*cosh(x);
}

double find_min1(double a,double b,double delta){
   double min = fabs(Derivative(MYCONST, a));
   for(double i=a;i<=b;){
   	double el=fabs(Derivative(MYCONST, i));
   	if(el<min){
       	min = el;
   	}
   	i+=delta;
   }
   return min;

}
double find_max(double a,double b,double delta){

   double max = fabs(SecondDerivative(MYCONST, a));
   //std::cout<<"a"<<max<<"\n";
   for(double i=a;i<=b;){
   	double el=fabs(SecondDerivative(MYCONST, i));
   	if(el>max &&el!=INFINITY ){
       	max = el;
   	}
   	i+=delta;
   }
   return max;

}
double Derivative_PHI(double x,double delta,int c){
   return 1-(2/(find_min1(0.1,6,delta)+ find_max(0.1,6,delta)))* Derivative(c,x);
}
double NEWTON(double X, double Eps, int& N,double delta) {
// extern double F1(double);
   double Y, Y1, DX, Eps0;
   N = 0;
   double m1 = find_min1(0.1,6,delta); // наименьшее значение модуля 1-ой производной
   double M2 =  find_max(0.1,6,delta); // наибольшее значение модуля 2-ой производной
   Eps0 = sqrt(2 * m1 * Eps / M2);
   do {
   	Y = F(X,MYCONST);
    std::cout<<"X"<<N<<": "<<Round_Truncation(X*1000)/1000<<" f(X):"<<Round_Truncation(F(X)*1000)/1000<<"\n";
   	std::cout<<"X"<<N<<": "<<Round_Truncation(X*100)/100<<" f(X):"<<Round_Truncation(F(X)*100)/100<<"\n";
   	std::cout<<"X"<<N<<": "<<Round_Truncation(X*10)/10<<" F(X): "<<Round_Truncation(Y*10)/10<<"\n";
   	std::cout<<"X"<<N<<": "<<X<<" F(X): "<<Y<<"\n";
	if (Y == 0.0) {
	return X;
	}
   	Y1 = Derivative(MYCONST,X);
   	if (Y1 == 0.0) {
       	puts("Производная обратилась в ноль\n");
       	exit(1);
   	}

   	DX = Y / Y1;
   	X -= DX;
   	N++;
   }// while(fabs(DX) >= Eps0);
   while(N<80);
   std::cout<<"X"<<N<<": "<<X<<" F(X): "<<Y<<"\n";
   return X;
}
double PHI(double x, double a, double b,double delta) {
   if (x == 0) {
   	std::cout<<"деление на 0!";
   	exit(1);
   }
   double min = find_min1(a, b,delta);
   double max = find_max(a, b,delta);
   //std::cout<<min<<"\n";
   //std::cout<<max<<"\n";
   double s = x - (2 / (min + max) )*F(x,MYCONST);

   s = Round(s, delta);
   //std::cout<<s<<"\n";
   return s;
}
double ITER (double X0, double Eps, int& N, double a, double b,double delta) {
   if (Eps <= 0.0) {
   	puts("Неверное задание точности\n");
   	exit(1); }
   //double Y = PHI(X0, a, b,delta);
   double X1 = PHI(X0, a, b,delta);
   double X2 = PHI(X1, a, b,delta);
   for (N = 2; fabs(X1 - X0)>Eps; N++) {
   	X0 = X1;
   	X1 = X2;
   	X2 = PHI(X1, a, b,delta);

   }
   return X2;
}
std::string Iter_Conditioning(int c,double x, double eps, double delta, double &ny){
   ny = fabs(1/(1- Derivative_PHI(x,delta,c)));

   if (ny <= (eps / delta)) {
   	return "good";
   } else {
   	return "bad";
   }
}



std::string Conditioning(double c, double x, double eps, double delta, double &ny) {
   double derivative = Derivative(c, x);
   std::cout << "deriv f(x)= " << derivative << "\n";
   ny = fabs(1 / derivative);
   std::cout << "ny= " << ny << "\n";
   if (ny <= (eps / delta)) {
   	return "ok";
   } else {
   	return "not ok";
   }
}


double Round(double X, double Delta) {
   if (Delta <= 1E-9) {
   	puts("Неверно задана точность округления\n");

   	exit(1);
   }
   if (X > 0.0) return (Delta * (long((X / Delta) + 0.5)));
   else return (Delta * (long((X / Delta) - 0.5)));
}

int main() {

   int N;
   double e, d, c;
   std::cin >> e;
   std::cin >> d;
   // std::cin >> c;
   int &N2 = N;
   double ny;
   //double eps2 = sqrt((2*find_min1(0.1,2.4,d)*e)/find_max(0.1,2.4,d));
   double x=NEWTON(3,e,N2,d);
   std::cout<<"NEWTON"<<"\n";
   std::cout<<x<<"\n";
   std::cout<<N2<<"\n";


/*	std::cout<<Derivative(c,x)<<std::endl;
//	std::cout<<Round(x,d)<<"\n";
   x = ITER(2,e,N2,0.1,6,d);
   std::cout<<"ITER"<<"\n";
   std::cout<<x<<"\n";
   std::cout<<N2<<"\n";

   x = BISECT(0.1, 6, e, N2, 1);
   std::cout<<"BISECT"<<"\n";
   std::cout<<x<<"\n";
   std::cout<<N2<<"\n";

   x = HORDA(0.1, 6, e, N2);
   std::cout<<"HORDA"<<"\n";
   std::cout<<x<<"\n";
   std::cout<<N2<<"\n";
   // double phi_deriv = Derivative_PHI(2, d, 1);
//	std::string ans = (abs(phi_deriv)) > 1 ? "not conv" : "conv";
//	std::cout << ans << '\n';

   //std::cout<<Conditioning(1, 3, e, d, ny)<<'\n';
//	std::cout<<x<<"\n";

//   std::cout<<"ny = "<<Iter_Conditioning(c,x,e,d,ny)<<": "<<ny<<"\n";
//	std::cout<<"N = "<<N2;*/

   return 0;
}
