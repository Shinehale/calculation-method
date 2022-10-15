// advanced generation with Completely selected principal element method
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void push_forward( vector<vector<double>>& A, vector<double>& B ){
	const int size = A.size();
	int pos = 0;
	for ( int times = 1; times < size; ++times ){
		for ( int line = pos + 1; line < size; ++line ){
			int tar = pos ;
			for ( int line = pos + 1; line < size; ++line ) 
			if ( abs(A[line][pos]) > abs(A[pos][pos]) ) tar = line;
			swap( A[tar], A[pos] );
			swap( B[tar], B[pos] );
			double coeff = - A[line][pos] / A[times-1][pos];
			for ( int j = pos; j < size; ++j )A[line][j] += coeff * A[times - 1][j];
			B[line] += B[times - 1] * coeff;
		}
		++pos;
	}


}

vector<double> back_subst( const vector<vector<double>>& A, const vector<double>& B ){
	const int size = A.size();
	vector<double> ans(size);
	for ( int pos = size - 1; pos >= 0; --pos ){
		double tot = 0.0;
		for ( int i = pos + 1; i < size; ++i ) tot += ans[i] * A[pos][i];
		ans[ pos ] = (B[pos] - tot) / A[pos][pos];
	}
	return ans;
}


int main(){
	cout << "Please input the size of your equations:";
	int size; cin >> size;
	cout << "Please insure your equations has the answer!" << endl;
	vector<vector<double>> A(size);
	vector<double> B, X;
	for ( int i = 0; i < size; ++i ){
		cout << "Please input the coefficient of the  " << i+1 << " line  element, all you need to input " << size + 1 << " elements" << endl;
		double val;
		for ( int j = 0; j < size; ++j )  {
			cin >> val;
			A[i].push_back( val );
		}
		cin >> val;
		B.push_back( val );
	}
	push_forward( A, B );
	// for ( int i = 0; i < size; ++i ){
	// 	for ( int j = 0; j < size; ++j )
	// 		cout << A[i][j] << " ";
	// 	cout << endl;
	// }
	X = back_subst( A, B );  
	for ( int i = 0; i < (int)X.size(); ++i ) cout << "x" << i+1 << " = ", printf("%.10lf\n", X[i] );
	return 0;
}
/*
3
1 2 3 4
1 2 4 5
2 3 4 6
*/