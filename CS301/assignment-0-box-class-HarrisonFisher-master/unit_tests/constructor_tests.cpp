/**
 * Created by Varick Erickson on 5/31/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 *
 * The purpose of this file is to test the constructors.
 */
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <istream>
#include "catch.hpp"
#include "../Box.h"

TEST_CASE("Default constructor - 1 point") {

    Box myBox;
    REQUIRE(myBox.getWidth() == 0);
    REQUIRE(myBox.getHeight() == 0);
    REQUIRE(myBox.getLength() == 0);
}


TEST_CASE("Good Values, Box(length, width, height) - 1 point") {
    // Test to make sure the default constructor works properly
    // for good values
    for (double w = 0; w < 100; w++) {
        for (double h = 0; h < 100; h++) {
            for (double l = 0; l < 100; l++) {
                Box myBox(w, h, l);
                REQUIRE(myBox.getWidth() == w);
                REQUIRE(myBox.getHeight() == h);
                REQUIRE(myBox.getLength() == l);
            }
        }
    }
}

TEST_CASE("Bad Values, Box(length, width, height) - 1 point") {
    // Test to make sure the default constructor works properly
    // for bad values
    for (double w = -100; w < 0; w++) {
        for (double h = -100; h < 0; h++) {
            for (double l = -100; l < 0; l++) {
                REQUIRE_THROWS_WITH(Box(w, h, l), "Negative Dimension");
            }
        }
    }
}
