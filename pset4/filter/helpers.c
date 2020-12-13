#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Essentially for every pixel I'm just finding the average value of the 3 colours and setting them all to that

            int greyscale_val = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3.0f);

            image[i][j].rgbtBlue = greyscale_val;
            image[i][j].rgbtGreen = greyscale_val;
            image[i][j].rgbtRed = greyscale_val;
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For this one I reckon I'll need to make a new image and then set the original to be that, I don't think I can just change it because I'll change a pixel, and need to use it later in the row for the reflection
    // Might be a better way of doing this that would save the memory of making a whole new image but for now it works

    // So start by initialisng a new image

    RGBTRIPLE reflection[height][width];

    // Now make that reflected image using the original

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            reflection[i][width - (j+1)].rgbtBlue = image[i][j].rgbtBlue;
            reflection[i][width - (j+1)].rgbtGreen = image[i][j].rgbtGreen;
            reflection[i][width - (j+1)].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // And finally set the original to be the new reflection's values

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtBlue = reflection[x][y].rgbtBlue;
            image[x][y].rgbtGreen = reflection[x][y].rgbtGreen;
            image[x][y].rgbtRed = reflection[x][y].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // So again here we need to look at each individual pixel. Again I think we need to make a new image here otherwise we risk changing the pixels which are then used in the other calculations

    // So again, initialise a new image

    RGBTRIPLE blurred[height][width];

    // I'm also going to initialise the ints I need for my conditions in my loop here

    int red;
    int green;
    int blue;
    int cond_count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Problem here is that our calculation needs to change based on whether we're looking at a corner, edge, or bits in the middle. So we need a lot of conditions here

            // Actually going to initialise a value for the Green, Blue and Red, then add to it based on each condition, rather than do a whole summation for each condition

            red = 0;
            blue = 0;
            green = 0;
            cond_count = 0;

            // First because all pixels do it, we add the pixel value itself

            red += image[i][j].rgbtRed;
            blue += image[i][j].rgbtBlue;
            green += image[i][j].rgbtGreen;
            cond_count++;

            // Now going to go through each pixel in the surrounding grid, starting with top-left
            if (j != 0 && i != 0)
            {
                red += image[i-1][j-1].rgbtRed;
                blue += image[i-1][j-1].rgbtBlue;
                green += image[i-1][j-1].rgbtGreen;
                cond_count++;
            }

            // Top
            if (i != 0)
            {
                red += image[i-1][j].rgbtRed;
                blue += image[i-1][j].rgbtBlue;
                green += image[i-1][j].rgbtGreen;
                cond_count++;
            }

            // Top-right
            if (i != 0 && j != width-1)
            {
                red += image[i-1][j+1].rgbtRed;
                blue += image[i-1][j+1].rgbtBlue;
                green += image[i-1][j+1].rgbtGreen;
                cond_count++;
            }

            // Left
            if (j != 0)
            {
                red += image[i][j-1].rgbtRed;
                blue += image[i][j-1].rgbtBlue;
                green += image[i][j-1].rgbtGreen;
                cond_count++;
            }

            // Right
            if (j != width-1)
            {
                red += image[i][j+1].rgbtRed;
                blue += image[i][j+1].rgbtBlue;
                green += image[i][j+1].rgbtGreen;
                cond_count++;
            }

            // Bottom-left
            if (i != height-1 && j != 0)
            {
                red += image[i+1][j-1].rgbtRed;
                blue += image[i+1][j-1].rgbtBlue;
                green += image[i+1][j-1].rgbtGreen;
                cond_count++;
            }

            // Bottom
            if (i != height-1)
            {
                red += image[i+1][j].rgbtRed;
                blue += image[i+1][j].rgbtBlue;
                green += image[i+1][j].rgbtGreen;
                cond_count++;
            }

            // Finally, bottom-right
            if (i != height-1 && j != width-1)
            {
                red += image[i+1][j+1].rgbtRed;
                blue += image[i+1][j+1].rgbtBlue;
                green += image[i+1][j+1].rgbtGreen;
                cond_count++;
            }

            // And now we make the pixel in our new image. Is there a better way of gettign the average than having to cast everything as a float? Seems a bit rubbish tbh
            blurred[i][j].rgbtRed = round((float)red/(float)cond_count);
            blurred[i][j].rgbtBlue = round((float)blue/(float)cond_count);
            blurred[i][j].rgbtGreen = round((float)green/(float)cond_count);

        }
    }

    // And finally set the original to be the new blurred image's values

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtBlue = blurred[x][y].rgbtBlue;
            image[x][y].rgbtGreen = blurred[x][y].rgbtGreen;
            image[x][y].rgbtRed = blurred[x][y].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Going to start by making a new image, which is the same as the original but with a black border around it. Should make the calculation easier later on

    // First we initialise it (with an extra 2 pixels on each edge to add the border)

    RGBTRIPLE bordered[height+2][width+2];

    // Now add the border, and fill in the middle

    for (int i = 0; i < height+2; i++)
    {
        for (int j = 0; j < width+2; j++)
        {
            // First the black border
            if (i == 0 || j == 0 || i == height+1 || j == width+1)
            {
                bordered[i][j].rgbtRed = 0;
                bordered[i][j].rgbtGreen = 0;
                bordered[i][j].rgbtBlue = 0;
            }

            else
            {
                // Now we fill in the middle
                bordered[i][j].rgbtRed = image[i-1][j-1].rgbtRed;
                bordered[i][j].rgbtGreen = image[i-1][j-1].rgbtGreen;
                bordered[i][j].rgbtBlue = image[i-1][j-1].rgbtBlue;
            }
        }
    }

    // Now we're going to make another image, this one though to show where the edges are

    RGBTRIPLE edged[height][width];

    int Gxred;
    int Gyred;
    int Gxgreen;
    int Gygreen;
    int Gxblue;
    int Gyblue;
    int edge_red;
    int edge_green;
    int edge_blue;


    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Gxred = ((bordered[y][x].rgbtRed * -1) + (bordered[y][x+2].rgbtRed * 1) + (bordered[y+1][x].rgbtRed * -2) + (bordered[y+1][x+2].rgbtRed * 2) + (bordered[y+2][x].rgbtRed * -1) + (bordered[y+2][x+2].rgbtRed * 1));
            Gyred = ((bordered[y][x].rgbtRed * -1) + (bordered[y][x+1].rgbtRed * -2) + (bordered[y][x+2].rgbtRed * -1) + (bordered[y+2][x].rgbtRed * 1) + (bordered[y+2][x+1].rgbtRed * 2)  + (bordered[y+2][x+2].rgbtRed * 1));
            Gxgreen = ((bordered[y][x].rgbtGreen * -1) + (bordered[y][x+2].rgbtGreen * 1) + (bordered[y+1][x].rgbtGreen * -2) + (bordered[y+1][x+2].rgbtGreen * 2) + (bordered[y+2][x].rgbtGreen * -1) + (bordered[y+2][x+2].rgbtGreen * 1));
            Gygreen = ((bordered[y][x].rgbtGreen * -1) + (bordered[y][x+1].rgbtGreen * -2) + (bordered[y][x+2].rgbtGreen * -1) + (bordered[y+2][x].rgbtGreen * 1) + (bordered[y+2][x+1].rgbtGreen * 2)  + (bordered[y+2][x+2].rgbtGreen * 1));
            Gxblue = ((bordered[y][x].rgbtBlue * -1) + (bordered[y][x+2].rgbtBlue * 1) + (bordered[y+1][x].rgbtBlue * -2) + (bordered[y+1][x+2].rgbtBlue * 2) + (bordered[y+2][x].rgbtBlue * -1) + (bordered[y+2][x+2].rgbtBlue * 1));
            Gyblue = ((bordered[y][x].rgbtBlue * -1) + (bordered[y][x+1].rgbtBlue * -2) + (bordered[y][x+2].rgbtBlue * -1) + (bordered[y+2][x].rgbtBlue * 1) + (bordered[y+2][x+1].rgbtBlue * 2)  + (bordered[y+2][x+2].rgbtBlue * 1));


            // Having to write Gx * Gx rather than Gx^2 as the to the power of operator goes out of the range of int, and putting it as a double isn't allowed either. Probably a better way of doing this but it works

            edge_red = round(sqrt((float)Gxred*(float)Gxred + (float)Gyred*(float)Gyred));
            edge_green = round(sqrt((float)Gxgreen*(float)Gxgreen + (float)Gygreen*(float)Gygreen));
            edge_blue = round(sqrt((float)Gxblue*(float)Gxblue + (float)Gyblue*(float)Gyblue));

            if (edge_red > 255)
            {
                edge_red = 255;
            }

            if (edge_green > 255)
            {
                edge_green = 255;
            }

            if (edge_blue > 255)
            {
                edge_blue = 255;
            }

            edged[y][x].rgbtRed = edge_red;
            edged[y][x].rgbtGreen = edge_green;
            edged[y][x].rgbtBlue = edge_blue;
        }
    }

    // And finally set the original to be the new edge detection image's values

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtBlue = edged[a][b].rgbtBlue;
            image[a][b].rgbtGreen = edged[a][b].rgbtGreen;
            image[a][b].rgbtRed = edged[a][b].rgbtRed;
        }
    }

    return;
}
