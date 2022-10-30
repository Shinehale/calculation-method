#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<utility>

using namespace std;

using db = double;
using Dvec = vector<db>;

double Lagrange( const db& tar, const Dvec& X, const Dvec& Y ){
	double tot = 0.0;
	const int size = X.size();
	for ( int pos = 0; pos < size; ++pos ){
		double newAddValue =  1.0;
		for ( int i = 0; i < size; ++i ){
			if ( pos != i ) 
				newAddValue *= ( tar - X[i] ) / ( X[pos] - X[i] );
		}
		tot += Y[pos] * newAddValue;
	}
	return tot;
}

int main(){
	Dvec X,Y;
	cout << "Please input the total number of the value:" << endl;
	int size; cin >> size;
	for ( int i = 0; i < size; ++i ) {
		double fx, fy;
		cout << "Please input the " << i + 1 << "value ( x , y ): \n";
		cin >> fx >> fy;  
		X.push_back( fx );
		Y.push_back( fy );
	}
	cout << "Input the value of X you want:" << endl;
	double xTar; cin >> xTar;
	cout << "The predictable value of Y is " << endl;
	printf("%.8lf", Lagrange( xTar, X, Y ) );
	return 0;
}

/**
5
0 0 
0.3926 0.7555 
0.7854 1.3408
1.1781 1.6289
1.5708 1.5708
0.5890
*/
