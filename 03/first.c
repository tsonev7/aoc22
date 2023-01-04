#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 256

int getPriority(char c)
{
    int priority = 0;

    // a...z -> 1...26
    // A...Z -> 27...52

    // ASCII
    // a...z -> 97...122
    // A...Z -> 65...90

    // a...z -> -96
    // A...Z -> -38

    int ascii = (int)c;

    // printf("%c %d \n", c, ascii);
    // printf("---------------\n");

    // [a...z]
    if (ascii >= 97 && ascii <= 122)
    {
        priority = c - 96;
    }

    // [A...Z]
    if (ascii >= 65 && ascii <= 90)
    {
        priority = c - 38;
    }

    printf("%c %d \n", c, priority);
    printf("---------------\n");

    // printf("%d", priority);
    return priority;
}

int main()
{
    FILE *pFile;
    char line[MAX_LEN];

    int totalPriority = 0;

    pFile = fopen("input", "r");
    while (fgets(line, MAX_LEN, pFile))
    {
        bool duplicateFound = false;
        int length = strlen(line) - 1; // fgets() puts newline at the end of the string, thus -1
        for (int i = 0; i < (length / 2); i++)
        {
            if (!duplicateFound)
            {
                for (int k = length / 2; k < length; k++)
                {
                    if (line[i] == line[k])
                    {
                        totalPriority += getPriority(line[i]);
                        duplicateFound = true;
                        break;
                    }
                }
            }
        }
    }

    printf("%d", totalPriority);

    fclose(pFile);

    return 0;
}