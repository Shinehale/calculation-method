#include<iostream>
#include<cmath>
#include<vector>

using namespace std;
using db = double;
using Devc = vector<double>;


void push_forward( vector<vector<double>>& A, vector<double>& B ){
	const int size = A.size();
	int pos = 0;
	for ( int times = 1; times < size; ++times ){
		for ( int line = pos + 1; line < size; ++line ){
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


void calc_matrix(vector<Dvec> A, Devc B, Devc& ans ){
    push_forward( A, B );
    ans = back_subst(A, B);
}


void calc( const Dvec& X, const Devc& Y, Dvec& rv, const int& time){
    vector<Devc> A;
    Devc Y , ans;
    const int size = X.size();
    for ( int i = 0; i < time + 1; ++i) A.push_back( Devc( time + 1 ));
    for ( int i = 0; i < time + 1; ++i ) 
        for ( int j = 0; j < time + 1; ++j ){
            double tot = 0.0;
            for ( int s = 0; s < size; ++s ) tot += pow( X[s], i ) * pow( X[s], j );
            A[i][j] = tot;
        }
    for ( int i = 0; i < time + 1; ++i){
        double tot = 0;
        for ( int s = 0; s < size; ++s ) tot += Y[s] * pow( X[s], i );
        Y.push_back( tot );
    }
    calc_matrix( A, B, ans );
}



int main(){
    Devc X, Y;
    cout << "Please input your value size:" << endl;
    int size; cin >> size;
    cout << "Please input all the value you have as the format (x,y) and the () is not needed:" << endl;
    for ( int i = 0; i < size; ++i ) {
        db x, y; cin >> x >> y;
        X.push_back( x );
        Y.push_back( y );
    }
    cout << "Please input the order of the function you want:" << endl;
    int times ; cin >> times;
    Devc ans;
    calc( X, Y, ans, times );
    cout << ans[0];
    for ( int i = 1; i < times; ++i ) cout << " + " << ans[i] << "x^" << i;
    cout << "x^" << ans[times] << endl;
    return 0;
}