#include<iostream>
#include<cmath>
#include<vector>
#include<cstdio>

using namespace std;
using Dvec = vector<double>;
const double INITIAL_VALUE = 1.0;
const double eps = 1e-5;


namespace SOR{
	const double RelaxationFactor = 0.125;

	auto f = []( const double& x ) { return x * x; };


	void init( Dvec& x, const int& size )
	{	
		x.clear();
		for ( int i = 0; i < size; ++i ) x.push_back(INITIAL_VALUE);
		cout << endl;
	
	}
	void calc_iteration( const vector<Dvec>& A, const Dvec& B, Dvec& X )
	{
		const int Size = X.size();
		for ( int pos = 0; pos < Size; ++pos ){
			double tot = 0.0;
			for ( int i = 0; i < Size; ++ i) 
			tot += A[pos][i] * X[i];
			X[pos] = X[pos] + RelaxationFactor * ( B[pos] - tot ) / A[pos][pos];
		}
	} 
	double calc_accuracy( const Dvec& pre, const Dvec& newone )
	{
		// in this position, we will use the distance between the two vector as the accuracy
		const int Size = pre.size();
		double tot = 0.0;
		for ( int i = 0; i < Size; ++i ) tot = max( tot, fabs( pre[i] - newone[i] ) );
		return tot;
	}
	void Main( const vector<vector<double>>& A, const vector<double>& B ){
		cout <<" *******In the SOR function*********" << endl;
		const int size = A.size();
		vector<double> X;
		init( X , size );
		// finish the iteration untill to the concrecy that you want!
		int times = 0;
		while ( true ){
			++times;
			Dvec pre = X;
			calc_iteration( A, B, X );
			if ( calc_accuracy( pre, X ) < eps )  break;
		}
		// output the matrix X you have get in the past;
		cout << "After " << times <<" times iteration, the matrix X is :" <<endl;
		for ( auto each : X ) printf(" %.10f", each );
		cout << endl << endl;
	} 
};


namespace JOR{
	const double RelaxationFactor = 0.07;
	/**
		for the B = -D^(-1)*(L+U) does have the eigenvalue larger than or equal to the 1
		So it does not have the Relaxation Factor, we wanna define it as 0.07
	*/

	auto f = []( const double& x ) { return x * x; };

	void init( Dvec& x, const int& size )
	{	
		x.clear();
		for ( int i = 0; i < size; ++i ) x.push_back(INITIAL_VALUE);
		cout << endl;
	}
	Dvec calc_iteration( const vector<Dvec>& A, const Dvec& B, const Dvec& X )
	{
		Dvec XNew = X;
		const int Size = X.size();
		for ( int pos = 0; pos < Size; ++pos ){
			double tot = 0.0;
			for ( int i = 0; i < Size; ++ i) 
			tot += A[pos][i] * X[i];
			XNew[pos] = X[pos] + RelaxationFactor * ( B[pos] - tot ) / A[pos][pos];
		}
		return XNew;
	} 
	double calc_accuracy( const Dvec& pre, const Dvec& newone )
	{
		// in this position, we will use the distance between the two vector as the accuracy
		const int Size = pre.size();
		double tot = 0.0;
		for ( int i = 0; i < Size; ++i ) tot = max( tot, fabs( pre[i] - newone[i] ) );
		return tot;
	}
	void Main( const vector<vector<double>>& A, const vector<double>& B ){
		cout <<" *******In the JOR function*********" << endl;
		const int size = A.size();
		vector<double> X;
		init( X , size );
		// finish the iteration untill to the concrecy that you want!
		int times = 0;
		while ( true ){
			++times;
			Dvec newOne = calc_iteration( A, B, X );
			if ( calc_accuracy( X, newOne ) < eps )  break;
			X = newOne;
		}
		// output the matrix X you have get in the past;
		cout << "After " << times <<" times iteration, the matrix X is :" <<endl;
		for ( auto each : X ) printf(" %.10f", each );
		cout << endl; 
	} 
};



int main()
{
	cout << "Please input the size of your equations:";
	int size; cin >> size;
	cout << "Please insure your equations has the answer!" << endl;
	vector<vector<double>> A(size);
	vector<double> B;
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
	SOR::Main( A, B );
	JOR::Main( A, B ); 
	return 0;
}

/*
4 
5 -1 -1 -1 -4
-1 10 -1 -1 12
-1 -1 5 -1 8
-1 -1 -1 10 34

5
1 2 3 4 5 55
-2 3 4 5 6 66
-3 -4 5 6 7 63
-4 -5 -6 7 8 36
-5 -6 -7 -8 9 -25

*/
