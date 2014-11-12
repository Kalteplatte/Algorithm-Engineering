#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
using namespace std;


unsigned long Fibonacci1 (int n);


unsigned long Fibonacci2 (int n);


unsigned long Fibonacci3 (int n);
vector<vector<double>> IdentityM(vector<vector<double>> v);

vector<vector<double> > MatrixMult(vector<vector<double> > v, vector<vector<double> > w);

vector<vector<double> > ExponentiationBySquaring(vector<vector<double> > v, double n);

unsigned long Fibonacci4(int n);

double sExponentiationBySquaring(double x, int n);

unsigned long Fibonacci5(int n);

unsigned long Fibonacci6(int n);

int main (){	int n;                /* test various numbers n */	cin >> n;	assert(Fibonacci2(n)==Fibonacci6(n));    /* note that Fibonacci6 is correct, so its used for testing */	assert(Fibonacci2(n)==Fibonacci6(n));	assert(Fibonacci3(n)==Fibonacci6(n));	assert(Fibonacci4(n)==Fibonacci6(n));	assert(Fibonacci5(n)==Fibonacci6(n));	int x=0;               /* Input so that the window stays */	cin >> x;	return 0;}  /* note that this test simply fails with a n big enough , e.g. 80 */