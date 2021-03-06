#include <vector>
#include <stdio.h>
#include <assert.h>
#include <limits>
#include "Bellman.h"
#include <time.h>      
#include <chrono>

using namespace std;



//test if the mutation from CRS into matrix and backwards works correctly
void testmutate1(CRS graph){
	vector <vector<double>> matrix;
	matrix=createNormal(graph);
	CRS graph2=createCRS(matrix);
	assert(graph.value.size()==graph2.value.size());
	assert(graph.col_idx.size()==graph2.col_idx.size());
	assert(graph.row_idx.size()==graph2.row_idx.size());
	for (unsigned long i=0;i<graph.value.size();i++){
		assert(graph.value[i]==graph2.value[i]);
		assert(graph.row_idx[i]==graph2.row_idx[i]);
	}
	for (unsigned long i=0;i<graph.col_idx.size();i++){
		assert(graph.col_idx[i]==graph2.col_idx[i]);
	}

}

//test if the mutation from matrix into CRS and backwards works correctly
void testmutate2(vector <vector<double>> matrix){
	CRS graph=createCRS(matrix);
	vector <vector<double>> matrix2;
	matrix2=createNormal(graph);
	
	assert(matrix.size()==matrix2.size());
	assert(matrix[0].size()==matrix[2].size());
	unsigned long size = matrix.size();
	for (unsigned long i=0;i<size;i++){
		for (unsigned long j=0; j<size;j++){
			if (matrix[i][j]==matrix[i][j]) assert(matrix[i][j]==matrix2[i][j]);
			else assert(matrix2[i][j]!=matrix2[i][j]);
		}
	}
}

//test if the given paths from i to j are smaller or equal to other paths from i to j over other points
void testpath(vector <vector<double>> matrix){
	unsigned long size=matrix.size();
	for (unsigned long i=0;i<size;i++){
		for (unsigned long j=0; j<size;j++){
			if(matrix[i][j]==matrix[i][j] && matrix[j][i]==matrix[j][i]) assert(matrix[i][i]<=matrix[i][j]+matrix[j][i]);
		    if(matrix[i][i]==-std::numeric_limits<double>::infinity() && matrix[i][j]==matrix[i][j]) assert(matrix[i][j]==-std::numeric_limits<double>::infinity());
		}
	}
}

//create a random graph in the given dimension
vector <vector<double>> createGraph(unsigned long dimension){
	//srand (time(NULL));
	int quote1=rand()%100;
	int quote2=rand()%100;
	
	vector <vector<double>> graph; 
	graph.resize(dimension,vector<double>(dimension,std::numeric_limits<double>::quiet_NaN()));
	

	for (unsigned long i=0;i<dimension;i++){
		for (unsigned long k=0;k<dimension;k++){
			if (k==i) graph[i][k]=0;
			else if ((rand()%100)<=quote1) {
				unsigned long r=rand()%100;
				r=r-quote2;
				graph[i][k]=r;
			}
		}
	}
	return graph;
}


//Measures the time AllOpt needs for using Bellman-Ford on a graph
double MeasureTime(vector <vector<double>> graph){  //Measures the time of a function in microseconds, 
	auto start = chrono::high_resolution_clock::now();

	/*for(int i=0;i<1000;i++)*/ All(graph);  

	auto stop = chrono::high_resolution_clock::now();

    
	double elapsed = chrono::duration_cast<chrono::microseconds>(stop-start).count();
	return elapsed;
}





int main(){

	//testing purposes
	/*vector <vector<double>> graph; 
	unsigned long V = 100;
	for (unsigned long i=0; i <100; i++){
		graph=createGraph(V);
		CRS matrix=createCRS(graph);
		testmutate1(matrix);
		testmutate2(graph);
		All(graph);
		testpath(graph);
	}*/

	vector <vector<double>> graph;
	double sum=0;
	unsigned long dimension=10;
	for (unsigned long i=0; i<5;i++){
		graph=createGraph(dimension);
		sum=sum+MeasureTime(graph);
	}
	printf("%f",sum/5);
	return 0;
}