#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

int main()
{
    FILE *pFile;
    char buffer[MAX_LEN];
    int maxNumber = 0;
    int currentNumber = 0;

    // Read the first gorup of numbers and set that to be the max number
    pFile = fopen("input", "r");
    while (strcmp(buffer, "\n"))
    {
        fgets(buffer, MAX_LEN, pFile);
        maxNumber += atoi(buffer);
    };

    // Read the rest of the groups and compare each group to the maxNumber
    while (fgets(buffer, MAX_LEN, pFile))
    {
        currentNumber += atoi(buffer);
        if (!strcmp(buffer, "\n"))
        {
            printf("Current number: %d, Max number: %d \n", currentNumber, maxNumber);
            if (maxNumber < currentNumber)
            {
                maxNumber = currentNumber;
            }

            currentNumber = 0;
        }
    }

    printf("%d", maxNumber);

    fclose(pFile);

    return 0;
}
