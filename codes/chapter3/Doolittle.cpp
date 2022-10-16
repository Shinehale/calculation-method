#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


void calc_L_and_U( vector<vector<double>>& L, vector<vector<double>>& U, const vector<vector<double>>& A ){
	const int Size = A.size(); L.clear(); U.clear();
	for ( int i = 0; i < Size; ++i ) L.push_back( vector<double>(Size) );
	for ( int i = 0; i < Size; ++i ) U.push_back( vector<double>(Size) );
	for ( auto i = 0ull; i < A.size(); ++i ) U[0][i] = A[0][i] ;
	for ( auto i = 0ull; i < A.size(); ++i ) for ( int j = 0; j <= i; ++j ) L[i][j] =  1;
	for ( int i = 1; i < Size; ++i ) L[i][0] = A[i][0] / U[0][0];
	for ( int line = 1; line < Size; ++line ) {
		// calculate the U corresponding line 
		for ( int k = line; k  < Size; ++k ) {
			double tot = 0.0;
			for ( int i = 0; i < line ; ++i ) tot += L[line][i] * U[i][k];
			U[line][k] = A[line][k] - tot;
		}
		// calculate the L corresponding line 
		for ( int k = line; k < Size; ++k ){
			double tot = 0.0;
			for ( int i = 0; i < line; ++i ) tot += L[k][i] * U[i][line];
			L[k][line] = ( A[k][line] - tot ) / U[line][line]; 
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
	X[size - 1] = B[size - 1] / A[size - 1 ][size - 1];
	for (int i = size - 2; i >= 0 ; --i){
		double tot = 0.0;
		for ( int j = i + 1; j < size; ++j ) tot += X[j] * A[i][j];
		X[i] = (B[i] - tot) / A[i][i];
	}
}


int main(){
	cout << "Please input the size of your equations:";
	int size; cin >> size;
	cout << "Please insure your equations has the answer!" << endl;
	vector<vector<double>> A(size), L(size), U(size);
	vector<double> B, X, Y ;
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

	// calculate the matrix L and U and output them 
	calc_L_and_U( L, U, A );
	cout << endl << "The matrix L is: "<< endl;  
	for ( int i = 0; i < size; ++i ){
		for ( auto j = 0ull; j < L[i].size(); ++j ) cout << L[i][j] << " ";
		cout << endl;
	}
	cout << endl << "The matrix U is: "<< endl;  

	for ( int i = 0; i < size; ++i ){
		for ( auto j = 0ull; j < U[i].size(); ++j ) cout << U[i][j] << " ";
		cout << endl;
	}

	// calculate matrix Y and output it 
	calc_Y( L, B ,Y );
	cout << "The matrix Y is: " << endl;
	for ( auto i = 0ull; i < Y.size(); ++i ) cout << Y[i] << " ";
	cout << endl;

	// calculate matrix X and output it 
	calc_X( U, Y, X );
	cout << " the answer matrix X is :" << endl;
	for ( int i = 0; i < size; ++i ) cout << X[i] << " ";
	cout << endl;
	return 0;

	return 0;
}
/*

4
1 -2 3 -1 2
4 -1 -2 2 4
3  2 -1 1 8
2 5 2 -2 10
*/