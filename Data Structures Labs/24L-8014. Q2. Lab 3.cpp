#include <iostream>
using namespace std;

int countProductFrequency(int** inventory, int rows, int cols, int productID) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (inventory[i][j] == productID) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int rows = 3;
    int cols = 3;
    int productID = 101;

 
    int** inventory = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        inventory[i] = new int[cols];
    }

    inventory[0][0] = 101; inventory[0][1] = 102; inventory[0][2] = 103;
    inventory[1][0] = 101; inventory[1][1] = 104; inventory[1][2] = 105;
    inventory[2][0] = 106; inventory[2][1] = 101; inventory[2][2] = 107;

    int frequency = countProductFrequency(inventory, rows, cols, productID);
    cout << "Product ID " << productID << " appears " << frequency << " times in the inventory." << endl;

    for (int i = 0; i < rows; ++i) {
        delete[] inventory[i];
    }
    delete[] inventory;

    return 0;
}

