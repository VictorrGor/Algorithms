#include <iostream>

template <class T>
int binary_search(T* _arr, int _size, T _el)
{
	if (_size && _arr)
	{
		bool flag = true;
		
		int low = 0;
		int high = _size - 1;
		int mid = _size / 2;
		while (low <= high)
		{
			if (_arr[mid] > _el)
			{
				high = mid - 1;
			}
			else if (_arr[mid] < _el)
			{
				low = mid + 1;
			}
			else
			{
				return mid;
			}
			mid = (high + low) / 2;
		}
		return -1;
	}
	else
	{
		throw "Incorrect values!\n";
	}
}

int main()
{
	int size = 10;
	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
	{
		arr[i] = i*10;
	}

	int res = binary_search<int>(arr, size, 5);
	if (res >= 0) std::cout << "Result is: " << res << std::endl;
	else std::cout << "There are no such element." << std::endl;
	
	delete[] arr;
}