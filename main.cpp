#include <vector>
#include <iostream>

void printSoduku(const std::vector<std::vector<int>> &matrix);
bool safe(const std::vector<std::vector<int>> &matrix, const int &x, const int &y, const int &key);
bool isFull(const std::vector<std::vector<int>> &matrix);
bool solveSudoku(std::vector<std::vector<int>> &matrix);


int main()
{
	/*
			Make a program that solves ANY sudoku puzzle
			Here are some tests that you can copy and paste into the program

						*****IMPORTANT: PLEASE ENTER THE MATRIX EXAMPLES ONE-BY-ONE Copy and Paste will disorient the numbers *******

			You can verify the solution by looking at it :)
			'0' will denote an empty space


			3 0 6 5 0 8 4 0 0
			5 2 0 0 0 0 0 0 0
			0 8 7 0 0 0 0 3 1
			0 0 3 0 1 0 0 8 0
			9 0 0 8 6 3 0 0 5
			0 5 0 0 9 0 6 0 0
			1 3 0 0 0 0 2 5 0
			0 0 0 0 0 0 0 7 4
			0 0 5 2 0 6 3 0 0

			1 0 6 0 0 9 4 0 0
			3 0 0 8 0 7 0 0 0
			2 0 7 0 3 0 0 0 0
			4 9 0 0 0 0 6 0 0
			0 3 1 4 0 8 5 2 0
			0 0 8 0 0 0 0 4 7
			0 0 0 0 1 0 7 0 2
			0 0 0 9 0 2 0 0 4
			0 0 2 6 0 0 1 0 5

			0 1 0 3 0 0 9 0 6
			4 0 0 0 6 0 0 0 0
			0 0 7 9 0 0 0 0 2
			0 8 0 0 2 5 0 3 0
			0 5 0 0 0 0 0 1 0
			0 9 0 8 3 0 0 6 0
			9 0 0 0 0 6 4 0 0
			0 0 0 0 8 0 0 0 7
			8 0 5 0 0 7 0 2 0

			0 5 2 4 0 0 0 0 0	
			0 9 0 7 0 1 0 0 0	
			0 0 0 3 0 0 4 0 2	
			7 0 6 0 9 0 1 0 0	
			1 0 0 0 0 0 0 0 7	
			0 0 8 0 1 0 6 0 3	
			4 0 7 0 0 2 0 0 0	
			0 0 0 5 0 4 0 6 0	
			0 0 0 0 0 6 2 3 0	

		*/
	std::vector<std::vector<int>> matrix(9, std::vector<int>(9));
	std::cout << "Please enter the matrix: " << std::endl;

	for (int j = 0; j < 9; j++)
		for (int k = 0; k < 9; k++)
			std::cin >> matrix[j][k];
	printSoduku(matrix);
	solveSudoku(matrix);
	printSoduku(matrix);
}

void printSoduku(const std::vector<std::vector<int>> &matrix)
{
	for (int j = 0; j < 9; j++)
	{
		std::cout << std::endl;
		if (j % 3 == 0)
			std::cout << "-------------------------" << std::endl;
		for (int k = 0; k < 9; k++)
		{
			if ((k) % 3 == 0)
				std::cout << "| ";
			if (matrix[j][k] != 0)
				std::cout << matrix[j][k] << " ";
			else
				std::cout << "_" << " ";
			if (k == 8)
				std::cout << "| ";
		}
		if (j == 8)
			std::cout << std::endl << "-------------------------" << std::endl;
	}
}

bool safe(const std::vector<std::vector<int>> &matrix, const int &x, const int &y, const int &key)
{
	bool exists = false;
	/*
	 check box
	 smallX and smallY are used to find the upper left hand spot of the sub-box x and y are in

	  Ex:
	  x = 1, y = 0, key = 3
	  3 0 6
	  5 2 0
	  0 8 7

	   smallX = 1-(1%3) = 0;
	   smallY = 0-(0%3) = 0;

	   Now smallX and smallY are designated the top left hand spot of this sub-box
	   At this point we can check for the key's existance with a nested forloop
	   In this example, key = 3 and is in spot [0][0] therefore exists = true
	*/
	int smallX = x - (x % 3);
	int smallY = y - (y % 3);
	for (int i = smallX; i < smallX + 3; i++)
		for (int j = smallY; j < smallY + 3; j++)
			if (matrix[i][j] == key)
				exists = true;
	// check row
	for (int i = 0; i < 9; i++)
		if (matrix[x][i] == key)
			exists = true;

	// check  column
	for (int i = 0; i < 9; i++)
		if (matrix[i][y] == key)
			exists = true;

	return exists;

}
// Needed for the stopping condition
bool isFull(const std::vector<std::vector<int>> &matrix)
{
	bool full = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (matrix[i][j] == 0)
				full = false;
		}
	}


	return full;
}
bool solveSudoku(std::vector<std::vector<int>> &matrix)
{
	// stopping condition
	if (isFull(matrix))
		return true;
	// Find the next empty spot, this is found by looking for a '0'
	int x = 0;
	int y = 0;
	bool found = false;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			if (matrix[i][j] == 0)
			{
				x = i;
				y = j;
				found = true;
				break;
			}
		if (found)
			break;
	}

	// check all avialable numnbers 1...9
	for (int i = 1; i <= 9; i++)
	{
		//	first we don't know if it exists so we assume it doesn't
		bool exists = false;
		//	We check if it is safe to use this spot.
		//	if this spot is NOT safe to use then this number DOES exist in the row/col/box
		if (safe(matrix, x, y, i))
			exists = true;
		//	If it IS safe to use (DOES NOT EXIST IN THE ROW/COL/BOX )then we add it to the matrix
		if (!exists)
		{
			matrix[x][y] = i;
			//	We call the function again because we arent done unless the matrix is full (stopping condtion) in which case we return true (we are done)
			if (solveSudoku(matrix))
				return true;
			//	if the matrix is not full and the numbers we used dont work then we leave it blank
			matrix[x][y] = 0;
		}
	}
	// once it is left blank we return false so that we can BACKTRACK to the cell prior to this one
	return false;
}
