#include<iostream>
#include<vector>

using namespace std;
using Dvec = vector<double>;
using db = double;

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

void calc( const Dvec& X, const Dvec& Y, const double tarVal){
    if ( tarVal > X[size - 1] ) return 0;
    // in this case, you may change it as a bool expression 
    vector< Dvec > A, N ;
    Dvec h, B, C, M ;
    const int size = X.size();
    for ( int i = 0; i < size; ++i ) A.push_back(Dvec(size)), B.push_back(0);
    for ( int i = 0; i < size - 1; ++i ) h[i] = X[i + 1] - X[i];
    for ( int pos = 1; pos < size - 1; ++pos ) {
        A[pos][pos] = 2*(h[pos-1] + h[pos]);
        A[pos][pos - 1] = h[pos - 1];
        A[pos][pos + 1] = h[pos];
    }
    A[0][0] = 1; A[size-1][size-1] = 1;
    for ( int i = 1; i < size - 1; ++i)  B[i] = 6 * (Y[i+1] - Y[i]) / h[i] - (Y[i] - Y[i-1]) / h[i-1];
    B[0] = 0; B[size - 1] = 0;
    calc_M_and_Gam(A, B, N, C);
    calc_X(N, C, M);int pos = 0;
    for ( int  i = 0; i < size - 1; ++i) if ( X[i] <= tarVal && X[i+1] > tarVal ) pos = i;
    double a = Y[pos], 
           b = ( Y[pos + 1] - Y[pos] ) / h[pos] - h[pos] / 2 * M[pos] - h[pos] / 6 * ( M[pos + 1] - M[pos]),
           c = M[pos] / 2,
           d = ( M[pos + 1] - M[pos]) / (6 * h[pos]);
    return a + b*(tarVal - X[pos]) + c*(tarVal - X[pos]) * (tarVal - X[pos]) + d * (tarVal - X[pos])
            * (tarVal - X[pos]) * (tarVal - X[pos]);
}
int main()
{
    int size;
    cout << "Please input the size of your data:" << endl;
    cin >> size;
    Dvec X, Y, A, B ;
    cout << "Please input the pair of the value one by one: 
                \n like ( x, y ) and the () is not needed \n please ensure they are orded in X " << endl;
    for ( int i = 0; i < size; ++i ) {
        db x, y; cin >> x >> y;
        X.push_back( x );
        Y.push_back( y );
    }   
    db tarVal; 
    cout << "Please input the value you want to predict:" << endl;
    cin >> tarVal;
    db ans = calc( X, Y, tarVal );
    cout << "The value of the f(x) you wanna predict is :" << endl;
    cout << ans << endl;
    return 0;
}