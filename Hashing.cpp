#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "TimeInterval.h"
//Define the table size as 26, since there are
//26 letters in the alphabet and will be stored
//by first letters

#define size 26
	
int hashFunction(std::string string)
{
	int hash=0;
	int location;
	hash=(int)string[0]-1;
	//making the hashing value 32, so since A is 65 and a is 92
	//when converted to ascii values. and take away one so the 
	//remainder of both is 0, getting stored in the first slot. 
	location=hash%32;
	return location;
}

struct node
{
	std::string word;
	node*next;
};

int main()
{
	//Create a new hashTable and empty it
	node* hashTable[size];
	for(int x=0; x<size;x++)
	{
		hashTable[x]=new node;
		hashTable[x]->word="";
		hashTable[x]->next=NULL;
	}
	//Create a float to store time and make a new time object
	float totalTime;
	TimeInterval* timeClock=new TimeInterval;
	std::string line;
	//used to store input and find hash location of input
	std::string answer;
	int location;
	std::ifstream file ("Dictionary.txt");
	if(file.is_open())
	{
		//get line will get the next line in the file as long as there
		//is a next line to get.
		while(getline(file,line))
		{
			//delete whitespace from string 
			int z;
			for(z=0; z<line.length(); z++)
			{
				if(line[z]=='\r')
				{
					line.erase(z,1);
				}
			}
			int location=hashFunction(line);
			if(hashTable[location]->word=="")
			{
				hashTable[location]->word=line;
			}
			else
			{
				//create a new node and search through
				//current table until you find the end of the list
				node* a=hashTable[location];
				node* b=new node;
				b->word=line;
				b->next=NULL;
				while(a->next!=NULL)
				{
					a=a->next;
				}
				a->next=b;
			}
		}
	file.close();
	std::cout << "Please enter a word: ";
	std::cin >> answer;
	//begin timing 
	timeClock->start();
	//first pass to find the word and return true
	for(int y=0; y<size; y++)
	{
		//create a temp node to search through table
		node* c=hashTable[y];
		while(c != NULL)
		{
			std::string temp=c->word;
			if(temp==answer)
			{
				std::cout << "True" << std::endl;
				c=c->next;
				//raise y so the loop will end after finding word
				y=50;
			}
			else if(temp!=answer && y==25 && c->next==NULL)
			{
				std::cout << "False" << std::endl;
				//since the description didnt say that we had to print similar letters if the word
				//isnt in the dictionary, i did not print any nor the time in micro seconds
				return 0;
				c=c->next;
			}
			else
			{
				c=c->next;
			}
		}
		delete c;
	}
	//Create a second pass through to get 
	//similar words and print them so True is always printed first
	//otherwise true will be wherever the element is in the table
	for(int y2=0; y2<size; y2++)
	{
		//create another temp node to find similar words
		node* d=hashTable[y2];
		while(d != NULL)
		{
			std::string temp=d->word;
			//since the example doesn't print the user entered word
			// we omit it from the results displayed
			if(temp[0]==answer[0] && temp[1]==answer[1] && temp!=answer)
			{
				std::cout << temp << std::endl;
				d=d->next;
			}
			//go to the next element in the table
			else
			{
				d=d->next;
			}
		}
		delete d;
	}
	}
	else
	{
		std::cout << "file not found" << std::endl;
		return 0;
	}
	//end timing
	timeClock->stop();
	totalTime=timeClock->GetInterval();
	std::cout << totalTime << " Micro seconds." << std::endl;
	delete timeClock;
	return 0;
}
	