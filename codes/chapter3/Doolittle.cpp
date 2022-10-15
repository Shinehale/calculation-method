#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


void calc_L_and_U( vector<int>& L, vector<int>& U, const vector<int>& A ){
	for ( auto i = 0; i < A.size(); ++i ) U[0].push_back( A[0][i] );
	for ( auto i = 0; i < A.size(); ++i )
}


int main(){
	cout << "Please input the size of your equations:";
	int size; cin >> size;
	cout << "Please insure your equations has the answer!" << endl;
	vector<vector<double>> A(size), L(size), U(size);
	vector<double> B, X;
	for ( int i = 0; i < size; ++i ){
		cout << "Please input the coefficient of the  " << i+1 << " line  element, all you need to input " << size + 1 << " elements" << endl;
		double val;
		for ( int j = 0; j < size; ++j ){
			cin >> val;
			A[i].push_back( val );
		}
		cin >> val;
		B.push_back( val );
	}
	calc_L_and_U( L, U, A );
	return 0;
}
/*

3
0.001 2.000 3.000 1.000
-1.000 3.712 4.623 2.000
-2.000 1.070 5.643 3.000

*/