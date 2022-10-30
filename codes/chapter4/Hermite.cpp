#include<iostream>
#include<cmath>
#include<vector>
#include<cstdio>

using namespace std;

using db = double;
using Dvec = vector<double>;
const double eps = 1e-9;
	
double Hermite( const double& tarX, const Dvec& X, const Dvec& Y, const Dvec& DY){
	const int size = X.size();
	double rv = 0.0;
	for ( int ord = 0; ord < size; ++ord ){
		double totValue = 1.0, diff = 0.0;
		for ( int i = 0; i < size; ++i )
			if ( ord != i ) {
				totValue *= ( tarX - X[i] ) / ( X[ord] - X[i]);
				diff += 1.0 / ( X[ord] - X[i] );
			}
		rv += ( Y[ord] + ( tarX - X[ord] ) * ( DY[ord] - 2 * Y[ord] * diff ) ) * totValue * totValue;
	}
	return rv;
}


int main(){
	cout << "This is derived by the Hermite,please input the size of the value:" << endl;
	int size; cin >> size;
	Dvec X, Y, DY;
	for (int i = 0; i < size; ++i ){
		cout << "Please input the " << i << " set of the value (3 value in a set):" << endl;
		double x, y, dy; cin >> x >> y >> dy;
		X.push_back( x );
		Y.push_back( y );
		DY.push_back( dy );
	}
	cout << "Please input the value you want to predict:" << endl;
	double tarX; cin >> tarX;
	cout << "The predictable value you want is : " << endl;
	printf("%.8f", Hermite( tarX, X, Y, DY ) );
	return 0;

}
/*
3
1  0.6931471805599453	1.193147180559945
1.2	0.9461488324371243	1.333911905818816
1.4 1.225656232295460	1.458802070687233
1.3 		
*/
