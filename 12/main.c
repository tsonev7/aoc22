
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256

#define COL_SIZE 154
#define ROW_SIZE 41
// #define COL_SIZE 8
// #define ROW_SIZE 5

typedef struct Point
{
    int x;
    int y;
    int size;
} Point;

void parseInput(int grid[ROW_SIZE][COL_SIZE], Point *start, Point *end)
{
    int row = 0;
    char currentLine[256];
    FILE *pFile;

    pFile = fopen("input.txt", "r");
    while (fgets(currentLine, MAX_LEN, pFile))
    {
        for (int col = 0; col < COL_SIZE; col++)
        {
            if (currentLine[col] == 'S')
            {
                start->x = row;
                start->y = col;
                start->size = (int)'a';
                grid[row][col] = 'a';
            }
            else if (currentLine[col] == 'E')
            {
                end->x = row;
                end->y = col;
                end->size = (int)'z';
                grid[row][col] = 'z';
            }
            else
            {
                grid[row][col] = currentLine[col];
            }
        }
        row++;
    };

    fclose(pFile);
}

// push item at the end of the queue
void enqueue(Point **queue, int *queue_start_index, int *queue_end_index, Point *p)
{
    if (*queue_end_index == -1)
    {
        *queue_start_index = 0;
    }

    (*queue_end_index)++;
    queue[*queue_end_index] = p;
}

// remove item from the front of the queue
Point *dequeue(Point **queue, int *queue_start_index, int *queue_end_index)
{
    int startIndex = *queue_start_index;
    int endIndex = *queue_end_index;

    Point *item = queue[startIndex];

    (*queue_start_index)++;

    if (startIndex == endIndex)
    {
        *queue_start_index = *queue_end_index = -1;
    }

    return item;
}

void dealloc(Point **grid, int end)
{
    for (int i = 0; i <= end; i++)
    {
        free(grid[i]);
    }
}

void traverse(
    Point *p,
    Point **queue,
    int *queue_start_index,
    int *queue_end_index,
    int grid[ROW_SIZE][COL_SIZE],
    int distances[ROW_SIZE][COL_SIZE])
{
    if ((grid[p->x][(p->y) + 1] <= (p->size) + 1) &&
        p->y + 1 < COL_SIZE &&
        distances[p->x][(p->y) + 1] == 0) // EAST
    {
        distances[p->x][(p->y) + 1] = distances[p->x][p->y] + 1;

        Point *nextPoint = malloc(sizeof(Point));
        nextPoint->size = grid[p->x][(p->y) + 1];
        nextPoint->x = p->x;
        nextPoint->y = (p->y) + 1;

        enqueue(queue, queue_start_index, queue_end_index, nextPoint);
    }

    if ((grid[p->x][(p->y) - 1] <= (p->size) + 1) &&
        p->y - 1 >= 0 &&
        distances[p->x][(p->y) - 1] == 0) // WEST
    {
        distances[p->x][(p->y) - 1] = distances[p->x][p->y] + 1;

        Point *nextPoint = malloc(sizeof(Point));
        nextPoint->size = grid[p->x][(p->y) - 1];
        nextPoint->x = p->x;
        nextPoint->y = (p->y) - 1;

        enqueue(queue, queue_start_index, queue_end_index, nextPoint);
    }

    if ((grid[(p->x) - 1][(p->y)] <= (p->size) + 1) &&
        p->x - 1 >= 0 &&
        distances[(p->x) - 1][(p->y)] == 0) // NORTH
    {
        distances[(p->x) - 1][(p->y)] = distances[p->x][p->y] + 1;

        Point *nextPoint = malloc(sizeof(Point));
        nextPoint->size = grid[(p->x) - 1][(p->y)];
        nextPoint->x = (p->x) - 1;
        nextPoint->y = p->y;

        enqueue(queue, queue_start_index, queue_end_index, nextPoint);
    }

    if ((grid[(p->x) + 1][(p->y)] <= (p->size) + 1) &&
        p->x + 1 < ROW_SIZE &&
        distances[(p->x) + 1][(p->y)] == 0) // SOUTH
    {
        distances[(p->x) + 1][(p->y)] = distances[p->x][p->y] + 1;

        Point *nextPoint = malloc(sizeof(Point));
        nextPoint->size = grid[(p->x) + 1][(p->y)];
        nextPoint->x = (p->x) + 1;
        nextPoint->y = p->y;

        enqueue(queue, queue_start_index, queue_end_index, nextPoint);
    }

    free(p);
}

bool isEmpty(int start, int end)
{
    return (start == -1) && (end == -1);
}

void setStartPositions(int grid[ROW_SIZE][COL_SIZE], Point positions[100], int *length)
{
    for (int k = 0; k < COL_SIZE; k++)
    {
        if (grid[0][k] == 'a' ||
            grid[0][k] == 'S')
        {
            Point newPoint;
            newPoint.x = 0;
            newPoint.y = k;
            newPoint.size = (int)'a';
            positions[*length] = newPoint;
            (*length)++;
        }
        if (grid[ROW_SIZE - 1][k] == 'a' ||
            grid[ROW_SIZE - 1][k] == 'S')
        {
            Point newPoint;
            newPoint.x = ROW_SIZE - 1;
            newPoint.y = k;
            newPoint.size = (int)'a';
            positions[*length] = newPoint;
            (*length)++;
        }
    }

    for (int k = 1; k < ROW_SIZE - 1; k++)
    {
        if (grid[k][0] == 'a' || grid[k][0] == 'S')
        {
            Point newPoint;
            newPoint.x = k;
            newPoint.y = 0;
            newPoint.size = (int)'a';
            positions[*length] = newPoint;
            (*length)++;
        }
        if (grid[k][ROW_SIZE - 2] == 'a' || grid[k][ROW_SIZE - 2] == 'S')
        {
            Point newPoint;
            newPoint.x = k;
            newPoint.y = ROW_SIZE - 1;
            newPoint.size = (int)'a';
            positions[*length] = newPoint;
            (*length)++;
        }
    }
}

int getShortestDistance(int grid[ROW_SIZE][COL_SIZE], Point s, Point e)
{
    int distances[ROW_SIZE][COL_SIZE] = {0};
    Point *queue[ROW_SIZE * COL_SIZE] = {NULL};

    Point *start = malloc(sizeof(Point));
    start->x = s.x;
    start->y = s.y;
    start->size = s.size;

    Point *end = malloc(sizeof(Point));
    end->x = e.x;
    end->y = e.y;
    end->size = e.size;

    int queue_start_index = -1;
    int queue_end_index = -1;

    distances[start->x][start->y] = 1;
    enqueue(queue, &queue_start_index, &queue_end_index, start);
    while (!isEmpty(queue_start_index, queue_end_index))
    {
        Point *current = dequeue(queue, &queue_start_index, &queue_end_index);
        traverse(current, queue, &queue_start_index, &queue_end_index, grid, distances);
    }

    return distances[e.x][e.y] - 1;
}

int main(void)
{
    int grid[ROW_SIZE][COL_SIZE] = {0};

    Point startPositions[1000];
    int length = 0;
    Point start, end;

    parseInput(grid, &start, &end);
    setStartPositions(grid, startPositions, &length);

    int currentDistance = getShortestDistance(grid, startPositions[0], end);
    for (int i = 1; i < length; i++)
    {
        int distance = getShortestDistance(grid, startPositions[i], end);
        currentDistance = (distance < currentDistance && distance != -1) ? distance : currentDistance;
    }

    return 0;
}