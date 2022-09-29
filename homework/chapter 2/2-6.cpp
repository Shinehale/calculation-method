#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

const double eps = 1e-9;
const double pi = 3.1415926;
//x - 2 sin(x + pi / 3)
double func( const double& x ){
	return x - 2 * sin ( x + pi / 3 );
}

double funcDeriv( const double& x ){
	return (func(x + eps) - func( x )) / eps;
}

double newton ( const double &x ){
	double x0 = x, x1 = x0 - func( x0 ) / funcDeriv( x0 );
	while ( fabs( x0 - x1 ) > eps ){
		x0 = x1;
		x1 = x0 - func( x0 ) / funcDeriv( x0 );
	}
	return x1;

}

int main(){
	printf("the zero point is %.8lf \n", newton( 1.0 ) );
	return 0;
}