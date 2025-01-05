#include <iostream>


using namespace std;

//late <typename T>
class LinkedList
{
private:
	struct Node
	{
		int data;
		Node* next;

		Node(int value)
		{
			data = value;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
	}
	void insertatStart(int const& element)
	{
		Node* newNode = new Node(element);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else {

			newNode->next = head;

			head = newNode;
		}
	}

	void insertatEnd(int const& element)
	{
		Node* newNode = new Node(element);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
	}
	void printList()
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			cout << temp->data << "->";
			temp = temp->next;

		}


	}

	bool findelement(int const key) const
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			if (temp->data == key)
			{
				cout << "true" << endl;
				return true;
			}
			temp = temp->next;


		}
		cout << "false" << endl;
		return false;
		



	}

	bool isEmpty()
	{
		if (head == nullptr)
		{
			cout << "\ntrue";
			return head == nullptr;
		}
		else {
			cout << "false";
			return false;
		}
	}
	void DeleteStart()
	{
		if (head == nullptr)
		{
			cout << "List is already empty" << endl;
		}
		else {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void DeleteEnd()
	{
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* temp = head;
			while (temp->next != tail)
			{
				temp = temp->next;


			}
			delete tail;
			tail = temp;
			tail->next = nullptr;
		}
	}

	int findMax()
	{

		Node* temp = head;
		
		if (head == nullptr)
		{
			return 0;
		}
		else {
			int maxValue = 0;
			while (temp != nullptr)
			{
				if (temp->data > maxValue)
				{
					maxValue = temp->data;
					
				}
				temp = temp->next;
			}
			cout <<"\nMaximum Value: "<< maxValue << endl;
		}
		


	}
	void sortList()
	{
      if (head == nullptr) {
            return;
        }
        bool swapped;
        Node* current;
        Node* lastSorted = nullptr;

        do {
            swapped = false;
            current = head;

            while (current->next != lastSorted) {
                if (current->data > current->next->data) {
                    swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
            lastSorted = current;
        } while (swapped);
	}

};


int main()
{
	LinkedList list;
	list.insertatStart(2);
	list.insertatStart(22);
	cout << "\nLinked List after Insert at Start: "<<endl;
	list.printList();
	list.insertatEnd(10);
	list.insertatEnd(5);
	list.insertatEnd(20);
	list.insertatEnd(25);
	cout << "\nLinked List after Insert at End" << endl;
	list.printList();
	list.DeleteEnd();
	cout << "\nLinked List after Delete End\n";
	list.printList();
	list.DeleteStart();
	cout << "\n Linked list after Delete start\n";
	list.printList();

	//t.DeleteEnd();

	//out << "Linked List after deleteEnd" << endl;
	//ist.printList();
		//ut << "\n Maximum Value" << endl;
	//ist.findMax();
	cout << "\nFind Element(10): ";
	list.findelement(10);
	cout << "\nFind Element(100): ";
	list.findelement(100);
	cout << "Is List empty: ";
	list.isEmpty();
	list.findMax();
	list.sortList();
	cout<<"\nList after Sorting: "<<endl;
	list.printList();
}
