#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Stack
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(T value, Node* nextNode = nullptr)
		{
			data = value;
			next = nextNode;
		}
	};
	Node* top;
	int count;
public:
	Stack()
	{
		top = nullptr;
		count = 0;
	}

	~Stack()
	{
		Clear();
	}

	void Push(const T& element)
	{
		Node* newNode = new Node(element, top);
		top = newNode;
		count++;
	}

	T Pop()
	{
		if (top == nullptr)
		{
			cout << "stack is empty" << endl;
			return 0;
		}
		else
		{
			Node* temp = top;
			T item = top->data;
			top = top->next;
			delete temp;
			count--;
			return item;
		}


	}

	T topitem() const
	{
		if (top == nullptr)
		{
			cout << "Stack is Empty" << endl;
			return -1;
		}
		else
		{
			T item = top->data;
			return item;
		}
	}

	bool isEmpty()
	{
		if (top == nullptr)
		{
			return true;
		}
		return false;
	}
	void Clear()
	{
		while (top != nullptr)
		{
			Pop();
		}
	}

	int size() const
	{
		return count;
	}

	

	bool IsFullyParenthesized(const string& expression) {
		Stack<char> s;
		for (char ch : expression) {
			if (ch == '(' || ch == '[' || ch == '{') {
				s.Push(ch);
			}
			else if (ch == ')' || ch == ']' || ch == '}') {
				if (s.isEmpty()) {
					return false;
				}
				char top = s.Pop();

				if ((ch == ')' && top != '(') ||
					(ch == ']' && top != '[') ||
					(ch == '}' && top != '{')) {
					return false;
				}
			}
		}
		return s.isEmpty();
	}

};



int main()
{
	Stack<int> stack1;
	stack1.Push(5);
	stack1.Push(15);
	stack1.Push(25);
	stack1.Push(35);
	stack1.Push(45);
	stack1.Push(55);
	

	cout<<"The size of Stack is: " << stack1.size()<<endl;
	cout<<"The top element is as follows: " << stack1.topitem() << endl;
	cout << "The Popped Values are as follows: " ;
	while (!stack1.isEmpty())
	{
		cout << stack1.Pop()<<"  ";
	}
	cout << endl;

	Stack<int> stack2;
	stack2.Push(5);
	stack2.Push(15);
	stack2.Push(25);
	stack2.Push(35);
	stack2.Push(45);
	stack2.Push(55);

	stack2.Pop();
	stack2.Clear();

	Stack<string> stack3;

	string expression = "{[()()]}";
	cout<<"{[()()]}: " << stack3.IsFullyParenthesized(expression) << endl;


	string expression2 = "{[()(}";
	cout << "{[()(}: " << stack3.IsFullyParenthesized(expression2) << endl;

}