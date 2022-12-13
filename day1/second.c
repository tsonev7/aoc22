#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int main()
{
    FILE *pFile;
    char buffer[MAX_LEN];

    int currentNumber = 0, first = 0, second = 0, third = 0;

    pFile = fopen("input", "r");
    while (fgets(buffer, MAX_LEN, pFile))
    {
        currentNumber += atoi(buffer);
        if (!strcmp(buffer, "\n"))
        {
            printf("%d %d %d %d \n", first, second, third, currentNumber);
            if (currentNumber > first && currentNumber <= second)
            {
                first = currentNumber;
            }
            else if (currentNumber > second && currentNumber <= third)
            {
                first = second;
                second = currentNumber;
            }
            else if (currentNumber > third)
            {
                first = second;
                second = third;
                third = currentNumber;
            };

            currentNumber = 0;
        }
    }

    int result = first + second + third;
    printf("%d", result);

    return 0;
}
