#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include "fibonacci.cpp"
using namespace std;

unsigned long Fibonacci1 (int n);
unsigned long Fibonacci2 (int n);

unsigned long Fibonacci3 (int n);
vector<vector<double> > IdentityM(vector<vector<double> > v);

vector<vector<double> > MatrixMult(vector<vector<double> > v, vector<vector<double> > w);

vector<vector<double> > ExponentiationBySquaring(vector<vector<double> > v, double n);

unsigned long Fibonacci4(int n);

unsigned long Fibonacci5(int n);

unsigned long Fibonacci6(int n);


int main (){	/*assert(Fibonacci1(60)==Fibonacci6(60));*/	assert(Fibonacci2(60)==Fibonacci6(60));	assert(Fibonacci3(60)==Fibonacci6(60));	assert(Fibonacci4(60)==Fibonacci6(60));	assert(Fibonacci5(60)==Fibonacci6(60));	return 0;} 