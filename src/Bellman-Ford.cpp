//This algorithm gets a Graph G=(V,E) represented with a matrix. The matrix will then be changed to a matrix which elements tell us the smallest/shortest path from one point to another.
//The difference to the Dijkstra-algorithm are the (possible) negative weights.
//Note that the given matrix will be handled as if it's directed and has only zeroes on the diagonal. Certain values will tell us that there is no direct connection between two points. (see below)
//In the beginning every point has the distance 0 to itself, therefore the diagonal is zero.
//Due to the fact of the negative weights, the zeroes on the diagonal may change to negative numbers in the algorithm. In this case we have at least one negative cycle inside the graph.

//Note that the check for NaN is different in VS and other compilers. So here we will check i==i, which returns false if i=NaN

#include <vector>
#include <stdio.h>
#include <assert.h>
#include <limits>
#include "Bellman.h"

using namespace std;
//TODO
//complexity+space
//CSR


//This void changes the paths from start to every other point, so that (if there exists a connection) in the end the shortest path from start to every connected point is shown.
void newPaths(vector<vector<double>>& graph, int start){
	int size=graph.size();
	for (int i=0;i<size;i++){
		if(graph[start][i]==graph[start][i]){    //Check if you need the path from i to other points. If start and i are not connected then ignore 
			for (int j=0;j<size;j++){
				if(graph[i][j]==graph[i][j]){										                 //
					if(graph[start][j]>graph[i][j]+graph[start][i] || graph[start][j]!=graph[start][j]){  //together in one if? Don't know how to say (maybe if(graph[i][j]!=NULL && (graph[start][j]<graph[i][j] || graph[start][j]==NULL)) ?)
						graph[start][j]=graph[i][j]+graph[start][i];
					}
				}
			}
		}
	} 

}

//Nothing special, just uses newPaths on the whole graph
void newGraph(vector<vector<double>>& graph){
	int size=graph.size();
	for (int i=0; i<size;i++) newPaths(graph,i);
}



//if start has the value -INF, this function changes every successive point to -INF
void makeInf(vector<vector<double>>& graph,int start){
	if (graph[start][start]!=-std::numeric_limits<double>::infinity()) return;
	int size=graph.size();
	for (int j=0;j<size;j++){
		if (graph[start][j]==graph[start][j]){
			graph[start][j]=-std::numeric_limits<double>::infinity();
		} 
	}
}

//This Algo checks if there exists a negative cycle in the graph, by adding the path from a point i to a point j and then backwards.
//In addition it changes (with makeInf() ) all related points to -INF)
bool checkNeg(vector<vector<double>>& graph){
	bool info=1;
	int size=graph.size();
	for (int i=0;i<size;i++){
		for (int j=0;j<size;j++){
			if (graph[i][j]==graph[i][j] && graph[j][i]==graph[j][i]){
				if(graph[i][j]+graph[j][i]<0 || graph[j][i]==-std::numeric_limits<double>::infinity() || graph[i][j]==-std::numeric_limits<double>::infinity()){
					info=0;
					graph[i][i]=-std::numeric_limits<double>::infinity();
					makeInf(graph,i);
				}
			}
		}
	}
	return info;
}

//simple Algorithm to show the matrix graph in a proper format
void Output(vector<vector<double>> graph){ 
	int size=graph.size();
	for (int i=0;i<size;i++){
		for (int k=0;k<size;k++){
			if (graph[i][k]!=graph[i][k]) printf("%5s ","N");
			else if (graph[i][k]==-std::numeric_limits<double>::infinity()) printf ("%5s ", "-INF");
			else	printf("%5.0f ",graph[i][k]);
		}
		printf("\n");
	}
	printf("\n \n");
}

//simply use all the functions together
void All(vector<vector<double>>& graph){
	Output(graph);
	newGraph(graph);
	Output(graph);
	bool info=checkNeg(graph);
	Output(graph);
	test(graph);
}

//tests if all -INF's have -INF as successor
void test(vector<vector<double>> graph){
	for (int i=0;i<graph.size();i++){
		for (int k=0;k<graph.size();k++){
			if (graph[i][i]==-std::numeric_limits<double>::infinity()) assert(graph[i][k]==-std::numeric_limits<double>::infinity() || graph[i][k]!=graph[i][k]);
		}
	}
}

//changes a normal matrix into a CSR-Matrix
//note that it's not necessary to check if one row of the original mtraix is empty, because the elements on the diagonal are never empty.
CSR createCSR(vector<vector<double>> graph){
	CSR matrix;
	int old_i=0;
	for (int i=0;i<graph.size();i++){
		for (int k=0;k<graph.size();k++){
			if (graph[i][k]==graph[i][k]) {
				matrix.value.push_back(graph[i][k]);
				matrix.col_idx.push_back(k);
				if(matrix.row_idx.size()==0) matrix.row_idx.push_back(0);
				else if(old_i!=i) matrix.row_idx.push_back(matrix.value.size()-1);
				old_i=i;
			}
		}
	}
	return matrix;
}


//changes a CSR-matrix into a normal matrix
//in this case we assume a square-matrix
vector <vector<double>> createNormal(CSR matrix){
	vector <vector<double>> normal;
	int size=matrix.row_idx.size();
	normal.resize(size,vector<double>(size,std::numeric_limits<double>::quiet_NaN()));
	for (int i=0;i<size;i++){
		if (i==size-1){ 
			for (int j=matrix.row_idx[i];j<matrix.value.size();j++){
				normal[i][matrix.col_idx[j]]=matrix.value[j];
			}
		}
		else {
			for (int j=matrix.row_idx[i];j<matrix.row_idx[i+1];j++){
				normal[i][matrix.col_idx[j]]=matrix.value[j];
			}
		}
	}
	return normal;
}

//generates Output of a CSR matrix in it's  own form
void OutputCSR(CSR matrix){
	for (int i=0;i<matrix.value.size();i++) printf("%5.0f",matrix.value[i]);
	printf("\n");
	for (int i=0;i<matrix.col_idx.size();i++) printf("%5d",matrix.col_idx[i]);
	printf("\n");
	for (int i=0;i<matrix.row_idx.size();i++) printf("%5d",matrix.row_idx[i]);
	printf("\n\n\n");

}


/*int main(){

	return 0;
}*/