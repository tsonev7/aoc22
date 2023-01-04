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

void push(char arr[], char value)
{
    int l = strlen(arr);
    arr[l] = value;
    arr[l + 1] = '\0';
    return;
}

int main(void)
{
    char buffer[BUFFER_SIZE];

    FILE *pFile;
    pFile = fopen("input.txt", "r");

    // we have single line in this input
    fgets(buffer, BUFFER_SIZE, pFile);
    printf("%s", buffer);

    int n = strlen(buffer);
    for (int i = 0; i < n - 15; i++)
    {
        char arr[14] = "";
        for (int k = i; k < i + 14; k++)
        {
            push(arr, buffer[k]);
        }

        if (isSet(arr))
        {
            printf("%d", i + 14);
            break;
        }
    }

    fclose(pFile);

    return 0;
}