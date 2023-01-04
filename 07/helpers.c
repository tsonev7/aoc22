
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

int get_size(Node *node)
{
    int totalSize = node->size;
    for (int i = 0; i < node->childrenCount; i++)
    {
        totalSize += get_size(node->children[i]);
    }

    return totalSize;
}

void push(Node **arr, Node *node, int *length)
{
    arr[(*length)++] = node;
}

// extract the size from the beginning of the line
int extract_size(char *str)
{
    return strtol(str, NULL, 10);
}

int build_tree(Node **nodes)
{
    char currentLine[MAX_LEN];
    FILE *pFile = fopen("input.txt", "r");
    int length = 0;

    // construct root node manually

    Node *rootNode = malloc(sizeof(Node));
    rootNode->parent = NULL;
    rootNode->size = 0;
    rootNode->childrenCount = 0;
    strcpy(rootNode->name, "\\");
    push(nodes, rootNode, &length);

    Node *currendNode = rootNode;

    fgets(currentLine, MAX_LEN, pFile); // discard first line

    while (fgets(currentLine, MAX_LEN, pFile))
    {
        // remove newline
        currentLine[strlen(currentLine) - 1] = '\0';
        if (currentLine[0] == '$') // command
        {
            if (strstr(currentLine, "cd .."))
            {
                currendNode = currendNode->parent;
            }
            else if (strstr(currentLine, "$ ls")) // do nothing for ls
            {
            }
            else // command is cd <new folder>
            {
                char *token;
                token = strtok(currentLine, " ");
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");

                Node *newNode = malloc(sizeof(Node));
                newNode->size = 0;
                newNode->childrenCount = 0;
                newNode->parent = currendNode;
                strcpy(newNode->name, token);

                push(nodes, newNode, &length);
                push(currendNode->children, newNode, &currendNode->childrenCount);
                currendNode = newNode;
            }
        }
        else
        {
            int size = extract_size(currentLine);
            if (size)
            {
                currendNode->size += size;
            }
        }
    }

    for (int i = 0; i < length; i++)
    {
        Node *currentNode = nodes[i];
        int currentSize = get_size(nodes[i]);
        nodes[i]->totalSize = get_size(nodes[i]);
    }

    return length;
}

void dealloc(Node **array, int length)
{
    for (int i = 0; i < length; i++)
    {
        free(array[i]);
    }
}