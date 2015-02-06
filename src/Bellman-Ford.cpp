//This algorithm gets a Graph G=(V,E) represented with a matrix. The matrix will then be changed to a matrix which elements tell us the smallest/shortest path from one point to another.
//The difference to the Dijkstra-algorithm are the (possible) negative weights.
//Note that the given matrix will be handled as if it's directed and has only zeroes on the diagonal. Certain values will tell us that there is no direct connection between two points. (see below)
//In the beginning every point has the distance 0 to itself, therefore the diagonal is zero.
//Due to the fact of the negative weights, the zeroes on the diagonal may change to negative numbers in the algorithm. In this case we have at least one negative cycle inside the graph.

//Note that the check for NaN is different in VS and other compilers. So here we will check i==i, which returns false if i=NaN

//everytime the complexity is given, the value V indicates the number of points. The Value E indicates the number of edges
//if O(E/V) shows up: This indicates O(average of the edges, which meet at one point)
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <limits>
#include "Bellman.h"

using namespace std;

//This void changes the paths from start to every other point, so that (if there exists a connection) in the end the shortest path from start to every connected point is shown.
//runs in O(V^2)
void newPaths(vector<vector<double>>& graph, unsigned long start){
	unsigned long size=graph.size();
	for (unsigned long next=0;next<size;next++){
		if(graph[start][next]==graph[start][next]){    //Check if you need the path from i to other points. If start and i are not connected then ignore 
			for (unsigned long end=0;end<size;end++){
				if(graph[next][end]==graph[next][end]){										                 //
					if(graph[start][end]>graph[next][end]+graph[start][next] || graph[start][end]!=graph[start][end]){ 
						if (graph[start][end]!=graph[start][end] && end<next) {
							graph[start][end]=graph[next][end]+graph[start][next];
							next=end-1;														//if end was before next and the path from start to end didn't exist, we also have to check the paths from start over next
							break;															//Note that this means extra work, because we will check next again, but in the worst case the work of the double-loop goes from O(n^2) to O(2*n^2)
						}else graph[start][end]=graph[next][end]+graph[start][next];
					}
				}
			}
		}
	} 

}

//Nothing special, just uses newPaths on the whole graph
//runs in O(V^3) => O(V* (complexity of newPaths()) )
void newGraph(vector<vector<double>>& graph){
	unsigned long size=graph.size();
	for (unsigned long i=0; i<size;i++) newPaths(graph,i);
}



//if start has the value -INF, this function changes every successive point to -INF. This includes graph[start][start].
//runs in O(V)
void makeInf(vector<vector<double>>& graph,unsigned long start){
	if (graph[start][start]!=-std::numeric_limits<double>::infinity()) return;
	unsigned long size=graph.size();
	for (unsigned long j=0;j<size;j++){
		if (graph[start][j]==graph[start][j]){
			graph[start][j]=-std::numeric_limits<double>::infinity();
		} 
	}
}

//This Algo checks if there exists a negative cycle in the graph, by adding the path from a point i to a point j and then backwards.
//In addition it changes (with makeInf() ) all related points to -INF)
//runs in O(V^3) => O(V^2 * (complexity of makeInf))
bool checkNeg(vector<vector<double>>& graph){
	bool info=false;
	unsigned long size=graph.size();
	for (unsigned long i=0;i<size;i++){
		for (unsigned long j=0;j<size;j++){
			if (graph[i][j]==graph[i][j] && graph[j][i]==graph[j][i]){
				if(graph[i][j]+graph[j][i]<0 || graph[j][i]==-std::numeric_limits<double>::infinity() || graph[i][j]==-std::numeric_limits<double>::infinity()){
					info=true;
					graph[i][i]=-std::numeric_limits<double>::infinity();
					makeInf(graph,i);
				}
			}
		}
	}
	return info;
}

//simple Algorithm to show the matrix graph in a proper format
//runs in O(V^2)
void Output(vector<vector<double>> graph){ 
	unsigned long size=graph.size();
	for (unsigned long i=0;i<size;i++){
		for (unsigned long k=0;k<size;k++){
			if (graph[i][k]!=graph[i][k]) printf("%5s ","N");
			else if (graph[i][k]==-std::numeric_limits<double>::infinity()) printf ("%5s ", "-INF");
			else	printf("%5.0f ",graph[i][k]);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

//changes a normal matrix into a CRS-Matrix
//note that it's not necessary to check if one row of the original mtraix is empty, because the elements on the diagonal are never empty.
//runs in O(V^2)
CRS createCRS(vector<vector<double>> graph){
	CRS matrix;
	unsigned long old_i=0;
	for (unsigned long i=0;i<graph.size();i++){
		for (unsigned long k=0;k<graph.size();k++){
			if (graph[i][k]==graph[i][k]) {
				matrix.value.push_back(graph[i][k]);
				matrix.row_idx.push_back(k);
				if(matrix.col_idx.size()==0) matrix.col_idx.push_back(0);
				else if(old_i!=i) matrix.col_idx.push_back(matrix.value.size()-1);
				old_i=i;
			}
		}
	}
	return matrix;
}


//changes a CRS-matrix into a normal matrix
//in this case we assume a square-matrix
//runs in O(V * E/V) = O(E)
vector <vector<double>> createNormal(CRS matrix){
	vector <vector<double>> normal;
	unsigned long size=matrix.col_idx.size();
	normal.resize(size,vector<double>(size,std::numeric_limits<double>::quiet_NaN()));
	for (unsigned long i=0;i<size;i++){
		int ending = matrix.value.size();
		if (i<size-1) matrix.col_idx[i+1];
		for (unsigned long j=matrix.col_idx[i];j<ending;j++){
			normal[i][matrix.row_idx[j]]=matrix.value[j];
		}
	}
	return normal;
}

//generates Output of a CRS matrix in it's  own form
//runs in O(V+E+E)
void OutputCRS(CRS matrix){
	for (unsigned long i=0;i<matrix.value.size();i++) printf("%5.0f",matrix.value[i]);
	printf("\n");
	for (unsigned long i=0;i<matrix.row_idx.size();i++) printf("%5d",matrix.row_idx[i]);
	printf("\n");
	for (unsigned long i=0;i<matrix.col_idx.size();i++) printf("%5d",matrix.col_idx[i]);
	printf("\n\n\n");

}

//checks a CRS-matrix if start reaches end directly, if yes changes idx to that index
//if not changes idx to the index where this path belongs
// runs in O(E/V)
bool XreachesY(unsigned long start,unsigned long end,unsigned long& idx,CRS graph){
	unsigned long size=graph.col_idx.size();
	unsigned long ending = graph.row_idx.size();
	if (start<size-1) ending=graph.col_idx[start+1];
	idx=graph.col_idx[start];
	for (unsigned long ptr=graph.col_idx[start]; ptr<ending; ptr++){
		unsigned long test=graph.row_idx[ptr];
		if (test<end) idx=ptr;													//in case there's no connection: we set idx
		if (graph.row_idx[ptr]==end){
			idx=ptr;
			return true;
		}
	}
	return false;
}

//newPaths for CRS
//O(V*E/V)=O(E)
void newPathsCRS(CRS& graph, unsigned long start){
	unsigned long size=graph.col_idx.size();
	unsigned long ending1=graph.row_idx.size();
	if (start<size-1) ending1=graph.col_idx[start+1];

	for (unsigned long next_point=graph.col_idx[start];next_point<ending1; next_point++){    //check every point, which is reachable from start
		unsigned long ending2=graph.row_idx.size();
		if (graph.row_idx[next_point]<size-1) ending2=graph.col_idx[graph.row_idx[next_point]+1];

		for(unsigned long ptr = graph.col_idx[graph.row_idx[next_point]]; ptr<ending2; ptr++){    //check every point, which is reachable from next_point
			unsigned long end=graph.row_idx[ptr];
			unsigned long idx=0;
			double sum=graph.value[next_point] + graph.value[ptr];   //sum = path from start to next_point + path from next_point to end
			if (XreachesY(start,end,idx,graph)){
				if (graph.value[idx]>sum) graph.value[idx]=sum;
			}else {
				for (unsigned long i=start+1;i<size;i++) graph.col_idx[i]++;
				++ending2;
				++ending1;
				if(idx<next_point) ++next_point;	
				graph.row_idx.insert(graph.row_idx.begin()+idx,end);
				graph.value.insert(graph.value.begin()+idx,sum);
				if (graph.row_idx[next_point]>end){						//see newPaths: if the new path is before next_point we have to check this also
					next_point=idx-1;
					break;
				}
			}
		}
	}
}


//newGraph for CRS
// runs in O(V* (complexity of newPathsCRS)) = O(V*E)
void newGraphCRS(CRS& graph){
	unsigned long size=graph.col_idx.size();
	for (unsigned long i=0;i<size;i++) newPathsCRS(graph,i);
}



//newGraph for CRS, which, if too many paths exist, will change the CRS to a matrix.
// runs in O(V* (complexity of newPathsCRS)) = O(V*E)
void newGraphCRS2(CRS& graph){
	unsigned long size=graph.col_idx.size();
	unsigned long critical_length = size / 10 ;     //at this point we will change the function to newGraph()
	for (unsigned long i=0;i<size;i++) {
		newPathsCRS(graph,i);
		if ((graph.value.size()/ size) >= critical_length){
			vector <vector<double>> matrix;
			matrix = createNormal(graph);
			for (unsigned long j=i;j<size;j++) newPaths(matrix,j);
			graph=createCRS(matrix);
			return;
		}
	}
}




//if start has the value -INF, this function changes every successive point to -INF
// runs in O(V)
void makeInfCRS(CRS& graph,unsigned long start,unsigned long self_path){
	if (graph.value[self_path]!=-std::numeric_limits<double>::infinity()) return;
	unsigned long size=graph.col_idx.size();
	unsigned long ending=graph.row_idx.size();
	if(start<size-1) ending=graph.col_idx[start+1];
	for (unsigned long j=graph.col_idx[start];j<ending;j++){
		graph.value[j]=-std::numeric_limits<double>::infinity();
	}
}

//This Algo checks if there exists a negative cycle in the graph, by adding the path from a point i to a point j and then backwards. This includes graph[start][start].
//In addition it changes (with makeInfCRS() ) all related points to -INF)
// runs in O( V*E*(complexity of makeInfCRS)) = O(V^2*E) 
bool checkNegCRS(CRS& graph){
	bool info=false;
	unsigned long size=graph.col_idx.size();
	for (unsigned long i=0;i<size;i++){
		unsigned long ending=graph.row_idx.size();
		if(i<size-1) ending=graph.col_idx[i+1];
		for (unsigned long j=graph.col_idx[i];j<ending;j++){
			unsigned long k=graph.col_idx[graph.row_idx[j]];
			while (graph.row_idx[k]<i && k<graph.row_idx.size()-1) k++; //checks if the path from j to i exists
			if(graph.row_idx[k]==i){
				if(graph.value[j]+graph.value[k]<0 || graph.value[j]==-std::numeric_limits<double>::infinity() || graph.value[k]==-std::numeric_limits<double>::infinity()){
					info=true;
					k=graph.col_idx[i];
					while (graph.row_idx[k]<i) k++;   //k now shows the index for the path from i to itself (the points which are 0 by default)
					graph.value[k]=-std::numeric_limits<double>::infinity();
					makeInfCRS(graph,i,k);
				}
			}
		}
	}
	return info;
}

//simple use of two functions
void All(vector <vector<double>>& graph){
	newGraph(graph);
	checkNeg(graph);
}

void AllCRS(CRS& graph){
	newGraphCRS(graph);
	checkNegCRS(graph);
}

void AllCRS2(CRS& graph){
	newGraphCRS2(graph);
	checkNegCRS(graph);
}

//this one first uses the format of CRS. This format is more effective than the matrix-format, but needs more space
// so the new variable critical_length is needed. This variable indicates at which point it is more effective to use the amtrix-format
void AllOpt(vector <vector<double>>& graph){
	CRS matrix=createCRS(graph);
	unsigned long size = matrix.col_idx.size();
	unsigned long critical_length= size / 10;   //further testing needed
	bool test = true;
	for (unsigned long i=0; i<size; i++){
		if(test){ 
			newPathsCRS(matrix,i);
			if ((matrix.value.size()/ size) >= critical_length){
				graph=createNormal(matrix);
				test=false;
			}
		}else newPaths(graph,i);
	}
	if (test) {
		checkNegCRS(matrix);
		graph=createNormal(matrix);
	}else checkNeg(graph);
}
	


/*int main(){

	return 0;
}*/