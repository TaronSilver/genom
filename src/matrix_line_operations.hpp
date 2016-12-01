//
//  matrix_line_operations.hpp
//  
//
//  Created by Mättu on 29.11.16.
//
//

#ifndef matrix_line_operations_hpp
#define matrix_line_operations_hpp

#include <stdio.h>
#include <algorithm>

/*!
 * @brief   Gives the maximum value of a line
 *
 * @param   A line of a matrix, made as a vector of doubles
 *
 * @return  Minimum value found in the line
 */
double max_of_line(std::vector<double> line);


/*!
 * @brief   Gives the minimum value of a line
 *
 * @param   A line of a matrix, made as a vector of doubles
 *
 * @return  Minimum value found in the line
 */
double min_of_line(std::vector<double> line);


/*!
 * @brief   Adds up values in a line
 *
 * @param   A line of a matrix, made as a vector of doubles
 *
 * @return  Sum of the values in the line
 */
double sum_of_line(std::vector<double> line);

#endif /* matrix_line_operations_hpp */
