#ifndef BELLMAN_H 
#define BELLMAN_H 

#include <vector>
#include <stdio.h>
#include <assert.h>
#include <limits>
using namespace std;


struct CRS{
	vector<double> value;
	vector<unsigned long> row_idx;
	vector<unsigned long> col_idx;
};

void newPaths(vector<vector<double>>&, unsigned long);

void newGraph(vector<vector<double>>&);

void makeInf(vector<vector<double>>&,unsigned long);

bool checkNeg(vector<vector<double>>&);

void Output(vector<vector<double>>);

CRS createCRS(vector<vector<double>>);

vector <vector<double>> createNormal(CRS);

void OutputCRS(CRS);

void newPathsCRS(CRS&,unsigned long);

void newGraphCRS(CRS&);

void newGraphCRS(CRS&);

void newGraphCRS2(CRS&);

void makeInfCRS(CRS&,unsigned long,unsigned long);

bool checkNegCRS(CRS&);

void All(vector <vector<double>>&);

void AllCRS(CRS&);

void AllCRS2(CRS&);

void AllOpt(vector <vector<double>>&);

#endif