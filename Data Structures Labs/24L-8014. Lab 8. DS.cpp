#include <iostream>

using namespace std;


class AVL
{
private:
	class AVLNode
	{
	public:
		int data;
		AVLNode* left;
		AVLNode* right;

		AVLNode(int value)
		{
			data = value;
			left = right = nullptr;
		}

	};

	AVLNode* root;



	int getHeight(AVLNode* node)
	{
		if (node == nullptr)
		{
			return -1;
		}
		int left = getHeight(node->left);
		int right = getHeight(node->right);
		return max(left, right)+1;
	}

	AVLNode* findMin(AVLNode* node)
	{
		AVLNode* current = node;
		while (current->left != nullptr)
		{
			current = current->left;
		}
		return current;

	}


	int balanceFactor(AVLNode* node)
	{
		if (node == nullptr)
		{
			return -1;
		}

		return (getHeight(node->left) - getHeight(node->right));
	}


	AVLNode* leftRotate(AVLNode* node)
	{
		AVLNode* newNode = node->right;
		AVLNode* t2 = newNode->left;


		newNode->left = node;
		node->right = t2;
		return newNode;
	}


	AVLNode* rightRotate(AVLNode* node)
	{
		AVLNode* newNode = node->left;
		AVLNode* t2 = newNode->right;

		newNode->right = node;
		node->left = t2;
		return newNode;
	}

	AVLNode* leftRightRotation(AVLNode* node)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	AVLNode* rightLeftRotation(AVLNode* node)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	AVLNode* balance(AVLNode* node, int value)
	{
		int BF = balanceFactor(node);
		cout<<"Balance Factor = "<<BF<<"\tNode ="<<node->data<<endl;

		if (BF > 1 && node->left->data > value)
		{
			cout<<"Tree has an left-left imbalance with a BF of: "<<BF<<" at node value of "<<node->data<<endl;
			return rightRotate(node);
		}

		if (BF < -1 && node->right->data < value)
		{
			cout<<"Tree has an right-right imbalance with a BF of: "<<BF<<" at node value of "<<node->data<<endl;
			return leftRotate(node);
		}

		if (BF > 1 && node->left->data < value)
		{
			cout<<"Tree has an right-left imbalance with a BF of: "<<BF<<" at node value of "<<node->data<<endl;
			return leftRightRotation(node);
		}
		if (BF<-1 && node->right->data > value)
		{
			cout<<"Tree has an left-right imbalance with a BF of: "<<BF<<" at node value of "<<node->data<<endl;
			return rightLeftRotation(node);

		}
		return node;
	}

//	AVLNode* insertNode(AVLNode* node, int value)
//	{
//		AVLNode* newNode = new AVLNode(value);
//		if (node == nullptr)
//		{
//			node = newNode;
//			return node;
//		}
//		else if (node->data > value)
//		{
//			node->left = insertNode(node->left, value);
//		}
//		else if (node->data < value)
//		{
//			node->right = insertNode(node->right, value);
//		}
//		else
//		{
//			if (node->left == nullptr)
//			{
//				AVLNode* temp = node->right;
//				delete node;
//				return temp;
//			}
//			if (node->right == nullptr)
//			{
//				AVLNode* temp = node->left;
//				delete node;
//				return temp;
//			}
//			else
//			{
//				AVLNode* temp = findMin(node->right);
//				node->data = temp->data;
//				remove(temp->data, node->right);
//			}
//
//			balance(node, value);
//
//		}
//		return node;
//	}



	AVLNode* insertNode(AVLNode* node, int value)
	{
		AVLNode* newNode = new AVLNode(value);
		if (node == nullptr)
		{
			node = newNode;
			return newNode;
		}
		

		if (node->data < value)
		{
			node->right = insertNode(node->right, value);
		}
		else if (node->data > value)
		{
			node->left = insertNode(node->left, value);
		}
		else
		{
			return node;
		}
		
		return balance(node, value);
	}
	
	
	
	
	void preOrder(AVLNode* node)
	{
		if (node)
		{
			
			preOrder(node->left);
			cout << node->data << endl;
			preOrder(node->right);
		}
	}


	void remove(const int& x, AVLNode*& t) {

		if (t == nullptr)

			return; 

		if (x < t->data)

			remove(x, t->left);

		else if (t->data < x)

			remove(x, t->right);

		else if (t->left != nullptr && t->right != nullptr) {//Two children

			t->data = findMin(t->right)->data;

			remove(t->data, t->right);

		}

		else {

			AVLNode* oldNode = t;

			if (t->left != nullptr) t = t->left;

			else t = t->right;

			delete oldNode;

		}
		balance(t, x);
	}

public:
	AVL()
	{
		root = nullptr;
	}


	void insert(int key)
	{
		root = insertNode(root, key);
	}

	void display()
	{
		preOrder(root);
	}
	
	int getBF()
	{
		return balanceFactor(root);
	}
	
	void removeNode(const int& x)
	{
		remove(x, root);
	}

};



int main()
{
	AVL avl1;
	avl1.insert(10);
	avl1.insert(30);
	avl1.insert(20);
	avl1.insert(100);
	avl1.insert(90);
	avl1.insert(00);
	avl1.insert(30);
	avl1.insert(40);
	avl1.insert(60);
	avl1.insert(70);
	avl1.insert(80);
	
	cout<<"List after Insertion"<<endl;
	avl1.display();
	
	
	
	avl1.removeNode(40);
	cout<<"List after Deletion"<<endl;
	avl1.display();
	//avl1.getBF();
}
