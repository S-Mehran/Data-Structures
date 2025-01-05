#include <iostream>

using namespace std;

void matrix_multiply(int** array1, int**array2, int row1, int col1, int row2, int col2)
{
	int multiple;
	int** array3 = new int*[row1];
	for (int i=0; i<row1; i++)
	{
		array3[i] = new int[col1];
	}
	if (row1!=row2 && col1!=col2)
	{
		return;
	}
	else 
	{
	for (int i=0; i<row1;i++)
	{
		for (int j=0; j<col1;j++)
		{
			multiple = array1[i][j] * array2[i][j];
//			cout << "\n"<<multiple<<endl;
			array3[i][j] = multiple;
		}
//		cout<<endl;
	}
}

cout << "New array with multiplied values is as follows: "<<endl;
for (int i=0; i<row1; i++)
{
	for (int j=0; j<col1;j++)
	{
		cout <<array3[i][j]<<' ';
	}
	cout<<endl;
}

}


int main()
{
	int row1 = 3;
	int row2 = 3;
	int col1 = 3;
	int col2=3;
	int** array1 = new int*[row1];
    for (int i = 0; i < row1; ++i) {
        array1[i] = new int[col1];
    }

    
    array1[0][0] = 101; array1[0][1] = 102; array1[0][2] = 103;
    array1[1][0] = 101; array1[1][1] = 104; array1[1][2] = 105;
    array1[2][0] = 106; array1[2][1] = 101; array1[2][2] = 107;
    
    
    int** array2 = new int*[row2];
    for (int i = 0; i < row1; ++i) {
        array2[i] = new int[col2];
    }
    
    array2[0][0] = 1; array2[0][1] = 2; array2[0][2] = 3;
    array2[1][0] = 10; array2[1][1] = 10; array2[1][2] = 5;
    array2[2][0] = 6; array2[2][1] = 1; array2[2][2] = 7;
    
    matrix_multiply(array1, array2, row1, col1, row2, col2);
}
