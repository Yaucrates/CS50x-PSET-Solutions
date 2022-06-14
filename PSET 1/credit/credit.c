#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getDigit(long creditCardNum, int digit);
int ccLength(long creditCardNum);
bool validate(long creditCardNum);
string cardType(long creditCardNum, bool valid);

int main(void)
{
    const long creditCardNum = get_long("Number: ");

    bool valid = validate(creditCardNum);

    // Outputs type of card if valid
    printf("%s", cardType(creditCardNum, valid));
}

int getDigit(long creditCardNum, int digit)
{
    // Gets you the digit you need.
    long num = creditCardNum % (long) pow(10, digit);
    return num / pow(10, digit - 1);
}

int ccLength(long creditCardNum)
{
    // Find you the length of the Credit Card.
    // Idea behind this is if (10^N > num) but (10^(N-1) < num) then the credit card has N digits.
    int totalDigits = 1;
    while (creditCardNum > pow(10, totalDigits))
    {
        totalDigits++;
    }
    return totalDigits;
}

bool validate(long creditCardNum)
{
    // Validates Credit Card w/ Luhn's Algorithm
    int digitsInCC = ccLength(creditCardNum);
    int total = 0;

    // Implementation of Luhn's Algorithm.
    for (int i = 0; i < digitsInCC; i++)
    {
        if (i % 2 == 1)
        {
            int tmp = 2 * getDigit(creditCardNum, i + 1);
            if (tmp > 9)
            {
                /**
                 * 2*n, where n is 0 to 9, gives us a range of numbers from 0 to 18.
                 * We will only consider numbers greater than 9
                 * If 2*n > 10, then we have to sum the digits of 2*n and add that instead of 2*n
                 * There for we'll only deal with 10-18
                 * The ten's place is always 1 for those numbers
                 * To get the one's place, you can do 2*n - 10 ( this will elimate the tens place since it is always 1 )
                 * ( ten's place ) + ( one's place) = ( 1 ) + ( 2*n - 10 ) = 2*n - 9
                 * Since tmp is 2*n, we can simplify it to be tmp - 9
                 * P.S. FUTURE YOUSIF, YOU KNEW THIS WAS A BAD COMMENT, BUT YOU DON'T KNOW WHY OTHER THAN IT'S BULKY AND SEEMS TRIVIAL. PROCEED TO CRINGE.
                 */
                total += tmp - 9;
            }
            else
            {
                total += tmp;
            }
        }
        else
        {
            total += getDigit(creditCardNum, i + 1);
        }
    }

    return (total % 10 == 0);
}

string cardType(long creditCardNum, bool valid)
{
    // checks for invalidity
    if (!valid)
    {
        return "INVALID\n";
    }

    int digitsInCC = ccLength(creditCardNum);
    int doubleDigits = 10 * getDigit(creditCardNum, digitsInCC) + getDigit(creditCardNum, digitsInCC - 1);

    if ((doubleDigits == 34 || doubleDigits == 37) && digitsInCC == 15)
    {
        return "AMEX\n";
    }

    if ((doubleDigits > 50 && doubleDigits < 56) && digitsInCC == 16)
    {
        return "MASTERCARD\n";
    }

    if ((doubleDigits / 10 == 4) && (digitsInCC == 13 || digitsInCC == 16))
    {
        return "VISA\n";
    }

    return "INVALID\n";
}