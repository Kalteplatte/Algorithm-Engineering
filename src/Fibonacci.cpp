#include <vector>
#include <stdio.h>
#include <math.h>
//#include <chrono>
#include <iostream>
#include <assert.h>
using namespace std;


unsigned long Fibonacci1 (int n){        //recursive function
	assert (n>=0);
	if (n<=1)	return n;
	return Fibonacci1(n-1)+Fibonacci1(n-2);
}


unsigned long Fibonacci2 (int n){      //function with linear time and linear memory
	assert (n>=0);
	if(n<=1)	return n;
	vector <unsigned long> fib (n+1);
	fib[0]=0;
	fib[1]=1;
	int i=2;

	while(i<=n){
		fib[i]=fib[i-1]+fib[i-2];		i++;	}
	return fib[n];
}


unsigned long Fibonacci3 (int n){  //function with linear time and constant memory
	assert (n>=0);
	if(n<=1)	return n;
	int fib [3];
	fib[0]=0;
	fib[1]=1;
	int i;
	for(i=2; i<n+1;i++){
		fib[2]=fib[1]+fib[0];
		fib[0]=fib[1];
		fib[1]=fib[2];
	}
	return fib[2];
}
vector<vector<double>> IdentityM(vector<vector<double>> v){ //returns an identitymatrix with the dimensions of v
	assert(v.size()==v[0].size());                          //v.size = number of rows in v ;   v[0].size = number of columns in v[0] <=> number of columns in v
	unsigned int i;
	unsigned int j;
	for (i=0; i<v.size(); i++){
		for (j=0; j<v.size();j++){
			if(i==j) v[i][j]=1;
			else v[i][j]=0;
		}
	}
	return v;
}

vector<vector<double> > MatrixMult(vector<vector<double> > v, vector<vector<double> > w){ //multiplies two matrix', if the dimensions are correct
	assert(v.size()==w[0].size());                                                        //check if the dimensions are correct
	vector<vector<double>> x;
	vector< vector<double> > erg;
	erg.resize( v.size() , vector<double>( w[0].size() , 0 ) );                        // setting a matrix called 'erg' with 0 at every position and the correct dimensions
	unsigned int i;
	unsigned int j;
	unsigned int k;
	for (i=0; i<v[0].size() ;i++){
		for(j=0; j< w.size();j++){
			for(k=0; k<v.size(); k++){
				erg[i][j]=erg[i][j]+v[i][k]*w[k][j];
			}
		}
	}

	return erg;
}

vector<vector<double> > ExponentiationBySquaring(vector<vector<double> > v, double n){ // function that runs an exponentation in logarithmic time
	if (n==0) return IdentityM(v); 
	if (n==1) return v;
	int m =static_cast<int>(n);
	if ((m%2)==0) return ExponentiationBySquaring(MatrixMult(v,v), n/2.0);
	return MatrixMult(v,ExponentiationBySquaring(MatrixMult(v,v), (n-1)/2.0));
}

unsigned long Fibonacci4(int n){ // function that uses a matrix to get the Fibonaccinumbers and runs in logarithmic time and logarithmic memory
	assert (n>=0);
	if (n<=1) return n;
	vector< vector<double> > fib;
	fib.resize( 2 , vector<double>( 2 , 1 ) );       // setting the Fibonacci Matrix fib = |0 1| , note that the n-th Fibonaccinumber is also the number at fib^n [0][1]
	fib[0][0]=0;                                     //                                    |1 1|                                                         (or fib^n [1][0], because fib is symmetric)
	unsigned long Output = (unsigned long)ExponentiationBySquaring(fib,n)[0][1];
	return Output;
}

unsigned long Fibonacci5(int n){ // function that uses only one term, which was generated by diagonalyzing the matrix from Fibonacci4, runs in constant time and constant memory
	assert (n>=0);
	if (n<=1) return n;
	double lambda = (1+ sqrt(5.0))/2.0;
	double nlambda = pow(lambda,n);
	double erg;
	erg = floor(nlambda/sqrt(5.0)+0.5);  // single term, that returns the n-th fibonaccinumber. this term is calculated by diagonalyzing the Matrix from Fibonacci4()
	return (unsigned long)erg;
}

unsigned long Fibonacci6(int n){  //Simple LookupTable for Fibonaccinumbers with open end, only limited by my own lazyness
	if(n<=1) return n;
	unsigned long lookup_table[]={0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976,7778742049,12586269025,20365011074,32951280099,53316291173,86267571272,139583862445,225851433717,365435296162,591286729879,956722026041,1548008755920,2504730781961,4052739537881,6557470319842,10610209857723,17167680177565,27777890035288,44945570212853,72723460248141,117669030460994,190392490709135,308061521170129,498454011879264,806515533049393,1304969544928657,2111485077978050,3416454622906707,5527939700884757,8944394323791464,14472334024676221,23416728348467685,37889062373143906,61305790721611591,99194853094755497,160500643816367088,259695496911122585,420196140727489673,679891637638612258,1100087778366101931,1779979416004714189,2880067194370816120,4660046610375530309,7540113804746346429,12200160415121876738};
	assert (n<(sizeof(lookup_table)/sizeof(lookup_table[0])));
	return lookup_table[n];
}

//auto MeasureTime(int n, int i){  //Measures the time of a Fibonacci-function, which calculates the n-th Fibonaccinumber, 'i' will tell which function to use 
//	assert(1<=i<=6);
	
//	auto start = chrono::high_resolution_clock::now();

//    auto stop = chrono::high_resolution_clock::now();    
//    auto elapsed = stop - start;
//    auto us = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();  //
//	return us;
//}

__int64 MeasureCycles ( unsigned int low, unsigned int high )   //function that measures the current CPU-cycles
{
		_asm
		{
			_emit 0x0f	// insert rtdsc opcode
			_emit 0x31
			mov high , edx
			mov low , eax
		}		
	return ( (__int64) high << 32 ) + low;
}

int main(){
	unsigned int high = 0;
	unsigned int low = 0; 
	double CycleStart = GetCPUCount ( low, high );
 
	Fibonacci1(5);
 
	double CycleEnd = GetCPUCount ( low, high );
	cout << CycleStart - CycleEnd;
	int j;
	cin >> j;
	return 0;
}