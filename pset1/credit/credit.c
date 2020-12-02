#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    long credit = get_long("Is number credit: \n");
    int num1  = (credit / 1) % 10;
    int num2  = (credit / 10) % 10;
    int num3  = (credit / 100) % 10;
    int num4  = (credit / 1000) % 10;
    int num5  = (credit / 10000) % 10;
    int num6  = (credit / 100000) % 10;
    int num7  = (credit / 1000000) % 10;
    int num8  = (credit / 10000000) % 10;
    int num9  = (credit / 100000000) % 10;
    int num10 = (credit / 1000000000) % 10;
    int num11 = (credit / 10000000000) % 10;
    int num12 = (credit / 100000000000) % 10;
    int num13 = (credit / 1000000000000) % 10;
    int num14 = (credit / 10000000000000) % 10;
    int num15 = (credit / 100000000000000) % 10;
    int num16 = (credit / 1000000000000000) % 10;


    int auxOne = 0;
    int auxTwo = 0;

    num2  = num2  * 2;
    if (num2 > 9)
    {
        auxOne = num2 % 10;
        auxTwo = (num2 / 10) % 10;
        num2 = auxOne + auxTwo;
    }

    num4  = num4  * 2;
    if (num4 > 9)
    {
        auxOne = num4 % 10;
        auxTwo = (num4 / 10) % 10;
        num4 = auxOne + auxTwo;
    }

    num6  = num6  * 2;
    if (num6 > 9)
    {
        auxOne = num6 % 10;
        auxTwo = (num6 / 10) % 10;
        num6 = auxOne + auxTwo;
    }

    num8  = num8  * 2;
    if (num8 > 9)
    {
        auxOne = num8 % 10;
        auxTwo = (num8 / 10) % 10;
        num8 = auxOne + auxTwo;
    }

    num10 = num10 * 2;
    if (num10 > 9)
    {
        auxOne = num10 % 10;
        auxTwo = (num10 / 10) % 10;
        num10 = auxOne + auxTwo;
    }

    num12 = num12 * 2;
    if (num12 > 9)
    {
        auxOne = num12 / 10;
        auxTwo = num12 - (auxOne * 10);
        num12 = auxOne + auxTwo;
    }

    num14 = num14 * 2;
    if (num14 > 9)
    {
        auxOne = num14 % 10;
        auxTwo = (num14 / 10) % 10;
        num14 = auxOne + auxTwo;
    }

    num16 = num16 * 2;
    if (num16 > 9)
    {
        auxOne = num16 % 10;
        auxTwo = (num16 / 10) % 10;
        num16 = auxOne + auxTwo;
    }

    int total1 = num1 + num3 + num5 + num7 + num9 + num11 + num13 + num15;
    int total2 = num2 + num4 + num6 + num8 + num10 + num12 + num14 + num16;
    // total /= 10;
    int total = total1 + total2;
    int type = 0;
    if (num16 > 0)
    {
        type = (num16 * 10) + num15;
    }
    else if (num15 > 0)
    {
        type = (num15 * 10) + num14;
    }
    else if (num14 > 0)
    {
        type = (num14 * 10) + num13;
    }
    else if (num13 > 0)
    {
        type = (num13 * 10) + num12;
    }

    if (total % 10 == 0)
    {
        if ((type >= 50 && type <= 55) || type == 22)
        {
            printf("MASTERCARD\n");
        }
        else if (type == 34 || type == 37)
        {
            printf(" AMEX\n");
        }
        else if (type >= 40 && type <= 49)
        {
            printf("VISA\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}
