#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <assert.h>
#include "fibonacci.h"
using namespace std;



int main (){ /*tests all Fibonaccifunctions with asserts, the n in each comments shows the biggest n, which doesn't fail*/	/*test Fibonacci1, n=? (function is too slow)*/	assert(Fibonacci1(1)==Fibonacci6(1));	assert(Fibonacci1(3)==Fibonacci6(3));	assert(Fibonacci1(4)==Fibonacci6(4));	assert(Fibonacci1(10)==Fibonacci6(10));	assert(Fibonacci1(20)==Fibonacci6(20));	assert(Fibonacci1(25)==Fibonacci6(25));		/*test Fibonacci2, n=93*/	assert(Fibonacci2(2)==Fibonacci6(2));	assert(Fibonacci2(10)==Fibonacci6(10));	assert(Fibonacci2(40)==Fibonacci6(40));	assert(Fibonacci2(50)==Fibonacci6(50));	assert(Fibonacci2(80)==Fibonacci6(80));	assert(Fibonacci2(93)==Fibonacci6(93));			/*test Fibonacci3, n=93*/	assert(Fibonacci3(2)==Fibonacci6(2));	assert(Fibonacci3(10)==Fibonacci6(10));	assert(Fibonacci3(40)==Fibonacci6(40));	assert(Fibonacci3(50)==Fibonacci6(50));	assert(Fibonacci3(80)==Fibonacci6(80));	assert(Fibonacci3(93)==Fibonacci6(93));		/*test Fibonacci4, n=78*/	assert(Fibonacci4(2)==Fibonacci6(2));	assert(Fibonacci4(10)==Fibonacci6(10));	assert(Fibonacci4(40)==Fibonacci6(40));	assert(Fibonacci4(50)==Fibonacci6(50));	assert(Fibonacci4(78)==Fibonacci6(78));		/*test Fibonacci41, n=78*/	assert(Fibonacci41(2)==Fibonacci6(2));	assert(Fibonacci41(10)==Fibonacci6(10));	assert(Fibonacci41(40)==Fibonacci6(40));	assert(Fibonacci41(50)==Fibonacci6(50));	assert(Fibonacci41(78)==Fibonacci6(78));		/*test Fibonacci5, n=78*/	assert(Fibonacci5(2)==Fibonacci6(2));	assert(Fibonacci5(10)==Fibonacci6(10));	assert(Fibonacci5(40)==Fibonacci6(40));	assert(Fibonacci5(50)==Fibonacci6(50));	assert(Fibonacci5(78)==Fibonacci6(78));		return 0;} 