#include <iostream>
#include <string>
using namespace std;

class HashTable {
private:
    struct Node {
        string key; 
        int value;  
        Node* next; 

        Node(string k, int v) 
		{
        	key = k;
        	value = v;
        	next = nullptr;
		
		}
    };

    int size;     
    Node** table; 

    int hashCode(string& key) {
        int hash = 0;
        int a = 33;
        for (int i = 0; i < key.length(); i++) {
            hash = (hash * a + key[i]) % size;
        }
        return hash;
    }

public:
    
    HashTable(int tableSize) 
	{
		size = tableSize;
        table = new Node*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    
    void Insert(string key, int value) 
	{
        int index = hashCode(key);
        Node* newNode = new Node(key, value);

    
        newNode->next = table[index];
        table[index] = newNode;
    }

    
    void Delete(string key) 
	{
        int index = hashCode(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr && current->key != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Key not found: " << key << endl;
            return;
        }

        if (prev == nullptr) {
            table[index] = current->next; 
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "Key deleted: " << key << endl;
    }

 
    void Update(string key, int newValue) {
        int index = hashCode(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                current->value = newValue;
                return;
            }
            current = current->next;
        }

        cout << "Key not found: " << key << endl;
    }

 
    int Access(string key) {
        int index = hashCode(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        cout << "Key not found: " << key << endl;
        return -1; 
    }


    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }
};





int main() {

    HashTable ht(53);


    ht.Insert("Karachi", 45);
    ht.Insert("Lahore", 55);
    ht.Insert("Islamabad", 30);
    ht.Insert("Peshawar", 50);
    ht.Insert("Dhaka", 40);
    ht.Insert("Quetta", 30);
    ht.Insert("Delhi", 100);
    ht.Insert("New York", 20);
    ht.Insert("Layyah", 30);
    ht.Insert("Multan", 50);
    ht.Insert("Balakot", 40);
    ht.Insert("Rawalpindi", 40);



    ht.Update("Lahore", 60);


    int index = ht.Access("Lahore");
    if (index != -1) 
	{
        cout << "Pollution index of Lahore: " << index << "%" << endl;
    }
    index = ht.Access("Delhi");
    if (index != -1) 
	{
        cout << "Pollution index of Lahore: " << index << "%" << endl;
    }
    
    index = ht.Access("Quetta");
    if (index != -1) 
	{
        cout << "Pollution index of Lahore: " << index << "%" << endl;
    }


    ht.Delete("Quetta");


    ht.Access("Quetta");

    return 0;
}

