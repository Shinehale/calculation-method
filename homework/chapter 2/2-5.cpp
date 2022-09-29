#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>

using namespace std;

const double& eps = 1e-9;

//f(x) = ax - sin(x) + 1 /  (1+ a )
double func( const double &x ){
	return ( 0.5 * x - sin( x ) + 1 ) / 1.5 ;
}
 double picard( const double& x ){
 	double x0 = x, x1 = func( x0 );
 	while ( fabs( x0 - x1 ) >= eps ){
 		x0 = x1 ;
 		x1 = func( x0 );
 	}
 	return x0;
 }

int main(){
	printf(" the zero point is: %.8lf\n", picard( 0.5 ));
	return 0;
}