//
//  matrix_line_operations.cpp
//  
//
//  Created by Mättu on 29.11.16.
//
//

#include <vector>

#include "matrix_line_operations.hpp"

//-----------------------------------------------------------------------

double max_of_line(std::vector<double> line) {
    std::vector<double>::iterator maximum_of_line;
    maximum_of_line = std::max_element(line.begin(), line.end());
    return *maximum_of_line;
}


//-----------------------------------------------------------------------

double min_of_line(std::vector<double> line) {
    std::vector<double>::iterator minimum_of_line;
    minimum_of_line = std::min_element(line.begin(), line.end());
    return *minimum_of_line;
}


//-----------------------------------------------------------------------

double sum_of_line(std::vector<double> line) {
    double sum(0.0);
    unsigned int size(line.size());
    
    for (unsigned int index(0); index < size; index++) {
        sum += line[index];
    }
    return sum;
}
