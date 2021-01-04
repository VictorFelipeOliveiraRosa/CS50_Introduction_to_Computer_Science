#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void isUpper(char cUpper, int key)
{
    if ((key + (int)cUpper) <= 90)
    {
        printf("%c", cUpper + key);
    }

    else if ((key + (int)cUpper) > 90)
    {
        int c = ((int)cUpper + key) % 90;
        c += 64;
        if (c <= 90)
        {
            printf("%c", (char)c);
        }
        else
        {
            do
            {
                c = c % 90;
                c += 64;
            }
            while (c > 90);
            printf("%c", (char)c);
        }
    }

    else
    {
        printf("%c", cUpper);
    }
}

void isLower(char cLower, int key)
{
    if ((key + (int)cLower) <= 122)
    {
        printf("%c", cLower + key);
    }

    else if ((key + (int)cLower) > 122)
    {
        int c = ((int)cLower + key) % 122;
        c += 96;
        if (c <= 122)
        {
            printf("%c", (char)c);
        }
        else
        {
            do
            {
                c = c % 122;
                c += 96;
            }
            while (c > 122);
            printf("%c", (char)c);
        }
    }

    else
    {
        printf("%c", cLower);
    }
}

void code_msg(string text, int key)
{
    int length = strlen(text);
    printf("ciphertext: ");
    for (int index = 0; index < length; index += 1)
    {

        if (isalpha(text[index]))
        {
            if (isupper(text[index]))
            {
                isUpper(text[index], key);
            }

            if (islower(text[index]))
            {
                isLower(text[index], key);
            }
        }
        else
        {
            printf("%c", text[index]);
        }
    }
    printf("\n");

}

int main(int args, char *argv[ ])
{
    if (args == 1 || args > 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    else
    {
        int cont = 0;
        int length = strlen(argv[1]);
        for (int index = 0; index < length; index += 1)
        {
            if (isalpha(argv[1][index]))
            {
                cont += 1;
            }
        }
        if (cont > 0)
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
        else
        {
            int k = atoi(argv[1]);
            printf("Success\n");
            printf("%d\n", k);
            string text = get_string("plaintext:  ");
            code_msg(text, k);
            return 0;
        }
    }

}

