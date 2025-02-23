#include <iostream>
#include <string>
using namespace std;


class MinHeap {
private:
	
	class Node 
	{
	public:
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        this->left = nullptr;
        this->right = nullptr;
    }
};
	
    Node** heapArr;
    int size;
    int capacity;

    void heapifyDown(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heapArr[left]->freq < heapArr[smallest]->freq)
            smallest = left;
        if (right < size && heapArr[right]->freq < heapArr[smallest]->freq)
            smallest = right;

        if (smallest != idx) {
            swap(heapArr[idx], heapArr[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int idx) {
        int parent = (idx - 1) / 2;
        if (idx && heapArr[idx]->freq < heapArr[parent]->freq) {
            swap(heapArr[idx], heapArr[parent]);
            heapifyUp(parent);
        }
    }

public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        heapArr = new Node*[capacity];

        size = 0;
    }

    ~MinHeap() {
        delete[] heapArr;
    }

    void insert(Node* node) {
        if (size == capacity) {
            cout << "Heap Overflow\n";
            return;
        }

        heapArr[size] = node;
        heapifyUp(size);
        size++;
    }

    Node* extractMin() {
        if (size <= 0)
            return nullptr;

        if (size == 1) {
            size--;
            return heapArr[0];
        }

        Node* root = heapArr[0];
        heapArr[0] = heapArr[size - 1];
        size--;
        heapifyDown(0);

        return root;
    }

    int getSize() {
        return size;
    }
    
    
    
    
    void generateHuffmanCodes(Node* root, string code, string huffmanCodes[256]) {
    if (!root) 
    {
    	return;
	}

    if (!root->left && !root->right) 
	{
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}


void huffmanCoding(string input) 
{
    int freq[256] = {0};
    for (char ch : input) 
	{
        freq[ch]++;
    }


    MinHeap minHeap(256);
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            minHeap.insert(new Node((char)i, freq[i]));
        }
    }


    while (minHeap.getSize() > 1) {
        Node* left = minHeap.extractMin();
        Node* right = minHeap.extractMin();

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        minHeap.insert(merged);
    }

    Node* root = minHeap.extractMin();


    string huffmanCodes[256];
    generateHuffmanCodes(root, "", huffmanCodes);


    cout << "Frequency Table:\n";
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            cout << (char)i << ": " << freq[i] << "\n";
        }
    }

 
    cout << "\nHuffman Codes:\n";
    for (int i = 0; i < 256; i++) {
        if (!huffmanCodes[i].empty()) {
            cout << (char)i << ": " << huffmanCodes[i] << "\n";
        }
    }

 
    cout << "\nCompressed Binary String:\n";
    string compressedString = "";
    for (char ch : input) {
        compressedString += huffmanCodes[ch];
    }
    cout << compressedString << "\n";
}

};




int main() 
{
    string input;
    cout << "Enter the string to compress: ";
    cin >> input;
    
    MinHeap code1(256);
    code1.huffmanCoding(input);


    return 0;
}

