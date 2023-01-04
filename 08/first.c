#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256
#define ROW_SIZE 99
#define COL_SIZE 99

int toInt(char c)
{
    return (int)c - 48;
}

void parseInput(int arr[][COL_SIZE])
{
    char buffer[COL_SIZE + 1];
    FILE *pFile = fopen("input.txt", "r");

    int row = 0, column = 0;

    pFile = fopen("input.txt", "r");
    while (fgets(buffer, BUFFER_SIZE, pFile))
    {
        for (int col = 0; col < strlen(buffer); col++)
        {
            arr[row][col] = toInt(buffer[col]);
        }
        row++;
    }

    fclose(pFile);
}

bool checkLeft(int grid[][COL_SIZE], int x, int y)
{
    int el = grid[x][y];

    for (int y1 = y - 1; y1 >= 0; y1--)
    {
        if (grid[x][y1] >= el)
        {
            return false;
        }
    }

    return true;
}

bool checkRight(int grid[][COL_SIZE], int x, int y)
{
    int el = grid[x][y];

    for (int y1 = y + 1; y1 < COL_SIZE; y1++)
    {
        if (grid[x][y1] >= el)
        {
            return false;
        }
    }

    return true;
}

bool checkTop(int grid[][COL_SIZE], int x, int y)
{
    int el = grid[x][y];

    for (int x1 = x - 1; x1 >= 0; x1--)
    {
        if (grid[x1][y] >= el)
        {
            return false;
        }
    }

    return true;
}

bool checkBottom(int grid[][COL_SIZE], int x, int y)
{
    int el = grid[x][y];

    for (int x1 = x + 1; x1 < ROW_SIZE; x1++)
    {
        if (grid[x1][y] >= el)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int grid[ROW_SIZE][COL_SIZE];
    parseInput(grid);

    int total = 0;
    for (int x = 0; x < COL_SIZE; x++)
    {
        for (int y = 0; y < ROW_SIZE; y++)
        {
            bool result = checkLeft(grid, x, y) || checkRight(grid, x, y) || checkTop(grid, x, y) || checkBottom(grid, x, y);

            if (result)
            {
                total++;
            }
        }
    }

    printf("Result: %d", total);

    return 0;
}