#include <iostream>
#include <stack>
#include <queue>
using namespace std;


class BST
{
	struct Node
	{
		int data;
		Node* left;
		Node* right;
		
		Node(int value)
		{
			data =value;
			left = nullptr;
			right = nullptr;
		}
	};
	
	Node* root;

public:
	BST()
	{
		root = nullptr;
	}
	
	Node* copy(Node* otherRoot)
	{
		if (otherRoot == nullptr)
		{
			return nullptr;
		}
		
		Node* newNode = new Node(otherRoot->data);
		newNode->left = copy(otherRoot->left);
		newNode->right = copy(otherRoot->right);
		return newNode;
	}
	
	bool insert(int value, Node*& node)
	{
		Node* newNode = new Node(value);
		if (node == nullptr)
		{
			node = newNode;
			cout<<"Value is added"<<endl;
			return true;
		}
		
		if (value>node->data)
		{
			return insert(value, node->right);
		}
		
		else if (value<node->data)
		{
			return insert(value, node->left);
		}
		else
		{
			cout<<"Value already exist"<<endl;
			return false;
		}
		
		
	}
	
	void inOrderPrint()
	{
		
		stack<Node*> stack1;
		Node* current = root;
		while (!stack1.empty() || current!=nullptr)
		{
			while (current!=nullptr)
			{
				stack1.push(current);
				
				current = current->left;
			}
			
			current = stack1.top();
			stack1.pop();
			cout<<current->data<<" ";
			current = current->right;
		}
		cout<<endl;
	}
	
	void inOrderRecursive(Node* node)
	{
		if (node)
		{
		inOrderRecursive(node->left);
		cout<<node->data<<" ";
		inOrderRecursive(node->right);
}
	}
	
	
	bool insertVal(int value)
	{
		insert(value, root);
	}	
		
		
	void levelOrderPrint()
	{
		Node* current = root;
		if (current==nullptr)
		{
			return;
		}
		queue<Node*> q;
		q.push(current);
		while(!q.empty())
		{
			current = q.front();
			cout<<current->data<<" ";
			q.pop();
			if (current->right!=nullptr)
			{
				q.push(current->right);
			}
			if (current->left != nullptr)
			{
				q.push(current->left);
			}
		}
		cout<<endl;
		
	}
	
	
	bool search(int value, Node* node)
	{
		if (node == nullptr)
		{
			cout<<value<<": Value Not found"<<endl;
			return false;
		}
		
		if (node->data == value)
		{
			cout<<value<<": Value found"<<endl;
			return true;
		}

		else if (value < node->data)
		{
			return search(value, node->left);
		}
		else if (value > node->data)
		{
			return search(value, node->right);
		}
		
		else
		{
			cout<<"Value Not Found"<<endl;
			return false;
		}
		
	}
	
	int countNodes(Node* node)
	{
		if (node==nullptr)
		{
			return 0;
		}
		else
		{
			return 1+countNodes(node->left)+countNodes(node->right);
		}
	}
	
	int countLeaf(Node* node)
	{
		if (node==nullptr)
		{
			return 0;
		}
		
		if (node->left == nullptr && node->right == nullptr)
		{
			return 1;
		}
		

		else
		{
			return countLeaf(node->left)+countLeaf(node->right);
		}
	}
	
	void Destroy(Node* node)
	{
		if (node)
		{
			Destroy(node->left);
			Destroy(node->right);
			delete node;
		}
	}
	
	bool searchWrap(int value)
	{
		search(value, root);
	}
	
	int wrapCount()
	{
		countNodes(root);
	}
	
	int wrapLeaf()
	{
		countLeaf(root);
	}
	
	~BST()
	{
		Destroy(root);
		cout<<"Tree Destroyed"<<endl;
	}
	
	
	void wrapinOrder()
	{
		inOrderRecursive(root);
	}
};

int main()
{
	BST tree1;
	tree1.insertVal(15);
	tree1.insertVal(5);
	tree1.insertVal(25);
	tree1.insertVal(55);
	tree1.insertVal(25);
	tree1.insertVal(15);
	tree1.insertVal(23);
	tree1.insertVal(65);
	tree1.insertVal(35);
	cout<<"In Order using Recursion: ";
	tree1.wrapinOrder();
	cout<<endl;
	cout<<"InOrder Print Iteratively: ";
	tree1.inOrderPrint();
	cout<<"Level Order Print: ";
	tree1.levelOrderPrint();
	
	tree1.searchWrap(25);
	tree1.searchWrap(75);
	
	cout<<"Number of Nodes: "<<tree1.wrapCount()<<endl;
	
	cout<<"Number of Leaves: "<<tree1.wrapLeaf()<<endl;
	

	
}
