#include <cs50.h>
#include <stdio.h>

int get_integer(string printString);

int get_integer(string printString)
{
    int number = 0;
    printf("%s", printString);
    scanf("%d", &number);
    return number;
}

int main(void)
{
    int n = 0;

    do
    {
        n = get_integer("Number: \n");
    }
    while (n < 1);

    for (int line = 1; line <= n; line += 1)
    {
        for (int column = 1; column <= n - line; column += 1)
        {
            printf(" ");
        }
        for (int has = 1; has <= line; has += 1)
        {
            printf("#");
        }
        printf("\n");
    }
}