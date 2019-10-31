#include <iostream>
#include <omp.h> 
#include <chrono> 
#define N 20 

using namespace std;
using namespace std::chrono; 

void merge_back(int *arr, int i, int j, int l, int m) {
	int _i = i, _m = m, k = 0; 
	int temp[1 << 10]; 	

	while(i <= j && l <= m) {
		if(arr[i] < arr[l]) {
			temp[k++] = arr[i++]; 
		} else {
			temp[k++] = arr[l++]; 
		}
	}

	while(i <= j) {
		temp[k++] = arr[i++]; 
	}

	while(l <= m) {
		temp[k++] = arr[l++]; 
	}

	for(int i = _i, z = 0; i <= _m; i++, z++) {
		arr[i] = temp[z]; 
	}
}


void merge_sort(int *arr, int start, int end) {
	if(start < end) {
		int mid = (start + end) / 2; 

		#pragma omp parallel sections 
		{
			#pragma omp section 
			{
				merge_sort(arr, start, mid); 
			}

			#pragma omp section 
			{
				merge_sort(arr, mid + 1, end); 
			}
		}

		merge_back(arr, start, mid, mid + 1, end); 
	}
}	

int main() {

	int arr[N]; 

	auto start = high_resolution_clock::now();

	cout<<"--------- Array before sorting ----------\n"; 

	for(int i = 0; i < N; i++) { 
		arr[i] = rand() % 1000; 
		cout<<arr[i]<<"\t"; 
	}		
		cout<<endl; 

	merge_sort(arr, 0, N - 1); 		

	cout<<"--------- Array after sorting ----------\n"; 

	for(int i = 0; i < N; i++) { 
		cout<<arr[i]<<"\t"; 
	}		
		cout<<endl; 


	auto end = high_resolution_clock::now();


	cout<<"Time required : "<<(duration_cast<milliseconds>(end - start).count())<<" ms."<<endl; 

	return 0;
}