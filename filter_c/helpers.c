#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            int rgb = round((float)(r + g + b) / 3);

            if (rgb > 255)
            {
                image[i][j].rgbtRed = 255;
                image[i][j].rgbtGreen = 255;
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtRed = rgb;
                image[i][j].rgbtGreen = rgb;
                image[i][j].rgbtBlue = rgb;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            int sepiaRed = round((float)((0.393 * r) + (0.769 * g) + (0.189 * b)));
            int sepiaGreen = round((float)((0.349 * r) + (0.686 * g) + (0.168 * b)));
            int sepiaBlue = round((float)((0.272 * r) + (0.534 * g) + (0.131 * b)));

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int cont = width;
    int reflect = width - 1;

    for (int i = 0; i < height; i += 1)
    {

        // if (width % 2 != 0)
        // {
            for (int j = 0; j < width / 2; j += 1)
            {
                int r = image[i][reflect - j].rgbtRed;
                int g = image[i][reflect - j].rgbtGreen;
                int b = image[i][reflect - j].rgbtBlue;

                image[i][reflect - j].rgbtRed = image[i][j].rgbtRed;
                image[i][reflect - j].rgbtGreen = image[i][j].rgbtGreen;
                image[i][reflect - j].rgbtBlue = image[i][j].rgbtBlue;

                image[i][j].rgbtRed = r;
                image[i][j].rgbtGreen = g;
                image[i][j].rgbtBlue = b;

            }

        // if (width % 2 == 0)
        // {
        //     for (int j = 0; j <= width / 2; j += 1)
        //     {
        //         int r = image[i][reflect - j].rgbtRed;
        //         int g = image[i][reflect - j].rgbtGreen;
        //         int b = image[i][reflect - j].rgbtBlue;

        //         image[i][reflect - j].rgbtRed = image[i][j].rgbtRed;
        //         image[i][reflect - j].rgbtGreen = image[i][j].rgbtGreen;
        //         image[i][reflect - j].rgbtBlue = image[i][j].rgbtBlue;

        //         image[i][j].rgbtRed = r;
        //         image[i][j].rgbtGreen = g;
        //         image[i][j].rgbtBlue = b;

        //     }
        // }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];

    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    int r0 = image[i][j].rgbtRed;
                    int g0 = image[i][j].rgbtGreen;
                    int b0 = image[i][j].rgbtBlue;

                    int r1 = image[i][j + 1].rgbtRed;
                    int g1 = image[i][j + 1].rgbtGreen;
                    int b1 = image[i][j + 1].rgbtBlue;

                    int r2 = image[i + 1][j].rgbtRed;
                    int g2 = image[i + 1][j].rgbtGreen;
                    int b2 = image[i + 1][j].rgbtBlue;

                    int r3 = image[i + 1][j + 1].rgbtRed;
                    int g3 = image[i + 1][j + 1].rgbtGreen;
                    int b3 = image[i + 1][j + 1].rgbtBlue;

                    int r = round((float)(r0 + r1 + r2 + r3) / 4);
                    int g = round((float)(g0 + g1 + g2 + g3) / 4);
                    int b = round((float)(b0 + b1 + b2 + b3) / 4);

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }

                if (j > 0 && j < width - 1)
                {
                    int r1 = image[i][j - 1].rgbtRed;
                    int g1 = image[i][j - 1].rgbtGreen;
                    int b1 = image[i][j - 1].rgbtBlue;


                    int ro = image[i][j].rgbtRed;
                    int go = image[i][j].rgbtGreen;
                    int bo = image[i][j].rgbtBlue;

                    int r2 = image[i][j + 1].rgbtRed;
                    int g2 = image[i][j + 1].rgbtGreen;
                    int b2 = image[i][j + 1].rgbtBlue;

                    int r3 = image[i + 1][j - 1].rgbtRed;
                    int g3 = image[i + 1][j - 1].rgbtGreen;
                    int b3 = image[i + 1][j - 1].rgbtBlue;

                    int r4 = image[i + 1][j].rgbtRed;
                    int g4 = image[i + 1][j].rgbtGreen;
                    int b4 = image[i + 1][j].rgbtBlue;

                    int r5 = image[i + 1][j + 1].rgbtRed;
                    int g5 = image[i + 1][j + 1].rgbtGreen;
                    int b5 = image[i + 1][j + 1].rgbtBlue;

                    int r = round((float)(ro + r1 + r2 + r3 + r4 + r5) / 6);
                    int g = round((float)(go + g1 + g2 + g3 + g4 + g5) / 6);
                    int b = round((float)(bo + b1 + b2 + b3 + b4 + b5) / 6);

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }

                if (j == width - 1)
                {
                    int r1 = image[i][j - 1].rgbtRed;
                    int g1 = image[i][j - 1].rgbtGreen;
                    int b1 = image[i][j - 1].rgbtBlue;

                    int r0 = image[i][j].rgbtRed;
                    int g0 = image[i][j].rgbtGreen;
                    int b0 = image[i][j].rgbtBlue;

                    int r2 = image[i + 1][j - 1].rgbtRed;
                    int g2 = image[i + 1][j - 1].rgbtGreen;
                    int b2 = image[i + 1][j - 1].rgbtBlue;

                    int r3 = image[i + 1][j].rgbtRed;
                    int g3 = image[i + 1][j].rgbtGreen;
                    int b3 = image[i + 1][j].rgbtBlue;

                    int r = round((float)(r0 + r1 + r2 + r3) / 4);
                    int g = round((float)(g0 + g1 + g2 + g3) / 4);
                    int b = round((float)(b0 + b1 + b2 + b3) / 4);

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }
            }

            if (i > 0 && i < height - 1)
            {
                if (j == 0)
                {

                    int r1 = image[i - 1][j].rgbtRed;
                    int g1 = image[i - 1][j].rgbtGreen;
                    int b1 = image[i - 1][j].rgbtBlue;

                    int r2 = image[i - 1][j + 1].rgbtRed;
                    int g2 = image[i - 1][j + 1].rgbtGreen;
                    int b2 = image[i - 1][j + 1].rgbtBlue;

                    int r0 = image[i][j].rgbtRed;
                    int g0 = image[i][j].rgbtGreen;
                    int b0 = image[i][j].rgbtBlue;

                    int r3 = image[i][j + 1].rgbtRed;
                    int g3 = image[i][j + 1].rgbtGreen;
                    int b3 = image[i][j + 1].rgbtBlue;

                    int r4 = image[i + 1][j].rgbtRed;
                    int g4 = image[i + 1][j].rgbtGreen;
                    int b4 = image[i + 1][j].rgbtBlue;

                    int r5 = image[i + 1][j + 1].rgbtRed;
                    int g5 = image[i + 1][j + 1].rgbtGreen;
                    int b5 = image[i + 1][j + 1].rgbtBlue;

                    int r = round((float)(r0 + r1 + r2 + r3 + r4 + r5) / 6);
                    int g = round((float)(g0 + g1 + g2 + g3 + g4 + g5) / 6);
                    int b = round((float)(b0 + b1 + b2 + b3 + b4 + b5) / 6);

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }

                if (j > 0 && j < width - 1)
                {
                    int r1 = image[i - 1][j - 1].rgbtRed;
                    int g1 = image[i - 1][j - 1].rgbtGreen;
                    int b1 = image[i - 1][j - 1].rgbtBlue;

                    int r2 = image[i - 1][j].rgbtRed;
                    int g2 = image[i - 1][j].rgbtGreen;
                    int b2 = image[i - 1][j].rgbtBlue;

                    int r3 = image[i - 1][j + 1].rgbtRed;
                    int g3 = image[i - 1][j + 1].rgbtGreen;
                    int b3 = image[i - 1][j + 1].rgbtBlue;

                    int r4 = image[i][j - 1].rgbtRed;
                    int g4 = image[i][j - 1].rgbtGreen;
                    int b4 = image[i][j - 1].rgbtBlue;

                    int r0 = image[i][j].rgbtRed;
                    int g0 = image[i][j].rgbtGreen;
                    int b0 = image[i][j].rgbtBlue;

                    int r5 = image[i][j + 1].rgbtRed;
                    int g5 = image[i][j + 1].rgbtGreen;
                    int b5 = image[i][j + 1].rgbtBlue;

                    int r6 = image[i + 1][j - 1].rgbtRed;
                    int g6 = image[i + 1][j - 1].rgbtGreen;
                    int b6 = image[i + 1][j - 1].rgbtBlue;

                    int r7 = image[i + 1][j].rgbtRed;
                    int g7 = image[i + 1][j].rgbtGreen;
                    int b7 = image[i + 1][j].rgbtBlue;

                    int r8 = image[i + 1][j + 1].rgbtRed;
                    int g8 = image[i + 1][j + 1].rgbtGreen;
                    int b8 = image[i + 1][j + 1].rgbtBlue;

                    int r = round((float)(r0 + r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8) / 9);
                    int g = round((float)(g0 + g1 + g2 + g3 + g4 + g5 + g6 + g7 + g8) / 9);
                    int b = round((float)(b0 + b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8) / 9) ;

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }

                if (j == width - 1)
                {
                    int r1 = image[i - 1][j - 1].rgbtRed;
                    int g1 = image[i - 1][j - 1].rgbtGreen;
                    int b1 = image[i - 1][j - 1].rgbtBlue;

                    int r2 = image[i - 1][j].rgbtRed;
                    int g2 = image[i - 1][j].rgbtGreen;
                    int b2 = image[i - 1][j].rgbtBlue;

                    int r3 = image[i][j - 1].rgbtRed;
                    int g3 = image[i][j - 1].rgbtGreen;
                    int b3 = image[i][j - 1].rgbtBlue;

                    int r0 = image[i][j].rgbtRed;
                    int g0 = image[i][j].rgbtGreen;
                    int b0 = image[i][j].rgbtBlue;

                    int r4 = image[i + 1][j - 1].rgbtRed;
                    int g4 = image[i + 1][j - 1].rgbtGreen;
                    int b4 = image[i + 1][j - 1].rgbtBlue;

                    int r5 = image[i + 1][j].rgbtRed;
                    int g5 = image[i + 1][j].rgbtGreen;
                    int b5 = image[i + 1][j].rgbtBlue;

                    int r = round((float)(r0 + r1 + r2 + r3 + r4 + r5) / 6);
                    int g = round((float)(g0 + g1 + g2 + g3 + g4 + g5) / 6);
                    int b = round((float)(b0 + b1 + b2 + b3 + b4 + b5) / 6);

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }
            }

            if (i == height - 1)
            {
                if (j == 0)
                {
                    int r1 = image[i - 1][j].rgbtRed;
                    int g1 = image[i - 1][j].rgbtGreen;
                    int b1 = image[i - 1][j].rgbtBlue;

                    int r2 = image[i - 1][j + 1].rgbtRed;
                    int g2 = image[i - 1][j + 1].rgbtGreen;
                    int b2 = image[i - 1][j + 1].rgbtBlue;

                    int r0 = image[i][j].rgbtRed;
                    int g0 = image[i][j].rgbtGreen;
                    int b0 = image[i][j].rgbtBlue;

                    int r3 = image[i][j + 1].rgbtRed;
                    int g3 = image[i][j + 1].rgbtGreen;
                    int b3 = image[i][j + 1].rgbtBlue;

                    int r = round((float)(r0 + r1 + r2 + r3) / 4);
                    int g = round((float)(g0 + g1 + g2 + g3) / 4);
                    int b = round((float)(b0 + b1 + b2 + b3) / 4);

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }

                if (j > 0 && j < width - 1)
                {
                    int r1 = image[i][j - 1].rgbtRed;
                    int g1 = image[i][j - 1].rgbtGreen;
                    int b1 = image[i][j - 1].rgbtBlue;

                    int r0= image[i][j].rgbtRed;
                    int g0 = image[i][j].rgbtGreen;
                    int b0 = image[i][j].rgbtBlue;

                    int r2 = image[i][j + 1].rgbtRed;
                    int g2 = image[i][j + 1].rgbtGreen;
                    int b2 = image[i][j + 1].rgbtBlue;

                    int r3 = image[i - 1][j - 1].rgbtRed;
                    int g3 = image[i - 1][j - 1].rgbtGreen;
                    int b3 = image[i - 1][j - 1].rgbtBlue;

                    int r4 = image[i - 1][j].rgbtRed;
                    int g4 = image[i - 1][j].rgbtGreen;
                    int b4 = image[i - 1][j].rgbtBlue;

                    int r5 = image[i - 1][j + 1].rgbtRed;
                    int g5 = image[i - 1][j + 1].rgbtGreen;
                    int b5 = image[i - 1][j + 1].rgbtBlue;

                    int r = round((float)(r0 + r1 + r2 + r3 + r4 + r5) / 6);
                    int g = round((float)(g0 + g1 + g2 + g3 + g4 + g5) / 6);
                    int b = round((float)(b0 + b1 + b2 + b3 + b4 + b5) / 6);

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }

                if (j == width - 1)
                {
                    int r1 = image[i][j - 1].rgbtRed;
                    int g1 = image[i][j - 1].rgbtGreen;
                    int b1 = image[i][j - 1].rgbtBlue;

                    int r0 = image[i][j].rgbtRed;
                    int g0 = image[i][j].rgbtGreen;
                    int b0 = image[i][j].rgbtBlue;

                    int r2 = image[i - 1][j - 1].rgbtRed;
                    int g2 = image[i - 1][j - 1].rgbtGreen;
                    int b2 = image[i - 1][j - 1].rgbtBlue;

                    int r3 = image[i + 1][j].rgbtRed;
                    int g3 = image[i + 1][j].rgbtGreen;
                    int b3 = image[i + 1][j].rgbtBlue;

                    int r = round((float)(r0 + r1 + r2 + r3) / 4);
                    int g = round((float)(g0 + g1 + g2 + g3) / 4);
                    int b = round((float)(b0 + b1 + b2 + b3) / 4);

                    copy_image[i][j].rgbtRed = r;
                    copy_image[i][j].rgbtGreen = g;
                    copy_image[i][j].rgbtBlue = b;
                }
            }
        }
    }
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            image[i][j].rgbtRed = copy_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy_image[i][j].rgbtBlue;
        }
    }
}
