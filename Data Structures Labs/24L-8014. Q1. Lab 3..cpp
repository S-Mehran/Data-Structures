#include <iostream>
using namespace std;



void seatingPosition(char** array, int row, int col, char Student)
{
	for (int i=0; i<row;i++)
	{
		for (int j=0; j<col; j++)
		{
			if (Student == array[i][j])
			{
				cout << "Student is sitting at Row No "<<i<<" and Column No "<< j;
				return;
			}



		}
		
	}
	cout<<"Student does not exist in class";
	
}




int main()
{
	char** classroom;
	int row, col;
	cout<<"Number of Rows: "<<endl;
	cin>>row;
	cout<<"Number of Columns: "<<endl;
	cin>>col;
	classroom = new char*[row];
	int i,j;
	for (i=0;i<row;i++)
	{
		classroom[i] = new char[col];
	}
	cout << "Enter " << (row * col) << " students to the Class\n";

	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

		cout << "Enter the elements at Row " << i + 1 << " Column " << j + 1 << endl;

	cin >> classroom[i][j];
}
}
	
	cout << "Here is your 2D Array:" << endl;

	for (i = 0; i < row; i++) {

	for (j = 0; j < col; j++) {

	cout << classroom[i][j] << ' ';

	}

	cout << endl;

	}
	
	seatingPosition(classroom, row, col, 'f');
	

	for (i = 0; i < row; i++) {

	delete[] classroom[i];

}

	delete[] classroom;

	return 0;
}
