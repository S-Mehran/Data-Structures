#include <iostream>
#include <string>
using namespace std;

int findGDC(int a, int b)
{
	if (b==0)
	{
		return a;
	}
	else if (b>a)
	{
		return 0;
	}
	else
	{
		 int var = findGDC(b, a%b);
		 return var;
	}
	
}


int binarySearchInRange(int arr[], int low, int high, int target)
{
	int middle = (low+high)/2;
	if (arr[middle] == target)
	{
		cout<<"The target value "<<target<<" Present at index: "<<middle<<endl;
		return middle;
	}
	else if(low>=high)
	{
		cout<<"The target value "<<target<<" is Not Present"<<endl;
		return -1;
	}
	else if(target<arr[middle])
	{
		return binarySearchInRange(arr, low, middle-1, target);
	}
	else
	{
		return binarySearchInRange(arr, middle+1, high, target);
	}
}

void generateSubsequences(string str, string current, int index)
{
	int n = str.length();
	if (index == n)
	{
		cout<<current<<" ";
		return;
	}
	
	generateSubsequences(str, current+str[index], index+1);
	generateSubsequences(str, current, index+1);
	
}




int main()
{
	//Question 1
	cout<<"GDC of (10, 2) is: "<<findGDC(10, 2)<<endl;
	cout<<"GDC of (20, 4) is: "<<findGDC(20, 4)<<endl;
	cout<<endl;
	
	//Question 2
	int array[] = {10, 20, 30, 40, 50, 60};
	binarySearchInRange(array, 1, 6, 50);
	binarySearchInRange(array, 1, 6, 100);
	cout<<endl;
	
	//Question 3
	string var = "abc";
	cout<<"All subsets of 'abc' are: ";
	generateSubsequences(var, "", 0);
	
	
}
