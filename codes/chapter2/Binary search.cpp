#include<iostream>
#include<cmath>
#include<cstdio>

using namespace std;
const double eps = 1e-8;


// assume the function is f(x) = x^3 - x -1
double func(const double &x){
	double ans = 0.0;
	ans = x * x * x - x - 1;
	return ans;
}


int main(){
	double L = 1.0, R = 1.5;
	while ( abs( L - R ) > eps ){
		double mid = ( R + L ) / 2.0;
		double value = func( mid );
		if ( value * func( L ) < 0 ) R = mid;
		else if ( value * func( R ) < 0) L = mid;
	}
	cout <<"the answer to the equation is: ";
	printf( "%.10lf\n", L);
	return 0;
}