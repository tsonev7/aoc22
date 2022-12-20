#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct operation
{
    int stackFrom;
    int stackTo;
    int count;
} operation;

char pop(char stack[])
{
    char item = stack[strlen(stack) - 1];
    stack[strlen(stack) - 1] = '\0';
    return item;
};

void push(char stack[], char value)
{
    int l = strlen(stack);
    stack[l] = value;
    stack[l + 1] = '\0';
    return;
}

operation parseLine(char *line)
{
    operation op;
    int count = 0, from = 0, to = 0;

    if (3 == sscanf(line, "%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d", &count, &from, &to))
    {
        op.count = count;
        op.stackFrom = from;
        op.stackTo = to;
    };

    return op;
}

void executeOperation(operation op, char stacks[][50])
{
    char tmp[op.count];

    for (int i = 0; i < op.count; i++)
    {
        char c = pop(stacks[op.stackFrom - 1]);
        tmp[i] = c;
    }

    for (int i = op.count - 1; i >= 0; i--)
    {
        push(stacks[op.stackTo - 1], tmp[i]);
    }
}

int main()
{

    int stacksCount = 9;
    int maxSize = 50;

    char stacks[stacksCount][maxSize];
    strcpy(stacks[0], "STHFWR");
    strcpy(stacks[1], "SGDQW");
    strcpy(stacks[2], "BTW");
    strcpy(stacks[3], "DRWTNQZJ");
    strcpy(stacks[4], "FBHGLVTZ");
    strcpy(stacks[5], "LPTCVBSG");
    strcpy(stacks[6], "ZBRTWGP");
    strcpy(stacks[7], "NGMTCJR");
    strcpy(stacks[8], "LGBW");

    FILE *pFile;
    char currentLine[256];

    pFile = fopen("input.txt", "r");
    while (fgets(currentLine, 256, pFile))
    {
        operation op = parseLine(currentLine);
        executeOperation(op, stacks);
    }

    for (int i = 0; i < stacksCount; i++)
    {
        int stackSize = strlen(stacks[i]);
        printf("%c", stacks[i][stackSize - 1]);
    };

    printf("\n");

    return 0;
}