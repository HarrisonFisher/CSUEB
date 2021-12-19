#include "ImageMaker.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
ImageMaker::ImageMaker(){

    //Set Height and Width to 0
    SetWidth(0);
    SetHeight(0);

    //Set pen to Black
    SetPenRed(0);
    SetPenGreen(0);
    SetPenBlue(0);

    //Set image to white
    for (int x = 0; x < MAX_WIDTH; x++){
        for (int y = 0; y < MAX_HEIGHT; y++){
            image[x][y][RED] = MAX_COLOR;
            image[x][y][GREEN] = MAX_COLOR;
            image[x][y][BLUE] = MAX_COLOR;
        }
    }
}

ImageMaker::ImageMaker(string filename){

    //Set the image to white
    for (int x = 0; x < MAX_WIDTH; x++){
        for (int y = 0; y < MAX_HEIGHT; y++){
            image[x][y][RED] = MAX_COLOR;
            image[x][y][GREEN] = MAX_COLOR;
            image[x][y][BLUE] = MAX_COLOR;
        }
    }

    //Load image
    LoadImage(filename);

    //Set pen to black
    SetPenRed(0);
    SetPenGreen(0);
    SetPenBlue(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImageMaker::LoadImage(string filename){

    string line;
    fstream file;
    string word, t, q;

    file.open(filename.c_str());

    if (file.good()){ //if file can open

        {//Gather Headers
            file >> word;
            if (word != "P3"){ throw "Bad magic number"; }
            magic = word;

            file >> word;
            if (stoi(word)>=MAX_WIDTH || stoi(word)<=0 ){ throw "Width out of bounds"; }
            width = stoi(word);

            file >> word;
            if (stoi(word)>=MAX_HEIGHT || stoi(word)<=0 ){ throw "Height out of bounds"; }
            height = stoi(word);

            file >> word;
            if (stoi(word)!=MAX_COLOR){ throw "Max color range not 255"; }
        }

        //Gather Pixels
        for (int y = 0; y < GetHeight(); y++){
            for (int x = 0; x < GetWidth(); x++){

                file >> word;
                if (stoi(word) < 0 or stoi(word) > MAX_COLOR){ throw "Color value invalid"; }
                image[x][y][RED] = stoi(word);

                file >> word;
                if (stoi(word) < 0 or stoi(word) > MAX_COLOR){ throw "Color value invalid"; }
                image[x][y][GREEN] = stoi(word);

                file >> word;
                if (stoi(word) < 0 or stoi(word) > MAX_COLOR){ throw "Color value invalid"; }
                image[x][y][BLUE] = stoi(word);
            }
        }
    }else{//File did not open
        throw "File failed to open";
    }
}

void ImageMaker::SaveImage(string filename){
    if (GetHeight() == 0 or GetWidth() == 0) throw "Image must have non-zero dimensions";

    //Save Headers to file
    ofstream myfile;
    myfile.open (filename);
    myfile << "P3\n";
    myfile << GetWidth() << " " << GetHeight()<< "\n";
    myfile << MAX_COLOR << "\n";

    //Save pixels to file
    for (int y = 0; y < GetHeight(); y++){
        for (int x = 0; x < GetWidth(); x++){
            myfile << image[x][y][RED] << ' ' << image[x][y][GREEN]  << ' ' << image[x][y][BLUE] << ' ';
        }
        myfile << '\n';
    }
    myfile.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int ImageMaker::GetWidth(){ return this->width; } //Get width of image

int ImageMaker::GetHeight(){ return this->height; } //Get height of image

void ImageMaker::SetWidth(int width){
    if (width < 0 || width > MAX_WIDTH){ throw "Width out of bounds"; } //Set the image width
    this->width = width;
}
void ImageMaker::SetHeight(int height){
    if (height < 0 || height > MAX_HEIGHT){ throw "Height out of bounds"; } //Set the image height
    this->height = height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int ImageMaker::GetPenRed(){ return this->pen_red; } //Get red value of pen color

int ImageMaker::GetPenGreen(){ return this->pen_green; } //Get green value of pen color

int ImageMaker::GetPenBlue(){ return this->pen_blue; }  //Get the blue value of pen color

void ImageMaker::SetPenRed(int newR){   //Set the red value of pen color
    if (newR < 0 || newR > MAX_COLOR){ throw "Color value invalid"; }
    this->pen_red = newR;
}
void ImageMaker::SetPenGreen(int newG){ //Set the green value of pen color
    if (newG < 0 || newG > MAX_COLOR){ throw "Color value invalid"; }
    this->pen_green = newG;
}
void ImageMaker::SetPenBlue(int newB){  //Set the blue value of pen color
    if (newB < 0 || newB > MAX_COLOR){ throw "Color value invalid"; }
    this->pen_blue = newB;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImageMaker::DrawPixel(int x, int y){
    if (!PointInBounds(x,y)){ throw "Point out of bounds"; }
    if (GetWidth() == 0){ throw "Point out of bounds"; }
    if (GetHeight() == 0){ throw "Point out of bounds"; }

    //Drawing the pixel
    image[x][y][RED] = GetPenRed();
    image[x][y][GREEN] = GetPenGreen();
    image[x][y][BLUE] = GetPenBlue();
}
void ImageMaker::DrawRectangle(int x1, int y1, int x2, int y2){
    if (!PointInBounds(x1,y1)){ throw "Point out of bounds"; }
    if (!PointInBounds(x2,y2)){ throw "Point out of bounds"; }

    //Draw all 4 lines of Rectangle
    DrawLine(x1,y1,x1,y2);
    DrawLine(x2,y1,x2,y2);
    DrawLine(x1,y1,x2,y1);
    DrawLine(x1,y2,x2,y2);
}
void ImageMaker::DrawLine(int x1, int y1, int x2, int y2) {
    if (!PointInBounds(x1,y1)){ throw "Point out of bounds"; }
    if (!PointInBounds(x2,y2)){ throw "Point out of bounds"; }

    if (x1 == x2){//The x Values match
        if (y1 == y2){//y values match so draw a dot
            DrawPixel(x1,y1);
        }else{//slope undefined (Vertical  line)
            if (y1>y2){
                //Swap points
                //no need to swap x values since they are the same
                swap(y1,y2);
            }
            //Draw Vertical line
            for (int y = y1; y < y2+1; y++){
                DrawPixel(x1,y);
            }
        }
    }else{ //The x values are different
        if (x1 > x2){
            //swap points
            swap(x1,x2);
            swap(y1,y2);
        }
        //Uses float (for x values) to prevent dashed line for some cases
        //This is b/c some y values have same (digital) x value
        for (float x = x1; x < x2; x+=0.01){
            float m = ((float)y2-(float)y1)/((float)x2-(float)x1);
            float y = (m*(x-x1))+y1; // y = m(x-x1)+y1
            //Draw point in line
            DrawPixel(round(x),round(y));
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ImageMaker::PointInBounds(int x, int y){ //true or false if the points given is in bounds of the max image
    bool myReturn = true;
    if (x < 0 || x >= MAX_HEIGHT){ myReturn = false; }
    if (y < 0 || y >= MAX_WIDTH){ myReturn = false; }
    return myReturn;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
