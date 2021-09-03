#include <iostream>
#include <time.h>

template <class T>
void printArray(T* _arr, size_t _size)
{
	for (int i = 0; i < _size; ++i)
	{
		std::cout << _arr[i] << " ";
	}
	std::cout << "\n";
}


template<class T>
size_t findSmallest(T* _src, size_t _size)
{
	T min = _src[0];
	size_t num = 0;
	//flag = false;
	for (int j = 0; j < _size; ++j)
	{
		if (_src[j] < min)
		{
			//flag = true;
			num = j;
			min = _src[j];
		}
	}
	return num;
}

template<class T>
void selectionSort(T* _src, size_t _size)
{
	if (_src && _size)
	{

		bool flag = false;
		size_t num;
		T buf;

		for (int i = 0; i < _size; ++i)
		{
			num = findSmallest(_src + i, _size - i) + i;
			buf = _src[i];
			_src[i] = _src[num];
			_src[num] = buf;
		}
	}
	else
	{
		throw "Uncorrect values!";
	}
}

int main()
{
	srand(time(NULL));
	int size = 10;
	int* arr = new int[size];

	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand() % 100;
	}

	printArray(arr, size);
	selectionSort(arr, size);
	printArray(arr, size);

	delete[] arr;
}