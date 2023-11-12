#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int a, int b)
{
    if ((a > 0) || (b > 0))
    {
        if (a >= b)
            return a;
        else
            return b;
    }
    else
    {
        if (a >= b)
            return b;
        else
            return a;
    }
}

int bintoDecimal(int *a, int size)
{
    int dec = 0;
    int j = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        if (a[i] == 1)
            dec += pow(2, j);
        j++;
    }
    return dec;
}

int bits(int a)
{
    int count = 0;
    while (a != 0)
    {
        a = a / 2;
        count++;
    }
    return count;
}

void display(int *a, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", a[i]);
    }
    printf("\t");
}

int *convertBinary(int a, int size)
{
    int *bin;
    bin = (int *)malloc((size) * sizeof(int));
    int count = bits(a);
    int i = size - 1;
    while (a != 0)
    {
        bin[i] = a % 2;
        a = a / 2;
        i--;
    }
    while (i >= 0)
    {
        bin[i] = 0;
        i--;
    }
    return bin;
}

int *twosComplement(int a, int size)
{
    int *bin;
    bin = (int *)malloc((size) * sizeof(int));
    bin = convertBinary(a, size);
    for (int j = 0; j < size; j++)
    {
        if (bin[j] == 0)
            bin[j] = 1;
        else
            bin[j] = 0;
    }
    for (int k = size - 1; k >= 0; k--)
    {
        if (bin[k] == 1)
            bin[k] = 0;
        else
        {
            bin[k] = 1;
            break;
        }
    }
    return bin;
}

void shiftLeft(int *a, int *q, int size)
{

    for (int j = 0; j < size - 1; j++)
    {
        a[j] = a[j + 1];
    }
    a[size - 1] = q[0];
    for (int j = 0; j < size - 1; j++)
    {
        q[j] = q[j + 1];
    }
    display(a, size);
    display(q, size - 1);
    printf("\tLSL\n");
}

void binAddition(int *a, int *b, int *q, int size)
{
    int c = 0;
    for (int j = size - 1; j >= 0; j--)
    {
        if (a[j] == 1)
        {
            if (b[j] == 1 && c == 1)
            {
                a[j] = 1;
                c = 1;
            }
            else if (b[j] == 0 && c == 0)
            {
                a[j] = 1;
                c = 0;
            }
            else if (b[j] == 1 && c == 0)
            {
                a[j] = 0;
                c = 1;
            }
            else
            {
                a[j] = 0;
                c = 1;
            }
        }
        else
        {
            if (b[j] == 1 && c == 1)
            {
                a[j] = 0;
                c = 1;
            }
            else if (b[j] == 0 && c == 0)
            {
                a[j] = 0;
                c = 0;
            }
            else if (b[j] == 1 && c == 0)
            {
                a[j] = 1;
                c = 0;
            }
            else
            {
                a[j] = 1;
                c = 0;
            }
        }
    }
    display(a, size);
    display(q, size);
}

void restoring(int *a, int *bc, int *q, int size)
{
    int temp[size];
    printf("A\tQ\tStep\n");
    for (int i = 0; i < size; i++)
    {
        printf("\nStep %d:\n", i + 1);
        shiftLeft(a, q, size);
        for (int k = 0; k < size; k++)
        {
            temp[k] = a[k];
        }
        binAddition(a, bc, q, size);
        printf("\tA-B\n");
        if (a[0] == 1)
        {
            printf("Restoring A and Qo = 0\n");
            q[size - 1] = 0;
            for (int j = 0; j < size; j++)
            {
                a[j] = temp[j];
            }
        }
        else
        {
            printf("Not restoring A and Qo = 1\n");
            q[size - 1] = 1;
        }
        display(a, size);
        display(q, size);
    }
    if (a[0] == 1)
        a = temp;
}

void nonrestoring(int *a, int *b, int *bc, int *q, int size)
{
    printf("A\tQ\tStep\n");
    for (int i = 0; i < size; i++)
    {
        printf("\nStep %d:\n", i + 1);
        shiftLeft(a, q, size);
        if (a[0] == 1)
        {
            binAddition(a, b, q, size);
            printf("\tA+B\n");
        }
        else
        {
            binAddition(a, bc, q, size);
            printf("\tA-B\n");
        }
        if (a[0] == 1)
            q[size - 1] = 0;
        else
            q[size - 1] = 1;
        display(a, size);
        display(q, size);
    }
}

int main()
{
    int a, b;
    printf("Enter the two numbers to divide by restoring and non-restoring algorithm: \n");
    scanf("%d %d", &a, &b);
    int size = bits(max(a, b));
    int *dividend, *divisor, *divisorc, *acc;
    acc = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        acc[i] = 0;
    }
    printf(" B = ");
    if (b >= 0)
    {
        divisor = convertBinary(b, size);
        display(divisor, size);
        printf("\nBc = ");
        divisorc = twosComplement(b, size);
        display(divisorc, size);
    }
    else
    {
        divisor = convertBinary((-1 * b), size);
        display(divisor, size);
        printf("\nBc = ");
        divisorc = twosComplement((-1 * b), size);
        display(divisorc, size);
    }
    printf("\nQ = ");
    if (a >= 0)
    {
        dividend = convertBinary(a, size);
        display(dividend, size);
    }
    else
    {
        dividend = convertBinary((-1 * a), size);
        display(dividend, size);
    }
    printf("\nA = ");
    display(acc, size);
    printf("\n");
    int n;
    printf("Select 1 for restoring and 2 for non-restoring algorithm\n");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
    {
        printf("\nBy Restoring Algorithm\n");
        restoring(acc, divisorc, dividend, size);
        break;
    }
    case 2:
    {
        printf("\nBy Non-Restoring Algorithm\n");
        nonrestoring(acc, divisor, divisorc, dividend, size);
        break;
    }
    }
    if (a >= 0 && b > 0)
    {
        printf("\nQuotient = ");
        display(dividend, size);
        printf("which is equivalent to %d", a / b);
        printf("\nRemainder = ");
        display(acc, size);
        printf("which is equivalent to %d", a % b);
    }
    else if (a >= 0 && b < 0)
    {
        printf("\nQuotient = ");
        int temp = bintoDecimal(dividend, size);
        dividend = twosComplement(temp, size);
        display(dividend, size);
        printf("which is equivalent to %d", a / b);
        printf("\nRemainder = ");
        display(acc, size);
        printf("which is equivalent to %d", a % b);
    }
    else if (a < 0 && b < 0)
    {
        printf("\nQuotient = ");
        display(dividend, size);
        printf("which is equivalent to %d", a / b);
        printf("\nRemainder = ");
        int temp = bintoDecimal(acc, size);
        acc = twosComplement(temp, size);
        display(acc, size);
        printf("which is equivalent to %d", a % b);
    }
    else
    {
        printf("\nQuotient = ");
        int temp2 = bintoDecimal(dividend, size);
        dividend = twosComplement(temp2, size);
        display(dividend, size);
        printf("which is equivalent to %d", a / b);
        printf("\nRemainder = ");
        int temp = bintoDecimal(acc, size);
        acc = twosComplement(temp, size);
        display(acc, size);
        printf("which is equivalent to %d", a % b);
    }
}