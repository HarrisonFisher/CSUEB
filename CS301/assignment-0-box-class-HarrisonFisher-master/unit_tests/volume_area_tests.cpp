/**
 * Created by Varick Erickson on 5/31/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 *
 * The purpose of this file is to test the volume and area functions.
 */
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <istream>
#include "catch.hpp"
#include "../Box.h"

TEST_CASE("Testing Volume - 1 Point") {
    for (int w = 0; w < 100; w++) {
        for (int h = 0; h < 100; h++) {
            for (int l = 0; l < 100; l++) {
                Box myBox;
                myBox.setWidth(w);
                myBox.setHeight(h);
                myBox.setLength(l);

                REQUIRE(myBox.getVolume() == w*h*l);
            }
        }
    }
}

TEST_CASE("Testing Surface Area - 1 Point") {
    for (int w = 0; w < 100; w++) {
        for (int h = 0; h < 100; h++) {
            for (int l = 0; l < 100; l++) {
                Box myBox;
                myBox.setWidth(w);
                myBox.setHeight(h);
                myBox.setLength(l);

                REQUIRE(myBox.getSurfaceArea() == 2*(w*h + w*l + h*l));
            }
        }
    }
}