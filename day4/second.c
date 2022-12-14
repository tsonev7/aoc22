
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 256

int main(void)
{
    char currentLine[MAX_LEN];

    FILE *pFile = fopen("input", "r");

    int totalSubsets = 0;

    while (fgets(currentLine, MAX_LEN, pFile))
    {
        currentLine[strlen(currentLine) - 1] = '\0';

        char *firstPair = strtok(currentLine, ",");
        char *secondPair = strtok(NULL, ",");

        int a1 = atoi(strtok(firstPair, "-"));
        int a2 = atoi(strtok(NULL, "-"));

        int b1 = atoi(strtok(secondPair, "-"));
        int b2 = atoi(strtok(NULL, "-"));

        if (!(a2 < b1 || b2 < a1))
        {
            totalSubsets++;
        }
    }

    printf("%d", totalSubsets);

    return 0;
}