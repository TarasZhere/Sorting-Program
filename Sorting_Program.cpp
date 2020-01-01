/*
Taras Zherebetskyy

CSI 330

file:
  sortingProgram.cpp

Description:
  Program to implement:
  Insertion sort, Heapsort, Mergesort, and Quicksort
  base on the pseudocode in these slides.

Carateristics:
  The program compare the time run between the
  diferent sortings algorithm
*/

#include <iostream>
#include <ctime>
#include <chrono>

using namespace std::chrono;
using namespace std;

const int SIZE = 500; /* size of the array, change this number for diferent array size */

/* FUNCTION */
void copy_Array(int A[], int B[])
{
	for (int i = 0; i < SIZE; i++)
		A[i] = B[i];
}
void printArr(int arr[])
{
	for (int i = 0; i < SIZE; i++)
		cout << arr[i] << "  ";
	cout << endl;
}
void swap(int *A, int *B)
{
	auto temp = A;
	A = B;
	B = temp;
}

/*     PROTOTYPE FUNCTIONS     */

/* INSERTION SORTING */
void insertionSort(int arr[]);
/* HEAP SORTING */
void adjust(int[], int, int);
void heapSort(int[]);
/* MERGE SORTING */
void mergeSort(int[], int, int);
void merge(int[], int, int, int);
/* QUICK SORTING */
int partitioning(int[], int, int);
void quick(int[], int, int);
void quickSort(int[]);

/* MAIN FUNCTION */
int main()
{
	int arr[SIZE];

	srand(time(0));
	/* Giving random values to the array */
	for (int i = 0; i < SIZE; i++)
		arr[i] = ((rand() % 1000));

	int arr_Insertion[SIZE], arr_Heap[SIZE], arr_Merge[SIZE], arr_Quick[SIZE];
	/* COPYING ARRAYS */
	copy_Array(arr_Insertion, arr);
	copy_Array(arr_Heap, arr);
	copy_Array(arr_Merge, arr);
	copy_Array(arr_Quick, arr);


	cout << "Printing the not sorted array:" << endl;
	printArr(arr);

	cout << "Performing Insertion Sort:" << endl;
	auto start = high_resolution_clock::now();
	insertionSort(arr_Insertion);
	auto stop = high_resolution_clock::now();
	cout << "Time taken for sorting: " << time << " ms." << endl << endl;

	cout << "Performing Heap Sort:" << endl;
	start = high_resolution_clock::now();
	heapSort(arr_Heap);
	stop = high_resolution_clock::now();
	cout << "Time taken for sorting: " << time << " ms." << endl << endl;

	cout << "Performing Merge Sort:" << endl;
	start = high_resolution_clock::now();
	mergeSort(arr_Merge, 0, SIZE - 1);
	printArr(arr_Merge);
	stop = high_resolution_clock::now();
	cout << "Time taken for sorting: " << time << " ms." << endl << endl;

	cout << "Performing Quick Sort:" << endl;
	start = high_resolution_clock::now();
	quickSort(arr_Quick);
	stop = high_resolution_clock::now();
	cout << "Time taken for sorting: " << time << " ms." << endl << endl;


	system("pause");
	return NULL;
}

/* INSERTION SORTING */
void insertionSort(int arr[])
{
	int key;
	int j;
	for (int i = 1; i < SIZE; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && key < arr[j])
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}

	printArr(arr);
}

/* HEAP SORTING */
void adjust(int arr[], int n, int i)
{
	int largest = i;
	int L = 2 * i + 1;
	int R = 2 * i + 2;

	if (L < n && arr[L] > arr[largest])
		largest = L;

	if (R < n && arr[R] > arr[largest])
		largest = R;

	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		adjust(arr, n, largest);
	}
}

void heapSort(int arr[])
{
	int n = SIZE;
	for (int i = n / 2 - 1; i >= 0; i--)
		adjust(arr, n, i);

	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		adjust(arr, i, 0);
	}

	printArr(arr);
}

/* MERGE SORTING */
void merge(int arr[], int start, int mid, int end)
{
	int *temp = new int[end - start + 1];

	int i = start, j = mid + 1, k = 0;

	while (i <= mid && j <= end) {
		if (arr[i] <= arr[j]) {
			temp[k] = arr[i];
			k += 1; i += 1;
		}
		else {
			temp[k] = arr[j];
			k += 1; j += 1;
		}
	}

	while (i <= mid)
	{
		temp[k] = arr[i];
		k += 1; i += 1;
	}

	while (j <= end)
	{
		temp[k] = arr[j];
		k += 1; j += 1;
	}

	for (i = start; i <= end; i += 1)
	{
		arr[i] = temp[i - start];
	}

	free(temp);
	temp = NULL;
}

void mergeSort(int arr[], int start, int end) {

	if (start < end)
	{
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

/* QUICK SORTING */
int partitioning(int arr[], int start, int end)
{
	int pivot = arr[end], index = start;

	for (int j = start; j < end; j++)
	{
		if (arr[j] <= pivot)
		{
			swap(arr[j], arr[index]);
			index++;
		}
	}
	swap(arr[index], arr[end]);
	return index;
}

void quick(int arr[], int start, int end)
{
	if (start < end)
	{
		int j = partitioning(arr, start, end);
		quick(arr, start, j - 1);
		quick(arr, j + 1, end);
	}
}

void quickSort(int arr[])
{
	quick(arr, 0, SIZE - 1);

	printArr(arr);
}
