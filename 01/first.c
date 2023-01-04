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

    pFile = fopen("input", "r");
    while (fgets(buffer, MAX_LEN, pFile))
    {
        currentNumber += atoi(buffer);
        if (!strcmp(buffer, "\n"))
        {
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
