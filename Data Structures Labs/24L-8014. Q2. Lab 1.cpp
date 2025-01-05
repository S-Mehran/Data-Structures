#include <iostream>
#include <vector>
#include <chrono> // For measuring time
#include <algorithm> // For std::sort
#include <iomanip> // For setting precision of time output

using namespace std;

// Function to display the array
ostream& operator<<(ostream& os, const vector<int>& arr) {
    for (const int& elem : arr) {
        os << elem << " ";
    }
    return os;
}

// Function to input the array elements
istream& operator>>(istream& is, vector<int>& arr) {
    for (int& elem : arr) {
        is >> elem;
    }
    return is;
}

// Bubble Sort Algorithm
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort Algorithm
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Function to insert an element in a sorted array
void insertInSortedArray(vector<int>& arr, int element) {
    auto pos = lower_bound(arr.begin(), arr.end(), element);
    arr.insert(pos, element);
}

int main() {
    // Request user input for the array size
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> arr(size);
    cout << "Enter " << size << " elements:" << endl;
    cin >> arr;

    // Display the original array
    cout << "Original array: " << arr << endl;

    // Bubble Sort
    vector<int> bubbleArr = arr; // Copy of the original array
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(bubbleArr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> bubbleSortDuration = end - start;

    // Selection Sort
    vector<int> selectionArr = arr; // Copy of the original array
    start = chrono::high_resolution_clock::now();
    selectionSort(selectionArr);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> selectionSortDuration = end - start;

    // Display the sorted arrays and timing
    cout << "Array after Bubble Sort: " << bubbleArr << endl;
    cout << "Time taken by Bubble Sort: " << fixed << setprecision(6) << bubbleSortDuration.count() << " seconds" << endl;

    cout << "Array after Selection Sort: " << selectionArr << endl;
    cout << "Time taken by Selection Sort: " << fixed << setprecision(6) << selectionSortDuration.count() << " seconds" << endl;

    // Insert a new element
    int newElement;
    cout << "Enter a new element to insert: ";
    cin >> newElement;
    insertInSortedArray(bubbleArr, newElement);

    // Display the final array after insertion
    cout << "Array after inserting new element: " << bubbleArr << endl;

    return 0;
}

