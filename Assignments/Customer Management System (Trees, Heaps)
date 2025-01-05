#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class User {
public:
    int userID;
    string userName;
    string email;
    string country;
    string type;

    User(int id, string name, string mail, string ctry, string usrType) 
    {
        	userID = id;
        	userName = name;
        	email = mail;
        	country = ctry;
        	type = usrType;
		}

    void display() {
        cout << "UserID: " << userID << ", Name: " << userName 
             << ", Email: " << email << ", Country: " << country 
             << ", Type: " << type << endl;
    }
};


class Node {
public:
    User* user;
    Node* next;
    Node* prev;

    Node(User* u)
    {
    	user = u;
    	next = nullptr;
    	prev = nullptr;
	}
};




template <typename KeyType, typename ValueType>
class AVLNode {
public:
    KeyType key;
    ValueType value; // Pointer to User record in DLL
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(KeyType k, ValueType val)
    {
    	key = k;
    	value = val;
    	left = nullptr;
    	right = nullptr;
    	height = 1;
	}
};

template <typename KeyType, typename ValueType>
class AVLTree {
private:
    AVLNode<KeyType, ValueType>* root;

    int getHeight(AVLNode<KeyType, ValueType>* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}


    int getBalance(AVLNode<KeyType, ValueType>* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}


    AVLNode<KeyType, ValueType>* rotateRight(AVLNode<KeyType, ValueType>* y) {
        AVLNode<KeyType, ValueType>* x = y->left;
        AVLNode<KeyType, ValueType>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode<KeyType, ValueType>* rotateLeft(AVLNode<KeyType, ValueType>* x) {
        AVLNode<KeyType, ValueType>* y = x->right;
        AVLNode<KeyType, ValueType>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode<KeyType, ValueType>* insert(AVLNode<KeyType, ValueType>* node, KeyType key, ValueType value) {
        if (node == nullptr) {
            return new AVLNode<KeyType, ValueType>(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            return node; // Duplicate keys not allowed
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) 
		{
			return rotateRight(node);
		}
        if (balance < -1 && key > node->right->key) 
        {
        	return rotateLeft(node);
		}
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode<KeyType, ValueType>* search(AVLNode<KeyType, ValueType>* node, KeyType key) {
        if (node == nullptr || node->key == key)
            return node;

        if (key < node->key)
            return search(node->left, key);

        return search(node->right, key);
    }

    void inOrderTraversal(AVLNode<KeyType, ValueType>* node, vector<KeyType>& keys) {
        if (node != nullptr) {
            inOrderTraversal(node->left, keys);
            keys.push_back(node->key);
            inOrderTraversal(node->right, keys);
        }
    }

public:
    AVLTree()
    {
    	root = nullptr;
	}

    void insert(KeyType key, ValueType value) {
        root = insert(root, key, value);
    }

    AVLNode<KeyType, ValueType>* search(KeyType key) {
        return search(root, key);
    }

    vector<KeyType> getAllKeys() {
        vector<KeyType> keys;
        inOrderTraversal(root, keys);
        return keys;
    }
};



// GroupNode: For singly linked list within each AVL node
class GroupNode {
public:
    Node* userNode;  // Pointer to user node in DLL
    GroupNode* next;

    GroupNode(Node* userNode)
    {
    	this->userNode = userNode;
    	next = nullptr;
	}
};

// AVL Node for Group Index
template <typename KeyType>
class GroupAVLNode {
public:
    KeyType key; // Country or Type
    GroupNode* groupHead;  // Head of linked list of users for this key
    GroupAVLNode* left;
    GroupAVLNode* right;
    int height;

    GroupAVLNode(KeyType k)
    {
    	key = k;
    	groupHead = nullptr;
    	left = nullptr;
    	right = nullptr;
    	height = 1;
	}
};

// Group AVL Tree Class
template <typename KeyType>
class GroupAVLTree {
private:
    GroupAVLNode<KeyType>* root;


	//Helpet functions for retrieving height, balance factor, rotations, searching and insertion
    int getHeight(GroupAVLNode<KeyType>* node) {
        return node == nullptr ? 0 : node->height;
    }

    int getBalance(GroupAVLNode<KeyType>* node) {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    GroupAVLNode<KeyType>* rotateRight(GroupAVLNode<KeyType>* y) {
        GroupAVLNode<KeyType>* x = y->left;
        GroupAVLNode<KeyType>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    GroupAVLNode<KeyType>* rotateLeft(GroupAVLNode<KeyType>* x) {
        GroupAVLNode<KeyType>* y = x->right;
        GroupAVLNode<KeyType>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    GroupAVLNode<KeyType>* insert(GroupAVLNode<KeyType>* node, KeyType key, Node* userNode) {
        if (node == nullptr) {
            GroupAVLNode<KeyType>* newNode = new GroupAVLNode<KeyType>(key);
            newNode->groupHead = new GroupNode(userNode);
            return newNode;
        }

        if (key < node->key) {
            node->left = insert(node->left, key, userNode);
        }
		else if (key > node->key) {
            node->right = insert(node->right, key, userNode);
        } 
		else {
            GroupNode* newGroupNode = new GroupNode(userNode);
            newGroupNode->next = node->groupHead;
            node->groupHead = newGroupNode;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) 
		{
			return rotateRight(node);
		}
        if (balance < -1 && key > node->right->key) 
        {
        	return rotateLeft(node);
		}
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    GroupAVLNode<KeyType>* search(GroupAVLNode<KeyType>* node, KeyType key) {
        if (node == nullptr || node->key == key) 
		{
			return node;
		}

        if (key < node->key) {
        	return search(node->left, key);
		}
        return search(node->right, key);
    }

public:
    GroupAVLTree() 
	{
		root = nullptr;
	}  


	//Wrapper functions for insertion and searching
    void insert(KeyType key, Node* userNode) {
        root = insert(root, key, userNode);
    }

    GroupAVLNode<KeyType>* search(KeyType key) {
        return search(root, key);
    }
	
	//Helper display
    void display(GroupAVLNode<KeyType>* node) {
        if (node) {
            display(node->left);
            cout << node->key << " -> ";
            GroupNode* current = node->groupHead;
            while (current) {
                current->userNode->user->display();
                current = current->next;
            }
            display(node->right);
        }
    }
	
	
	//Wrapper display
    void display() {
        display(root);
    }
};







class UserList {
private:
    Node* head; // Head of the doubly linked list

    // Indices for username and email
    AVLTree<int, Node*>* UserIDIndex = nullptr;
    AVLTree<string, Node*>* usernameIndex = nullptr;
    AVLTree<string, Node*>* emailIndex = nullptr;
    GroupAVLTree<string>* countryIndex = nullptr;
    GroupAVLTree<string>* typeIndex = nullptr;

public:
	//Constructor
    UserList()
    {
    	head = nullptr;
	}


	void searchByUserID(int id)
	{
		if (UserIDIndex == nullptr)
		{
      	Node* current = head;
        UserIDIndex = new AVLTree<int, Node*>();
        while (current) 
		{
            UserIDIndex->insert(current->user->userID, current);
            current = current->next;
        }
        cout << "UserID Index created." << endl;
		}
		AVLNode<int, Node*>* result = UserIDIndex->search(id);
		if (result)
		{
			result->value->user->display();
		}
		else
		{
			cout<<"User Not Found"<<endl;
		}
	}
//	void searchByUserID(int id)
//	{
//		Node* current = head;
//		while (current!=nullptr)
//		{
//			if (current->user->userID == id)
//			{
//				cout<<"User Found having UserID of "<<id<<endl;
//				User* result
//				return;
//			}
//			current = current->next;
//		}
//		cout<<"User not Found"<<endl;
//	}

	
	
	//Doubly Linked List Operaitons
	void insertUser(User* user) 
	{
    Node* newNode = new Node(user);
    
    // Insertion into the doubly linked list in sorted order by userID
    if (!head || head->user->userID > user->userID) {
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next && current->next->user->userID < user->userID)
            current = current->next;

        newNode->next = current->next;
        if (current->next) 
		{
			current->next->prev = newNode;
		}
        current->next = newNode;
        newNode->prev = current;
    }

    // Update AVL indices if they exist
    if (usernameIndex) 
    {
    	usernameIndex->insert(user->userName, newNode);
	}
    if (emailIndex) 
    {
    	emailIndex->insert(user->email, newNode);
	}

    cout << "User inserted and indices updated if they exist." << endl;
}

// Function to Delete a User and Update Indices
void deleteUser(int userID) {
    Node* current = head;

    // Find the user in the doubly linked list
    while (current && current->user->userID != userID) {
        current = current->next;
    }

    if (!current) {
        cout << "User with UserID " << userID << " not found." << endl;
        return;
    }

    // Remove from doubly linked list
    if (current->prev) 
	{
		current->prev->next = current->next;
	}
    if (current->next) 
    {
    	current->next->prev = current->prev;
	}
    if (current == head) 
    {
    	head = current->next;
	}

    // Update AVL indices if they exist
    if (usernameIndex) 
    {
    	usernameIndex->search(current->user->userName)->value = nullptr;
	}
    if (emailIndex) 
    {
    	emailIndex->search(current->user->email)->value = nullptr;
	}

    delete current;
    cout << "User deleted and indices updated." << endl;
}

// Function to Print All Users
void printAllUsers() {
    Node* current = head;
    cout << "User List:" << endl;
    while (current) {
        current->user->display();
        current = current->next;
    }
}

    // 1. Create an Index on the Username
    void createUsernameIndex() {
        if (usernameIndex != nullptr)  //edge case 
		{
            cout << "Username Index already exists." << endl;
            return;
        }
        //new avl tree is created. It is then populated through user data for searching
        Node* current = head;
        usernameIndex = new AVLTree<string, Node*>();
        while (current) 
		{
            usernameIndex->insert(current->user->userName, current);
            current = current->next;
        }
        cout << "Username Index created." << endl;
    }

    // 2. Delete an Index on the Username
    void deleteUsernameIndex() {
        if (usernameIndex == nullptr) {
            cout << "Username Index does not exist." << endl;
            return;
        }
        delete usernameIndex;
        usernameIndex = nullptr;  //to undangle the username index
        cout << "Username Index deleted." << endl;
    }
	

	
	
    // 3. Search user efficiently using Username
    void searchByUsername(const string& username) {
        if (usernameIndex == nullptr) {
            cout << "Username Index not found. Please create the index first." << endl;
            return;
        }
        //data of search is stored in result. Searching is done though AVL Tree function
        AVLNode<string, Node*>* result = usernameIndex->search(username);
        if (result) {
            result->value->user->display();
        } else {
            cout << "User not found with username: " << username << endl;
        }
    }

    // 4. Create an Index on Email
    void createEmailIndex() {
        if (emailIndex != nullptr) {
            cout << "Email Index already exists." << endl;
            return;
        }
        //Create an AVL object and insert the user data into the object
        emailIndex = new AVLTree<string, Node*>();
        Node* current = head;
        while (current) {
            emailIndex->insert(current->user->email, current);
            current = current->next;
        }
        cout << "Email Index created." << endl;
    }

    // 5. Delete an Index on Email
    void deleteEmailIndex() {
        if (emailIndex == nullptr) {
            cout << "Email Index does not exist." << endl;
            return;
        }
        delete emailIndex;
        emailIndex = nullptr;
        cout << "Email Index deleted." << endl;
    }

    // 6. Search user using Email
    void searchByEmail(const string& email) {
        if (emailIndex == nullptr) {
            cout << "Email Index not found. Please create the index first." << endl;
            return;
        }
        
        AVLNode<string, Node*>* result = emailIndex->search(email);
        if (result) {
            result->value->user->display();
        } else {
            cout << "User not found with email: " << email << endl;
        }
    }

    // 7. Display all created indices
    void displayIndices() {
        cout << "Created Indices:" << endl;
        if (usernameIndex) {
            cout << "- Username Index exists." << endl;
        } else {
            cout << "- Username Index does not exist." << endl;
        }

        if (emailIndex) {
            cout << "- Email Index exists." << endl;
        } else {
            cout << "- Email Index does not exist." << endl;
        }
    }
    
    
    
                       //===========FOR QUESTION 3: GROUP AVL===============
    
    
     
    
    //GROUPAVL Enhancements


   // 1. Create Group Index on Country
    void createCountryIndex() {
        if (countryIndex != nullptr) {
            cout << "Country Index already exists." << endl;
            return;
        }
        //Inserting all values of users into the countryIndex object
        countryIndex = new GroupAVLTree<string>();
        Node* current = head;
        while (current) {
            countryIndex->insert(current->user->country, current);
            current = current->next;
        }
        cout << "Country Index created." << endl;
    }

    // 2. Delete Group Index on Country
    void deleteCountryIndex() {
        delete countryIndex;
        countryIndex = nullptr;
        cout << "Country Index deleted." << endl;
    }

    // 3. List users by Country
    void listUsersByCountry(const string& country) {
        if (!countryIndex) {
            cout << "Country Index not found. Please create it first." << endl;
            return;
        }
        //search country and print them all one by one using while loop
        GroupAVLNode<string>* node = countryIndex->search(country);
        if (node) {
            GroupNode* current = node->groupHead;
            while (current) {
                current->userNode->user->display();
                current = current->next;
            }
        } else {
            cout << "No users found for country: " << country << endl;
        }
    }

    // 4. Display Group Index on Country
    void displayCountryIndex() {
        if (countryIndex) {
            countryIndex->display();
        } else {
            cout << "Country Index not created." << endl;
        }
    }

    // 5. Create Group Index on Type
    void createTypeIndex() {
        if (typeIndex != nullptr) {
            cout << "Type Index already exists." << endl;
            return;
        }
        typeIndex = new GroupAVLTree<string>();
        Node* current = head;
        while (current) {
            typeIndex->insert(current->user->type, current);
            current = current->next;
        }
        cout << "Type Index created." << endl;
    }

    // 6. Delete Group Index on Type
    void deleteTypeIndex() {
        delete typeIndex;
        typeIndex = nullptr;
        cout << "Type Index deleted." << endl;
    }

    // 7. List users by Type
    void listUsersByType(const string& type) {
        if (!typeIndex) {
            cout << "Type Index not found. Please create it first." << endl;
            return;
        }
        GroupAVLNode<string>* node = typeIndex->search(type);
        if (node) {
            GroupNode* current = node->groupHead;
            while (current) {
                current->userNode->user->display();
                current = current->next;
            }
        } else {
            cout << "No users found for type: " << type << endl;
        }
    }

    // 8. Display Group Index on Type
    void displayTypeIndex() {
        if (typeIndex) {
            typeIndex->display();
        } else {
            cout << "Type Index not created." << endl;
        }
    }
    
};



//Complaint class to store the data for complaint
class Complaint {
public:
    int complaintID;
    int userID; // ID of the user who filed the complaint
    string description;  //complaint

    Complaint(int cID, int uID, string desc) 
        : complaintID(cID), userID(uID), description(desc) {}

    void display() {
        cout << "ComplaintID: " << complaintID 
             << ", UserID: " << userID 
             << ", Description: " << description << endl;
    }
};



//Priority queue with Heap Functions
class PriorityQueue {
private:
    struct HeapNode {
        int priority; // Based on user type
        Complaint* complaint;

        HeapNode(int p, Complaint* c) : priority(p), complaint(c) {}
    };

    vector<HeapNode> heap;
    map<string, int> typePriority = {{"Platinum", 5}, {"Gold", 4}, {"Silver", 3}, {"Regular", 2}, {"New", 1}};

    int parent(int i) 
	{ 
		return (i - 1) / 2; 
	}
    int leftChild(int i) { 
	return 2 * i + 1; 
	}
    int rightChild(int i) { 
	return 2 * i + 2; 
	}

    void heapifyUp(int index) {
        while (index != 0 && heap[parent(index)].priority < heap[index].priority) {
            swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int maxIndex = index;
        int l = leftChild(index);
        if (l < heap.size() && heap[l].priority > heap[maxIndex].priority)
            maxIndex = l;

        int r = rightChild(index);
        if (r < heap.size() && heap[r].priority > heap[maxIndex].priority)
            maxIndex = r;

        if (index != maxIndex) {
            swap(heap[index], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
	//Register a new complaint
    void registerComplaint(Complaint* complaint, string userType) 
	{
        int priority = typePriority[userType];          
        heap.push_back(HeapNode(priority, complaint));  //Uses vector for insertion
        heapifyUp(heap.size() - 1);     //Heapify function sorts the data on the basis of priority (highest data is at root)
        cout << "Complaint registered." << endl;
    }


	//Function to retrieve highest priority complaint
    Complaint* serviceComplaint() {
        if (heap.empty()) 
		{
            cout << "No complaints to service." << endl;
            return nullptr;
        }

        Complaint* topComplaint = heap[0].complaint;
        heap[0] = heap.back();        //Vector funct. for accessing the last element. It places the last element at root
        heap.pop_back();    //Removes the last element
        heapifyDown(0);

        return topComplaint;
    }

    void increasePriority(int complaintID) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i].complaint->complaintID == complaintID) {
                heap[i].priority = 6; // Max priority
                heapifyUp(i);    //Heapify function sorts the data on the basis of priority (highest data is at root)
                cout << "Priority increased for ComplaintID: " << complaintID << endl;
                return;
            }
        }
        cout << "Complaint not found." << endl;
    }

    void displayComplaintsByUserID(int userID) {
        for (const auto& node : heap) {
            if (node.complaint->userID == userID) {
                node.complaint->display();
            }
        }
    }
    
};


class ComplaintManager {
private:
    PriorityQueue complaintQueue;
    GroupAVLTree<int>* userIDIndex;

public:
    ComplaintManager() : userIDIndex(new GroupAVLTree<int>()) {}

    void registerComplaint(int complaintID, int userID, const string& description, const string& userType) 
	{
        Complaint* newComplaint = new Complaint(complaintID, userID, description);   
        complaintQueue.registerComplaint(newComplaint, userType); //
        userIDIndex->insert(userID, nullptr); // Group index for complaints
    }

    void serviceComplaint() {
        Complaint* complaint = complaintQueue.serviceComplaint();
        if (complaint) {
            cout << "Servicing Complaint: ";
            complaint->display();
        }
    }

    void displayComplaintsByUserID(int userID) {
        cout << "Complaints by UserID: " << userID << endl;
        complaintQueue.displayComplaintsByUserID(userID);
    }
    
    
    void increasePriority(int complaintID)
    {
    	complaintQueue.increasePriority(complaintID);
	}
    
    
    
};



#include <limits>
int main() {

    UserList userList;
    ComplaintManager complaintManager;
    
        // Adding Users
    userList.insertUser(new User(1, "Alice", "alice@example.com", "USA", "Gold"));
    userList.insertUser(new User(2, "Bob", "bob@example.com", "Canada", "Silver"));
    userList.insertUser(new User(3, "Charlie", "charlie@example.com", "USA", "Gold"));
    userList.insertUser(new User(4, "Alpha", "alpha@example.com", "China", "Platinum"));
    userList.insertUser(new User(5, "Sigma", "mehran@example.com", "China", "Platinum"));
    userList.insertUser(new User(6, "Doublin", "doublin@example.com", "Germany", "Gold"));
    userList.insertUser(new User(7, "Thetha", "thetha@example.com", "USA", "Silver"));
    userList.insertUser(new User(8, "Brown", "brown@example.com", "USA", "Gold"));
    
    
    //Complaints
    complaintManager.registerComplaint(101, 1, "Game crash on start", "Gold");
    complaintManager.registerComplaint(102, 2, "Unable to login", "Platinum");
    complaintManager.registerComplaint(103, 3, "Payment not processed", "Silver");
    complaintManager.registerComplaint(104, 4, "Game crash on start", "New");
    complaintManager.registerComplaint(105, 5, "Game is buggy", "Silver");
    complaintManager.registerComplaint(106, 6, "Game crash on start", "Gold");
    complaintManager.registerComplaint(107, 3, "Game crash on start", "New");



    int choice;

    do {
        cout << "\n===== Customer Service Module =====\n";
        cout << "1. Add User\n";
        cout << "2. Search User by UserID\n";
        cout << "3. Delete User by UserID\n";
        cout << "4. Print All Users\n";
        cout << "5. Create Index on Username\n";
        cout << "6. Delete Index on Username\n";
        cout << "7. Search User by Username\n";
        cout << "8. Create Index on Email\n";
        cout << "9. Delete Index on Email\n";
        cout << "10. Search User by Email\n";
        cout << "11. Create Group Index on Country\n";
        cout << "12. Delete Group Index on Country\n";
        cout << "13. List Users by Country\n";
        cout << "14. Create Group Index on Type\n";
        cout << "15. Delete Group Index on Type\n";
        cout << "16. List Users by Type\n";
        cout << "17. Register Complaint\n";
        cout << "18. Service Complaint\n";
        cout << "19. Display Complaints by UserID\n";
        cout << "20. Increase Priority\n";
        cout << "21. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int userID;
                string username, email, country, type;
                cout << "Enter UserID: ";
                cin >> userID;
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Email: ";
                cin >> email;
                cout << "Enter Country: ";
                cin >> country;
                cout << "Enter Type (Platinum, Gold, Silver, Regular, New): ";
                cin >> type;

                userList.insertUser(new User(userID, username, email, country, type));
                break;
            }

            case 2: {
                int userID;
                cout << "Enter UserID to search: ";
                cin >> userID;
                userList.searchByUserID(userID);
                break;
            }

            case 3: {
                int userID;
                cout << "Enter UserID to delete: ";
                cin >> userID;
                userList.deleteUser(userID);
                break;
            }

            case 4:
                userList.printAllUsers();
                break;

            case 5:
                userList.createUsernameIndex();
                break;

            case 6:
                userList.deleteUsernameIndex();
                break;

            case 7: {
                string username;
                cout << "Enter Username to search: ";
                cin >> username;
                userList.searchByUsername(username);
                break;
            }

            case 8:
                userList.createEmailIndex();
                break;

            case 9:
                userList.deleteEmailIndex();
                break;

            case 10: {
                string email;
                cout << "Enter Email to search: ";
                cin >> email;
                userList.searchByEmail(email);
                break;
            }

            case 11:
                userList.createCountryIndex();
                break;

            case 12:
                userList.deleteCountryIndex();
                break;

            case 13: {
                string country;
                cout << "Enter Country to list users: ";
                cin >> country;
                userList.listUsersByCountry(country);
                break;
            }

            case 14:
                userList.createTypeIndex();
                break;

            case 15:
                userList.deleteTypeIndex();
                break;

            case 16: {
                string type;
                cout << "Enter Type to list users: ";
                cin >> type;
                userList.listUsersByType(type);
                break;
            }

            case 17: {
                int complaintID, userID;
                string description, userType;
                cout << "Enter Complaint ID: ";
                cin >> complaintID;
                cout << "Enter UserID: ";
                cin >> userID;
                cout << "Enter Complaint Description: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, description);
                cout << "Enter User Type (Platinum, Gold, Silver, Regular, New): ";
                cin >> userType;

                complaintManager.registerComplaint(complaintID, userID, description, userType);
                break;
            }

            case 18:
                complaintManager.serviceComplaint();
                break;

            case 19: {
                int userID;
                cout << "Enter UserID to display complaints: ";
                cin >> userID;
                complaintManager.displayComplaintsByUserID(userID);
                break;
            }
            
            
            case 20: {
			
            	int complaintID;
            	cout<<"Enter the Complaint ID to increase priority: "<<endl;
            	cin>>complaintID;
            	complaintManager.increasePriority(complaintID);	
				break;
			}
            	

            case 21:
                cout << "Exiting the program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 21);

    return 0;


}
	

