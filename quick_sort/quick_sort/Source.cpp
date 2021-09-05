#include <iostream>
#include <time.h>
#include <omp.h>

template <class T>
void printArray(T* _arr, int _size)
{
	for (int i = 0; i < _size; ++i)
	{
		std::cout << _arr[i] << " ";
	}
	std::cout << "\n";
}

template <class T>
void quicksort(T* _arr, int _left, int _right)
{
	if (_arr)
	{
		if (_right - _left < 1) return;
		T& pivot = _arr[_left];
		T buf;
		int left_hold = _left;
		int right_hold = _right;
		while(_left < _right)
		{
			while ((_arr[_right] >= pivot) && (_left < _right))
			{
				--_right;
			}
			if (_left != _right)
			{
				++_left;
				while ((_arr[_left] <= pivot) && (_left < _right))
				{
					++_left;
				}
				buf = _arr[_left];
				_arr[_left] = _arr[_right];
				_arr[_right] = buf;
			}
		}
		buf = pivot;
		pivot = _arr[_right];
		_arr[_right] = buf;

		quicksort(_arr, left_hold, _left - 1);
		quicksort(_arr, _right + 1, right_hold);
	}
	else
	{
		throw "Incorrect initial values!";
	}
}

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

template <class T>
bool compare_arrays(T* _ar1, T* _ar2, int _size)
{
	int err = 0;
	for (int i = 0; i < _size; ++i)
	{
		if (_ar1[i] != _ar2[i]) ++err;
	}
	if (err) return false;
	else return true;
}

template <class T>
void selectionSort(T* _arr, size_t _size)
{
	int num = 0;
	for (size_t i = 0; i < _size; ++i)
	{
		num = i;
		for (size_t j = i + 1; j < _size; ++j)
		{
			if (_arr[j] < _arr[num]) num = j;
		}
		if (num != i) std::swap(_arr[i], _arr[num]);
	}
}


int main()
{
	srand(time(NULL));

	int size = 100000;

	int* arr = new int[size];
	int* arr_c = new int[size];
	int* arr_th = new int[size];

	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() % 100;
		arr_c[i] = arr[i];
		arr_th[i] = arr[i];
	}
	try
	{
		double tCustomStart = omp_get_wtime();
		quicksort(arr, 0, size-1);
		double tCustomEnd = omp_get_wtime();

		double tNativeStart = omp_get_wtime();
		qsort(arr_c, size, sizeof(int), compare);
		double tNativeEnd = omp_get_wtime();

		double tSelectionStart = omp_get_wtime();
		selectionSort(arr_th, size);
		double tSelectionEnd = omp_get_wtime();

		if (compare_arrays(arr, arr_c, size)) std::cout << "Success! Arrays are equal\n";
		else std::cout << "Arrays are not equal!\n";

		std::cout << "Native time: " << tNativeEnd - tNativeStart << "\n" << "Custom time: " << tCustomEnd - tCustomStart << "\n";
		std::cout << "Selection time: " << tSelectionEnd - tSelectionStart << "\n";
	}
	catch (const char* str)
	{
		std::cout << str << "\n";
	}
}