#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <utility>
using namespace std;

bool lesser(double a, double b){
	if(a<b) return 0;
	return 1;
}

bool morer(double a, double b){
	if(a>b) return 0;
	return 1;
}


vector <double> quicksort(vector <double> sort, bool (*less)(double,double)){
	if (sort.size()<=1) return sort;     //if the vector is empty or only one element, sorting makes no sense
	double index = sort[0];    //element to sort in this cycle
	int j=0;					// j will later show the position of index 
	for (int i=1; i<(sort.size()-1) ;i++){
		if (less(sort[i],index)==0){ 
			swap(sort[i],sort[j]);    // not beautiful. But it works and works faster than 'insert' 
			j++;
			if (j!=i+1)	swap(sort[j],sort[i]);
		}
	}
	vector<double> split_lo(sort.begin(), sort.begin() + j);    //split sort in 2 vectors. The first one ends before the index, the second one begins after the index
	vector<double> split_hi(sort.begin() + j + 1, sort.end());
	split_lo=quicksort(split_lo,less);
	split_hi=quicksort(split_hi,less);
	split_lo.push_back(index);                                  //add index at the end of split_lo
	merge(split_lo.begin(), split_lo.end(), split_hi.begin(),split_hi.end(), sort.begin());  //Merge split_lo and split_hi to create sort
	return sort;
}

vector <double> insertionSort(vector <double> sort){
	return sort;
}


int main(){
	vector <double> v (4,4);
	v[0]=1;
    v[1]=3;
	v[2]=2;
	v=quicksort(v,lesser);
	for (int i = 0;i<v.size();i++) cout << v[i];
	return 0;
}