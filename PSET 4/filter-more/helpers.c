#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue + 1) / 3;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int reflected_j = width - j - 1;

            RGBTRIPLE tmp_pixel = image[i][j];
            image[i][j] = image[i][reflected_j];
            image[i][reflected_j] = tmp_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_img[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg_red = 0;
            float avg_green = 0;
            float avg_blue = 0;

            int total_pixels = 0;
            for (int i_shift = -1; i_shift < 2; i_shift++)
            {
                for (int j_shift = -1; j_shift < 2; j_shift++)
                {
                    if (i + i_shift < 0 || i + i_shift >= height || j + j_shift < 0 || j + j_shift >= width)
                    {
                        continue;
                    }

                    avg_red += tmp_img[i + i_shift][j + j_shift].rgbtRed;
                    avg_green += tmp_img[i + i_shift][j + j_shift].rgbtGreen;
                    avg_blue += tmp_img[i + i_shift][j + j_shift].rgbtBlue;

                    total_pixels++;
                }
            }

            avg_red = avg_red / total_pixels + 0.5;
            avg_green = avg_green / total_pixels + 0.5;
            avg_blue = avg_blue / total_pixels + 0.5;

            image[i][j].rgbtRed = avg_red;
            image[i][j].rgbtGreen = avg_green;
            image[i][j].rgbtBlue = avg_blue;
        }
    }
    return;
}

int sobel_operator(int x, int y)
{
    int sobel = round(sqrt(pow(x, 2) + pow(y, 2)));
    if (sobel > 255)
    {
        sobel = 255;
    }
    return sobel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    // Initializing Matrices for Gx,Gy
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // This takes the 3x3 area around pixel[i][j], applies the matrices
            int redx = 0;
            int greenx = 0;
            int bluex = 0;

            int redy = 0;
            int greeny = 0;
            int bluey = 0;

            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int x = i + r - 1;
                    int y = j + c - 1;
                    if (!(x < 0 || x == height || y < 0 || y == height))
                    {
                        redx += copy_image[x][y].rgbtRed * Gx[r][c];
                        greenx += copy_image[x][y].rgbtGreen * Gx[r][c];
                        bluex += copy_image[x][y].rgbtBlue * Gx[r][c];

                        redy += copy_image[x][y].rgbtRed * Gy[r][c];
                        greeny += copy_image[x][y].rgbtGreen * Gy[r][c];
                        bluey += copy_image[x][y].rgbtBlue * Gy[r][c];
                    }
                }
            }

            // Alters the image using sobel
            image[i][j].rgbtRed = sobel_operator(redx, redy);
            image[i][j].rgbtGreen = sobel_operator(greenx, greeny);
            image[i][j].rgbtBlue = sobel_operator(bluex, bluey);
        }
    }

    return;
}