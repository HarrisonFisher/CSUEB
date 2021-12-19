#include "Box.h"

void Box::setWidth(double width){
    if (width < 0)
        throw "Negative Dimension";
    this->width = width;
}

void Box::setHeight(double height){
    if (height < 0)
        throw "Negative Dimension";
    this->height = height;
}

void Box::setLength(double length){
    if (length < 0)
        throw "Negative Dimension";
    this->length = length;
}

void Box::resize(double factor){
    width *= factor;
    height *= factor;
    height *= factor;
}