
using namespace std;

//QuickSort
#include<algorithm>
#include<exception>
int Partition(int data[], int length, int start, int end)
{
	if ((data == NULL) || (length <= 0) || (start < 0) || (end >= length))
		throw new std::exception("Invalid Parameters");
	int _small = start - 1;
	for (int index = start; index < end; ++index)
	{
		if (data[index] < data[end])
		{
			++_small;
			if (_small != index)
				swap(data[index], data[_small]);
		}
	}
	++_small;
	swap(data[_small], data[end]);
	return _small;
}

void QuickSort(int data[], int length, int start, int end)
{
	if (start == end)
		return;
	int index = Partition(data, length, start, end);
	if (index > start)
		QuickSort(data, length, start, index - 1);
	if (index < end)
		QuickSort(data, length, index + 1, end);
}

//InsertionSort
void insertionSort(int data[], int length, int start, int end)
{
	for (int i = start; i <= end; ++i)
	{
		int* loc = upper_bound(data, data + i, data[i]);
		int x = data[i];
		int* p = data + i;
		while (p != loc)
		{
			*p = *(p - 1);
			--p;
		}
		*p = x;
	}
}

//bubble sort
//void bubbleSort(int data[], int length, int start, int end)
//{
//	if (end == start)
//		return;
//	for (int i = start; i < end; ++i)
//	{
//		if (data[i]>data[i + 1])
//			swap(data[i], data[i + 1]);
//	}
//	bubbleSort(data, length, start, end - 1);
//}

void bubbleSort(int data[], int length, int start, int end)
{
	if ((data == NULL) || (length <= 0) || (start < 0) || (end >= length))
		throw new std::exception("Invalid Parameters");
	for (int i = end; i >= start; --i)
	{
		for (int j = start; j < i; ++j)
		{
			if (data[j]>data[j + 1])
				swap(data[j], data[j + 1]);
		}
	}
}

//selection sort
void selectionSort(int data[], int length, int start, int end)
{
	if ((data == NULL) || (length <= 0) || (start < 0) || (end >= length))
		throw new std::exception("Invalid Parameters");
	for (int i = start; i <= end; ++i)
	{
		int min_loc = i;
		for (int j = i; j <= end; ++j)
		{
			if (data[j] < data[min_loc])
				min_loc = j;
		}
		swap(data[i], data[min_loc]);
	}
}

//merge sort
void merge(int data[], int p, int m, int q)
{
	int* tmp = new int[q - m];
	memcpy(tmp, data + m + 1, (q - m)*sizeof(int));
	int j = q - m - 1;
	while ((m >= p) || (j >= 0)){
		if (m >= p){
			if (j >= 0){
				if (data[m] > tmp[j]){
					data[q] = data[m];
					--m;
				}
				else{
					data[q] = tmp[j];
					--j;
				}
			}
			else{
				data[q] = data[m];
				--m;
			}
		}
		else{
			data[q] = tmp[j];
			--j;
		}
		--q;
	}
	delete[] tmp;
}

void recursize_mergesort(int data[], int start, int end)
{
	if (start == end)
		return;
	if (end - start == 1){
		if (data[start] > data[end])
			swap(data[start], data[end]);
		return;
	}
	int middle = (start + end) / 2;
	recursize_mergesort(data, start, middle);
	recursize_mergesort(data, middle + 1, end);
	merge(data, start, middle, end);
}

void mergeSort(int data[], int length, int start, int end)
{
	if ((data == NULL) || (length <= 0) || (start < 0) || (end >= length))
		throw new std::exception("Invalid Parameters");
	recursize_mergesort(data, start, end);
}


//heap sort
void adjustHeap(int a[], int s, int e)	//s代表要调整的节点，e代表已经是堆的节点的最后一个节点
{
	int i = s, j = s * 2 + 1;
	while (j <= e)
	{
		if (j < e)
		{
			if (a[j]<a[j + 1])
				++j;
		}
		if (a[j] > a[i])
		{
			swap(a[j], a[i]);
			i = j;
			j = j * 2 + 1;
		}
		else
			break;
	}
}

void heapSort(int a[], int length)
{
	int n = (length - 2) / 2;
	for (int i = n; i >= 0; --i)
		adjustHeap(a, i, length - 1);
	int end = length - 1;
	for (int i = 0; i < length; ++i)
	{
		swap(a[0], a[end]);
		--end;
		adjustHeap(a, 0, end);
	}
}


//count sort
//void countSort(int a[], int length, int k)
//{
//	int* count = new int[k + 1];
//	memset(count, 0, (k + 1)*sizeof(int));
//	for (int i = 0; i < length; ++i)
//	{
//		++count[a[i]];
//	}
//	int n = 0;
//	for (int i = 0; i <= k; ++i)
//	{
//		if (count[i] != 0)
//		{
//			while (count[i] != 0)
//			{
//				a[n] = i;
//				++n;
//				--count[i];
//			}
//		}
//	}
//	delete[] count;
//}

void countSort(int a[], int length, int k)
{
	int* count = new int[k + 1];
	memset(count, 0, (k + 1)*sizeof(int));
	for (int i = 0; i < length; ++i)
		++count[a[i]];
	for (int i = 1; i < k + 1; ++i)
		count[i] += count[i - 1];
	int* b = new int[length];
	memcpy(b, a, length*sizeof(int));
	memset(a, 0, length*sizeof(int));
	for (int i = length - 1; i >= 0; --i)
	{
		a[count[b[i]] - 1] = b[i];
		--count[b[i]];
	}
	delete[] count;
	delete[] b;
}

//radix sort
void _countSort(int a[], int length, int k, int n)
{
	int* count = new int[k + 1];
	memset(count, 0, (k + 1)*sizeof(int));
	int x = k << n;
	for (int i = 0; i < length; ++i)
		++count[(a[i] & x) >> n];
	for (int i = 1; i < k + 1; ++i)
		count[i] += count[i - 1];
	int* b = new int[length];
	memcpy(b, a, length*sizeof(int));
	memset(a, 0, length*sizeof(int));
	for (int i = length - 1; i >= 0; --i){
		a[count[(b[i] & x) >> n] - 1] = b[i];
		--count[(b[i] & x) >> n];
	}
	delete[] count;
	delete[] b;
}

void radixSort(int a[], int length)
{
	for (int i = 0; i < 8; ++i)
		_countSort(a, length, 15, i * 4);
}