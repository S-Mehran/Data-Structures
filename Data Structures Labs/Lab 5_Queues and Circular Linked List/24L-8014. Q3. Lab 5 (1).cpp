#include <iostream>

using namespace std;

#include <iostream>
using namespace std;


template <typename T>
class Queue {
private:
	struct Node {
	public:
		T data;
		Node* next;

		Node(T value)
		{
			data = value;
			next = nullptr;
		}

	};

	Node* frontNode;
	Node* rearNode;
	int count;

public:

	Queue()
	{
		frontNode = nullptr;
		rearNode = nullptr;
		count = 0;
	}


	void enqueue(T value) {
		Node* newNode = new Node(value);
		if (rearNode) {
			rearNode->next = newNode;
		}
		rearNode = newNode;
		if (!frontNode)
		{
			frontNode = newNode;
		}
		count++;
	}

	int dequeue() {
		if (!frontNode) {
			cout << "Queue is empty." << endl;
			return -1;
		}
		Node* temp = frontNode;
		int val = frontNode->data;
		frontNode = frontNode->next;
		if (!frontNode) {
			rearNode = nullptr;
		}
		delete temp;
		count--;
	}



	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}






	void Display()
	{
		Node* current = frontNode;
		while (current)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}



};



void rearrangeQueue(Queue<int>& q) {
	int size1 = q.size();
	if (size1 % 2 != 0)
	{
		return;
	}

	Queue<int> tempQueue;
	int half = size1 / 2;
	for (int i = 0; i < half; ++i) {
		tempQueue.enqueue(q.dequeue());
	}

	for (int i = 0; i < half; ++i) {
		q.enqueue(tempQueue.dequeue());
		if (!q.isEmpty())
		{
			q.enqueue(q.dequeue());
		}



	}
}
int main() {

	Queue<int> q;
	int arr[] = { 3,4,6,8,9,3,2,5 };

	for (int i = 0; i < 8; i++)
	{
		q.enqueue(arr[i]);
	}

	q.Display();

	rearrangeQueue(q);

	q.Display();
	return 0;
}
