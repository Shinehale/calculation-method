#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

using db = double;
using Dvec = vector<double>;

double Newton( const db& tar, const Dvec& X, const Dvec& Y ){
	vector<Dvec> M;
	const int size = X.size();
	for ( int i = 0; i < size; ++i ) M.push_back( Dvec(size + 1) );
	for ( int line = 0; line < size; ++line ) M[line][0] = Y[line];
	for ( int pos = 1; pos < size; ++pos ) {
		for ( int line = pos; line < size; ++line ){
			M[line][pos] = ( M[line][pos - 1] - M[pos - 1][pos - 1] ) 
							/ ( X[line] - X[pos - 1]);
		}
	}
	for ( int i = 0; i < size; ++i ) {
		for ( int j = 0; j <= i; ++j ) 
			cout << M[i][j] << " ";
		cout << endl;
	}
	db ans = 0.0;
	for ( int pos = 0; pos < size; ++pos ){
		db tot = 1.0;
		for ( int i = 0; i < pos; ++i ) tot *= tar - X[i];
		ans += tot * M[pos][pos];
	}
	return ans;
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
	printf("%.8lf", Newton( xTar, X, Y ) );
	return 0;
}
/*
5
0.35 1.4586
0.50 1.5072
0.65 1.5765
0.80 1.6699
0.95 1.7913
0.7
*/