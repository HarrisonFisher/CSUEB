//
// Assignment Created by Varick Erickson
//

#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <cmath>
#include <fstream>

const int MAX_WIDTH = 800;//800;
const int MAX_HEIGHT = 800; //800;
const int MAX_COLOR = 255;
enum COLOR { RED, GREEN, BLUE };

using namespace std;

//  Please put your pre and post comments in this file. See page 139 in the textbook.

class ImageMaker
{
public:
    /*
     * Function: Default constructor for class
     *
     * Precondition: None
     *
     * Post-condition:
     * There are two constructors. The default constructor should create an image with 0 width and 0 height, and set the initial pen color to black (0, 0, 0).
     * The "image" variable should be initialized to be white (i.e. set every value in the variable "image" to 255).
     */
    ImageMaker();

    /*
     * Function: 2nd Constructor, and loads image
     *
     * Precondition:
     * Input filename is the file name you want to load
     *
     * Post-condition:
     * If the file fails to open, then it should throw "File failed to open"
     * If the magic number is not "P3", it should throw the string "Bad magic number"
     * If the width is out of bounds, you should throw the string "Width out of bounds"
     * If the height is out of bounds, you should throw the string "Height out of bounds"
     * If the maximum color value is not 255, you should throw the string "Max color range not 255"
     * If one of the pixels has a bad value, then you should throw the string "Color value invalid"
     */
    ImageMaker(string filename);

    // Opens image with filename and stores information into
    /*
     * Function: Loads the image
     *
     * Precondition: Input filename is the file name you want to load
     *
     * Post-condition:
     * load a ppm image into the image matrix and set the private variables accordingly.
     * If the file fails to open, then it should throw "File failed to open"
     * If the magic number is not "P3", it should throw the string "Bad magic number"
     * If the width is out of bounds, you should throw the string "Width out of bounds"
     * If the height is out of bounds, you should throw the string "Height out of bounds"
     * If the maximum color value is not 255, you should throw the string "Max color range not 255"
     * If one of the pixels has a bad value, then you should throw the string "Color value invalid"
     */
    void LoadImage(string filename);

    /*
     * Function: Saves the image
     *
     * Precondition:
     * Width and height were set
     * Input filename for file location/(file name) given
     *
     * Postcondition:s
     * GetHeight() and GetWidth() are not 0
     * Saves image to file location/(file name) given
     */
    void SaveImage(string filename);

    // Size functions
    /*
     * Function: Returns Width Value
     *
     * Precondition: If image not loaded the size will be 0
     *
     * Postcondition: none
     */
    int GetWidth();

    /*
     * Function: Returns Height Value
     *
     * Precondition: If image not loaded the size will be 0
     *
     * Postcondition: none
     */
    int GetHeight();

    /*
     * Function: Sets width of image
     *
     * Precondition:
     * If image not loaded the size will be 0 before function
     * The input value is the size you want to change it to
     *
     * Postcondition:
     * Sets the image value if not width < 0 || width > MAX_WIDTH
     * if true it will throw
     */
    void SetWidth(int width);

    /*
     * Function: Sets height of image
     *
     * Precondition:
     * If image not loaded the size will be 0 before function
     * The input value is the size you want to change it to
     *
     * Postcondition:
     * Sets the image value if not height < 0 || height > MAX_HEIGHT
     * if true it will throw
     */
    void SetHeight(int height);


    // Color functions
    /*
     * Function: Returns red value of pen
     *
     * Precondition: If you did not change its value, it will be 255 by default
     *
     * Postcondition: none
     */
    int GetPenRed();

    /*
     * Function: Returns green value of pen
     *
     * Precondition: If you did not change its value, it will be 255 by default
     *
     * Postcondition: none
     */
    int GetPenGreen();

    /*
     * Function: Returns blue value of pen
     *
     * Precondition: If you did not change its value, it will be 255 by default
     *
     * Postcondition: none
     */
    int GetPenBlue();

    /*
     * Function: Sets red value for pen
     *
     * Precondition: input red value
     *
     * Postcondition:
     * Will throw if the input value < 0 || if the input value > MAX_COLOR
     */
    void SetPenRed(int newR);

    /*
     * Function: Sets green value for pen
     *
     * Precondition: input the green value
     *
     * Postcondition:
     * Will throw if the input value < 0 || if the input value > MAX_COLOR
     */
    void SetPenGreen(int newG);

    /*
     * Function: Sets blue value for pen
     *
     * Precondition: input the blue value
     *
     * Postcondition:
     * Will throw if the input value < 0 || if the input value > MAX_COLOR
     */
    void SetPenBlue(int newB);

    // Drawing methods
    // These methods will use the current red, green, blue values of the pen
    /*
     * Function: Plots a point on image
     *
     * Precondition:
     * Input x and y value for point
     *
     * Postcondition:
     * If the point out of bounds it will throw
     * if point out of bounds it will throw
     * if height or width of image is 0 it will there
     */
    void DrawPixel(int x, int y);

    /*
     * Function: Draw 4 lines to create Rectangle on image
     *
     * Precondition:
     * inputs two points (x1,y1,x2,y2)
     *
     * Postcondition:
     * If either input points on image are out of bounds of the max image size it will throw
     */
    void DrawRectangle(int x1, int y1, int x2, int y2);

    /*
     * Function: Drawsa line on image
     *
     * Precondition: Input two points to draw line (x1,y1,x2,y2)
     *
     * Postcondition:
     * If either points out of bounds it will throw
     * If both x values and y values match it will draw a point
     * If both x values match but y values making an undefined slope it will fill all y values between y1 an y2
     * There is a slope b/c both x values dont match,will swap pounts if x1 is bigger than x2, then draws line.
     */
    void DrawLine(int x1, int y1, int x2, int y2);

private:
    string magic;
    int width;
    int height;
    int pen_red;    // Used by draw functions
    int pen_green;  // Used by draw functions
    int pen_blue;   // Used by draw functions
    bool PointInBounds(int x, int y);  // Not a bad idea to implement

               //   x          y
    short image[MAX_WIDTH][MAX_HEIGHT][3];
};

#endif //IMAGEMAKER_H
