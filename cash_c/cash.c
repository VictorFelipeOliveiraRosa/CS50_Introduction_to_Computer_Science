#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    float dollars = 0;

    do
    {
        dollars = get_float("X: \n");
    }
    while (dollars <= 0);

    dollars = round(dollars * 100);
    int cont = 0;

    do
    {
        if (dollars >= 25)
        {
            dollars -= 25;

        }
        else if (dollars >= 10)
        {
            dollars -= 10;
        }
        else if (dollars >= 5)
        {
            dollars -= 5;
        }
        else if (dollars >= 1)
        {
            dollars -= 1;
        }

        cont += 1;
    }
    while (dollars > 0);

    printf("Numero de moedas ---> %d\n", cont);
}