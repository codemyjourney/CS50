#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Helper function for sepia filter;
int check_value();

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue =  image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //gets the values of each color in the image
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            // gets the sepia value of the pixels
            sepiaRed = round(0.393 * red + 0.769 * green + 0.189 * blue)  ;
            sepiaGreen = round(0.349 * red + 0.686 * green + 0.168 * blue) ;
            sepiaBlue = round(0.272 * red + 0.534 * green + 0.131 * blue) ;

            image[i][j].rgbtRed = check_value(sepiaRed);
            image[i][j].rgbtBlue = check_value(sepiaBlue);
            image[i][j].rgbtGreen = check_value(sepiaGreen);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int swaps;
    if (width % 2 == 0)
    {
        swaps = width / 2;
    }
    else
    {
        swaps = round(width / 2);
    }

    for (int i = 0; i < height; i++)
    {
        int start = 0;
        int finish = width - 1;

        for (int s = 0; s < swaps; s++)
        {
            RGBTRIPLE temp = image[i][start];
            image[i][start] = image[i][finish];
            image[i][finish] = temp;
            start ++;
            finish --;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE ogImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ogImage[i][j] = image[i][j];
        }
    }

    for (int i = 0, red, green, blue, counter; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = green = blue = counter = 0;

            if (i >= 0 && j >= 0)
            {
                red += ogImage[i][j].rgbtRed;
                green += ogImage[i][j].rgbtGreen;
                blue += ogImage[i][j].rgbtBlue;
                counter++;
            }
            if (i >= 0 && j - 1 >= 0)
            {
                red += ogImage[i][j - 1].rgbtRed;
                green += ogImage[i][j - 1].rgbtGreen;
                blue += ogImage[i][j - 1].rgbtBlue;
                counter++;
            }
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                red += ogImage[i][j + 1].rgbtRed;
                green += ogImage[i][j + 1].rgbtGreen;
                blue += ogImage[i][j + 1].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j >= 0)
            {
                red += ogImage[i - 1][j].rgbtRed;
                green += ogImage[i - 1][j].rgbtGreen;
                blue += ogImage[i - 1][j].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += ogImage[i - 1][j - 1].rgbtRed;
                green += ogImage[i - 1][j - 1].rgbtGreen;
                blue += ogImage[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                red += ogImage[i - 1][j + 1].rgbtRed;
                green += ogImage[i - 1][j + 1].rgbtGreen;
                blue += ogImage[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                red += ogImage[i + 1][j].rgbtRed;
                green += ogImage[i + 1][j].rgbtGreen;
                blue += ogImage[i + 1][j].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                red += ogImage[i + 1][j - 1].rgbtRed;
                green += ogImage[i + 1][j - 1].rgbtGreen;
                blue += ogImage[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                red += ogImage[i + 1][j + 1].rgbtRed;
                green += ogImage[i + 1][j + 1].rgbtGreen;
                blue += ogImage[i + 1][j + 1].rgbtBlue;
                counter++;
            }

            image[i][j].rgbtRed = round(red / (counter * 1.0));
            image[i][j].rgbtGreen = round(green / (counter * 1.0));
            image[i][j].rgbtBlue = round(blue / (counter * 1.0));
        }
    }
    return;
}


int check_value(int sepia)
{
    if (sepia >= 256)
    {
        return 255;
    }
    else
    {
        return sepia;
    }
}
