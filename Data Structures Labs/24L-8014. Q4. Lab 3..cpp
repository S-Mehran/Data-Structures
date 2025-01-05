#include <iostream>
using namespace std;

void transpose(int** array1, int row, int col)
{
	int** new_array = new int*[col];
	for (int i=0; i<col;i++)
	{
		new_array[i] = new int[row];
	}
	
	for (int i=0; i<col;i++)
	{
		for (int j=0;j<row;j++)
		{
			new_array[i][j] = array1[j][i];
		}
	}
	
	delete[] array1;
	
	for (int i=0; i<col; i++)
	{
		for (int j=0; j<row;j++)
		{
			cout<< new_array[i][j]<<"  ";
		}
		cout<<endl;
	}
}
int main()
{
	int** warehouse;
	int row, col;
	cout<<"Number of Rows: "<<endl;
	cin>>row;
	cout<<"Number of Columns: "<<endl;
	cin>>col;
	warehouse = new int*[row];
	int i,j;
	for (i=0;i<row;i++)
	{
		warehouse[i] = new int[col];
	}

	cout << "Enter " << (row * col) << " numbers to the Array\n";

	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

		cout << "Enter the elements at Row " << i + 1 << " Column " << j + 1 << endl;

	cin >> warehouse[i][j];
	
	

}
}


	cout << "Here is your 2D Array:" << endl;

	for (i = 0; i < row; i++) {

	for (j = 0; j < col; j++) {

	cout << warehouse[i][j] << ' ';

	}

	cout << endl;

	}
	
	cout<<"Following is the transposed Array: "<<endl;
	transpose(warehouse, row, col);
	

	for (i = 0; i < row; i++) {

	delete[] warehouse[i];

}

	delete[] warehouse;

	return 0;
	
}
