#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class minHeap
{
	T* heap;
	int capacity;
	int size;

	int parent(int i)
	{
		return ((i - 1) / 2);
	}

	int left(int i)
	{
		return (2 * i + 1);
	}

	int right(int i)
	{
		return (2 * i + 2);
	}

	void bubbleup(int i)
	{
		while (i != 0 && heap[parent(i)] > heap[i])
		{
			swap(heap[parent(i)], heap[i]);
			i = parent(i);
		}
	}

	void bubbleDown(int i)
	{
		int l = left(i);
		int r = right(i);
		int smallest = i;

		if (l < size && heap[smallest] > heap[l])
		{
			smallest = l;
		}
		if (r<size && heap[smallest] > heap[r])
		{
			smallest = r;
		}

		if (smallest != i)
		{
			swap(heap[smallest], heap[i]);
			bubbleDown(i);
		}

	}


public:
	minHeap(int cap)
	{
		capacity = cap;
		heap = new int[cap];
		size = 0;
	}

	minHeap(T* arr, int n)
	{
		capacity = n;
		
		heap = new int[n];
		for (int i = 0; i < n; i++)
		{
			heap[i] = arr[i];
		}
		size = n;
		buildminHeap();
	}


	void buildminHeap()
	{
		int index;
		/*for (index = size / 2 - 1; index >= 0; index--)
		{
			bubbleDown(index);
		}*/

		for (index = size - 1; index >= 0; index--)
		{
			swap(heap[0], heap[index]);
			bubbleDown(index);
		}

	}


	void insert(const T& x)
	{
		if (size >= capacity)
		{
			cout << "Heap is Full" << endl;
			return;
		}

		size++;
		int index = size - 1;
		heap[index] = x;
		bubbleup(index);
	}

	bool isEmpty()
	{
		return size == 0;
	}
	
	const T& getMin() const
	{
		return heap[0];
	}

	int deleteMin()
	{
		if (size == 0)
		{
			cout << "Heap is Empty" << endl;
			return -1;
		}
		if (size == 1)
		{
			size--;
			return heap[0];
		}
		int temp = heap[0];
		heap[0] = heap[size - 1];
		size--;
		bubbleDown(0);
		return temp;
	}





	void print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << heap[i] << "  ";
		}
		cout << endl;
	}

	bool deleteAll(int key)
	{
		if (size == 0)
		{
			return true;
		}
		int index = 0;
		for (int i = 0; i < size; i++)
		{
			if (heap[i] == key)
			{
				heap[i] = heap[size - 1];
				size--;
				index = i;
				
			}
			
		}
		bubbleDown(index);
		return true;

	}


};


void HeapSort(int* arr, int n, int sorting_Order)
{
	minHeap<int> newHeap(arr, n);

	if (sorting_Order == 1)
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = newHeap.getMin();
			newHeap.deleteMin();
		}
		/*for (int i = 0; i < n; i++)
		{
			newHeap[i] = arr[i];
		}*/
		cout << "Array after HeapSort (Ascending Order)" << endl;
		for (int i = 0; i < n; i++)
		{
			cout<<arr[i]<<"  ";
		}
		cout << endl;
		

	}

	if (sorting_Order == 0)
	{
		for (int i = n-1; i >= 0; i--)
		{
			arr[i] = newHeap.getMin();
			newHeap.deleteMin();
			
		}
		cout << "Array after HeapSort (Descending Order)" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << arr[i] << "  ";
		}
		cout << endl;
	}
}




int main()
{
	minHeap<int> heap2(50);
	heap2.insert(10);
	heap2.insert(30);
	heap2.insert(20);
	heap2.insert(5);
	heap2.insert(10);
	heap2.insert(27);
	cout << "Heap after Insertion" << endl;
	heap2.print();
	cout << "Heap after Delete All" << endl;
	heap2.deleteAll(10);
	heap2.print();
		
	
	
	int array[] = { 10, 4, 5, 30, 3, 300 };

		minHeap<int> obj(array, 6);
		cout << "Heap after Parametrized Constructor" << endl;
		obj.print();
		cout << "First, 2nd and 3rd Minimum" << endl;
		for (int i = 0; i < 3; ++i)
		{
			cout<< obj.getMin() << " ";
			obj.deleteMin();
		}
		cout << endl;
		
		int array1[] = { 10, 4, 5, 30, 3, 300 };
		cout << "Array before Heap Sort" << endl;
		for (int i = 0; i < 6; i++)
		{
			cout << array1[i] << "  ";
		}
		cout << endl;
		HeapSort(array1, 6, 1);
		

		HeapSort(array1, 6, 0);

		

		return 0;
	
}