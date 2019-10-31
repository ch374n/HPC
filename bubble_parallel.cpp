#include <iostream>
#include <omp.h> 
#include <chrono> 
#define N 20 

using namespace std;
using namespace std::chrono; 

void swap(int &i, int &j) {
	i ^= j; 
	j ^= i; 
	i ^= j; 
}

void bubble_sort(int *arr) {
	for(int i = 0; i < N; i++) {
		int start = i % 2; 

		#pragma omp parallel for 
		for(int j = start; j < N - 1; j += 2) {
			if(arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int main() {
	int arr[N]; 

	auto start = high_resolution_clock::now();

	cout<<"------------ Array before sorting ------------\n"; 

	for(int i = 0; i < N; i++) {
		arr[i] = rand() % 1000;
		cout<<arr[i]<<"\t"; 
	}	
		cout<<endl; 

	bubble_sort(arr); 

	cout<<"------------ Array after sorting ------------\n"; 

	for(int i = 0; i < N; i++) {
		cout<<arr[i]<<"\t"; 
	}	
		cout<<endl; 


	auto end = high_resolution_clock::now();


	cout<<"Time required : "<<(duration_cast<milliseconds>(end - start).count())<<" ms."<<endl; 

	return 0;
}