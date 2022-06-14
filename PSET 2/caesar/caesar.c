#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool isInt(string decimal);
string caesarCipher(string encode, int shift);
char caesarShift(char letter, int shift);

int main(int argc, string argv[])
{
    if (argc != 2 || !isInt(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plainText = get_string("plaintext:  ");
    string cipherText = caesarCipher(plainText, atoi(argv[1]));

    printf("ciphertext: %s\n", cipherText);

    return 0;
}

bool isInt(string decimal)
{
    for (int i = 0, n = strlen(decimal); i < n; i++)
    {
        if (isdigit(decimal[i]) == 0)
        {
            return false;
        }
    }
    return true;
}


string caesarCipher(char encode[], int shift)
{
    for (int i = 0, n = strlen(encode); i < n; i++)
    {
        encode[i] = caesarShift(encode[i], shift);
    }
    return encode;
}

char caesarShift(char letter, int shift)
{
    if (isalpha(letter) == 0)
    {
        return letter;
    }

    // To shift a text within a range, use the formula (x is the thing being shifted): lowerbound + (x + shift - lowerbound) % (upperbound - lowerboard + 1)
    if (islower(letter) != 0)
    {
        return 97 + (letter + shift - 97) % 26;
    }
    return 65 + (letter + shift - 65) % 26;
}