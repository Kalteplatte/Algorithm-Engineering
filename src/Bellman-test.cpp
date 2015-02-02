#include <vector>
#include <stdio.h>
#include <assert.h>
#include <limits>
#include "Bellman.h"
using namespace std;


int main(){

	//testing purposes
	vector <vector<double>> graph; 
	int V = 5;
	graph.resize(V,vector<double>(V,std::numeric_limits<double>::quiet_NaN()));
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
	graph=createNormal(matrix);
	Output(graph);
	return 0;
}