#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;
using Dvec = vector<double>;

void calc_L( const vector<Dvec>& A, vector<Dvec>& L ){  
	const int Size = A.size();
	L.clear(); for ( int i = 0; i < Size; ++i ) L.push_back( Dvec(Size) );
	// step 1
	L[0][0] = sqrt(A[0][0]);
	for ( int i = 1; i < Size; ++i ) L[i][0] = A[i][0] / L[0][0];
	// step 2
	for ( int line = 1; line < Size; ++line ){
		double tot = 0.0;
		for ( int i = 0; i < line; ++i ) tot += L[line][i] * L[line][i];
		L[line][line] = sqrt( A[line][line] - tot );
		for ( int pos = line + 1 ; pos < Size; ++pos ){
			tot = 0.0;
			for ( int i = 0; i < line; ++i ) tot += L[line][i] * L[pos][i];
			L[pos][line] = ( A[pos][line] - tot ) / L[line][line];
		}
	}	
}

void calc_Y( const vector<vector<double>>& L, const vector<double>& B, vector<double>& Y ){
	Y.clear();
	const int Size = L.size();
	for ( int pos = 0; pos < Size; ++pos ) {
		double tot = 0.0 ;
		for ( int i = 0; i < pos; ++i ) tot += L[pos][i] * Y[i];
		Y.push_back( (B[pos] - tot) / L[pos][pos] );
	}
}

void calc_X( const vector<vector<double>>& A, const vector<double>& B, vector<double>& X ){
	X.clear();const int size = A.size();
	for ( int i = 0; i < size; ++i ) X.push_back( 0.0 );
	vector<vector<double>> M;
	for ( int i = 0; i < size; ++i ) M.push_back( vector<double>(size) );
		for ( int i = 0; i < size; ++i ) for ( int j = 0; j < size; ++j ) M[i][j] = A[j][i];
	X[size - 1] = B[size - 1] / M[size - 1 ][size - 1];
	for (int i = size - 2; i >= 0 ; --i){
		double tot = 0.0;
		for ( int j = i + 1; j < size; ++j ) tot += X[j] * M[i][j];
		X[i] = (B[i] - tot) / M[i][i];
	}
}


int main(){
	cout << "Please input the size of your equations:";
	int size; cin >> size;
	cout << "Please insure your equations has the answer!" << endl;
	vector<Dvec> A(size), L(size);
	Dvec B, X, Y ;
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

	// calculate matrix L and ouput it!
	calc_L( A, L );
	cout << endl << "The matrix L is: "<< endl;  
	for ( int i = 0; i < size; ++i ){
		for ( auto j = 0ull; j < L[i].size(); ++j ) cout << L[i][j] << " ";
		cout << endl;
	}

	// calculate the equation LY = B and find the value of the matrix Y 
	calc_Y( L, B ,Y );
	cout << "The matrix Y is: " << endl;
	for ( auto i = 0ull; i < Y.size(); ++i ) cout << Y[i] << " ";
	cout << endl;

	//calculate the equation L^TX = Y and find the value of the matrix X
	calc_X( L, Y, X );
	cout << " the answer matrix X is :" << endl;
	for ( int i = 0; i < size; ++i ) cout << X[i] << " ";
	cout << endl;

}
/*

4
4 -2 4 2 8
-2 10 -2 -7 2
4 -2 8 4 16
2 -7 4 7 6

*/