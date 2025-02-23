#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>
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

int ApplyOperator(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: throw runtime_error("Invalid operator");
    }
}


int Precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int EvaluateInfix(string expression) {
    Stack<int> operands;
    Stack<char> operators;
    unordered_map<char, int> variables;

for (char ch : expression) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        if (variables.find(ch) == variables.end()) {
            cout << "Enter value for " << ch << ": ";
            int value;
            cin >> value;
            variables[ch] = value;
        }
    }
}


    for (size_t i = 0; i < expression.length(); i++) {
        char ch = expression[i];

        if (isspace(ch)) continue;

        if (isdigit(ch)) {
            int num = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            operands.Push(num);
        } else if (isalpha(ch)) {
            operands.Push(variables[ch]);
        }

        else if (ch == '(') {
            operators.Push(ch);
        }

        else if (ch == ')') {
            while (!operators.isEmpty() && operators.topitem() != '(') {
                char op = operators.Pop();
                int b = operands.Pop();
                int a = operands.Pop();
                operands.Push(ApplyOperator(op, a, b));
            }
            operators.Pop(); 
        }

        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!operators.isEmpty() && Precedence(operators.topitem()) >= Precedence(ch)) {
                char op = operators.Pop();
                int b = operands.Pop();
                int a = operands.Pop();
                operands.Push(ApplyOperator(op, a, b));
            }
            operators.Push(ch);
        }
    }


    while (!operators.isEmpty()) {
        char op = operators.Pop();
        int b = operands.Pop();
        int a = operands.Pop();
        operands.Push(ApplyOperator(op, a, b));
    }


    return operands.Pop();
}

int main() {
    string expression;
    cout << "Enter infix expression: ";
    getline(cin, expression);

//    try {
        int result = EvaluateInfix(expression);
        cout << "Result: " << result << endl;
//    } catch (const exception& e) {
  //      cout << "Error: " << e.what() << endl;
  //  }

    return 0;
}


