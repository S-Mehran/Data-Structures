#include <vector>
#include <list>
#include <string>
#include <map>
#include <iostream>
#include <functional>

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

class Complaint;
class Node {
public:
    User* user;
    Node* next;
    Node* prev;
              // Pointer to a User object
    Complaint* complaint; // Pointer to a Complaint object
              // Pointer to the previous node

    Node(User* u)
    {
    	user = u;
    	next = nullptr;
    	prev = nullptr;
	}
	
	
  // Constructor for Complaint nodes
    Node(Complaint* c) : user(nullptr), complaint(c), next(nullptr), prev(nullptr) {}
};

class HashTable {
private:
    struct HashNode {
        int userID;
        Node* userNode; // Pointer to the User node in the doubly linked list
        bool isOccupied;

        HashNode() : userID(-1), userNode(nullptr), isOccupied(false) {}
    };

    vector<HashNode> table;
    int capacity;
    int size;

    // Universal Hash Function
    int hash1(int key) {
        return key % capacity;
    }

    int hash2(int key) {
        return 1 + (key % (capacity - 1));
    }

    int doubleHashing(int key, int i) {
        return (hash1(key) + i * hash2(key)) % capacity;
    }

public:
    HashTable(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        table = vector<HashNode>(capacity);
    }

    void insert(int userID, Node* userNode) {
        if (size >= capacity / 2) {
            cout << "Rehashing required (not implemented here)." << endl;
            return;
        }

        int i = 0, index;
        do {
            index = doubleHashing(userID, i++);
            if (!table[index].isOccupied) {
                table[index].userID = userID;
                table[index].userNode = userNode;
                table[index].isOccupied = true;
                size++;
                return;
            }
        } while (i < capacity);
        cout << "Hash Table Overflow" << endl;
    }

    Node* search(int userID) {
        int i = 0, index;
        do {
            index = doubleHashing(userID, i++);
            if (table[index].isOccupied && table[index].userID == userID) {
                return table[index].userNode;
            }
        } while (i < capacity && table[index].isOccupied);
        return nullptr;
    }

    void remove(int userID) {
        int i = 0, index;
        do {
            index = doubleHashing(userID, i++);
            if (table[index].isOccupied && table[index].userID == userID) {
                table[index].isOccupied = false;
                size--;
                return;
            }
        } while (i < capacity && table[index].isOccupied);
    }

    // Check if the hash table is empty
    bool empty() const {
        return size == 0;
    }

    // Clear the hash table
    void clear() {
        for (auto& node : table) {
            node.isOccupied = false;
        }
        size = 0;
        cout << "Hash table cleared." << endl;
    }
};



class HashTableChaining {
private:
    struct HashNode {
        string key;    // Username or Email
        Node* userNode; // Pointer to corresponding node in the doubly linked list

        HashNode(string k, Node* n) : key(k), userNode(n) {}
    };

    vector<list<HashNode>> table;
    int capacity;

    int hash(string key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue = (hashValue * 31 + c) % capacity;
        }
        return hashValue;
    }

public:
    HashTableChaining(int cap) : capacity(cap) {
        table.resize(capacity);
    }

    void insert(string key, Node* userNode) 
	{
        int index = hash(key);
        for (auto& node : table[index]) {
            if (node.key == key) {
                node.userNode = userNode; // Update existing key
                return;
            }
        }
        table[index].emplace_back(key, userNode);
    }

    Node* search(string key) {
        int index = hash(key);
        for (const auto& node : table[index]) {
            if (node.key == key) {
                return node.userNode;
            }
        }
        return nullptr;
    }

    void remove(string key) {
        int index = hash(key);
        table[index].remove_if([&](const HashNode& node) { return node.key == key; });
    }
    
    
    bool empty() const {
    for (const auto& chain : table) {
        if (!chain.empty()) {
            return false; // Found a non-empty chain
        }
    }
    return true; // All chains are empty
}


	void clear() {
    for (auto& chain : table) {
        chain.clear(); // Clear each chain (linked list)
    }
    cout << "Hash table cleared." << endl;
}

};



class GroupHashTable {
private:
    struct GroupNode {
        string key;              // Attribute value (e.g., Country or Type)
        list<Node*> userNodes;   // List of User nodes
        bool isOccupied;         // Flag for collision handling

        GroupNode() : key(""), isOccupied(false) {}
    };

    vector<GroupNode> table;
    int capacity;
    int size;

    // Universal Hash Function
    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % capacity;
        }
        return hash;
    }

    // Linear Probing for Country Index
    int linearProbing(const string& key, int i) {
        return (hashFunction(key) + i) % capacity;
    }

    // Quadratic Probing for Type Index
    int quadraticProbing(const string& key, int i) {
        return (hashFunction(key) + i * i) % capacity;
    }

public:
    GroupHashTable(int initialCapacity = 10) : capacity(initialCapacity), size(0) {
        table = vector<GroupNode>(capacity);
    }

    void insert(const string& key, Node* userNode, bool useLinearProbing = true) {
        int i = 0, index;

        do {
            index = useLinearProbing ? linearProbing(key, i) : quadraticProbing(key, i);
            if (!table[index].isOccupied || table[index].key == key) {
                if (!table[index].isOccupied) {
                    table[index].key = key;
                    table[index].isOccupied = true;
                }
                table[index].userNodes.push_back(userNode);
                size++;
                return;
            }
            i++;
        } while (i < capacity);

        cout << "Hash Table Overflow" << endl;
    }

    void remove(const string& key, bool useLinearProbing = true) {
        int i = 0, index;

        do {
            index = useLinearProbing ? linearProbing(key, i) : quadraticProbing(key, i);
            if (table[index].isOccupied && table[index].key == key) {
                table[index].userNodes.clear();
                table[index].isOccupied = false;
                size--;
                return;
            }
            i++;
        } while (i < capacity);

        cout << "Key not found in hash table." << endl;
    }

    list<Node*> search(const string& key, bool useLinearProbing = true) {
        int i = 0, index;

        do {
            index = useLinearProbing ? linearProbing(key, i) : quadraticProbing(key, i);
            if (table[index].isOccupied && table[index].key == key) {
                return table[index].userNodes;
            }
            i++;
        } while (i < capacity);

        return list<Node*>();
    }

    void display() {
        for (int i = 0; i < capacity; ++i) {
            if (table[i].isOccupied) {
                cout << table[i].key << " -> ";
                for (const auto& node : table[i].userNodes) {
                    cout << node->user->userName << ", ";
                }
                cout << endl;
            }
        }
    }
	
	 


    // Check if the hash table is empty
    bool empty() const {
        return size == 0;
    }

    // Clear the hash table
    void clear() {
        for (auto& node : table) {
            node.isOccupied = false;
        }
        size = 0;
        cout << "Hash table cleared." << endl;
    }

};






class UserList {
private:
    Node* head;
    HashTable userIDIndex;
    HashTableChaining usernameIndex;
    HashTableChaining emailIndex;
    GroupHashTable countryIndex;
    GroupHashTable typeIndex;

public:
    UserList(int capacity) 
        : head(nullptr), userIDIndex(capacity), usernameIndex(capacity), emailIndex(capacity), countryIndex(10), typeIndex(10) {}

    void insertUser(User* user) {
        Node* newNode = new Node(user);

        // Insert into doubly linked list
        if (!head || head->user->userID > user->userID) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->user->userID < user->userID) {
                current = current->next;
            }
            newNode->next = current->next;
            if (current->next) current->next->prev = newNode;
            current->next = newNode;
            newNode->prev = current;
        }

        // Update Hash indices
        userIDIndex.insert(user->userID, newNode);
        usernameIndex.insert(user->userName, newNode);
        emailIndex.insert(user->email, newNode);
    }

    Node* searchUserByID(int userID) {
        return userIDIndex.search(userID);
    }

    Node* searchUserByUsername(string username) {
        return usernameIndex.search(username);
    }

    Node* searchUserByEmail(string email) {
        return emailIndex.search(email);
    }

    void deleteUser(int userID) {
        Node* node = userIDIndex.search(userID);
        if (!node) return;

        // Remove from doubly linked list
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == head) head = node->next;

        // Remove from hash indices
        userIDIndex.remove(userID);
        usernameIndex.remove(node->user->userName);
        emailIndex.remove(node->user->email);

        delete node;
    }

    void printAllUsers() {
        Node* current = head;
        while (current) {
            current->user->display();
            current = current->next;
        }
    }
    
    
    void createUsernameIndex() {
    if (!usernameIndex.empty()) {
        cout << "Username Index already exists." << endl;
        return;
    }
    //Inserting all elements into Username Index
    Node* current = head;
    while (current) {
        usernameIndex.insert(current->user->userName, current);
        current = current->next;
    }

    cout << "Username Index created." << endl;
}


	void deleteUsernameIndex() {
    if (usernameIndex.empty()) {
        cout << "Username Index does not exist." << endl;
        return;
    }

    usernameIndex.clear();
    cout << "Username Index deleted." << endl;
}


//Searching By Username. 
void searchByUsername(const string& username) {
    if (usernameIndex.empty()) {
        cout << "Username Index does not exist. Please create the index first." << endl;
        return;
    }

    Node* result = usernameIndex.search(username); //Index is found using hash function and linked list is traversed in the given index
    if (result) {
        result->user->display();
    } else {
        cout << "User not found by username: " << username << endl;
    }
}



void createEmailIndex() 
{
    if (!emailIndex.empty()) {
        cout << "Email Index already exists." << endl;
        return;
    }

    Node* current = head;
    while (current) {
        emailIndex.insert(current->user->email, current);
        current = current->next;
    }

    cout << "Email Index created." << endl;
}



void deleteEmailIndex() {
    if (emailIndex.empty()) {
        cout << "Email Index does not exist." << endl;
        return;
    }

    emailIndex.clear();
    cout << "Email Index deleted." << endl;
}


void searchByEmail(const string& email) {
    if (emailIndex.empty()) {
        cout << "Email Index does not exist. Please create the index first." << endl;
        return;
    }
	//Searching is done through index and thus chains are traversed at that index
    Node* result = emailIndex.search(email);
    if (result) {
        result->user->display();
    } else {
        cout << "User not found by email: " << email << endl;
    }
}



void displayIndices() {
    cout << "Indices Status:" << endl;

    if (!usernameIndex.empty()) {
        cout << "- Username Index: Exists" << endl;
    } else {
        cout << "- Username Index: Does not exist" << endl;
    }

    if (!emailIndex.empty()) {
        cout << "- Email Index: Exists" << endl;
    } else {
        cout << "- Email Index: Does not exist" << endl;
    }
}


//================GROUP INDICES=====================
    // Create Group Index on Country
    void createCountryIndex() {
        if (!countryIndex.empty()) {
        cout << "Country Index already Exists." << endl;
        return;
    }
		//Using Linear Probing for Insertion such that Clusters of Users of same countries are formed
		Node* current = head;
        while (current) {
            countryIndex.insert(current->user->country, current, true); // Linear Probing
            current = current->next;
        }
        cout << "Country Index created." << endl;
    }

    // Delete Group Index on Country
    void deleteCountryIndex() {
    	if (countryIndex.empty()) {
        cout << "Country Index does not exist." << endl;
        return;
    }
        countryIndex = GroupHashTable(10);
        cout << "Country Index deleted." << endl;
    }

    // List Users by Country
    void listUsersByCountry(const string& country) {
    	if (countryIndex.empty()) {
        cout << "Country Index does not exist." << endl;
        return;
    }
		//Using Linear probing for Searching
        list<Node*> users = countryIndex.search(country, true);
        if (!users.empty()) {
            cout << "Users in " << country << ":" << endl;
            for (const auto& node : users) {
                node->user->display();
            }
        } else {
            cout << "No users found in " << country << "." << endl;
        }
    }

    // Display Group Index for Country
    void displayCountryIndex() {
        cout << "Country Index:" << endl;
        countryIndex.display();
    }

    // Create Group Index on Type
    void createTypeIndex() {
    	if (!typeIndex.empty()) {
        cout << "Country Index already exists." << endl;
        return;
    }
    //Using Quadratic Probing to Insert elements Type Index
        Node* current = head;
        while (current) {
            typeIndex.insert(current->user->type, current, false); // Quadratic Probing
            current = current->next;
        }
        cout << "Type Index created." << endl;
    }

    // Delete Group Index on Type
    void deleteTypeIndex() {
    	if (typeIndex.empty()) {
        cout << "Country Index does not exist." << endl;
        return;
    }
        typeIndex = GroupHashTable(10);
        cout << "Type Index deleted." << endl;
    }

    // List Users by Type
    void listUsersByType(const string& type) {
        if (typeIndex.empty()) {
        cout << "Country Index does not exist." << endl;
        return;
    }
    //Using Quadratic Probing to Search Users
		list<Node*> users = typeIndex.search(type, false);
        if (!users.empty()) {
            cout << "Users of type " << type << ":" << endl;
            for (const auto& node : users) {
                node->user->display();
            }
        } else {
            cout << "No users found of type " << type << "." << endl;
        }
    }

    // Display Group Index for Type
    void displayTypeIndex() {
        cout << "Type Index:" << endl;
        typeIndex.display();
    }


	//Second Country Display Function required for Complaint Management
	list<Node*> listUsersByCountryComplaint(const string& country) {
    list<Node*> users; // List to hold the users from the specified country
    Node* current = head;

    while (current) {
        if (current->user->country == country) {
            users.push_back(current); // Add matching user nodes to the list
        }
        current = current->next;
    }

    return users;
}




};





class Complaint {
public:
    int complaintID;
    int userID;
    string userType;
    string description;

    Complaint(int cID, int uID, const string& uType, const string& desc)
        : complaintID(cID), userID(uID), userType(uType), description(desc) {}

    void display() const {
        cout << "ComplaintID: " << complaintID
             << ", UserID: " << userID
             << ", UserType: " << userType
             << ", Description: " << description << endl;
    }
};

class ComplaintNode {
public:
    Complaint* complaint;
    ComplaintNode* next;

    // Constructor
    ComplaintNode(Complaint* c) : complaint(c), next(nullptr) {}
};



class PriorityQueue {
private:
    struct HeapNode {
        int priority;
        Complaint* complaint;

        HeapNode(int p, Complaint* c) : priority(p), complaint(c) {}
    };

    vector<HeapNode> heap;
    map<string, int> typePriority = {{"Platinum", 5}, {"Gold", 4}, {"Silver", 3}, {"Regular", 2}, {"New", 1}};

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int index) {
        while (index != 0 && heap[parent(index)].priority < heap[index].priority) {
            swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }

//Heapify is done on the basis of priority
    void heapifyDown(int index) {
        int maxIndex = index;
        int l = leftChild(index);
        if (l < heap.size() && heap[l].priority > heap[maxIndex].priority)
            maxIndex = l;

        int r = rightChild(index);
        if (r < heap.size() && heap[r].priority > heap[maxIndex].priority)  //Max Priority customer will be at the root
            maxIndex = r;

        if (index != maxIndex) {
            swap(heap[index], heap[maxIndex]);
            heapifyDown(maxIndex);
        }
    }

public:
    void registerComplaint(Complaint* complaint) {
        int priority = typePriority[complaint->userType];
        heap.push_back(HeapNode(priority, complaint));
        heapifyUp(heap.size() - 1);
    }

    Complaint* serviceComplaint() {
        if (heap.empty()) {
            cout << "No complaints to service." << endl;
            return nullptr;
        }

        Complaint* topComplaint = heap[0].complaint;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return topComplaint;
    }

    void increasePriority(int complaintID) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i].complaint->complaintID == complaintID) {
                heap[i].priority = 6; // Highest priority
                heapifyUp(i);
                cout << "Priority increased for ComplaintID: " << complaintID << endl;
                return;
            }
        }
        cout << "Complaint not found." << endl;
    }

    void displayComplaints() const {
        cout << "All complaints in the queue:" << endl;
        for (const auto& node : heap) {
            node.complaint->display();
        }
    }
};


class ComplaintManager {
private:
    PriorityQueue complaintQueue;
    GroupHashTable userIDIndex; // Group index for complaints by UserID

public:
    ComplaintManager() : userIDIndex(10) {}

//    void registerComplaint(int complaintID, int userID, const string& userType, const string& description) {
//        Complaint* newComplaint = new Complaint(complaintID, userID, userType, description);
//        complaintQueue.registerComplaint(newComplaint);
//        userIDIndex.insert(to_string(userID), new ComplaintNode(newComplaint), true); // Linear probing
//        cout << "Complaint registered." << endl;
//    }
    
    void registerComplaint(int complaintID, int userID, const string& userType, const string& description)
    {
    	 Complaint* newComplaint = new Complaint(complaintID, userID, userType, description);
    	 complaintQueue.registerComplaint(newComplaint);
    	 userIDIndex.insert(to_string(userID), new Node(newComplaint), true);
    	 cout << "Complaint registered." << endl;
	}

    void serviceComplaint() {
        Complaint* complaint = complaintQueue.serviceComplaint();
        if (complaint) {
            cout << "Servicing Complaint: ";
            complaint->display();
        }
    }

    void increasePriority(int complaintID) {
        complaintQueue.increasePriority(complaintID);
    }

    void displayComplaintsByUserID(int userID) {
        cout << "Complaints by UserID " << userID << ":" << endl;
        list<Node*> complaints = userIDIndex.search(to_string(userID), true);
        for (const auto& node : complaints) {
            node->complaint->display();
        }
    }

    void displayComplaintsByCountry(UserList& userList, const string& country) {
        cout << "Complaints by users from " << country << ":" << endl;
        list<Node*> users = userList.listUsersByCountryComplaint(country); // From UserList
        for (const auto& user : users) {
            displayComplaintsByUserID(user->user->userID);
        }
    }
};




int main() {
    UserList userList(100);
    userList.insertUser(new User(1, "Alice", "alice@example.com", "USA", "Gold"));
    userList.insertUser(new User(2, "Bob", "bob@example.com", "Canada", "Silver"));
    userList.insertUser(new User(3, "Charlie", "charlie@example.com", "USA", "Platinum"));
    userList.insertUser(new User(4, "Alpha", "alpha@example.com", "Pakistan", "Gold"));
    userList.insertUser(new User(5, "Delta", "delta@example.com", "Germany", "Silver"));
    userList.insertUser(new User(6, "Omega", "omega@example.com", "USA", "Platinum"));



    User* user1 = new User(7, "Mehran", "mehran@gmail.com", "Pakistan", "Gold");
    userList.insertUser(user1);
    

    // Create and Display Group Index for Country
    userList.createCountryIndex();
    userList.displayCountryIndex();

    // List Users by Country
    userList.listUsersByCountry("USA");

    // Create and Display Group Index for Type
    userList.createTypeIndex();
    userList.displayTypeIndex();

    // List Users by Type
    userList.listUsersByType("Gold");

    
    
       // Register complaints
    ComplaintManager complaintManager;
	complaintManager.registerComplaint(101, 1, "Gold", "Login issues");
    complaintManager.registerComplaint(102, 2, "Silver", "Payment not processed");
    complaintManager.registerComplaint(103, 3, "Platinum", "Game crashes");
    
    
        complaintManager.serviceComplaint();

    // Increase priority
    complaintManager.increasePriority(102);

    // Display complaints by user
    complaintManager.displayComplaintsByUserID(1);


    int choice;
    do {
        cout << "\n===== User Management with Hash Indices =====\n";
        cout << "1. Create Username Index\n";
        cout << "2. Delete Username Index\n";
        cout << "3. Search User by Username\n";
        cout << "4. Create Email Index\n";
        cout << "5. Delete Email Index\n";
        cout << "6. Search User by Email\n";
        cout << "7. Display Indices Status\n";
        cout << "8. Create Group Index on Country\n";
        cout << "9. Delete Group Index on Country\n";
        cout << "10. Search Users by Country Name\n";
        cout << "11. Create Group Index on User Type\n";
        cout << "12. Delete Group Index on User Type\n";
        cout << "13. Search Users By Type\n";
        cout << "14. Display Type Index\n";
        cout << "15. Display Country Index\n";
        cout << "16. Register Complaint\n";
        cout << "17. Service Complaint\n";
        cout << "18. Increase User Priority\n";
        cout << "19. Display Complaint of User\n";
        cout << "20. Display Complaints by Country\n";
        cout << "21. Exit\n";
		cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                userList.createUsernameIndex();
                break;

            case 2:
                userList.deleteUsernameIndex();
                break;

            case 3: {
                string username;
                cout << "Enter Username to search: ";
                cin >> username;
                userList.searchByUsername(username);
                break;
            }

            case 4:
                userList.createEmailIndex();
                break;

            case 5:
                userList.deleteEmailIndex();
                break;

            case 6: {
                string email;
                cout << "Enter Email to search: ";
                cin >> email;
                userList.searchByEmail(email);
                break;
            }

            case 7:
                userList.displayIndices();
                break;

            
            
            case 8: {
            	userList.createCountryIndex();
				break;
			}
			case 9: {
				userList.deleteCountryIndex();
				break;
			}
			case 10: {
				string country;
				cout<<"Enter the Country: ";
				cin>>country;
				userList.listUsersByCountry(country);
				break;
			}
			
			case 11: {
				userList.createTypeIndex();
				break;
			}
			
			case 12: {
				userList.deleteTypeIndex();
				break;
			}
			
			case 13: {
				string type;
				cout<<"Enter the Type of User: ";
				cin>>type;
				userList.listUsersByType(type);
				break;
			}
			
			case 14: {
				userList.displayTypeIndex();
				break;
			}
			case 15:
				userList.displayCountryIndex();
				break;
				
			case 16: {
				int id, userid;
				string usertype, description;
				cout<<"Enter Complaint ID: ";
				cin>>id;
				cout<<"Enter User ID: ";
				cin>>userid;
				cout<<"Enter the User Type: ";
				cin.ignore();
				getline(cin, usertype);
				cout<<"Enter the Complaint Description: ";
				cin.ignore();
				getline(cin, description);
				complaintManager.registerComplaint(id, userid, usertype, description);
				break;
			}
			
			case 17: {
				complaintManager.serviceComplaint();
				break;
			}
			
			case 18: {
				int id;
				cout<<"Enter the Complaint ID: ";
				cin>>id;
				complaintManager.increasePriority(id);
				break;
			}
			
			case 19: {
				int userid;
				cout<<"Enter the User ID to be searched: ";
				cin>>userid;
				complaintManager.displayComplaintsByUserID(userid);
				break;
			}
			
			case 20: {
				string country;
				cout<<"Enter the Country Name: ";
				cin>>country;
				complaintManager.displayComplaintsByCountry(userList, country);
				break;
			}
			case 21:
                cout << "Exiting program." << endl;
                break;
				

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 21);

    return 0;
}

