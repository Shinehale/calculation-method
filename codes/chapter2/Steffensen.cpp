#include<iostream>
#include<cstdio>
#include<cmath>

using std::cout; using std::endl;

const double eps = 1e-8;
// the target function is x^3 - x - 1
double func( const double& x ){
	//return x * x * x - x - 1; 
	return x + sin( x ) - 1;
}


double steff( const double& x ){

	double x0 = x, value = func( x0 ), x1 = x0 - ( value * value ) / ( value - func( x0- value ) );
	while ( fabs( x1 - x0 ) > eps ){
		x0 = x1;
		double value = func( x0 );
		x1 = x0 - ( value * value ) / ( value - func( x0- value ) );
	}
	return x0;
}


int main(){
	cout << "The function zero point is : ";
	printf("%.10lf\n", steff( 1.0 ) );
	return 0; 
}