#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE red = image[i][j].rgbtRed;
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;

            BYTE grey = round((red + blue + green) / 3.0);

            image[i][j].rgbtRed = grey;
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;

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
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE original_image[height][width])
{
    int steps[9][2] = {{1, -1}, {1, 0}, {1, 1}, {0, -1}, {0, 0}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}};
    int rsum, gsum, bsum;

    RGBTRIPLE image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = original_image[i][j];
        }
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rsum = 0;
            gsum = 0;
            bsum = 0;
            int counter = 0;
            bool checked = false;
            if (i == 0 && j == 0 && !checked)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (steps[k][0] != -1 && steps[k][1] != -1)
                    {
                        rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                        gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                        bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                        counter++;
                        checked = true;
                    }

                }
            }
            else if (i == 0 && j == width - 1 && !checked)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (steps[k][0] != -1 && steps[k][1] != 1)
                    {
                        rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                        gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                        bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                        counter++;
                        checked = true;
                    }

                }
            }
            else if (i == height - 1 && j == 0 && !checked)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (steps[k][0] != 1 && steps[k][1] != -1)
                    {
                        rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                        gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                        bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                        counter++;
                        checked = true;
                    }

                }
            }
            else if (i == height - 1 && j == width - 1 && !checked)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (steps[k][0] != 1 && steps[k][1] != 1)
                    {
                        rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                        gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                        bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                        counter++;
                        checked = true;
                    }

                }
            }
            else if (i == height - 1 && !checked)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (steps[k][0] != 1)
                    {
                        rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                        gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                        bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                        counter++;
                        checked = true;
                    }

                }
            }
            else if (j == width - 1 && !checked)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (steps[k][1] != 1)
                    {
                        rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                        gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                        bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                        counter++;
                        checked = true;
                    }

                }
            }
            else if (i == 0 && !checked)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (steps[k][0] != -1)
                    {
                        rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                        gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                        bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                        counter++;
                        checked = true;
                    }

                }
            }
            else if (j == 0 && !checked)
            {
                for (int k = 0; k < 9; k++)
                {
                    if (steps[k][1] != -1)
                    {
                        rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                        gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                        bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                        counter++;
                        checked = true;
                    }

                }
            }
            else
            {
                for (int k = 0; k < 9; k++)
                {
                    rsum += image[i + steps[k][0]][j + steps[k][1]].rgbtRed;
                    gsum += image[i + steps[k][0]][j + steps[k][1]].rgbtGreen;
                    bsum += image[i + steps[k][0]][j + steps[k][1]].rgbtBlue;
                    counter++;
                    checked = true;
                }
            }
            //printf("%i, %i", rsum, counter);

            original_image[i][j].rgbtRed = round(rsum / (float) counter);
            original_image[i][j].rgbtBlue = round(bsum / (float) counter);
            original_image[i][j].rgbtGreen = round(gsum / (float) counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE original_image[height][width])
{
    int rGx, gGx, bGx, rGy, gGy, bGy;
    RGBTRIPLE image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = original_image[i][j];
        }
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rGx = 0;
            gGx = 0;
            bGx = 0;
            rGy = 0;
            gGy = 0;
            bGy = 0;

            bool checked = false;

            // Replace the functions with the Gx and Gy conditions for each colour
            // Calculations are all done below


            if (i == 0 && j == 0 && !checked)
            {
                // Gx, clockwise

                rGx += (2 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed);

                gGx += (2 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);

                bGx += (2 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);

                // Gy, clockwise

                rGy += (image[i + 1][j + 1].rgbtRed + 2 * image[i + 1][j].rgbtRed);

                gGy += (image[i + 1][j + 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen);

                bGy += (image[i + 1][j + 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue);
            }
            else if (i == 0 && j == width - 1 && !checked)
            {
                // Gx, clockwise

                rGx += (-image[i + 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);

                gGx += (-image[i + 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);

                bGx += (-image[i + 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);

                // Gy, clockwise

                rGy += (2 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed);

                gGy += (2 * image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen);

                bGy += (2 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue);
            }
            else if (i == height - 1 && j == 0 && !checked)
            {
                // Gx, clockwise

                rGx += (image[i - 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed);

                gGx += (image[i - 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen);

                bGx += (image[i - 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue);

                // Gy, clockwise

                rGy += (-2 * image[i - 1][j].rgbtRed + -image[i - 1][j + 1].rgbtRed);

                gGy += (-2 * image[i - 1][j].rgbtGreen + -image[i - 1][j + 1].rgbtGreen);

                bGy += (-2 * image[i - 1][j].rgbtBlue + -image[i - 1][j + 1].rgbtBlue);
            }
            else if (i == height - 1 && j == width - 1 && !checked)
            {
                // Gx, clockwise

                rGx += (-image[i - 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);

                gGx += (-image[i - 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);

                bGx += (-image[i - 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);

                // Gy, clockwise

                rGy += (-image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed);

                gGy += (-image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen);

                bGy += (-image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue);
            }
            else if (i == height - 1 && !checked)
            {
                // Gx, clockwise

                rGx += (-image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);

                gGx += (-image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);

                bGx += (-image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);

                // Gy, clockwise

                rGy += (-image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed + -image[i - 1][j + 1].rgbtRed);

                gGy += (-image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen + -image[i - 1][j + 1].rgbtGreen);

                bGy += (-image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue + -image[i - 1][j + 1].rgbtBlue);
            }
            else if (j == width - 1 && !checked)
            {
                // Gx, clockwise

                rGx += (-image[i - 1][j - 1].rgbtRed + -image[i + 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);

                gGx += (-image[i - 1][j - 1].rgbtGreen + -image[i + 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);

                bGx += (-image[i - 1][j - 1].rgbtBlue + -image[i + 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);

                // Gy, clockwise

                rGy += (-image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed + 2 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed);

                gGy += (-image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen + 2 * image[i + 1][j].rgbtGreen + image[i + 1][j -
                1].rgbtGreen);

                bGy += (-image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue + 2 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue);
            }
            else if (i == 0 && !checked)
            {
                // Gx, clockwise

                rGx += (2 * image[i][j + 1].rgbtRed
                        + image[i + 1][j + 1].rgbtRed + -image[i + 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);

                gGx += (2 * image[i][j + 1].rgbtGreen
                        + image[i + 1][j + 1].rgbtGreen + -image[i + 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);

                bGx += (2 * image[i][j + 1].rgbtBlue
                        + image[i + 1][j + 1].rgbtBlue + -image[i + 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);

                // Gy, clockwise

                rGy += (image[i + 1][j + 1].rgbtRed + 2 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed);

                gGy += (image[i + 1][j + 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen);

                bGy += (image[i + 1][j + 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue);
            }
            else if (j == 0 && !checked)
            {
                // Gx, clockwise

                rGx += (image[i - 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed
                    + image[i + 1][j + 1].rgbtRed);

                gGx += (image[i - 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen
                    + image[i + 1][j + 1].rgbtGreen);

                bGx += (image[i - 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue
                    + image[i + 1][j + 1].rgbtBlue);

                // Gy, clockwise

                rGy += (-2 * image[i - 1][j].rgbtRed + -image[i - 1][j + 1].rgbtRed
                + image[i + 1][j + 1].rgbtRed + 2 * image[i + 1][j].rgbtRed);

                gGy += (-2 * image[i - 1][j].rgbtGreen + -image[i - 1][j + 1].rgbtGreen
                + image[i + 1][j + 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen);

                bGy += (-2 * image[i - 1][j].rgbtBlue + -image[i - 1][j + 1].rgbtBlue
                + image[i + 1][j + 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue);
            }
            else
            {
                // Gx, clockwise

                rGx += (-image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed - image[i + 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed);

                gGx += (-image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen);

                bGx += (-image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue);

                // Gy, clockwise

                rGy += (-image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + 2 * image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed);

                gGy += (-image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen);

                bGy += (-image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue);
            }
            //printf("%i, %i", rsum, counter);

            int red = round(pow((float) pow(rGx, 2) + pow(rGy, 2), 0.5));
            int green = round(pow((float) pow(gGx, 2) + pow(gGy, 2), 0.5));
            int blue = round(pow((float) pow(bGx, 2) + pow(bGy, 2), 0.5));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            original_image[i][j].rgbtRed = red;
            original_image[i][j].rgbtBlue = blue;
            original_image[i][j].rgbtGreen = green;
        }
    }
    return;
}
