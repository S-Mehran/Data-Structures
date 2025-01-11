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
		if (isFull()) {
			rearNode->next = newNode;
		}
		else {
			frontNode = newNode;
		}
		rearNode = newNode;
		count++;
	}

	void dequeue() {
		if (isEmpty()) {
			cout << "Queue is empty." << endl;
			return;
		}
		Node* temp = frontNode;
		frontNode = frontNode->next;
	//	if (!frontNode) {
//			rearNode = nullptr;
//		}
		delete temp;
		count--;
	}

	bool isFull() {
		return false;
	}

	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}

	int front() {
		if (isEmpty()) {
			cout << "Queue is Empty" << endl;
			return 0;

		}
		return frontNode->data;
	}

	T rear() {
		if (!isEmpty()) {
			return rearNode->data;
		}
		else
		{
			cout << "Queue is Empty" << endl;
		}
	}
};



int main() {
	Queue<int> queue1;
	queue1.enqueue(10);
	queue1.enqueue(20);
	queue1.enqueue(30);
	cout << "Front: " << queue1.front() << endl;
	cout << "Rear: " << queue1.rear() << endl;
	cout << "Size: " << queue1.size() << endl;
	queue1.dequeue();
	cout << "Front after dequeue: " << queue1.front() << endl;
	return 0;
}
