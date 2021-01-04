#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int indexOf(char el, string arr);
bool valid_k(string k);
void msg_encode(string msg, string key);

int indexOf(char el, string arr)
{
    int n_i = 0;
    int length = strlen(arr);
    for (int index = 0; index < length; index += 1)
    {
        if (arr[index] == tolower(el) || arr[index] == toupper(el))
        {
            n_i = index;
            break;
        }
    }
    return n_i;
}

bool valid_k(string k)
{
    int length = strlen(k);
    for (int index = 0; index < length; index += 1)
    {
        if (isalpha(k[index]))
        {
            if (indexOf(k[index], k) != index)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

void msg_encode(string msg, string key)
{
    int  length = strlen(msg);
    printf("ciphertext: ");
    for (int index = 0; index < length; index += 1)
    {
        if (isalpha(msg[index]))
        {

            if (isupper(msg[index]))
            {
                int k = (int)msg[index] - 65;
                printf("%c", toupper(key[k]));
            }

            if (islower(msg[index]))
            {
                int k = (int)msg[index] - 97;
                printf("%c", tolower(key[k]));
            }

        }
        else
        {
            printf("%c", msg[index]);
        }
    }
    printf("\n");
}

int main(int args, string argv[ ])
{
    if (args == 2)
    {
        if (valid_k(argv[1]) && strlen(argv[1]) == 26)
        {
            string msg = get_string("plaintext:  ");
            msg_encode(msg, argv[1]);
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    return 0;
}


// YTNSHKVEFXRBAUQZCLWDMIPGJO