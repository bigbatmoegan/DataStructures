#include <iostream>
#include <ctime>
#include <time.h>
#include <stdlib.h>

void placement(int array[], int Size, int x)
{
	int max=x;
	int left=2*x+1;
	int right=2*x+2;
	int temp=0;
	//check if left is larger than root
	if(left<size && array[left]>array[max])
	{
		max=left;
	}
	//check if right is larger than root
	if(right<size && array[right]>array[max])
	{
		max=right;
	}
	if(max!=x)
	{
		temp=array[i];
		array[i]=array[max];
		array[max]=temp;
		//change affected sub tree
		placement(array, Size, max)
	}
}

void heapSort(int array[], int Size)
{
int main()
{
	srand(time(NULL));
	int size;
	int element;
	std::cout << "Please enter the size of the array: " ;
	std::cin >> size;
	int *array=new int[size];
	/*since the insructions said "any size of any set, which should be user defined"
	and didnt specify which was meant to be user defined, I decided that the size should
	be user defined, and just filling the rest randomly
	*/
	
	/*generating random numbers to fill and
	printing out unsorted array
	*/
	for(int i=0; i<size; i++)
	{
		//1 to 100 not including 0
		array[i]=rand()%100+1;
		if(i==(size-1))
		{
			std::cout << array[i] << std::endl;
		}
		else
		{
			
			std::cout << array[i] << ',';
		}
	}
	return 0;
}