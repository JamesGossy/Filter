#include <stdio.h>
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row ++)
    {
        for (int col = 0; col < width; col++)
        {
            int average = round((image[row][col].rgbtRed + image[row][col].rgbtGreen + image[row][col].rgbtBlue)/3.0);
            image[row][col].rgbtRed = average;
            image[row][col].rgbtBlue = average;
            image[row][col].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row ++)
    {
        for (int col = 0; col < width; col++)
        {
            int new_red = round((.393 * image[row][col].rgbtRed) + (.769 * image[row][col].rgbtGreen) + (.189 * image[row][col].rgbtBlue));
            int new_green = round((.349 * image[row][col].rgbtRed) + (.686 * image[row][col].rgbtGreen) + (.168 * image[row][col].rgbtBlue));
            int new_blue = round((.272 * image[row][col].rgbtRed) + (.534 * image[row][col].rgbtGreen) + (.131 * image[row][col].rgbtBlue));

            image[row][col].rgbtRed = (new_red > 255) ? 255 : new_red;
            image[row][col].rgbtGreen = (new_green > 255) ? 255 : new_green;
            image[row][col].rgbtBlue = (new_blue > 255) ? 255 : new_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row ++)
    {
        for (int col = 0; col < width/2; col++)
        {
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width-col-1];
            image[row][width-col-1] = temp;
        }
    }
    return;}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }

    for (int row = 0; row < height; row ++)
    {
        for (int col = 0; col < width; col++)
        {
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;

            int valid_pixels = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (row + i >= 0 && row + i < height && col + j >= 0 && col + j < width)
                    {
                        sum_red += copy[row+i][col+j].rgbtRed;
                        sum_green += copy[row+i][col+j].rgbtGreen;
                        sum_blue += copy[row+i][col+j].rgbtBlue;
                        valid_pixels += 1;
                    }
                }
            }
            image[row][col].rgbtRed = round((sum_red)/valid_pixels);
            image[row][col].rgbtGreen = round((sum_green)/valid_pixels);
            image[row][col].rgbtBlue = round((sum_blue)/valid_pixels);

        }
    }

    return;
}
