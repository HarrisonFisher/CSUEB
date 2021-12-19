/**
 * Created by Varick Erickson on 5/31/2021.
 *
 * You should not remove or change any of the tests in this file.
 * These are the same tests that will be used to grade your assignment.
 *
 * The purpose of this file is to test the getters and setters.
 */
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <istream>
#include "catch.hpp"
#include "../Box.h"

TEST_CASE("Testing Getters/Setters - 2 point") {
    for (int w = 0; w < 10; w++) {
        for (int h = 0; h < 10; h++) {
            for (int l = 0; l < 10; l++) {
                Box myBox;
                myBox.setWidth(w);
                myBox.setHeight(h);
                myBox.setLength(l);

                REQUIRE(myBox.getWidth() == w);
                REQUIRE(myBox.getHeight() == h);
                REQUIRE(myBox.getLength() == l);
            }
        }
    }
}

TEST_CASE("Testing Setters, Bad Values - 1 point") {
    for (int w = -10; w < 0; w++) {
        for (int h = -10; h < 0; h++) {
            for (int l = -10; l < 0; l++) {
                Box myBox;
                REQUIRE_THROWS_WITH(myBox.setWidth(w), "Negative Dimension");
                REQUIRE_THROWS_WITH(myBox.setHeight(h), "Negative Dimension");
                REQUIRE_THROWS_WITH(myBox.setLength(l), "Negative Dimension");
            }
        }
    }
}

TEST_CASE("Testing Resize - 1 point") {
    for (double factor = 0.5; factor < 2.0; factor += 0.25) {
        for (int w = 0; w < 10; w++) {
            for (int h = 0; h < 10; h++) {
                for (int l = 0; l < 10; l++) {
                    Box myBox;
                    myBox.setWidth(w);
                    myBox.setHeight(h);
                    myBox.setLength(l);

                    myBox.resize(factor);

                    REQUIRE(myBox.getWidth() == w * factor);
                    REQUIRE(myBox.getHeight() == h * factor);
                    REQUIRE(myBox.getLength() == l * factor);
                }
            }
        }
    }
}