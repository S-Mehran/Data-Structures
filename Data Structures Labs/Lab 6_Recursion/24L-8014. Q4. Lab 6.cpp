#include <iostream>

using namespace std;

class LinkedList
{
	struct Node
	{
		int data;
		Node* next;

		Node(int value, Node* ptr)
		{
			data = value;
			next = nullptr;
		}

	};

	Node* head;
	void addElementAtEnd(Node*& head, int data)
	{
		if (head == nullptr)
		{
			head = new Node(data, nullptr);
			return;
		}
		if (head->next == nullptr)
		{
			head->next = new Node(data, nullptr);
		}
		else {
			addElementAtEnd(head->next, data);
		}
	}


	int sumList(Node* head)
	{
		if (head == nullptr)
		{
			return 0;
		}
		else
		{
			int prevSum = sumList(head->next);
			return head->data + prevSum;
		}
	}

	void printList(Node* head)
	{
		if (head == nullptr)
		{
			cout << "List is Empty" << endl;
		}
		while (head != nullptr)
		{
			cout << head->data << " ";
			head = head->next;
		}
		cout << endl;
	}

public:
	


	LinkedList()
	{
		head = nullptr;
	}

	void wrapinsert(int value)
	{
		return addElementAtEnd(head, value);
	}

	int wrapsum()
	{
		return sumList(head);
	}

	void wrapPrint()
	{
		return printList(head);
	}
};

int main()
{
//	Node* head = nullptr;

	//addElementAtEnd(head, 5);
	//addElementAtEnd(head, 10);
	//addElementAtEnd(head, 15);
	//addElementAtEnd(head, 20);
	//addElementAtEnd(head, 25);
	//cout << "Linked List:" << endl;
	//printList(head);

	//cout << "The sum of Elements is: ";
	//cout << sumList(head)<<endl;

	LinkedList list1;
	list1.wrapinsert(5);
	list1.wrapinsert(10);
	list1.wrapinsert(15);
	list1.wrapinsert(20);
	list1.wrapinsert(25);
	cout << "Linked List:" << endl;
	list1.wrapPrint();
	cout << "The sum of Elements is: ";
	cout << list1.wrapsum() << endl;
}
