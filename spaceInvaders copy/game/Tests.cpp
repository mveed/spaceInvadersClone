//
//  Tests.cpp
//  game
//
//  Created by Matthew Veeder on 9/23/21.
//

#include "Tests.hpp"


void addDeleteObjectsTest(int vectorSize, int expectedValue, std::string errorMsg){
    if (vectorSize != expectedValue){
        std::cerr << errorMsg << " should equal " << expectedValue << ", instead returned " << vectorSize << "\n";
        exit(1);
    }
}

