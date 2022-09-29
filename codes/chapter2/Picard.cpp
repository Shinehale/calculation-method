#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>

using namespace std;

const double& eps = 1e-9;

double func( const double &x ){
	return exp(-x)  ;
}
 double picard( const double& x ){
 	double x0 = x, x1 = func( x0 );
 	while ( fabs( x0 - x1 ) >= eps ){
 		cout << x0 << endl;
 		x0 = x1 ;
 		x1 = func( x0 );
 	}
 	return x0;
 }

int main(){
	printf(" the zero point is: %.8lf\n", picard( 0.5 ));
	return 0;
}