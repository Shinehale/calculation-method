#include<iostream>
#include<cmath>
#include<cstdio>

using namespace std;

const double eps = 1e-9;

double func( const double& x ){
	return - sin( x ) + 1;
}

double Atiken( const double& xIn ){
	double x1 = func( xIn ), x2 = func( x1 ), xPre = xIn, 
		x = x2 - ( x2 - x1 ) * ( x2 - x1 ) / ( x2 - 2 * x1 + xPre );
	while ( fabs( x - xPre ) > eps  ){
		printf("%.8lf\n",x2);

		xPre = x ;
		x1 = func( xPre );
		x2 = func( x1 );
		x = x2 - ( x2 - x1 ) * ( x2 - x1 ) / ( x2 - 2 * x1 + xPre );
	}
	return x;
}

int main(){
	printf("the zero point of the function is %.8lf\n", Atiken( 0.0 ));
	return 0;
}