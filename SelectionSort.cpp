#include <iostream>
#include <ctime>
#include <time.h>
#include <stdlib.h>

void SelectionSort(int array[], int arrayLength);

int main()
{
	srand(time(NULL));
	// Variables to store the max length of array (n)
	int arrayLength=0;
	std::cout << "Please enter the number of numbers you want in the array: ";
	std::cin >> arrayLength;
	if(arrayLength>20)
	{
		std::cout << "Error, array size to large, resetting to 20" << std::endl;
		arrayLength=20;
	}
	
	// Array to be used and sorted
	int *array=new int[arrayLength];
	std::cout << "Randomly filling array with numbers." << std::endl;
	array[arrayLength];
	std::cout << "The unsorted array is: ";
	for(int i=0; i<arrayLength; i++)
	{
		array[i]=rand()%100+1;
		if(i==(arrayLength-1))
		{
			std::cout << array[i] << std::endl;
		}
		else
		{
			std::cout << array[i] << ",";
		}
	}
	SelectionSort(array, arrayLength);
	std::cout << "" << std::endl;
	std::cout << "The sorted array is: ";
	for(int i=0; i<arrayLength; i++)
	{
		if(i==(arrayLength-1))
		{
			std::cout << array[i] << std::endl;
		}
		else
		{
			std::cout << array[i] << ",";
		}
	}
	std::cout << "Goodbye!" << std::endl;
	delete [] array;
	return 0;
}

void SelectionSort(int array[], int arrayLength)
{
	// Move through the array
	for(int x=0; x<(arrayLength-1); x++)
	{
		//set the smallest value and find new one if needed
		int small=x;
		for(int y=x+1; y<arrayLength; y++)
		{
			if(array[y]<array[small])
			{
				small=y;
			}
			//swap smallest value with the first value
		}
		int temp=array[small];
		array[small]=array[x];
		array[x]=temp;
	}	
}