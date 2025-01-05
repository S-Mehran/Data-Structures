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
	
	
	Node* deleteNode(Node* node, int value)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		else if (node->data > value)
		{
			node->left = deleteNode(node->left, value);
		}
		else if (node->data < value)
		{
			node ->right = deleteNode(node->right, value);
		}
		
		else
		{
			if (node->left == nullptr)
			{
				Node* temp = node->right;
				delete node;
				return temp;
			}
			else if (node->right == nullptr)
			{
				Node* temp = node->left;
				delete node;
				return temp;
			}
			else
			{
				Node* temp = minValue(node->right);
				node->data = temp->data;
				node->right = deleteNode(node->right, temp->data);
			}
			
			
		}
		return node;
	}
	
	Node* wrapDelete(int value)
	{
		return deleteNode(root, value);
	}
	
	Node* minValue(Node* node)
	{
		Node* current = node;
		while (current->left != nullptr)
		{
			current = current -> left;
		}
		return current;
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
		return insert(value, root);
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
		return search(value, root);
	}
	
	int wrapCount()
	{
		return countNodes(root);
	}
	
	int wrapLeaf()
	{
		return countLeaf(root);
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


	int sumReplacementUtil(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		node->data = sumReplacementUtil(node->left) + sumReplacementUtil(node->right) + node->data;
		return node->data;
	}

	int sumReplacement()
	{
		return sumReplacementUtil(root);
	}

	void rightTree()
	{
		Node* current = root;
		if (current == nullptr)
		{
			return;
		}
		queue<Node*> q;
		q.push(current);
		while (!q.empty())
		{
			int n = q.size();
			for (int i = 0; i < n; i++)
			{
				current = q.front();
				q.pop();
				if (i == n - 1)
				{
					cout << current->data << " ";
				}
				if (current->left != NULL)
				{
					q.push(current->left);
				}
				if (current->right != NULL)
				{
					q.push(current->right);
				}


			}
		}
		cout << endl;
	}


	void leftTree()
	{
		Node* current = root;
		if (current == nullptr)
		{
			return;
		}
		queue<Node*> q;
		q.push(current);
		while (!q.empty())
		{
			int n = q.size();
			for (int i = 0; i < n; i++)
			{
				current = q.front();
				q.pop();
				if (i == 0)
				{
					cout << current->data << " ";
				}
				if (current->left != NULL)
				{
					q.push(current->left);
				}
				if (current->right != NULL)
				{
					q.push(current->right);
				}
			}
		}
		cout << endl;
	}


	bool isIdentical(Node* node1, Node* node2)
	{
		if (node1 == NULL && node2 == NULL)
		{
			return true;
		}
		if (node1 == NULL || node2 == NULL)
		{
			return false;
		}
		else
		{
			return (node1->data == node2->data)
			&& isIdentical(node1->left, node2->left)
			&& isIdentical(node1->right, node2->right);
		}

		
	}

	bool identicalTree(BST& otherTree)
	{
		return isIdentical(root, otherTree.root);
	}


	Node* LCA(Node* node, int n1, int n2)
	{
		if (node == NULL)
		{
			return NULL;
		}
		if (node->data == n1 || node->data == n2)
		{
			return node;
		}
		Node* left = LCA(node->left, n1, n2);
		Node* right = LCA(node->right, n1, n2);

		if (left == NULL && right == NULL)
		{
			return NULL;
		}
		if (left != NULL && right != NULL)
		{
			return node;
		}
		if (left != NULL)
		{
			return left;
		}
		return right;
	}

	bool isBST(Node* node)
	{
		if (node == NULL)
		{
			return true;
		}
		if (node->left && node->right)
		{
			if (node->data > node->left->data && node->data < node->right->data)
			{
				return true;
			}
			else if (node->data < node->left->data || node->data > node->right->data)
			{
				return false;
			}
	
		}

		bool left =  isBST(node->left);
		bool right =  isBST(node->right);
		if (left && right)
		{
			return true;
		}
		if (!left || !right)
		{
			return false;
		}
	}

	bool BSTorNot()
	{
		return isBST(root);
	}
	
	
	
	    //Function to store the zig zag order traversal of tree in a list.
    vector <int> zigZagTraversal()
    {
    	// Code here
    	vector<int> traversal;
    	int count = 1;
    	Node* current = root;
		if (current==nullptr)
		{
			return traversal;
		}
		queue<Node*> q;
		q.push(current);
		while(!q.empty())
		{
			current = q.front();
			cout<<current->data<<" ";
			q.pop();
			if (count%2==0)
			{
			if (current->right!=nullptr)
			{
				q.push(current->right);
				traversal.push_back(current->right->data);
			}
			if (current->left != nullptr)
			{
				q.push(current->left);
				traversal.push_back(current->left->data);
			}
			}
			else
			{
			if (current->left!=nullptr)
			{
				q.push(current->left);
				traversal.push_back(current->right->data);
			}
			if (current->right != nullptr)
			{
				q.push(current->right);
				traversal.push_back(current->right->data);
			}   
			}
			count++;
		}
		cout<<endl;
		return traversal;
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
	cout<<endl<<endl;
	
	tree1.wrapinOrder();
	cout<<endl;
	tree1.wrapDelete(35);
	tree1.wrapinOrder();
	

	BST tree2;
	tree2.insertVal(1);
	tree2.insertVal(2);
	tree2.insertVal(3);
	tree2.insertVal(4);
	tree2.insertVal(5);
	tree2.inOrderPrint();
	tree2.sumReplacement();
	tree2.inOrderPrint();

	BST tree3;
	tree3.insertVal(4);
	tree3.insertVal(2);
	tree3.insertVal(3);
	tree3.insertVal(1);
	tree3.insertVal(8);
	tree3.insertVal(9);
	tree3.insertVal(7);
	tree3.insertVal(6);
	tree3.insertVal(5);
	

	tree3.rightTree();


	BST tree4;
	tree4.insertVal(5);
	tree4.insertVal(3);
	tree4.insertVal(2);
	tree4.insertVal(4);
	tree4.insertVal(6);

	tree4.leftTree();


	BST tree5;
	tree5.insertVal(5);
	tree5.insertVal(3);
	tree5.insertVal(2);
	tree5.insertVal(4);
	tree5.insertVal(6);

	bool result = tree5.identicalTree(tree4);
	if (result)
	{
		cout << "Trees are identical" << endl;

	}
	else
	{
		cout << "Trees are different" << endl;
	}

	bool ans = tree5.BSTorNot();
	if (ans)
	{
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl;
	}
	
	
	tree5.zigZagTraversal();
}
