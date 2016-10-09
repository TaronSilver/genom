//
//  getPosition_test.cpp
//  
//
//  Created by Erica Geneletti and Katia Schalk on 05/10/16.
//
//

#include "Matrix.hpp"
#include <iostream>


void test_getPosition()
{
    
    char A('A');
    char B('B');
    char C('C');
    char G('G');
    char T('T');
    
    double res1, res2, res3, res4, res5, res6, res7;
   
    //if line value is invalid and negative
    res1 = (Matrix::getProbability(A, -3));
    std::cout << "Test 1: " << res1 << std::endl;
    
    //if line value is invalid and greater than 7
    res7 = (Matrix::getProbability(A, 9));
    std::cout << "Test 7: " << res7 << std::endl;

    //if nucleotid character is invalid
	res2 = (Matrix::getProbability(B, 3));
    std::cout << "Test 2: " << res2 << std::endl;
    
    //no problems column 1
    res3 = Matrix::getProbability(A, 3);
    std::cout << "Test 3: " << res3 << std::endl;
    
    //no problems column 2
    res4 = Matrix::getProbability(C, 3);
    std::cout << "Test 4: " << res4 << std::endl;
    
    //no problems column 3
    res5 = Matrix::getProbability(G, 3);
    std::cout << "Test 5: " << res5 << std::endl;
    
    //no problems column 4
    res6 = Matrix::getProbability(T, 3);
    std::cout << "Test 6: " << res6 << std::endl;
}
