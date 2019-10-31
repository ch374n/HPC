#include <iostream>
#include <chrono> 
#define N 4 
using namespace std;
using namespace std::chrono; 


int main() {
	
	int A[N][N], B[N][N], C[N][N]; 

	auto start = high_resolution_clock::now(); 

	cout<<"----- matrix A ------\n"; 

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			A[i][j] = rand() % 10; 
			cout<<A[i][j]<<"\t";	 
		}
			cout<<endl; 
	}

	cout<<"----- matrix B ------\n"; 

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			B[i][j] = rand() % 10; 
			cout<<B[i][j]<<"\t";	 
		}
			cout<<endl; 
	}


	#pragma omp parallel for
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			C[i][j] = 0; 

			for(int m = 0; m < N; m++) {
				C[i][j] += A[i][m] * B[m][j];
			}
		}
	}

	cout<<"----- Result ------\n"; 

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			cout<<C[i][j]<<"\t";	 
		}
			cout<<endl; 
	}

	auto end = high_resolution_clock::now(); 

	auto duration = duration_cast<milliseconds>(end - start); 

	cout<<"Time required : "<<duration.count()<<" ms."<<endl;

	return 0;
}