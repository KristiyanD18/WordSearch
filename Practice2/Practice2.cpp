#include <iostream>

using namespace std;

void printGrid(char** grid, int rows)
{
	cout << "ENTERED GRID:" << endl;
	for (size_t i = 0; i < rows; i++)
	{
		cout << grid[i] << endl;
	}
}

int strLen(const char* str)
{
	int len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}

	return len;
}

bool findPath(char** grid, const char* word, int index, int x, int y, int rows, int cols, bool** visited)
{
	if (index == strLen(word))
	{
		return true; // all characters matched
	}

	if (x < 0 || y < 0 || x >= rows || y >= cols || grid[x][y] != word[index] || visited[x][y] == true)
	{
		return false;
	}
	visited[x][y] = true; // mark this cell as visited

	// explore in all 4 possible directions (right, left, down, up)
	bool found = findPath(grid, word, index + 1, x + 1, y, rows, cols, visited)
		|| findPath(grid, word, index + 1, x - 1, y, rows, cols, visited)
		|| findPath(grid, word, index + 1, x, y + 1, rows, cols, visited)
		|| findPath(grid, word, index + 1, x, y - 1, rows, cols, visited);

	visited[x][y] = false; // unmark this cell (backtrack)

	return found;
}

bool exist(char** grid, const char* word, int rows, int cols)
{
	// dynamically allocate the visited array
	bool** visited = new bool* [rows];
	for (size_t i = 0; i < rows; i++)
	{
		visited[i] = new bool[cols] { 0 };
	}

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			if (findPath(grid, word, 0, i, j, rows, cols, visited))
			{
				// clean up the dynamically allocated memory (visited)
				for (int i = 0; i < rows; i++)
				{
					delete[] visited[i];
				}
				delete[] visited;

				return true;
			}
		}
	}

	// clean up the dynamically allocated memory (visited)
	for (int i = 0; i < rows; i++)
	{
		delete[] visited[i];
	}
	delete[] visited;

	return false;
}

int main()
{
	int rows = 0;
	cout << "enter rows: ";
	cin >> rows;

	int cols = 0;
	cout << "enter cols: ";
	cin >> cols;

	char** grid = new char* [rows];

	for (size_t i = 0; i < rows; i++)
	{
		char* word = new char[cols + 1];
		cout << "enter word on row " << i << ": ";
		cin >> word;
		grid[i] = word;
	}

	char* word = new char[100]; // allocate enough space for the word
	cout << "enter word to be found: ";
	cin >> word;

	printGrid(grid, rows);

	if (exist(grid, word, rows, cols)) 
	{
		std::cout << "Word found in the grid!" << std::endl;
	}
	else 
	{
		std::cout << "Word not found in the grid." << std::endl;
	}

	// clean up the dynamically allocated memory (grid)
	for (int i = 0; i < rows; i++) 
	{
		delete[] grid[i];
	}
	delete[] grid;

	delete[] word; // free the word memory

	return 0;
}