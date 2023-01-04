#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

// 9 combinations, no map in C :(
// X - rock (1pts)
// Y - paper (2pts)
// Z - scissors (3pts)
// A - rock
// B - paper
// C - scissors
// draw - 3 pts
// lost - 0 pts
// win - 6

int getAmount(first, second)
{
    if (first == 'A' && second == 'X')
    {
        return 0 + 3;
    }

    if (first == 'A' && second == 'Y')
    {
        return 3 + 1;
    }

    if (first == 'A' && second == 'Z')
    {
        return 6 + 2;
    }

    if (first == 'B' && second == 'X')
    {
        return 0 + 1;
    }

    if (first == 'B' && second == 'Y')
    {
        return 3 + 2;
    }

    if (first == 'B' && second == 'Z')
    {
        return 6 + 3;
    }

    if (first == 'C' && second == 'X')
    {
        return 0 + 2;
    }

    if (first == 'C' && second == 'Y')
    {
        return 3 + 3;
    }

    if (first == 'C' && second == 'Z')
    {
        return 6 + 1;
    }
}

char *extractSymbols(char string[])
{
    int i = 0;
    static char result[2];

    char *ptr = strtok(string, " ");
    while (ptr != NULL)
    {
        result[i++] = *ptr;
        ptr = strtok(NULL, " ");
    }

    return result;
}

int main()
{
    FILE *pFile;
    char buffer[MAX_LEN];

    int sum = 0;

    pFile = fopen("input", "r");
    while (fgets(buffer, MAX_LEN, pFile))
    {
        char *result = extractSymbols(buffer);
        char first = result[0];
        char second = result[1];

        int currentAmount = getAmount(first, second);
        printf("%d \n", currentAmount);
        sum += currentAmount;
    }

    printf("%d", sum);

    fclose(pFile);

    return 0;
}