#include <iostream>
#include <chrono> 
#define N 4

using namespace std;
using namespace std::chrono; 

int main() {
	int vector[N], matrix[N][N], output[N]; 

	auto start = high_resolution_clock::now();

		cout<<"matrix : \n"; 
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			matrix[i][j] = rand() % 10; 
			cout<<matrix[i][j]<<"\t"; 
		}
			cout<<endl; 
	}

		cout<<"vector : \n"; 
	for(int i = 0; i < N; i++) {
		vector[i] = rand() % 10;
		cout<<vector[i]<<"\t"; 
	}	
		cout<<endl; 

	#pragma omp parallel for 
	for(int col = 0; col < N; col++) {
		output[col] = 0; 

		for(int row = 0; row < N; row++) {
			output[col] += vector[row] * matrix[row][col];
		}
			cout<<endl;
	}

		cout<<"Result : ";
	for(int i = 0;  i < N; i++) {
		cout<<output[i]<<"\t"; 
	}
		cout<<endl; 

	auto end = high_resolution_clock::now();

	cout<<"Time required : "<<(duration_cast<milliseconds>(end - start).count())<<" ms."<<endl; 

	return 0;
}