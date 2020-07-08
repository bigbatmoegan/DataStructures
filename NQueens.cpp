#define N 8
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <stack>
//Setting the number of queens to 8
/*When doing this, I was able to get a board to
print off a solution, however once I implemented
the stack, it  held a different solution. I could
not figure out how to get the solutions to match, but
Both are in fact solutions as I checked on http://www.brainmetrix.com/8-queens/ */



//Determine if a spot is safe to place a Queen
bool canPlaceQueen(int gameBoard[N][N], int row, int column, std::stack<int> &stack)
{
    int x=0;
    int y=0;
    //Check the left side of the queens
    for(x=0; x<column; x++)
    {
        if(gameBoard[row][x]==1)
        {
			//stack.pop();
            return false;
        }
    }
    
    //Check diagnolly left up of the queens
    for(x=row, y=column; x>=0 && y>=0; x--, y--)
    {
        if(gameBoard[x][y]==1)
        {
			//stack.pop();
            return false;
        }
    }
    
    //Check diagonlly left down of the queens
    for(x=row, y=column; y>=0 && x<N; x++, y--)
    {
        if(gameBoard[x][y]==1)
        {
			//stack.pop();
            return false;
        }
    }
    return true;
	
}

bool solveLoop(int gameBoard[N][N], int column, std::stack<int> &stack, int* ptrFilled)
{
	
    if(column>=N)
    {
        return true;
    }
    for(int x=0; x<N; x++)
    {
		stack.push(x);
        if (canPlaceQueen(gameBoard, x, column, stack))
        {
            gameBoard[x][column]=1;
            if(solveLoop(gameBoard, column + 1, stack, ptrFilled))
            {
				*ptrFilled=*ptrFilled+1;
                return true;
            }
			
            gameBoard[x][column]=0;
        }
		stack.pop();
    }
    return false;
}

void printBoard(int gameBoard[N][N], int* ptrFilled, std::stack<int> &stack)
{
	std::cout << "Solution using locations off stack" << std::endl;
	std::cout << "  " << std::endl;
	for(int a=0; a<N; a++)
	{
		if(stack.empty()!=true)
		{
			int b=stack.top();
			std::cout << "On row: " << *ptrFilled << "  There is a queen at column: " << b << std::endl;
			*ptrFilled=*ptrFilled-1;
			stack.pop();
		}
		else
		{
			std::cout << "Somehow this is empty" << std::endl;
		}
	}
	std::cout << "  " << std::endl;
	std::cout << "One of many solutions from the board" << std::endl;
	std::cout << "  " << std::endl;
	for(int x=0; x<N; x++)
	{
		for (int y=0; y<N; y++)
		{
			std::cout << gameBoard[x][y];
		}
		std::cout << "\n";
	}
}

bool solveQ()
{
    int gameBoard[N][N]={ {0,0,0,0,0,0,0,0},
	                      {0,0,0,0,0,0,0,0},
	                      {0,0,0,0,0,0,0,0},
	                      {0,0,0,0,0,0,0,0},
	                      {0,0,0,0,0,0,0,0},
	                      {0,0,0,0,0,0,0,0},
	                      {0,0,0,0,0,0,0,0},
	                      {0,0,0,0,0,0,0,0} 
	};
	std::stack<int> myStack[8];
	int filled=0;
	int *ptrFilled;
	ptrFilled=&filled;
	if(solveLoop(gameBoard, 0, *myStack, &filled)==false)
	{
	    std::cout << "Error: Solution does not exist" << std::endl;
	    return false;
	}
	printBoard(gameBoard, &filled, *myStack);
	return true;
}



int main()
{
    solveQ();
    return 0;
}

