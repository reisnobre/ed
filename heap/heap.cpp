#include <iostream>
using namespace std;

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int *arr, int n, int i);
void heapSort(int arr[], int n);

int main(int argc, char const *argv[]) {
	int arr[] = {12, 11, 13, 5, 6, 7};
	int n = sizeof(arr)/sizeof(arr[0]) - 1;

	heapSort(arr, n);
	for (int i = 0; i < n; i++) std::cout << arr[i] << ' ';
	std::cout << '\n';
	return 0;
}


void heapify(int *arr, int n, int i) {
	int largest = i; // Initialize largest as root
	int l = 2*i; // left = 2*i + 1
	int r = 2*i + 1; // right = 2*i + 2
  // If left child is larger than root
  if (l < n && arr[l] > arr[largest]) largest = l;
  // If right child is larger than largest so far
  if (r < n && arr[r] > arr[largest]) largest = r;
  // If largest is not root
  if (largest != i) {
    swap(arr[i], arr[largest]);
    // Recursively heapify the affected sub-tree
    heapify(arr, n, largest);
  }
}

// main function to do heap sort
void heapSort(int arr[], int n) {
	// Build heap (rearrange array)
	for (int i = n / 2; i >= 0; i--) {
    heapify(arr, n, i);
  }

	// One by one extract an element from heap
	for (int i=n; i>=0; i--) {
		// Move current root to end
		swap(arr[0], arr[i]);
		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}
