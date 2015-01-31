//This algorithm gets a Graph G=(V,E) represented with a matrix. The matrix will then be changed to a matrix which elements tell us the smallest/shortest path from one point to another.
//The difference to the Dijkstra-algorithm are the (possible) negative weights.
//Note that the given matrix will be handled as if it's directed and has only zeroes on the diagonal. Certain values will tell us that there is no direct connection between two points. (see below)
//In the beginning every point has the distance 0 to itself, therefore the diagonal is zero.
//Due to the fact of the negative weights, the zeroes on the diagonal may change to negative numbers in the algorithm. In this case we have at least one negative cycle inside the graph.
#include <vector>
#include <stdio.h>
#include <assert.h>

using namespace std;
//TODO
//complexity+space
//CSR

double NO=0.01; //global variable, which indicates "no connection"
double N_INF=-0.01; //gloabal variable, which indicates that this point is part of a negative cycle


struct CSR{
	vector<double> value;
	vector<int> row_idx;
	vector<int> col_idx;
};

//This void changes the paths from start to every other point, so that (if there exists a connection) in the end the shortest path from start to every connected point is shown.
template <typename T>
void newPaths(vector<vector<T>>& graph, int start){
	int size=graph.size();
	for (int i=0;i<size;i++){
		if(graph[start][i]!=NO){    //Check if you need the path from i to other points. If start and i are not connected then ignore 
			for (int j=0;j<size;j++){
				if(graph[i][j]!=NO){										                 //
					if(graph[start][j]>graph[i][j]+graph[start][i] || graph[start][j]==NO){  //together in one if? Don't know how to say (maybe if(graph[i][j]!=NULL && (graph[start][j]<graph[i][j] || graph[start][j]==NULL)) ?)
						graph[start][j]=graph[i][j]+graph[start][i];
					}
				}
			}
		}
	} 

}

//Nothing special, just uses newPaths on the whole graph
template <typename T>
void newGraph(vector<vector<T>>& graph){
	int size=graph.size();
	for (int i=0; i<size;i++) newPaths(graph,i);
}



//if start has the value -INF, this function changes every successive point to -INF
template <typename T>
void makeInf(vector<vector<T>>& graph,int start){
	if (graph[start][start]!=N_INF) return;
	int size=graph.size();
	for (int j=0;j<size;j++){
		if (graph[start][j]!=NO){
			graph[start][j]=N_INF;
		} 
	}
}

//This Algo checks if there exists a negative cycle in the graph, by adding the path from a point i to a point j and then backwards.
//In addition it changes (with makeInf() ) all related points to -INF)
template <typename T>
bool checkNeg(vector<vector<T>>& graph){
	bool info=1;
	int size=graph.size();
	for (int i=0;i<size;i++){
		for (int j=0;j<size;j++){
			if (graph[i][j]!=NO && graph[j][i]!=NO){
				if(graph[i][j]+graph[j][i]<0 || graph[j][i]==N_INF || graph[i][j]==N_INF){
					info=0;
					graph[i][i]=N_INF;
					makeInf(graph,i);
				}
			}
		}
	}
	return info;
}

//simple Algorithm to show the matrix graph in a proper format
template <typename T>
void Output(vector<vector<T>> graph){ 
	int size=graph.size();
	for (int i=0;i<size;i++){
		for (int k=0;k<size;k++){
			if (graph[i][k]==NO) printf("%5s ","N");
			else if (graph[i][k]==N_INF) printf ("%5s ", "-INF");
			else	printf("%5.0f ",graph[i][k]);
		}
		printf("\n");
	}
	printf("\n \n");
}

//simply use all the functions together
template <typename T>
void All(vector<vector<T>>& graph){
	Output(graph);
	newGraph(graph);
	Output(graph);
	bool info=checkNeg(graph);
	Output(graph);
	test(graph);
}

//tests if all -INF's have -INF as successor
template <typename T>
void test(vector<vector<T>> graph){
	for (int i=0;i<graph.size();i++){
		for (int k=0;k<graph.size();k++){
			if (graph[i][i]==N_INF) assert(graph[i][k]==N_INF || graph[i][k]==NO);
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
			if (graph[i][k]!=NO) {
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

//generates Output of a CSR matrix in it's  own form
void OutputCSR(CSR matrix){
	for (int i=0;i<matrix.value.size();i++) printf("%5.0f",matrix.value[i]);
	printf("\n");
	for (int i=0;i<matrix.col_idx.size();i++) printf("%5d",matrix.col_idx[i]);
	printf("\n");
	for (int i=0;i<matrix.row_idx.size();i++) printf("%5d",matrix.row_idx[i]);
	printf("\n");

}


int main(){

	//testing purposes
	vector <vector<double>> graph; 
	int V = 5;
	graph.resize(V,vector<double>(V,NO));
	for (int i=0;i<V;i++){
		for (int k=0;k<V;k++){
			if (k==i) graph[i][k]=0;
			else if ((rand()%100)<=20) {
				int r=rand()%100;
				r=r-10;
				graph[i][k]=r;
			}
		}
	}
	CSR matrix=createCSR(graph);
	Output(graph);
	OutputCSR(matrix);
	return 0;
}