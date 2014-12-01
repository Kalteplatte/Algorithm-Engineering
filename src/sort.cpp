#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
using namespace std;


template <typename T>
bool lesser(T a, T b){
	return a<b;
}

template <typename T>
bool mores(T a, T b){
	return a>b;
}

template <typename T>
vector <T> quicksort(vector <T> sort, bool (*f)(T,T)){
	if (sort.size()<=1) return sort;     //if the vector is empty or only one element, sorting makes no sense
	T index = sort[0];    //element to sort in this cycle
	int j=0;					// j will later show the position of index 
	for (int i=0; i<=(sort.size()-1) ;i++){
		if (f(sort[i],index)){ 
			swap(sort[i],sort[j]);           // not beautiful. But it works and works faster than 'insert' 
			if (j+1!=i)	{					 //
				swap(sort[j+1],sort[i]);	 //
			}
			j++;							//index was moved "one step to the right"
		}
	}
	vector<T> split(sort.begin() + j + 1, sort.end());
	sort.erase(sort.begin() + j + 1, sort.end());                    //split sort in 2 vectors. The first one ends before the index, the second one begins after the index
	sort=quicksort(sort,f);
	split=quicksort(split,f);
	sort.push_back(index);                                  //add index at the end of sort
	for (int k=0;k<split.size();k++) sort.push_back(split[k]);
	return sort;
}

template <typename T>
vector <T> insertionsort(vector <T> sort,bool (*f)(T,T)){
	int k;
	for (int i=0;i<sort.size();i++){
		k=i;
		for (int j = i;j>=0;j--){
			if (f(sort[k],sort[j])) {
				swap(sort[k],sort[j]);
				k=j;
			}
		}
	}
	return sort;
}

template <typename T>
vector <T> mergesort(vector<T> sort, bool(*f)(T,T)){
	if (sort.size()<=1) return sort;
	int n=sort.size();
	vector<T> split(sort.begin() + n/2, sort.end());
	sort.erase(sort.begin() + n/2, sort.end());                    
	sort=mergesort(sort,f);
	split=mergesort(split,f);
	int sortcounter=0;
	int splitcounter=0;
	vector<T> res(n);
	int i=0;
	while (i<n){
		if(f(split[splitcounter],sort[sortcounter])){
			res[i]=split[splitcounter];
			splitcounter++;
		}else{
			res[i]=sort[sortcounter];
			sortcounter++;
		}
		i++;
		if(splitcounter == split.size()){
			while (sortcounter<sort.size()){
				res[i]=sort[sortcounter];
				i++;
				sortcounter++;
			}
		} 
		if(sortcounter == sort.size()){
			while (splitcounter<split.size()){
				res[i]=split[splitcounter];
				i++;
				splitcounter++;
			}
		}
	}
	return res;
}

template<typename T>
void test (vector<T> w, bool(*f)(T,T)){
	for (int j=1;j<w.size();j++){
		assert(f(w[j-1],w[j]) || w[j-1]==w[j]);
	}
}



int main(){
	int n=1000;
	vector <double> v (n);
	vector <double> w (n);
	vector <double> x (n);
	
	
	w=quicksort(v,mores<double>);						/*sort vector with identical elements, v=(0,0,...,0,0)*/
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=insertionsort(v,mores<double>);
	x=insertionsort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=mergesort(v,mores<double>);
	x=mergesort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	srand (1);											
	for (int j=0;j<n;j++) v[j]=rand() %1000;			/*random permutated vector with (mostly) different elements*/
	w=quicksort(v,mores<double>);
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=insertionsort(v,mores<double>);
	x=insertionsort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=mergesort(v,mores<double>);
	x=mergesort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	for (int j=0;j<n;j++) v[j]=rand() %10;			/*random permutated vector with repeating elements*/
	w=quicksort(v,mores<double>);
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=insertionsort(v,mores<double>);
	x=insertionsort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=mergesort(v,mores<double>);
	x=mergesort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	for (int j=0;j<n;j++) v[j]=j;			/*sorted vector (for lesser, for mores this one is reverse)*/
	w=quicksort(v,mores<double>);
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=insertionsort(v,mores<double>);
	x=insertionsort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=mergesort(v,mores<double>);
	x=mergesort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	for (int j=0;j<n;j++) v[j]=n-j;			/*reverse sorted vector (for mores, for lesser this one is sorted)*/
	w=quicksort(v,mores<double>);
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=insertionsort(v,mores<double>);
	x=insertionsort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=mergesort(v,mores<double>);
	x=mergesort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	return 0;
}