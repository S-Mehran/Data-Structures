#include <iostream>



using namespace std;

class HashTable {
private:
    int size;       
    int* arr;       
    bool rehashFlag; 
	int collisionMethod; 
    int numElements; 
    
    int hashIndex(int key) {
        return key % size;
    }


    int linearProbing(int key, int i) {
        return (hashIndex(key) + i) % size;
    }

    
    int linearProbingWithSteps(int key, int i, int c) {
        return (hashIndex(key) + i * c) % size;
    }

    
    int pseudoRandomProbing(int key, int i, int perm[]) {
        return (hashIndex(key) + perm[i]) % size;
    }

    
    int doubleHashing(int key, int i) {
        int hf2 = 1 + key % (size - 2);
        return (hashIndex(key) + i * hf2) % size;
    }

    void rehash() {
        int newSize = size * 2 + 1; 
        int* newArr = new int[newSize];
        for (int i=0; i<newSize;i++)
        {
        	newArr[i] = -1;
		}


        for (int i = 0; i < size; i++) {
            if (arr[i] != -1) {
                int key = arr[i];
                int index = key % newSize;
                int j = 0;
                while (newArr[index] != -1) {
                    index = (index + 1) % newSize; 
                }
                newArr[index] = key;
            }
        }

        delete[] arr;
        arr = newArr;
        size = newSize;
    }


    double loadFactor() {
        return static_cast<double>(numElements) / size;
    }

public:

    HashTable(bool rehashFlag, int collisionMethod) 
        : rehashFlag(rehashFlag), collisionMethod(collisionMethod), numElements(0) {
        size = 11;
        arr = new int[size];
        for (int i=0; i<size; i++)
        {
        	arr[i] = -1;
		}
    }


    ~HashTable() {
        delete[] arr;
    }
    
    
    
    int Insert(int key) {
        int index = hashIndex(key);
        int i = 0;
        int probeCount = 0;

        while (arr[index] != -1) {
            if (arr[index] == key)
			{
				cout<<"Key already exists"<<endl;
				return probeCount;
			 } 
			 
			 else if (collisionMethod ==1)
			 {
			 	index = linearProbing(key, i++);
			 }
			 else if (collisionMethod == 2)
			 {
			 	index = linearProbingWithSteps(key, ++i, 3);
			 }
			 else if (collisionMethod == 3)
			 {
			 	int perm[] = {1,3,5,7};
			 	index = pseudoRandomProbing(key, ++i, perm);
			 }
			 else if (collisionMethod == 4)
			 {
			 	index = doubleHashing(key, ++i);
			 }
			 else
			 {
			 	cout<<"Out of Range"<<endl;
			 }
			 probeCount++;
        }

        arr[index] = key;
        numElements++;

        if (rehashFlag && loadFactor() > 0.5) {
            rehash();
        }
        return probeCount;
    }


    void Delete(int key) {
        int index = hashIndex(key);
        int i = 0;

        while (arr[index] != -1) {
            if (arr[index] == key) {
                arr[index] = -1;
                numElements--;
                return;
            }
			
			 else if (collisionMethod ==1)
			 {
			 	index = linearProbing(key, i++);
			 }
			 else if (collisionMethod == 2)
			 {
			 	index = linearProbingWithSteps(key, ++i, 3);
			 }
			 else if (collisionMethod == 3)
			 {
			 	int perm[] = {1,3,5,7};
			 	index = pseudoRandomProbing(key, ++i, perm);
			 }
			 else if (collisionMethod == 4)
			 {
			 	index = doubleHashing(key, ++i);
			 }
			 else
			 {
			 	cout<<"Out of Range"<<endl;
			 	return;
			 }
        }
    }


    void Update(int key, int newValue) {
        Delete(key);
        Insert(newValue);
    }

    
    int Access(int key) {
        int index = hashIndex(key);
        int i = 0;

        while (arr[index] != -1) {
            if (arr[index] == key) {
                return index; 
            }
            else if (collisionMethod ==1)
			 {
			 	index = linearProbing(key, i++);
			 }
			 else if (collisionMethod == 2)
			 {
			 	index = linearProbingWithSteps(key, ++i, 3);
			 }
			 else if (collisionMethod == 3)
			 {
			 	int perm[] = {1,3,5,7};
			 	index = pseudoRandomProbing(key, ++i, perm);
			 }
			 else if (collisionMethod == 4)
			 {
			 	index = doubleHashing(key, ++i);
			 }
			 else
			 {
			 	cout<<"Out of Range"<<endl;
			 	return -1;
			 }
        }

        return -1; 
    }

    
    void Print() 
	{
        for (int i=0; i<size; i++)
        {
        	if (arr[i] == -1)
        	{
        		cout<<"Empty"<<endl;
			}
			else 
			{
				cout<<arr[i]<<endl;
			}
		}
    }
    
    
};

void calculateAverageProbes(HashTable& ht, int keys[], int arraySize) 
{
    int totalProbes = 0;
    int numKeys = arraySize;
    
    for (int i=0; i<numKeys; i++) 
	{
        int probeCount = ht.Insert(keys[i]); 
        totalProbes += probeCount;
    }

    double averageProbes = static_cast<double>(totalProbes) / numKeys;
    cout << "Average Probes: " << averageProbes << endl;
}




int main() {
	
    HashTable ht(false, 1); 
    ht.Insert(10);
    ht.Insert(22);
    ht.Insert(31);
    cout<<"Hash Table: "<<endl;
    ht.Print();

    cout << "Access key 22: " << ht.Access(22) << endl;

	
	
	int arrSize = 9;
    int keys[arrSize] = {10, 22, 31, 4, 15, 28, 17, 88, 59};


    HashTable ht1(false, 1); 
    HashTable ht2(false, 2); 
    HashTable ht3(false, 3); 
    HashTable ht4(false, 4); 

    cout << "Without Rehashing:" << endl;


	cout << "Linear Probing:" << endl;
    calculateAverageProbes(ht1, keys, arrSize);

    cout << "Linear Probing with Steps:" << endl;
    calculateAverageProbes(ht2, keys, arrSize);

    cout << "Pseudo-Random Probing:" << endl;
    calculateAverageProbes(ht3, keys, arrSize);

    std::cout << "Double Hashing:" << std::endl;
    calculateAverageProbes(ht4, keys, arrSize);


    HashTable ht5(true, 1); 
    HashTable ht6(true, 2); 
    HashTable ht7(true, 3); 
    HashTable ht8(true, 4); 

    cout << "\nWith Rehashing:" << endl;

    cout << "Linear Probing:" << endl;
    calculateAverageProbes(ht5, keys, arrSize);

    cout << "Linear Probing with Steps:" << endl;
    calculateAverageProbes(ht6, keys, arrSize);

    cout << "Pseudo-Random Probing:" << endl;
    calculateAverageProbes(ht7, keys, arrSize);

    cout << "Double Hashing:" << endl;
    calculateAverageProbes(ht8, keys, arrSize);

    return 0;
}




