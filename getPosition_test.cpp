//
//  getPosition_test.cpp
//  
//
//  Created by Erica Geneletti and Katia Schalk on 05/10/16.
//
//

#include "Matrix.hpp"

void test_getPosition()
{
    
    //if line value is invalid and negative
    double res1 = getPosition(A, -3);
    std::cout << "Test 1: " << res1 << std::endl;
    
    //if line value is invalid and greater than 7
    double res7 = getPosition(A, 9);
    std::cout << "Test 7: " << res7 << std::endl;

    //if nucleotid character is invalid
    double res2 = getPosition(B, 3);
    std::cout << "Test 2: " << res2 << std::endl;
    
    //no problems column 1
    double res3 = getPosition(A, 3);
    std::cout << "Test 3: " << res3 << std::endl;
    
    //no problems column 2
    double res4 = getPosition(C, 3);
    std::cout << "Test 4: " << res4 << std::endl;
    
    //no problems column 3
    double res5 = getPosition(G, 3);
    std::cout << "Test 5: " << res5 << std::endl;
    
    //no problems column 4
    double res6 = getPosition(T, 3);
    std::cout << "Test 6: " << res6 << std::endl;
}
