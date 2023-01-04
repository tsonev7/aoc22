
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT 200000
#define MONKEY_COUNT 8
#define ROUNDS 10000

typedef long (*Operation)(long);
typedef void (*Test)(long, struct Monkey **arr);

typedef struct Monkey
{
    long items[COUNT];
    long count;
    Operation op;
    Test test;

} Monkey;

void throw(Monkey * from, Monkey *to, long index)
{
    long value = from->items[index];
    from->items[index] = -1;
    to->items[to->count] = value;
    to->count++;
};

long reduce(long number)
{
    return number % 9699690; // MAGIC
}

long monkey0_op(long number)
{
    return number * 7;
}

void monkey0_test(long index, Monkey **arr)
{
    if (arr[0]->items[index] % 17 == 0)
    {
        throw(arr[0], arr[5], index);
    }
    else
    {
        throw(arr[0], arr[3], index);
    }
}

long monkey1_op(long number)
{
    return number + 4;
}

long monkey1_test(long index, Monkey **arr)
{
    if (arr[1]->items[index] % 3 == 0)
    {
        throw(arr[1], arr[0], index);
    }
    else
    {
        throw(arr[1], arr[3], index);
    }
}

long monkey2_op(long number)
{
    return number + 2;
}

void monkey2_test(long index, Monkey **arr)
{
    if (arr[2]->items[index] % 5 == 0)
    {
        throw(arr[2], arr[7], index);
    }
    else
    {
        throw(arr[2], arr[4], index);
    }
}

long monkey3_op(long number)
{
    return number + 7;
}

long monkey3_test(long index, Monkey **arr)
{
    if (arr[3]->items[index] % 7 == 0)
    {
        throw(arr[3], arr[5], index);
    }
    else
    {
        throw(arr[3], arr[2], index);
    }
}

long monkey4_op(long number)
{
    return number * 17;
}

long monkey4_test(long index, Monkey **arr)
{
    if (arr[4]->items[index] % 11 == 0)
    {
        throw(arr[4], arr[1], index);
    }
    else
    {
        throw(arr[4], arr[6], index);
    }
}

long monkey5_op(long number)
{
    return number + 8;
}

long monkey5_test(long index, Monkey **arr)
{
    if (arr[5]->items[index] % 19 == 0)
    {
        throw(arr[5], arr[2], index);
    }
    else
    {
        throw(arr[5], arr[7], index);
    }
}

long monkey6_op(long number)
{
    return number + 6;
}

long monkey6_test(long index, Monkey **arr)
{
    if (arr[6]->items[index] % 2 == 0)
    {
        throw(arr[6], arr[0], index);
    }
    else
    {
        throw(arr[6], arr[1], index);
    }
}

long monkey7_op(long number)
{
    return number * number;
}

long monkey7_test(long index, Monkey **arr)
{
    if (arr[7]->items[index] % 13 == 0)
    {
        throw(arr[7], arr[6], index);
    }
    else
    {
        throw(arr[7], arr[4], index);
    }
}

void setTestData(Monkey **arr)
{
    Monkey *monkey0 = malloc(sizeof(Monkey));
    monkey0->items[0] = 54;
    monkey0->items[1] = 89;
    monkey0->items[2] = 94;
    monkey0->count = 3;
    monkey0->test = monkey0_test;
    monkey0->op = monkey0_op;

    Monkey *monkey1 = malloc(sizeof(Monkey));
    monkey1->items[0] = 66;
    monkey1->items[1] = 71;
    monkey1->count = 2;
    monkey1->test = monkey1_test;
    monkey1->op = monkey1_op;

    Monkey *monkey2 = malloc(sizeof(Monkey));
    monkey2->items[0] = 76;
    monkey2->items[1] = 55;
    monkey2->items[2] = 80;
    monkey2->items[3] = 55;
    monkey2->items[4] = 55;
    monkey2->items[5] = 96;
    monkey2->items[6] = 78;
    monkey2->count = 7;
    monkey2->test = monkey2_test;
    monkey2->op = monkey2_op;

    Monkey *monkey3 = malloc(sizeof(Monkey));
    monkey3->items[0] = 93;
    monkey3->items[1] = 69;
    monkey3->items[2] = 76;
    monkey3->items[3] = 66;
    monkey3->items[4] = 89;
    monkey3->items[5] = 54;
    monkey3->items[6] = 59;
    monkey3->items[7] = 94;
    monkey3->count = 8;
    monkey3->test = monkey3_test;
    monkey3->op = monkey3_op;

    Monkey *monkey4 = malloc(sizeof(Monkey));
    monkey4->items[0] = 80;
    monkey4->items[1] = 54;
    monkey4->items[2] = 58;
    monkey4->items[3] = 75;
    monkey4->items[4] = 99;
    monkey4->count = 5;
    monkey4->test = monkey4_test;
    monkey4->op = monkey4_op;

    Monkey *monkey5 = malloc(sizeof(Monkey));
    monkey5->items[0] = 69;
    monkey5->items[1] = 70;
    monkey5->items[2] = 85;
    monkey5->items[3] = 83;
    monkey5->count = 4;
    monkey5->test = monkey5_test;
    monkey5->op = monkey5_op;

    Monkey *monkey6 = malloc(sizeof(Monkey));
    monkey6->items[0] = 89;
    monkey6->count = 1;
    monkey6->test = monkey6_test;
    monkey6->op = monkey6_op;

    Monkey *monkey7 = malloc(sizeof(Monkey));
    monkey7->items[0] = 62;
    monkey7->items[1] = 80;
    monkey7->items[2] = 58;
    monkey7->items[3] = 57;
    monkey7->items[4] = 93;
    monkey7->items[5] = 56;
    monkey7->count = 6;
    monkey7->test = monkey7_test;
    monkey7->op = monkey7_op;

    arr[0] = monkey0;
    arr[1] = monkey1;
    arr[2] = monkey2;
    arr[3] = monkey3;
    arr[4] = monkey4;
    arr[5] = monkey5;
    arr[6] = monkey6;
    arr[7] = monkey7;
}

long main(void)
{
    Monkey *arr[MONKEY_COUNT];

    setTestData(arr);

    long inspections[MONKEY_COUNT] = {0};

    for (long k = 0; k < ROUNDS; k++)
    {
        for (long i = 0; i < MONKEY_COUNT; i++)
        {
            Monkey *monkey = arr[i];

            for (long j = 0; j < monkey->count; j++)
            {
                if (monkey->items[j] > 0)
                {
                    inspections[i]++;
                    long newNumber = reduce(monkey->op(monkey->items[j]));
                    monkey->items[j] = newNumber;
                    monkey->test(j, arr);
                }
            }
        }
    }

    // dealloc
    for (long i = 0; i < MONKEY_COUNT; i++)
    {
        free(arr[i]);
    }

    return 0;
}
