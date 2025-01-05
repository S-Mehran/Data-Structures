#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

template <typename T>
class SinglyLinkedList {
private:
    // Node class to represent each node in the linked list
    class Node {
    public:
        T data;
        Node* next;

        Node(T const& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    // Constructor
    SinglyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor
    ~SinglyLinkedList() {
        while (!isEmpty()) {
            DeleteStart();
        }
    }

    // Check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Insert element at the start of the list
    void insertAtStart(T const& element) {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }

    // Insert element at the end of the list
    void insertAtEnd(T const& element) {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Print the list
    void printList() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Search for an element in the list
    bool findElement(T const& value) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Delete from the start of the list
    void DeleteStart() {
        if (isEmpty()) {
            cout << "List is empty. Nothing to delete." << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    // Delete from the end of the list
    void DeleteEnd() {
        if (isEmpty()) {
            cout << "List is empty. Nothing to delete." << endl;
            return;
        }
        if (head == tail) {  // Only one element
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
    }

    // Delete all occurrences of a given value
    void deleteAll(T const& value) {
        while (head != nullptr && head->data == value) {
            DeleteStart();
        }
        Node* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
                if (current->next == nullptr) {
                    tail = current;
                }
            } else {
                current = current->next;
            }
        }
    }

    // Find the maximum value in the list
    T findMax() const {
        if (isEmpty()) {
            cout<<"List is empty";
        }
        Node* temp = head;
        T maxVal = numeric_limits<T>::lowest();
        while (temp != nullptr) {
            if (temp->data > maxVal) {
                maxVal = temp->data;
            }
            temp = temp->next;
        }
        return maxVal;
    }

    // Sort the list using Bubble Sort
    void sortList() {
        if (isEmpty()) return;

        bool swapped;
        Node* ptr1;
        Node* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->data > ptr1->next->data) {
                    // Swap the data
                    T temp = ptr1->data;
                    ptr1->data = ptr1->next->data;
                    ptr1->next->data = temp;

                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

    // Check if two lists have the same contents
    bool isEqual(SinglyLinkedList const& other) const {
        Node* thisTemp = head;
        Node* otherTemp = other.head;

        while (thisTemp != nullptr && otherTemp != nullptr) {
            if (thisTemp->data != otherTemp->data) {
                return false;
            }
            thisTemp = thisTemp->next;
            otherTemp = otherTemp->next;
        }

        return thisTemp == nullptr && otherTemp == nullptr;
    }

    // Merge two linked lists together
    void merge(SinglyLinkedList& other) {
        if (isEmpty()) {
            head = other.head;
            tail = other.tail;
        } else if (!other.isEmpty()) {
            tail->next = other.head;
            tail = other.tail;
        }
        other.head = nullptr;
        other.tail = nullptr;
    }
    
    void kappend(int k)
    {
    	Node* newhead = nullptr;
    	Node* newTail = nullptr;
    	Node* current = head;
    	int length = 0;
    	while (current!=nullptr)
    	{
    		length++;
    		current = current->next;
    		
		}
		current = head;
		int count = 1;
		while (current->next!=nullptr)
		{
			if (count == (length-k))
			{
				newTail = current;
			}
			
			if (count == (length-k+1))
			{
				newhead = current;
			}
			current = current->next;
			count++;
			
		}
		
//		newTail->next = nullptr;
//		tail->next = head;
			tail->next = head;
			newTail->next = nullptr;
			head= newhead;
			tail = newTail;
		
		
	}
	
	void reverseList()
	{
		if (head==tail)
		{
			return;
		}
		Node* current=head;
		Node* next; 
		Node* prev = nullptr;
		
		while (current!=nullptr)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
			
	}
	tail = head;
	head = prev;
		
//		SinglyLinkedList<int> newList;
//		Node* current = head;
//	//	Node* tailCurrent = tail;
////		while (current->next!=nullptr)
////		{
////			current = current->next;
////		}
//		while (!isEmpty())
//		{
//		
//		newList.insertAtEnd(tail->data);
//		DeleteEnd();
//		//current = head;
//	}
//	newList.printList();
//	
	}
	
	
	SinglyLinkedList reverseList(int k)
	{
		if (head==tail)
		{
			return;
		}
		SinglyLinkedList<int> newList;
		int count =0;
		Node* current = head;
		while (!isEmpty())
		{
			if (count == k)
			{
				count = 0;
				while (count != k)
				{
					
				}
			}
			while (count != k)
			{
				newList.insertAtStart(head->data);
				DeleteStart();
			//	current = current->next;
				count++;
			}
		}
		newList.printList();
		this->head = newList.head;
		this->tail = newList.tail;
		return newList;
	}
	
	
	int sizeLL()
	{
		Node* current = head;
		int count = 0;
		while (current!=nullptr)
		{
			count++;
			current = current->next;
		}
		return count;
	}
	
	
	bool isPalindrome()
	{
		Node* current = head;
		int size = sizeLL();
		int* array = new int[size];
		int i =0;
		while (current!=nullptr)
		{
			array[i++] = current->data;
			current = current->next;
		}
		int first = 0;
		int last = size-1;
		while (last>first)
		{
			if (array[first]!=array[last])
			{
				return false;
			}
			else
			{
				first++;
				last--;
			}
		}
		return true;
	}
	
	
	int sumList()
	{
		if (head==nullptr)
		{
			return -1;
		}
		if (head==tail)
		{
			return head->data;
		}
		int sum = 0;
		Node* current = head;
		while (current!=nullptr)
		{
			sum+=current->data;
			current = current->next;
		}
		return sum;
	}
	
	int lengthLL()
	{
		if (head==nullptr)
		{
			return -1;
		}
		Node* current = head;
		int count = 0;
		while (current!=nullptr)
		{
			count++;
			current=current->next;
		}
		return count;
	}
	
	void sumofLL(SinglyLinkedList<int> list1, SinglyLinkedList<int> list2)
	{
		if (!list1.head || !list2.head)
		{
			return;
		}
		int len1 = list1.lengthLL();
		cout<<"len1"<<endl;
		int len2 = list2.lengthLL();
		while (len1!=len2)
		{
			if (len1>len2)
			{
				list2.insertAtStart(0);
				len2++;
				cout<<"Worked Till here"<<endl;
			}
			else
			{
				list1.insertAtStart(0);
				len1++;
			}
							cout<<"Worked Till here"<<endl;

		}
		list1.reverseList();
		list1.printList();
		list2.reverseList();
		list2.printList();
	//	SinglyLinkedList newList;
		Node* current1 = list1.head;
		Node* current2 = list2.head;
		int carry = 0;
		
		while (current1!=nullptr /*|| current2!=nullptr*/)
		{
//			int temp =0;
//			if (current1!=nullptr && current2!=nullptr)
//			{
//				temp = current1->data + current2->data + carry;
//				if (temp>9)
//				{
//					carry = carry+(temp-9);
//					temp = temp - carry;
//				}
//				
//
//			}
//			if (current1 != nullptr)
//			{
//					
//			}
			int temp = current1->data+current2->data+carry;
			if (temp>9)
			{
				carry = temp/10;
				temp = temp%10;
			}
			else
			{
				carry = 0;
			}
			insertAtEnd(temp);
			current1=current1->next;
			current2 = current2->next;
			
		}
		

		reverseList();
	}
	
};

int main() {
    SinglyLinkedList<int> list1;

    // Insert elements into the list
    list1.insertAtStart(2);
    list1.insertAtStart(6);
    list1.insertAtStart(7);
    list1.insertAtEnd(9);
    list1.insertAtStart(7);
    list1.insertAtStart(8);
    list1.insertAtStart(9);

    // Print the list
    cout << "List after inserting elements: ";
    list1.printList();

    // Delete all occurrences of 7
    list1.deleteAll(7);
    cout << "List after deleting all occurrences of 7: ";
    list1.printList();

    // Sort the list and print again
    list1.sortList();
    cout << "List after sorting: ";
    list1.printList();

    // Find and print the maximum value
    try {
        int maxVal = list1.findMax();
        cout << "Maximum value in the list: " << maxVal << endl;
    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    // Search for 2, 9, and 10 in the list
    cout << "Searching for 2 in the list: " << (list1.findElement(2) ? "Found" : "Not Found") << endl;
    cout << "Searching for 9 in the list: " << (list1.findElement(9) ? "Found" : "Not Found") << endl;
    cout << "Searching for 10 in the list: " << (list1.findElement(10) ? "Found" : "Not Found") << endl;

    // Define another list and check if both lists are the same
    SinglyLinkedList<int> list2;
    list2.insertAtStart(2);
    list2.insertAtEnd(9);
    cout << "Comparing two lists: " << (list1.isEqual(list2) ? "Same" : "Different") << endl;

    // Merge both lists
    list1.merge(list2);
    cout << "List after merging with the second list: ";
    list1.printList();

    // Delete from the start and print the list
    list1.DeleteStart();
    cout << "List after deleting from start: ";
    list1.printList();
    
    SinglyLinkedList<int> list3;
    list3.insertAtStart(1);
    list3.insertAtStart(2);
    list3.insertAtStart(3);
    list3.insertAtStart(4);
    list3.insertAtStart(5);
    list3.insertAtStart(6);
    list3.printList();
    list3.kappend(4);
    cout<<"UnReserved List"<<endl;
    list3.printList();
    cout<<"Reversed list"<<endl;
    list3.reverseList();
    list3.printList();
    
    
    SinglyLinkedList<int> list4;
    list4.insertAtStart(1);
    list4.insertAtStart(2);
    list4.insertAtStart(3);
    list4.insertAtStart(3);
    list4.insertAtStart(2);
    list4.insertAtStart(1);
    list4.printList();
//    list4.reverseList(3);
    if (list4.isPalindrome())
    {
    	cout<<"True"<<endl;
	}
	else
	{
		cout<<"False"<<endl;
	}
	
	
	cout<<"This"<<15/10<<endl;
	SinglyLinkedList<int> list5;
	list5.insertAtEnd(2);
	list5.insertAtEnd(4);
	list5.insertAtEnd(5);
	
	
	SinglyLinkedList<int> list6;
	list6.insertAtEnd(4);
	list6.insertAtEnd(5);
	
	SinglyLinkedList<int> list7;
	list7.sumofLL(list5, list6);
	list7.printList();
    return 0;
}

