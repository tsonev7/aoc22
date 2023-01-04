
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

        printf("%d-%d %d-%d \n", a1, a2, b1, b2);

        if ((a1 >= b1 && a2 <= b2) || (b1 >= a1 && b2 <= a2))
        {
            totalSubsets++;
        }
    }

    printf("%d", totalSubsets);

    return 0;
}