//This algorithm gets a Graph G=(V,E) represented with a matrix. The matrix will then be changed to a matrix which elements tell us the smallest/shortest path from one point to another.
//The difference to the Dijkstra-algorithm are the (possible) negative weights.
//Note that the given matrix will be handled as if it's directed and has only zeroes on the diagonal. NULLs will tell us that there is no direct connection between two points.
//In the beginning every point has the distance 0 to itself, therefore the diagonal is zero.
//Due to the fact of the negative weights, the zeroes on the diagonal may change to negative numbers in the algorithm. In this case we have at least one negative cycle inside the graph.
#include <vector>
#include <stdio.h>

using namespace std;
//TODO
//complexity+space
double NO=0.01; //global variable that indicates "no connection"

//checks if the given matrix represents a graph <=> matrix is square and the elements at the diagonal are 0
//necessary? (Con: additional time for computing, especially because we go along the matrix col-wise and row-wise => bad for cache)
/*template <typename T>
void isGraph(vector<vector<T>> matrix){
	assert(matrix.size()==matrix[0].size());  //check if matrix is square
	for (int i=0;i<matrix.size();i++){
		for(int j=i;j<matrix.size();j++){
			if (i==j) assert(matrix[i][j]==0);   //check if diagonal=0
		}
	}
}*/

//This void changes the paths from start to every other point, so that (if there exists a connection) in the end the shortest path from start to every connected point is shown.
template <typename T>
void newPaths(vector<vector<T>>& graph, int start){
	for (int i=0;i<graph.size();i++){
		if(graph[start][i]!=NO){    //Check if you need the path from i to other points. If start and i are not connected then ignore 
			for (int j=0;j<graph.size();j++){
				if(graph[i][j]!=NO){										                 //
					if(graph[start][j]>graph[i][j]+graph[start][i] || graph[start][j]==NO){  //together in one if? Don't know how to say (maybe if(graph[i][j]!=NULL && (graph[start][j]<graph[i][j] || graph[start][j]==NULL)) ?)
						graph[start][j]=graph[i][j]+graph[start][i];
					}
				}
			}
		}
	} 

}


/*template <typename T>
void newGraph(vector<vector<T>>& graph){


}


template <typename T>
void checkNeg(vector<vector<T>>& graph){
	char info="Es existiert kein negativer Zyklus.";
	for (int i=0;i<graph.size;i++){
		for (int j=0;j<graph.size();j++){
			graph[i][i]=graph[i][j]+graph[j][i];
			if(graph[i][i]<0){
				info="Es existiert ein negativer Zyklus."  
					//TODO
					//break? if yes change if-question (less running time for writing graph[i][i]); else change every point connected to i (including i) to number indicating the negative infinity (maybe NULL)
			}
		}
	}
}*/

//simple Algorithm to show the matrix graph in a proper format
template <typename T>
void Output(vector<vector<T>> graph){ 
	int j=graph.size();
	for (int i=0;i<j;i++){
		for (int k=0;k<j;k++){
			if (graph[i][k]==NO) printf("%5s ","N");
			else printf("%5.0f ",graph[i][k]);
		}
		printf("\n");
	}
	printf("\n \n");
}


int main(){

	//testing purposes
	vector <vector<double>> graph; 
	int V = 3;
	graph.resize(V,vector<double>(V,NO));
	for (int i=0;i<V;i++){
		for (int k=0;k<V;k++){
			if (k==i) graph[i][k]=0;
			else if ((rand()%100)<=80) {
				int r=rand()%100;
				r=r-50;
				graph[i][k]=r;
			}
		}
	};
	Output(graph);
	newPaths(graph,0);
	Output(graph);
	return 0;
}