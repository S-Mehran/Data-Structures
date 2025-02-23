#include <iostream>
using namespace std;

template <typename T>
class CLL
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(int value)
		{
			data = value;
			next = nullptr;
		}

	};

	Node* tail;

public:
	CLL()
	{
		tail = nullptr;
	}


	void insertatEnd(int value)
	{
		Node* newNode = new Node(value);
		if (tail == nullptr)
		{
			tail = newNode;
			newNode->next = tail;
		}

		else {
			Node* current = tail;
			while (current->next != tail)
			{
				current = current->next;
			}

			current->next = newNode;
			newNode->next = tail;
		}

	}

	void insertBefore(int v1, int v2)
	{
		Node* newNode = new Node(v1);
		Node* current = tail;
		Node* prev = nullptr;
		while (current != tail)
		{
			if (current->next->data == v2)
			{
				prev = current->next;
				current->next = newNode;
				newNode->next = prev;

			}
			current = current->next;
		}
	}

	bool Search(T key)
	{
		Node* current = tail;
		while (current != tail)
		{
			if (current->data == key)
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}


	void Update(T value)
	{
		Node* current = tail;
		while (current != tail)
		{
			if (current->data == value)
			{
				current->data = value;
				return;
			}
		}
	}

	bool Check()
	{
		return (tail->next != nullptr);
	}


	void printList()
	{
		Node* current = tail;
		while (current->next!= tail)
		{
			cout << current->data<<" ";
			current = current->next;
		}
		cout << tail->next->data<<endl;
	}


};


int main()
{
	CLL<int> list1;
	list1.insertatEnd(5);
	list1.insertatEnd(35);
	list1.insertatEnd(52);
	list1.insertatEnd(15);

	


//	list1.insertBefore(2, 35);
	list1.printList();

	cout << list1.Check() << endl;

	cout << list1.Search(5)<<endl;
	system("pause");
	return 0;

}
