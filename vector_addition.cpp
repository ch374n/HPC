#include <iostream>
#include <omp.h> 
#include <chrono> 
#define N 100 

using namespace std;
using namespace std::chrono; 

int main() {
	
	int a[N], b[N], c[N]; 	

	auto start = high_resolution_clock::now();


	#pragma omp parallel for 
	for(int i = 0; i < N; i++) {
		a[i] = rand() % N; 
		b[i] = rand() % N; 
	}	
		cout<<endl; 


		
	cout<<"------ Vector C ---------\n";

	#pragma omp parallel for 
	for(int i = 0; i < N; i++) {
		c[i] = a[i] + b[i];
		cout<<a[i]<<" + "<<b[i]<<" = "<<c[i]<<endl;
	}	
		cout<<endl; 

	auto end = high_resolution_clock::now();

	cout<<"Time required : "<<(duration_cast<milliseconds>(end - start).count())<<" ms."<<endl; 

		
	return 0;
}