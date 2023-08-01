#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void merge(int pData[], int low, int mid, int high);
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
	if (l < r) {
		int mid = (l + r) / 2;

		mergeSort(pData, l, mid);
		mergeSort(pData, mid + 1, r);
		merge(pData, l, mid, r);
	}
}

void merge(int pData[], int low, int mid, int high) {
	int i, j, k;
	int leftSize = mid - low + 1;
	int rightSize = high - mid;

	int* left = (int*)malloc(sizeof(int) * leftSize);
	extraMemoryAllocated += sizeof(left);
	int* right = (int*)malloc(sizeof(int) * rightSize);
	extraMemoryAllocated += sizeof(right);

	for (i = 0; i < leftSize; i++)
		left[i] = pData[i + low];
	for (j = 0; j < rightSize; j++)
		right[j] = pData[mid + 1 + j];

	i = j = 0;
	k = low;

	while (i < leftSize && j < rightSize) {
		if (left[i] <= right[j]) {
			pData[k] = left[i];
			i++;
		}
		else {
			pData[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < leftSize)
		pData[k++] = left[i++];
	while (j < rightSize)
		pData[k++] = right[j++];

	free(left);
	free(right);
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {
	int swap;
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--) {
			if (pData[j - 1] > pData[j]) {
				swap = pData[j];
				pData[j] = pData[j - 1];
				pData[j - 1] = swap;
			}
			else
				break;
		}
	}

}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
	int swap;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (pData[j] > pData[j + 1]) {
				swap = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = swap;
			}
		}
	}

}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {
	int index, swap;
	for (int i = 0; i < n - 1; i++) {
		index = i;
		for (int j = i; j < n; j++) {
			if (pData[index] > pData[j])
				index = j;
		}
		swap = pData[i];
		pData[i] = pData[index];
		pData[index] = swap;
	}


}

// parses input file to an integer array
int parseData(char* inputFileName, int** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (int*)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		extraMemoryAllocated += sizeof(*ppData);

		for (int i = 0; i < dataSz; i++)
			fscanf(inFile, "%d ", (*ppData + i));
	}

	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i = 0; i < 100; ++i)
	{
		printf("%d ", pData[i]);
	}
	printf("\n\t");

	for (i = sz; i < dataSz; ++i)
	{
		printf("%d ", pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
	double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt" };

	for (i = 0; i < 3; ++i)
	{
		int* pDataSrc, * pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);

		if (dataSz <= 0)
			continue;

		pDataCopy = (int*)malloc(sizeof(int) * dataSz);

		printf("---------------------------\n");
		printf("Dataset Size : %d\n", dataSz);
		printf("---------------------------\n");

		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.3lf\n", cpu_time_used);
		printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
		printArray(pDataCopy, dataSz);




		free(pDataCopy);
		free(pDataSrc);
	}

}