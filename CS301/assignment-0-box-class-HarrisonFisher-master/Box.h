//
// Created by we7289 on 5/31/2021.
//

#ifndef BOX_H
#define BOX_H


class Box {
public:
    Box():width(),height(0),length(0){};

    Box(int width, int height, int length):
        width(width < 0 ? throw "Negative Dimension": width),
        height(height < 0 ? throw "Negative Dimension": height),
        length(length < 0 ? throw "Negative Dimension": length){
    };

    double getWidth() const {return width;}
    void setWidth(double width);    //Box.cpp

    double getHeight() const {return height;}
    void setHeight(double height);  //Box.cpp

    double getLength() const {return length;}
    void setLength(double length);  //Box.cpp

    double getSurfaceArea() const {return 2*(length*(width+height)+(width*height));}
    double getVolume() const {return length*width*height;}

    void resize(double factor);     //Box.cpp

private:
    double width;
    double height;
    double length;
};
#endif // BOX_H