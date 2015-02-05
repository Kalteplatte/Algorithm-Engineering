#ifndef BELLMAN_H 
#define BELLMAN_H 

#include <vector>
#include <stdio.h>
#include <assert.h>
#include <limits>
using namespace std;


struct CSR{
	vector<double> value;
	vector<int> row_idx;
	vector<int> col_idx;
};

void newPaths(vector<vector<double>>&, int);

void newGraph(vector<vector<double>>&);

void makeInf(vector<vector<double>>&,int);

bool checkNeg(vector<vector<double>>&);

void Output(vector<vector<double>>);

CSR createCSR(vector<vector<double>>);

vector <vector<double>> createNormal(CSR);

void OutputCSR(CSR);

void newPathsCSR(CSR&,int);

void newGraphCSR(CSR&);

void newGraphCSR(CSR&);

void makeInfCSR(CSR&,int,int);

bool checkNegCSR(CSR&);

void All(vector <vector<double>>&);

void AllCSR(CSR&);

#endif