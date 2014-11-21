#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
using namespace std;

bool less(double a, double b){
	if(a<b) return 0;
	return 1;
}

bool more(double a, double b){
	if(a>b) return 0;
	return 1;
}


vector <double> quicksort(vector <double> sort, void (*less)(double,double)){
	if (sort.size()==1) return sort;
	double index = sort[0];
	return sort;
}

vector <double> insertionSort(vector <double> sort){
	return sort;
}


int main(){

	return 0;
}