#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define BUFFER_SIZE 5000

bool isSet(char arr[])
{
    int len = strlen(arr);

    for (int i = 0; i < len; i++)
    {
        for (int k = i + 1; k < len; k++)
        {
            if (arr[i] == arr[k])
            {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    char buffer[BUFFER_SIZE];

    FILE *pFile;
    pFile = fopen("input.txt", "r");

    // we have single line in this input
    fgets(buffer, BUFFER_SIZE, pFile);
    printf("%s", buffer);

    int i = 0;
    for (i = 0; i < strlen(buffer) - 1; i++)
    {
        char current[5] = {buffer[i],
                           buffer[i + 1],
                           buffer[i + 2],
                           buffer[i + 3], '\0'};

        bool isStartOfMarker = isSet(current);
        if (isSet(current))
        {
            printf("%d", i + 4);
            break;
        }
    }

    fclose(pFile);

    return 0;
}