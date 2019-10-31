#include <iostream>
#include <chrono> 
#define N 100 

using namespace std;
using namespace std::chrono;

__global__ void max_kernel(int *arr, int *n) {
	int tid = threadIdx.x; 

	int start = *n * tid; 
	int end = *n * (tid + 1); 

	for(int i = start + 1; i < end; i++) {
		if(arr[start] < arr[i]) {
			arr[start] = arr[i]; 
		}
	}
}



int main() {
	
	int *dev_arr, *dev_n, *arr, n = 5; 
	int pass = 0; 
	auto start = high_resolution_clock::now();

	cudaMalloc(&dev_arr, sizeof(int) * N); 
	cudaMalloc(&dev_n, sizeof(int)); 

	cudaMemcpy(dev_arr, arr, sizeof(int) * N, cudaMemcpyHostToDevice); 
	cudaMemcpy(dev_n, &n, sizeof(int), cudaMemcpyHostToDevice); 

	int len = N; 

	while(len > n) {

		max_kernel<<<1, len / n>>>(dev_arr, dev_n); 

		cudaDeviceSynchronize(); 

		cudaMemcpy(arr, dev_arr, sizeof(int) * N, cudaMemcpyDeviceToHost); 


		cout<<"Pass : "<<pass++<<endl; 

		for(int i = 0; i < (len / n); i++) {
			arr[i] = arr[i * n];
			cout<<arr[i]<<"\t"; 
		}

		cudaMemcpy(dev_arr, arr, sizeof(int) * N, cudaMemcpyHostToDevice); 

		len /= n; 
	}

	for(int i = 1; i < len; i++) {
		if(arr[0] < arr[i]) {
			arr[0] = arr[i]; 
		}
	}

	cout<<"Max : "<<arr[0]<<endl; 

	auto end = high_resolution_clock::now();

	cout<<"Time required : "<<(duration_cast<milliseconds>(end - start).count())<<" ms."<<endl; 

	return 0;
}