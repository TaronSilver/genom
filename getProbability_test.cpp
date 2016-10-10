//
//  getProbability_test.cpp
//  
//
//  Created by Erica Geneletti and Katia Schalk on 05/10/16.
//
//

#include "Matrix.hpp"

void test_getProbability()
{
    
    char A('A');
    char B('B');
    char C('C');
    char G('G');
    char T('T');
    
    double res1, res2, res3, res4, res5, res6, res7;
   
    //If line value is invalid : Negative
    res1 = Matrix::getProbability(A, -3);
    cout << "Test 1: " << res1 << endl;
    
    //If line value is invalid : Greater than 7
    res7 = Matrix::getProbability(A, 9);
    cout << "Test 7: " << res7 << endl;

    //If nucleotid character is invalid : Different than A, C, G, T
    res2 = Matrix::getProbability(B, 3);
    cout << "Test 2: " << res2 << endl;
    
    //No problems column 1
    res3 = Matrix::getProbability(A, 3);
    cout << "Test 3: " << res3 << endl;
    
    //No problems column 2
    res4 = Matrix::getProbability(C, 3);
    cout << "Test 4: " << res4 << endl;
    
    //No problems column 3
    res5 = Matrix::getProbability(G, 3);
    cout << "Test 5: " << res5 << endl;
    
    //No problems column 4
    res6 = Matrix::getProbability(T, 3);
    cout << "Test 6: " << res6 << endl;
}
