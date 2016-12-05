//
//  genomic_coordinates.cpp
//  
//
//  Created by Mättu on 29.11.16.
//
//

#include "genomic_coordinates.hpp"



//-------------------------------------------------------------------------

Coordinates::Coordinates(std::string filename) {
    
    std::ifstream file;
    file.open(filename);
    
    unsigned int startpos;
    unsigned int endpos;
    std::string line_location;
    std::string line_description;
    double line_score;
    
    unsigned int line(0);
    
    getline(file, file_description);
    line++;
    
    //First line:
    getline(file, line_location, ' ');
    if(not(file >> startpos >> endpos))
        error_reading_coordinates(line);
    
    
    if(file >> line_score)
        line_description_present = true;
    else {
        line_description_present = false;
        getline(file, line_description, ' ');
        file >> line_score;
    }
    
    fillNewLine(startpos, endpos, line_location, line_description, line_score);
    line++;
    
    if(line_description_present) {
        while (getline(file, line_location, ' ')) {
            if(not(file >> startpos >> endpos))
                error_reading_coordinates(line);
            if(not(getline(file, line_description, ' ')))
                error_reading_coordinates(line);
            if(not(file >> line_score))
                error_reading_coordinates(line);
            fillNewLine(startpos, endpos, line_location, line_description, line_score);
            line++;
        }
    }
    
    if(line_description_present) {
        while (getline(file, line_location, ' ')) {
            if(not(file >> startpos >> endpos >> line_score))
                error_reading_coordinates(line);
            fillNewLine(startpos, endpos, line_location, line_description, line_score);
            line++;
        }
    }
    
    file.close();
}




//-------------------------------------------------------------------------

void Coordinates::fillNewLine(unsigned int startpos,
                              unsigned int endpos,
                              std::string line_location,
                              std::string line_description,
                              double line_score) {
    
    location.push_back(line_location);
    start_pos.push_back(startpos);
    length.push_back(endpos - startpos);
    
    if(line_description_present)
        description.push_back(line_description);
    
    score.push_back(line_score);
}
