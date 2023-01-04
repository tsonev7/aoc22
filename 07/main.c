#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int first(Node **nodes, int length)
{
    int totalCount = 0;
    for (int i = 0; i < length; i++)
    {
        Node *currentNode = nodes[i];

        if (currentNode->totalSize <= MAX_FILE_SIZE)
        {
            totalCount += currentNode->totalSize;
        }
    }

    return totalCount;
}

int second(Node **nodes, int length)
{
    int max = 70000000;
    int required = 30000000;
    int allocated = nodes[0]->totalSize;
    int toFree = (allocated + required) - max;

    Node *node = nodes[0];
    int current = nodes[0]->totalSize - toFree;

    for (int i = 1; i < length; i++)
    {
        int currentTotalSize = nodes[i]->totalSize;
        if (currentTotalSize > toFree)
        {
            int diff = currentTotalSize - toFree;
            if (diff < current)
            {
                node = nodes[i];
            };
        }
    }

    return node->totalSize;
}

int main(void)
{
    Node *nodes[1000] = {NULL};
    int length = build_tree(nodes);

    int result = 0;
    result = first(nodes, length);

    printf("Result of first task: %d \n", result);

    result = second(nodes, length);
    printf("Result of second task: %d", result);

    dealloc(nodes, length);

    return 0;
}