#include <bits/stdc++.h>
using namespace std;

const int SIZE = 9; // 9x9 Sudoku grid

// Function to clear the screen
void clearScreen()
{
// For Windows
#ifdef _WIN32
    system("cls");
#else
    // For UNIX-like systems (Linux/macOS)
    system("clear");
#endif
}

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>> &grid)
{
    // Print the top border of the grid
    cout << "+-------+-------+-------+" << endl;

    for (int row = 0; row < SIZE; ++row)
    {
        for (int col = 0; col < SIZE; ++col)
        {
            // Print vertical borders and numbers
            if (col == 0)
                cout << "| "; // Left border for each row

            // Print the number or space (if empty)
            if (grid[row][col] == 0)
                cout << "  "; // Use string " " to avoid ASCII interpretation
            else
                cout << grid[row][col] << " ";

            // Print right border after every 3rd column
            if ((col + 1) % 3 == 0)
                cout << "| ";
        }
        cout << endl;

        // Print horizontal border after every 3rd row
        if ((row + 1) % 3 == 0)
            cout << "+-------+-------+-------+" << endl;
    }
}

// Check if it's safe to place a number in a specific position
bool isSafe(const vector<vector<int>> &grid, int row, int col, int num)
{
    // Check the row
    for (int x = 0; x < SIZE; ++x)
    {
        if (grid[row][x] == num)
        {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < SIZE; ++x)
    {
        if (grid[x][col] == num)
        {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// Solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>> &grid, int row, int col)
{
    // If we have reached the end of the grid
    if (row == SIZE - 1 && col == SIZE)
    {
        return true;
    }

    // Move to the next row if we are at the end of the current row
    if (col == SIZE)
    {
        row++;
        col = 0;
    }

    // If the current position is already filled, move to the next cell
    if (grid[row][col] != 0)
    {
        return solveSudoku(grid, row, col + 1);
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= SIZE; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            // Recursively attempt to fill in the next cells
            if (solveSudoku(grid, row, col + 1))
            {
                return true;
            }
        }

        // Reset the cell if the choice doesn't lead to a solution
        grid[row][col] = 0;
    }

    return false;
}

int main()
{
    vector<vector<int>> grid(SIZE, vector<int>(SIZE, 0)); // Initialize an empty grid

    // Take input from the user for the Sudoku puzzle with dynamic grid update
    for (int row = 0; row < SIZE; ++row)
    {
        for (int col = 0; col < SIZE; ++col)
        {
            clearScreen();   // Clear the screen before showing the updated grid
            printGrid(grid); // Show the current state of the grid

            cout << "\nEnter a number for row " << row + 1 << ", column " << col + 1 << " (0 for empty): ";
            cin >> grid[row][col];
        }
    }

    // Print the final inputted grid
    clearScreen(); // Clear the screen one last time before showing the final input
    cout << "\nInput Sudoku Puzzle:\n";
    printGrid(grid);

    // Solve the puzzle and display the result
    if (solveSudoku(grid, 0, 0))
    {
        cout << "\nSolved Sudoku Puzzle:\n";
        printGrid(grid);
    }
    else
    {
        cout << "\n\n----------------------------------------" << endl;
        cout << "No solution exists for the given puzzle." << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
