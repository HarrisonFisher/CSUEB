#include <iostream>
#include "Box.h"

using namespace std;



int main() {

    //*
    Box myBox;

    myBox.setWidth(2.0);
    cout << "Width: " << myBox.getWidth() << endl;

    myBox.setHeight(3.0);
    cout << "Height: " << myBox.getHeight() << endl;

    myBox.setLength(6.0);
    cout << "Length: " << myBox.getLength() << endl;
    cout << "Surface Area: " << myBox.getSurfaceArea() << endl;
    cout << "      Volume: " << myBox.getVolume() << endl;

    cout << endl;

    myBox.resize(0.5);
    cout << "Width: " << myBox.getWidth() << endl;
    cout << "Height: " << myBox.getHeight() << endl;
    cout << "Length: " << myBox.getLength() << endl;
    cout << "Surface Area: " << myBox.getSurfaceArea() << endl;
    cout << "      Volume: " << myBox.getVolume() << endl;
    //*/

    return 0;
}
