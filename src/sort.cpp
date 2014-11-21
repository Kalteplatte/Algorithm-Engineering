#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <utility>
#include <stdlib.h>
#include <time.h>
using namespace std;

bool lesser(double a, double b){
	if(a<b) return 0;
	return 1;
}

bool mores(double a, double b){
	if(a>b) return 0;
	return 1;
}


vector <double> quicksort(vector <double> sort, bool (*f)(double,double)){
	if (sort.size()<=1) return sort;     //if the vector is empty or only one element, sorting makes no sense
	double index = sort[0];    //element to sort in this cycle
	int j=0;					// j will later show the position of index 
	for (int i=0; i<=(sort.size()-1) ;i++){
		if (f(sort[i],index)==0){ 
			swap(sort[i],sort[j]);           // not beautiful. But it works and works faster than 'insert' 
			if (j+1!=i)	{					 
				swap(sort[j+1],sort[i]);
			}
			j++;							//index was moved "one step to the right"
		}
	}
	vector<double> split_lo(sort.begin(), sort.begin() + j);    //split sort in 2 vectors. The first one ends before the index, the second one begins after the index
	vector<double> split_hi(sort.begin() + j + 1, sort.end());
	split_lo=quicksort(split_lo,f);
	split_hi=quicksort(split_hi,f);
	split_lo.push_back(index);                                  //add index at the end of split_lo
	for (int k=0;k<split_hi.size();k++) split_lo.push_back(split_hi[k]);
	return split_lo;
}

vector <double> insertionSort(vector <double> sort,bool (*f)(double,double)){
	int k;
	for (int i=0;i<sort.size();i++){
		k=i;
		for (int j = i;j>=0;j--){
			if (f(sort[k],sort[j])==0) {
				swap(sort[k],sort[j]);
				k=j;
			}
		}
	}
	return sort;
}


int main(){
	srand (time(NULL));
	vector <double> v (10);
	for (int j=0;j<v.size();j++) v[j]=rand() %100;
	for (int k = 0;k<v.size();k++) cout << v[k] << " ";
	cout << endl;
	v=insertionSort(v,mores);
	for (int i = 0;i<v.size();i++) cout << v[i] << " ";
	return 0;
}