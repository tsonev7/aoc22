
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256
#define ROPE_LENGTH 10

typedef struct Point
{
    int x;
    int y;
} Point;

int max(int x, int y)
{
    return x <= y ? y : x;
}

void pushPoint(Point **arr, Point *point, int position)
{
    arr[position] = point;
}

Point *createPoint(int x, int y)
{
    Point *p = malloc(sizeof(Point));
    p->x = x;
    p->y = y;

    return p;
}

void moveHead(Point *p, char direction)
{
    if (direction == 'U')
    {
        p->x--;
    }
    else if (direction == 'D')
    {
        p->x++;
    }
    else if (direction == 'L')
    {
        p->y--;
    }
    else if (direction == 'R')
    {
        p->y++;
    }

    return;
}

void setPoint(Point *p, int x, int y)
{
    p->x = x;
    p->y = y;

    return;
}

bool shoudlMoveTail(Point *head, Point *tail)
{
    return max(abs(tail->x - head->x), abs(tail->y - head->y)) > 1;
}

void dealloc(Point **arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        free(arr[i]);
    }
}

bool equal(Point *p1, Point *p2)
{
    return p1->x == p2->x && p1->y == p2->y;
}

int countUniquePoints(Point **arr, int length)
{
    int res = 1;
    for (int i = 1; i < length; i++)
    {
        int j = 0;
        for (j = 0; j < i; j++)
            if (equal(arr[i], arr[j]))
                break;
        if (i == j)
            res++;
    }
    return res;
}

void moveTail(Point *head, Point *tail)
{
    if (head->x == tail->x)
    {
        if (head->y < tail->y)
        {
            tail->y--;
        }

        if (head->y > tail->y)
        {
            tail->y++;
        }
    }
    else if (head->y == tail->y)
    {
        if (head->x < tail->x)
        {
            tail->x--;
        }

        if (head->x > tail->x)
        {
            tail->x++;
        }
    }
    else if (head->x < tail->x && head->y > tail->y)
    {
        tail->x--;
        tail->y++;
    }
    else if (head->x > tail->x && head->y > tail->y)
    {
        tail->x++;
        tail->y++;
    }
    else if (head->x < tail->x && head->y < tail->y)
    {
        tail->x--;
        tail->y--;
    }
    else if (head->x > tail->x && head->y < tail->y)
    {
        tail->x++;
        tail->y--;
    }
}

int main(void)
{
    char buffer[256];
    FILE *pFile;

    Point *tailPositions[15000] = {NULL};
    int tailPositionsLength = 0;

    Point *rope[ROPE_LENGTH] = {NULL};
    for (int i = 0; i < ROPE_LENGTH; i++)
    {
        pushPoint(rope, createPoint(0, 0), i);
    };

    pushPoint(tailPositions, createPoint(0, 0), tailPositionsLength);

    pFile = fopen("input.txt", "r");
    while (fgets(buffer, MAX_LEN, pFile))
    {
        char direction = strtok(buffer, " ")[0];
        int number = atoi(strtok(NULL, " "));

        for (int i = 0; i < number; i++)
        {
            Point *head = rope[0];
            Point *tail = rope[1];

            moveHead(head, direction);
            for (int i = 1; i < ROPE_LENGTH; i++)
            {
                head = rope[i - 1];
                tail = rope[i];
                if (shoudlMoveTail(head, tail))
                {
                    moveTail(head, tail);
                }
            }

            pushPoint(tailPositions, createPoint(tail->x, tail->y), tailPositionsLength++);
        }
    }

    int unique = countUniquePoints(tailPositions, tailPositionsLength);

    fclose(pFile);
    dealloc(tailPositions, tailPositionsLength);

    return 0;
}