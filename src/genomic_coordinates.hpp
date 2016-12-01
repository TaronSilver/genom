//
//  genomic_coordinates.hpp
//  
//
//  Created by Mättu on 29.11.16.
//
//

#ifndef genomic_coordinates_hpp
#define genomic_coordinates_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>

class Coordinates {

private:
    
    std::vector <std::string> location;
    std::vector <unsigned int> start_pos;
    std::vector <unsigned int> length;
    std::vector <std::string> description;
    std::vector <double> score;
    
    bool line_description_present;
    
    std::string file_description;


    /*!
     * @brief   Fills a new line of genomic coordinates
     *
     * @param   Parameters to fill them with
     */
    void fillNewLine(unsigned int startpos,
                     unsigned int endpos,
                     std::string line_location,
                     std::string line_description,
                     double line_score);
    
public:
    
    /*!
     * @brief Constructor for genetic Coordinates
     *
     * @param Name of input file
     */
    Coordinates(std::string filename);
    
    
};


#endif /* genomic_coordinates_hpp */
