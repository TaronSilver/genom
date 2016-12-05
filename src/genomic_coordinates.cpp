//
//  genomic_coordinates.cpp
//  
//
//  Created by Mättu on 29.11.16.
//
//

#include "genomic_coordinates.hpp"




Coordinates::Coordinates( std::string file_description, std::string location, bool line_description_present)
:file_description(file_description),
location(location),
line_description_present(line_description_present)
{
    
    
}



//-------------------------------------------------------------------------


void Coordinates::fillNewLine(std::string line) {
    std::stringstream line_stream(line);
    unsigned int start_pos_line;
    unsigned int end_pos_line;
    std::string line_description;
    double line_score;
    
    if(not(line_stream >> start_pos_line >> end_pos_line)) {
        return;
    };
    
    if(line_description_present) {
        if(not(getline(line_stream, line_description, ' '))) {
            return;
        }
    }
    
    if(not(line_stream >> line_score)) {
        return;
    }

    start_pos.push_back(start_pos_line);
    length.push_back(end_pos_line - start_pos_line);
    
    if(line_description_present)
        description.push_back(line_description);
    
    score.push_back(line_score);
}

//-------------------------------------------------------------------------

SearchResults Coordinates::get_search_results(std::string seq_filename,
                                              unsigned int sequence,
                                              unsigned int startpos)
{
    std::ifstream file;
    file.open(seq_filename);

    SearchResults output;
    SearchResult intermediate;
    
    unsigned int coord_id(0);
    unsigned int streamsize(file.tellg());
    unsigned int position(startpos);
    
    std::string output_description("Sequence: ");
    
    // Moves to start of desired sequence
    for (unsigned int i(0); i<sequence; ) {
        while (file.ignore(streamsize, '>')) {
            i++;
            getline(file, output.description);
        }
    }
    // Skips comments
    while (file.peek() == ';') {
        file.ignore(streamsize, '\n');
    }
    
    // Saves description
    output.description += ", extracted from genomic coordinate file: ";
    output.description += file_description;
    output.description += ", on the chromosome / plasmid: ";
    output.description += location;
    
    
    // Checks if sequence exists
    if(file.peek() == EOF) {
        error_sequence_doesnt_exist();
        return output;
    }
    
    // Moves coord_id to coordinate after startpos (Overlaps are ignored!)
    while(start_pos[coord_id] < startpos)
        coord_id++;
    
    while(coord_id < start_pos.size()) {
        // Moves position to start position of the corresponding coord_id
        while (position <= start_pos[coord_id]) {
            position++;
            file.ignore();
        }
        // Fills the sequence
        for (unsigned int i(0); i<length[coord_id]; i++) {
            intermediate.sequence.push_back(file.get());
        }
        // Fills search results
        intermediate.position = start_pos[coord_id];
        intermediate.score = score[coord_id];
        intermediate.direction = '+';
        
        output.searchResults.push_back(intermediate);
        intermediate = SearchResult();
        
        // Checks if it is at end of file, quits loop if so
        if (file.peek() == EOF) {
            break;
        }
    }
    
    return output;
    
}


//-------------------------------------------------------------------------

std::string Coordinates::get_location() {
    return location;
}


//-------------------------------------------------------------------------
void Coordinates::print() {
    std::cout << "File: " << file_description << std::endl;
    std::cout << "Location: " << location << std::endl;
    if(line_description_present) {
        for (unsigned int i(0); i<start_pos.size(); i++) {
            std::cout << start_pos[i] << "\t" << length[i] << "\t"
            << description[i] << "\t" << score[i] << std::endl;
        }
    }
    else {
        for (unsigned int i(0); i<start_pos.size(); i++) {
            std::cout << "Startpos: " << start_pos[i] << "\t" << "Length: " << length[i] << "\t"
            << "Score: " << score[i] << std::endl;
        }
    }
}







