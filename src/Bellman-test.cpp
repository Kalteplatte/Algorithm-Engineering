#include <vector>
#include <stdio.h>
#include <assert.h>
#include <limits>
#include "Bellman.h"
#include <time.h>      

using namespace std;



//test if the mutation from CSR into matrix and backwards works correctly
void testmutate1(CSR graph){
	vector <vector<double>> matrix;
	matrix=createNormal(graph);
	CSR graph2=createCSR(matrix);
	assert(graph.value.size()==graph2.value.size());
	assert(graph.col_idx.size()==graph2.col_idx.size());
	assert(graph.row_idx.size()==graph2.row_idx.size());
	for (int i=0;i<graph.value.size();i++){
		assert(graph.value[i]==graph2.value[i]);
		assert(graph.row_idx[i]==graph2.row_idx[i]);
	}
	for (int i=0;i<graph.col_idx.size();i++){
		assert(graph.col_idx[i]==graph2.col_idx[i]);
	}

}

//test if the mutation from matrix into CSR and backwards works correctly
void testmutate2(vector <vector<double>> matrix){
	CSR graph=createCSR(matrix);
	vector <vector<double>> matrix2;
	matrix2=createNormal(graph);
	
	assert(matrix.size()==matrix2.size());
	assert(matrix[0].size()==matrix[2].size());
	int size = matrix.size();
	for (int i=0;i<size;i++){
		for (int j=0; j<size;j++){
			if (matrix[i][j]==matrix[i][j]) assert(matrix[i][j]==matrix2[i][j]);
			else assert(matrix2[i][j]!=matrix2[i][j]);
		}
	}
}

void testpath(vector <vector<double>> matrix){
	int size=matrix.size();
	for (int i=0;i<size;i++){
		for (int j=0; j<size;j++){
			if(matrix[i][j]==matrix[i][j] && matrix[j][i]==matrix[j][i]) assert(matrix[i][i]<=matrix[i][j]+matrix[j][i]);
		    if(matrix[i][i]==-std::numeric_limits<double>::infinity() && matrix[i][j]==matrix[i][j]) assert(matrix[i][j]==-std::numeric_limits<double>::infinity());
		}
	}
}

vector <vector<double>> createGraph(int dimension){
	srand (time(NULL));
	int quote1=rand()%100;
	int quote2=rand()%100;
	
	vector <vector<double>> graph; 
	graph.resize(dimension,vector<double>(dimension,std::numeric_limits<double>::quiet_NaN()));
	

	for (int i=0;i<dimension;i++){
		for (int k=0;k<dimension;k++){
			if (k==i) graph[i][k]=0;
			else if ((rand()%100)<=quote1) {
				int r=rand()%100;
				r=r-quote2;
				graph[i][k]=r;
			}
		}
	}
	return graph;
}
	

int main(){

	//testing purposes
	vector <vector<double>> graph; 
	int V = 100;
	for (int i=0; i <100; i++){
		graph=createGraph(V);
		CSR matrix=createCSR(graph);
		testmutate1(matrix);
		testmutate2(graph);
		All(graph);
		testpath(graph);
	}
	return 0;
}