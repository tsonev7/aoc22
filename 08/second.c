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

int checkLeft(int grid[][COL_SIZE], int x, int y)
{
    int el = grid[x][y];

    int count = 0;
    for (int y1 = y - 1; y1 >= 0; y1--)
    {
        count++;
        if (grid[x][y1] >= el)
        {
            break;
        }
    }

    return count;
}

int checkRight(int grid[][COL_SIZE], int x, int y)
{
    int el = grid[x][y];

    int count = 0;
    for (int y1 = y + 1; y1 < COL_SIZE; y1++)
    {
        count++;
        if (grid[x][y1] >= el)
        {
            break;
        }
    }

    return count;
}

int checkTop(int grid[][COL_SIZE], int x, int y)
{
    int el = grid[x][y];

    int count = 0;
    for (int x1 = x - 1; x1 >= 0; x1--)
    {
        count++;
        if (grid[x1][y] >= el)
        {
            break;
        }
    }

    return count;
}

int checkBottom(int grid[][COL_SIZE], int x, int y)
{
    int el = grid[x][y];

    int count = 0;
    for (int x1 = x + 1; x1 < ROW_SIZE; x1++)
    {
        count++;
        if (grid[x1][y] >= el)
        {
            break;
        }
    }

    return count;
}

int main(void)
{
    int grid[ROW_SIZE][COL_SIZE];
    parseInput(grid);

    int max = 0;
    for (int x = 0; x < COL_SIZE; x++)
    {
        for (int y = 0; y < ROW_SIZE; y++)
        {
            int result = checkLeft(grid, x, y) * checkRight(grid, x, y) * checkTop(grid, x, y) * checkBottom(grid, x, y);
            max = (result > max) ? result : max;
        }
    }

    printf("%d", max);

    return 0;
}