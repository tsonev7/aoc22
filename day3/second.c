#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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

    return priority;
}

char *createString(char *string)
{
    int length = strlen(string);
    string[length - 1] = '\0'; // remove trailing newline symbol

    char *ptr = malloc(length);
    return strncpy(ptr, string, length);
}

int main()
{
    FILE *pFile;

    int totalPriority = 0;
    pFile = fopen("input", "r");

    int linesRead = 0;
    char *line1 = NULL, *line2 = NULL, *line3 = NULL;

    char *currentLine;
    while (fgets(currentLine, MAX_LEN, pFile))
    {
        linesRead++;
        if (linesRead == 1)
        {
            line1 = createString(currentLine);
        }
        else if (linesRead == 2)
        {
            line2 = createString(currentLine);
        }
        else if (linesRead == 3)
        {
            line3 = createString(currentLine);

            linesRead = 0;

            bool repeatedSymbolFound = false;
            for (int i = 0; i < strlen(line1); i++)
            {
                if (!repeatedSymbolFound)
                {
                    for (int j = 0; j < strlen(line2); j++)
                    {
                        if (!repeatedSymbolFound)
                        {
                            for (int k = 0; k < strlen(line3); k++)
                            {
                                if (line1[i] == line2[j] && line1[i] == line3[k])
                                {
                                    repeatedSymbolFound = true;
                                    totalPriority += getPriority(line1[i]);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d", totalPriority);

    fclose(pFile);

    return 0;
}
