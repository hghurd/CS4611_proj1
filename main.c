/**
 * Author:          Garrett Hurd
 * MTU Username:    hghurd
 * Date:            2022-09-11
 * Filename:        main.c
 * Description:     This file will create two images: checkerboard.png and gradient.png.
 *                  This is Assignment 1 for CS4611.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMG_SIZE (512 * 512 * 3 - 1)
#define IMG_ROW (512 * 3 - 1)
#define IMG_DIM 512

int main() {
    //Creating arrays for each image.
    unsigned char *checkerboard = malloc(sizeof(unsigned char) * IMG_SIZE);
    unsigned char *gradient = malloc(sizeof(unsigned char) * IMG_SIZE);
    /*This variable will get used to compute where in the one-dimensional array pixel values should be altered.
     * I did this to essentially pretend that the image is actually a 2-dimensional array. As you will see,
     * I decided to use two nested for-loops to increment through all the pixels (I know, that's probably not the most
     * efficient way to do this) and then figure out where in the 1-D array I should be changing colours.
     */
    int pix = 0;


    /*
     * This section of code will generate checkerboard.png
     *
     * Since there are only two possible colours for any given pixel, I decided to use a boolean variable to represent
     * them. If colour == true, the pixel will be blue and if colour == false, the pixel will be red.
     */

    bool colour = false;
    for (int y = 0; y < IMG_DIM; y++) {
        //Invert which colour gets printed when one whole row has been printed
        if ((y % 64 == 0) && y != 0) {
            colour = !colour;
        }
        for (int x = 0; x < IMG_DIM; x++) {
            pix = (y * IMG_ROW) + (x * 3 + y);
            //Change the colour after moving 64 pixels right
            if (x % 64 == 0) {
                colour = !colour;
            }

            //Check what bool colour is set to. If colour is false, set the colour to red. Otherwise, set to blue
            if (colour) {
                checkerboard[pix] = 255;
                checkerboard[pix + 1] = 0;
                checkerboard[pix + 2] = 0;
            } else {
                checkerboard[pix] = 0;
                checkerboard[pix + 1] = 0;
                checkerboard[pix + 2] = 255;
            }

        }
    }

    //Write the PNG file checkerboard.png
    stbi_write_png("checkerboard.png", 512, 512, 3, checkerboard, 512 * 3);

    /*
    * This section of code will generate gradient.png
    */
    for (int y = 0; y < IMG_DIM; y++) {
        for (int x = 0; x < IMG_DIM; x++) {
            pix = (y * IMG_ROW) + (x * 3 + y);

            //Set red and green to increase as x increases and as y increases, respectively
            unsigned char red = (unsigned char) roundf(((float) x / (float) IMG_DIM) * 255);
            unsigned char green = (unsigned char) roundf(((float) y / (float) IMG_DIM) * 255);
            //Blue remains constant throughout the entire photo, so we can just set that manually
            unsigned char blue = 128;

            //Set the RGB value of the current pixel
            gradient[pix] = red;
            gradient[pix + 1] = green;
            gradient[pix + 2] = blue;

        }
    }
    //Write the PNG file gradient.png
    stbi_write_png("gradient.png", 512, 512, 3, gradient, 512 * 3);


    //Free the arrays for each of the images
    free(checkerboard);
    free(gradient);
    return 0;
}