#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define UNASSIGNED 0
#define N 9

class SudokuSolver 
{
    private:
        int grid[N][N];

    public:
        SudokuSolver(int initialGrid[N][N]) 
        {
            memcpy(grid, initialGrid, sizeof(grid));
        }

        bool Solve() 
        {
            int row, col;
            if (!FindUnassignedLocation(row, col))
                return true;
            for (int num = 1; num <= 9; num++) 
            {
                if (isSafe(row, col, num)) 
                {
                    grid[row][col] = num;
                    if (Solve())    return true;
                    grid[row][col] = UNASSIGNED;
                }
            }
            return false;
        }

        void PrintSolution() 
        {
            printGrid();
        }

    private:
        bool FindUnassignedLocation(int &row, int &col) 
        {
            for (row = 0; row < N; row++)
                for (col = 0; col < N; col++)
                    if (grid[row][col] == UNASSIGNED)
                        return true;
            return false;
        }

        bool UsedInRow(int row, int num) 
        {
            for (int col = 0; col < N; col++)
                if (grid[row][col] == num)
                    return true;
            return false;
        }

        bool UsedInCol(int col, int num) 
        {
            for (int row = 0; row < N; row++)
                if (grid[row][col] == num)
                    return true;
            return false;
        }

        bool UsedInBox(int boxStartRow, int boxStartCol, int num) 
        {
            for (int row = 0; row < 3; row++)
                for (int col = 0; col < 3; col++)
                    if (grid[row + boxStartRow][col + boxStartCol] == num)
                        return true;
            return false;
        }

        bool isSafe(int row, int col, int num) 
        {
            return !UsedInRow(row, num) && !UsedInCol(col, num) &&
                !UsedInBox(row - row % 3, col - col % 3, num);
        }

        void printGrid() 
        {
            for (int row = 0; row < N; row++) 
            {
                for (int col = 0; col < N; col++)
                    cout << grid[row][col] << "  ";
                cout << endl;
            }
        }
};

int main() 
{
    int initialGrid[N][N] = { {3, 0, 6, 5, 0, 8, 4, 0, 0},
                              {5, 2, 0, 0, 0, 0, 0, 0, 0},
                              {0, 8, 7, 0, 0, 0, 0, 3, 1},
                              {0, 0, 3, 0, 1, 0, 0, 8, 0},
                              {9, 0, 0, 8, 6, 3, 0, 0, 5},
                              {0, 5, 0, 0, 9, 0, 6, 0, 0},
                              {1, 3, 0, 0, 0, 0, 2, 5, 0},
                              {0, 0, 0, 0, 0, 0, 0, 7, 4},
                              {0, 0, 5, 2, 0, 6, 3, 0, 0}};

    SudokuSolver sudokuSolver(initialGrid);

    if (sudokuSolver.Solve())
        sudokuSolver.PrintSolution();
    else
        cout << "No solution exists" << endl;
    return 0;
}
