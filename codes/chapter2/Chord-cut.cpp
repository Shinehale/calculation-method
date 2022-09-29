#include<iostream>
#include<cstdio>
#include<cmath>

using std::cout; using std::endl;

const double eps = 1e-8;
// the target function is x^3 - x - 1
double func( const double& x ){
	return x * x * x - x - 1; 
}
double abs( const double& x ){
	return ( x < 0 ) ? (-x) : x;
}

double chordCut( const double& x0, const double& x1){
	double xPre = x0;
	double x = x1, xNext = x1 - ( x - xPre ) / ( func( x ) - func( xPre ) ) * func( x );
	while ( abs( x - xPre) > eps ){
		xPre = x ;
		x = xNext;
		xNext = x - ( x - xPre ) / ( func( x ) - func( xPre ) ) * func( x );
		
	}
	return x;
}

int main(){
	cout << "The function's zero point is : ";
	printf("%.10lf\n", chordCut( 1.0, 1.5) );
	return 0; 
}