#include <iostream>
#include <omp.h> 
#include <chrono> 
#define N 20 

using namespace std;
using namespace std::chrono; 

int binary_search(int *arr, int start, int end, int key) {

	while(start <= end) {
		int mid = (start + end) / 2; 

		if(arr[mid] == key) {
			return mid; 
		}
 
		if(arr[mid] < key) {
			start = mid; 
		} else {
			end = mid; 
		}
	}
	return -1; 
}

int main() {
	
	int arr[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; 

	int num_threads = omp_get_num_threads(); 
	int blockSize = N / num_threads; 
	int key = 10; 

	auto start = high_resolution_clock::now();

	#pragma omp parallel for 
	for(int i = 0; i < num_threads; i++) {
		int idx = binary_search(arr, blockSize * i, blockSize * i + blockSize - 1, key); 
		if(idx != -1) {
			cout<<"Element found at position "<<idx<<endl;
		}
	}

	auto end = high_resolution_clock::now();


	cout<<"Time required : "<<(duration_cast<milliseconds>(end - start).count())<<" ms."<<endl; 
	return 0;
}