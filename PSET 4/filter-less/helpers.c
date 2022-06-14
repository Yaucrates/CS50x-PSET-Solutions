#include "helpers.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue + 0.5;
            float sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue + 0.5;
            float sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue + 0.5;

            image[i][j].rgbtRed = sepiaRed;
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }

            image[i][j].rgbtGreen = sepiaGreen;
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
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
