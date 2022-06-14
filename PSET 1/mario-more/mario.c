#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get height between [1, 8]
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // total loops
    for (int blocks = 1; blocks <= height; blocks++)
    {
        // adds spaces
        for (int i = height - blocks; i > 0; i--)
        {
            printf(" ");
        }

        // adds blocks
        for (int i = 0; i < blocks; i++)
        {
            printf("#");
        }

        // add gap
        printf("  ");

        // add right pyramid
        for (int i = 0; i < blocks; i++)
        {
            printf("#");
        }

        // next level
        printf("\n");
    }
}