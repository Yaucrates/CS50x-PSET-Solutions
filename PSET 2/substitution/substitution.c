#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool validate(string sub);
string substitutionCipher(char encode[], string sub);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (!validate(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string plainText = get_string("plaintext:  ");
    string cipherText = substitutionCipher(plainText, argv[1]);

    printf("ciphertext: %s\n", cipherText);

    return 0;
}

bool validate(string sub)
{
    // Can only contain 26 letters.
    if (strlen(sub) != 26)
    {
        return false;
    }

    for (int i = 0; i < 26; i++)
    {
        // Makes sure everyone is a letter.
        if (isalpha(sub[i]) == 0)
        {
            return false;
        }
        // Ensures every letter is used once.
        for (int j = i + 1; j < 26; j++)
        {
            if (tolower(sub[i]) == tolower(sub[j]))
            {
                return false;
            }
        }
    }

    return true;
}

string substitutionCipher(char encode[], string sub)
{
    for (int i = 0, n = strlen(encode); i < n; i++)
    {
        if (islower(encode[i]) != 0)
        {
            int num = encode[i] - 97;
            encode[i] = tolower(sub[num]);
        }
        else if (isupper(encode[i]) != 0)
        {
            int num = encode[i] - 65;
            encode[i] = toupper(sub[num]);
        }
    }
    return encode;
}