#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
using namespace std;


// function to determinine order of vector
template <typename T>
bool lesser(T a, T b){
	return a<b;
}

// function to determinine order of vector
template <typename T>
bool mores(T a, T b){
	return a>b;
}


//slow version becuase it's not in-place
template <typename T> // runs in O(n*log(n))
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

//new version of mergesort that's in-place, note that it's a void
//left and right show the interval that shall be sorted in sort, so the void is started with left=0 and right=sort.size()-1
template <typename T> // runs in O(n*log(n))
void mergesort2(vector<T>& sort, int left, int right, bool(*f)(T,T)){		
	if (left<right){										//if the two rows right under this one give us a vector that's empty or 'filled negative' do nothing
		mergesort2(sort,left,left+(right-left)/2,f);		//use mergesort on the left side of the vector
		mergesort2(sort,left+(right-left)/2+1,right,f);		//use mergesort on the right side of the vector
		int i=left+(right-left)/2;
		int j=i+1;											//start with the index left of the middle of sort (=i) and right of the middle (=j), because from left to i and from j to right the vector is sorted

		while (j <=right && f(sort[j],sort[i])){			//to go on we have to be inside of the vector. Since we increase j, j has to fullfill j<=right. 
			while (i>=left && f(sort[i+1],sort[i])) {		//same here, but we decrase i
				swap(sort[i],sort[i+1]);					//let the element, that's primary on i+1, 'walk' to the right position, so that the vector is sorted from left to j (because at the start i+1=j)
				i--;
			}
			j++;											//repeat with the next element
			i=j-1;
		}
	}
}

/*new implementation of quicksort, which is in-place
note that this is a void.
Initialize this void with quicksort2(vector sort,0,sort.size()-1,f)*/
template <typename T> // runs in O(n*log(n))
void quicksort2(vector <T>& sort, int left, int right,bool(*f)(T,T)){
	if (sort.size()<=50){
		mergesort2(sort,left,right,f);
		return;
	}
	int i = left;
	int j = right;
	int k = 0;
	T pivot = (sort[left]+sort[right]+sort[left+(right-left)/2])/3;					//chooses the first element of the vector as pivot
	while (i+k <= j) {
        while (f(sort[i],pivot)){			//sets i, so that i = min(k \in {0,...,sort.size()-1}: !f(sort[k],pivot))		
              if (sort[i]==pivot) {
				  swap(sort[i],sort[i+1+k]);
				  k++;
			  }
              else i++;
		  }
        while (f(pivot,sort[j])){			//sets j, so that j = max(k \in {0,...,sort.size()-1}: !f(pivot,sort[k]))
              j--;
		}
        if (i+k <= j) {
			  swap(sort[i],sort[j]);		//because !f(sort[i],pivot) and !f(pivot,sort[j]) we can swap both
              i++;
              j--;
		}
	}
	if (left<j)quicksort2(sort, left, j,f);		//left side of the vector, if necessary
	if (i<right)quicksort2(sort, i, right,f);	//right side of the vector, if necessary
}

//simple implementation of insertionsort
template <typename T> // runs in O(n*n)
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


template <typename T> // runs in O(n*log(n))
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

//finds the parentindex for a vector that shall be sorted with heap
int parentindex(int Idx){
	assert(Idx>=0);
	if (Idx==0) return 0;
	return (Idx-1)/2;
}

//finds the index of the left child for a vector that shall be sorted with heap
int leftchild(int Idx){
	assert(Idx>=0);
	return Idx*2+1;
}

//finds the index of the left child for a vector that shall be sorted with heap
int rightchild(int Idx){
	assert(Idx>=0);
	return Idx*2+2;
}

//check if the vector is sorted for the heapstructure from index start to index end
template<typename T>
void isHeap(vector<T> w, bool(*f)(T,T), int start, int end){
	if (leftchild(start)>=end) return;
	for (int i=leftchild(start);i<=end;i++){
		//assert(f(w[parentindex(i)],w[i]) || w[parentindex(i)]==w[i]);
	}
}



//a vector w (that has heapstructure from index 0 to index end-1) gets a new element at the index 'end'. Now this vector shall have heapstructure from 0 to end
template<typename T>
void siftUp(vector<T>& w, bool(*f)(T,T),int end){
	//pre-condition
	isHeap(w,f,0,end);

	int Idx=end;
	int parentIdx=parentindex(Idx);
	while(Idx!=0){
		if (f(w[Idx],w[parentIdx])){
			swap(w[Idx],w[parentIdx]);
		} else break;
		Idx=parentIdx;
		parentIdx=parentindex(Idx);
	}
}

//a vector w (that has heapstructure) gets a new element at the beginning, and it has to be a heap again
template<typename T>
void siftDown(vector<T>& w, bool(*f)(T,T)){
	//pre-condition
	isHeap(v,f,1,v.end());

	int Idx=0;
	int childIdx=leftchild(Idx);
	while (childIdx<=w.size()){
		if (childIdx+1==w.size()) return;
		else if (f(w[childIdx+1],w[childIdx])) childIdx=childIdx+1;
		if (f(w[childIdx],w[Idx])) swap(w[childIdx],w[Idx]);
		Idx = childIdx;
		childIdx=leftchild(Idx);		
	}
}

//transforms a vector w into a vector with the heap-structure
template<typename T>
void createHeap (vector<T>& w, bool(*f)(T,T),int end){
	for (int i=0;i<=end;i++){
		siftUp(w,f,i);
	}
}

//sorts vector by using the heapstructure to get the smallest/biggest element
//note that this void needs another function g with !g=f
template<typename T>
void heapSort (vector<T>& sort, bool(*f)(T,T),  bool(*g)(T,T)){
	for (int i=1;i<=sort.size();i++){
		createHeap(sort,g,sort.size()-i);
		swap(sort[0],sort[sort.size()-i]);
	}
}

template<typename T>
void test (vector<T> w, bool(*f)(T,T)){
	for (int j=1;j<w.size();j++){
		assert(f(w[j-1],w[j]) || w[j-1]==w[j]);
	}
}



int main(){
	int n=10;
	vector <double> v (n);
	vector <double> w (n);
	vector <double> x (n);
	

	/*srand (1);											
	for (int j=0;j<n;j++) v[j]=rand() %1000;
	for (int k=0;k<v.size();k++){
		cout << v[k] << " ";
	}
	cout << endl;

	heapSort(v,lesser<double>, mores<double>);
	for (int j=0;j<n;j++){
		cout << v[j] << " ";
	}
	cout << endl;	
	test(v,lesser<double>);*/
	w=quicksort(v,mores<double>);						//sort vector with identical elements, v=(0,0,...,0,0)
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	quicksort2(w,0,n-1,mores<double>);
	quicksort2(x,0,n-1,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	mergesort2(w,0,n-1,mores<double>);
	mergesort2(x,0,n-1,lesser<double>);
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
	w=v;
	x=v;
	heapSort(w,mores<double>, lesser<double>);
	heapSort(x,lesser<double>, mores<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	srand (1);											
	for (int j=0;j<n;j++) v[j]=rand() %1000;			//random permutated vector with (mostly) different elements
	w=quicksort(v,mores<double>);
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	quicksort2(w,0,n-1,mores<double>);
	quicksort2(x,0,n-1,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	mergesort2(w,0,n-1,mores<double>);
	mergesort2(x,0,n-1,lesser<double>);
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
	w=v;
	x=v;
	heapSort(w,mores<double>, lesser<double>);
	heapSort(x,lesser<double>, mores<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	for (int j=0;j<n;j++) v[j]=rand() %10;			//random permutated vector with repeating elements
	w=quicksort(v,mores<double>);
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	quicksort2(w,0,n-1,mores<double>);
	quicksort2(x,0,n-1,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	mergesort2(w,0,n-1,mores<double>);
	mergesort2(x,0,n-1,lesser<double>);
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
	w=v;
	x=v;
	heapSort(w,mores<double>, lesser<double>);
	heapSort(x,lesser<double>, mores<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	for (int j=0;j<n;j++) v[j]=j;			//sorted vector (for lesser, for mores this one is reverse)
	w=quicksort(v,mores<double>);
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	quicksort2(w,0,n-1,mores<double>);
	quicksort2(x,0,n-1,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	mergesort2(w,0,n-1,mores<double>);
	mergesort2(x,0,n-1,lesser<double>);
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
	w=v;
	x=v;
	heapSort(w,mores<double>, lesser<double>);
	heapSort(x,lesser<double>, mores<double>);
	test (w, mores<double>);
	test (x, lesser<double>);

	for (int j=0;j<n;j++) v[j]=n-j;			//reverse sorted vector (for mores, for lesser this one is sorted)
	w=quicksort(v,mores<double>);
	x=quicksort(v,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	quicksort2(w,0,n-1,mores<double>);
	quicksort2(x,0,n-1,lesser<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	w=v;
	x=v;
	mergesort2(w,0,n-1,mores<double>);
	mergesort2(x,0,n-1,lesser<double>);
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
	w=v;
	x=v;
	heapSort(w,mores<double>, lesser<double>);
	heapSort(x,lesser<double>, mores<double>);
	test (w, mores<double>);
	test (x, lesser<double>);
	return 0;
}