
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 256

void first(int *cycles)
{
    int lookup[] = {20, 60, 100, 140, 180, 220};

    int total = 0;
    for (int i = 0; i < 6; i++)
    {
        total += cycles[(lookup[i] - 1)] * lookup[i];
        printf("%d \n", cycles[(lookup[i] - 1)] * lookup[i]);
    }

    printf("TOTAL %d \n", total);
}

void second(int cycles[1000], int length)
{
    int rowSize = 40;
    int k = length / rowSize;
    for (int i = 0; i < k; i++)
    {
        for (int j = i * rowSize; j < (i + 1) * rowSize; j++)
        {
            int spritePosition = cycles[j];
            int pixelPosition = j % rowSize;

            if (pixelPosition == spritePosition || pixelPosition == spritePosition - 1 || pixelPosition == spritePosition + 1)
            {
                printf("#");
            }
            else
            {
                printf(".");
            }
        }

        printf("\n");
    }
}

int main(void)
{
    char currentLine[256];
    FILE *pFile;

    int cycles[1000] = {0};

    int x = 1;
    int currentCycle = 0;

    pFile = fopen("input.txt", "r");
    while (fgets(currentLine, MAX_LEN, pFile))
    {
        if (strstr(currentLine, "addx"))
        {
            strtok(currentLine, " ");
            int number = atoi(strtok(NULL, " "));

            cycles[currentCycle] = x;
            cycles[++currentCycle] = x;
            currentCycle++;
            x += number;
        }
        else if (strstr(currentLine, "noop"))
        {
            cycles[currentCycle++] = x;
        }
    }

    second(cycles, currentCycle);

    fclose(pFile);

    return 0;
}