/**
 * Cholesky pro generation 
 * which for LDL^T = A 
 * so we can devide the matrix into two easy and simple equations to solve.
 * and do not using the sqrt algorithm.
 */


#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void calc_L_and_D( const vector< vector<double> >& A, vector<vector<double>>& L, vector<double>& D ){
	auto sqr = [](const double x) { return x*x;};
	const int Size = A.size();
	L.clear();D.clear();
	for (int i = 0; i < Size; ++i ){
		L.push_back(vector<double> () );
	 	for ( int j = 0; j < i + 1; ++j ) L[i].push_back( 1 );
	 }

	// step 1 
	D.push_back(A[0][0]);
	for ( int i = 1; i < Size; ++i ) L[i][0] = A[i][0] / D[0];
	// step 2
	//首先处理下D中元素，然后处理D对应的那一列中的元素
	//则设 i 为 当前计算位置，tot(k) = D[k] * A[i][k] * A[j][k] ，j 是当前列的最顶端元素的纵坐标 
	//最终对 前面全部的对应的tot求和 sum = sigma(tot(k)) (k = 0, j - 1)
	// L[i][j] = sum / D[j]
	for ( int pos = 1; pos < Size; ++pos ){
		double tot = 0.0;
		for ( int i = 0; i < pos ; ++i ) tot += sqr(L[pos][i]) * D[i];
		D[pos] = A[pos][pos] - tot;
		for ( int i = pos + 1; i < Size; ++i ) {
			tot = 0.0;
			for ( int k = 0; k < pos ;++k ) tot += L[i][k] * L[pos][k] * D[k];
			L[i][pos] = (A[i][pos] - tot) / D[pos];
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

void calc_X( const vector<double>& D, const vector<vector<double>>& L, vector<double>& X, const vector<double>& Y ){
	const int Size = L.size();
	X.clear();for ( int i = 0; i < Size; ++i ) X.push_back( 0.0 );
	vector<vector<double>> M; 								// M = DL^T 
	for (int i = 0; i < Size; ++i )	M.push_back( vector<double> (Size) );
	for ( int i = 0; i < Size; ++i )
		for ( int j = 0; j <= i; ++j )
			M[j][i] = L[i][j] * D[j];

	/* output the matrix M*/
	cout << "The matrix M = DL^T is: " << endl;
	for ( int i = 0; i < Size; ++i ){
		for ( auto j = 0ull; j < M[i].size(); ++j ) cout << M[i][j] << " ";
			cout << endl;
	}
	/* at this time ,the equation is MX = Y*/
	for ( int pos = Size - 1; pos >= 0; --pos ) {
		double tot = 0.0;
		for ( int j = pos + 1; j < Size; ++j ) tot += M[pos][j] * X[j];
		X[pos] = (Y[pos] - tot) / M[pos][pos];
	}
}



int main(){
	cout << "Please input the size of your equations:";
	int size; cin >> size;
	cout << "Please insure your equations has the answer!" << endl;
	vector<vector<double>> A(size), L(size);
	vector<double> B, X, D, Y;
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


	/* calc matrix L and matrix D ,output them */
	calc_L_and_D( A, L, D );
	cout << "The matrix L is: "<< endl;  
	for ( int i = 0; i < size; ++i ){
		for ( auto j = 0ull; j < L[i].size(); ++j ) cout << L[i][j] << " ";
			cout << endl;
	}
	cout << "The matrix D is: diag[ ";
	for ( int i = 0; i < size; ++i ) cout << D[i] << " "; 
	cout << "]" << endl;


	/*calc matrix Y and output it*/
	calc_Y( L, B ,Y );
	cout << "The matrix Y is: " << endl;
	for ( auto i = 0ull; i < Y.size(); ++i ) cout << Y[i] << " ";
	cout << endl;


	/*calc matrix X and output it*/
	calc_X( D, L, X, Y );
	cout << "The matrix X is: " << endl;
	for ( auto i = 0ull; i < X.size(); ++i ) cout << X[i] << " ";
	cout << endl;
	return 0;
}
/*

4
5 -4 1 0 2 
-4 6 -4 1 -1
1 -4 6 -4 -1
0 1 -4 5 2

*/