#include<iostream>
#include<vector>

using namespace std;
using Dvec = vector<double>;

void calc_M_and_Gam( const vector<Dvec>& A, const Dvec& B, vector<Dvec>& M, Dvec& C ){
	const int size = A.size();
	C.clear(); M.clear();
	for ( int i = 0; i < size; ++i ) M.push_back( Dvec(10) );
	for ( int i = 0; i < size; ++i ) M[i][i] = 1;
	//step 1
	M[0][1] = A[0][1] / A[0][0];
	C.push_back( B[0] / A[0][0] );
	//step 2
	for ( int line = 1; line < size - 1; ++line ) M[line][line + 1] = A[line][line + 1] / ( A[line][line] - M[line - 1][line] * A[line][line - 1]);
	for ( int line = 1; line < size; ++line ) C.push_back( (B[line] - C[line - 1] * A[line][line - 1] ) / ( A[line][line] - M[line - 1][line] * A[line][line - 1]) );	
}

void calc_X( const vector<Dvec>& A, const Dvec& B, Dvec& X ){
	X.clear();const int size = A.size();
	for ( int i = 0; i < size; ++i ) X.push_back( 0.0 );
	X[size - 1] = B[size - 1];
	for (int i = size - 2; i >= 0 ; --i) X[i] = B[i] - A[i][i + 1] * X[i + 1];
}


int main(){
	cout << "Please input the size of your equations:";
	int size; cin >> size;
	cout << "Please insure your equations has the answer!" << endl;
	vector<Dvec> A(size), Beta;
	Dvec B, Gam, X;
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

	/* output the A matrix*/
	cout << "The matrix A is: "<< endl;  
	for ( int i = 0; i < size; ++i ){
		for ( auto j = 0ull; j < A[i].size(); ++j ) cout << A[i][j] << " ";
			cout << endl;
	}

	calc_M_and_Gam( A, B, Beta, Gam );
	/* output the Beta matrix*/
	cout << "The matrix Beta is: "<< endl;  
	for ( int i = 0; i < size; ++i ){
		for ( auto j = 0ull; j < Beta[i].size(); ++j ) cout << Beta[i][j] << " ";
			cout << endl;
	}
	/* output the Gamma matrix*/
	cout << "The matrix Gamma is: "<< endl;  
	for ( int i = 0; i < size; ++i ) cout << Gam[i] << " ";
	cout << endl;


	/* calculate the matrix X and output the X matrix*/
	calc_X( Beta, Gam, X );
	cout << " the answer matrix is :" << endl;
	for ( int i = 0; i < size; ++i ) cout << X[i] << " ";
	cout << endl;
	return 0;

}
/*
input:
5
2 -1 0 0 0 1
-1 2 -1 0 0 0
0 -1 2 -1 0 0
0 0 -1 2 -1 0
0 0 0 -1 2 0

the output is:


The matrix A is:
2 -1 0 0 0
-1 2 -1 0 0
0 -1 2 -1 0
0 0 -1 2 -1
0 0 0 -1 2
The matrix Beta is:
1 -0.5 0 0 0 0 0 0 0 0
0 1 -0.666667 0 0 0 0 0 0 0
0 0 1 -0.75 0 0 0 0 0 0
0 0 0 1 -0.8 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
The matrix Gamma is:
0.5 0.333333 0.25 0.2 0.166667
 the answer matrix is :
0.833333 0.666667 0.5 0.333333 0.166667
*/