//
//  genomic_coordinates.cpp
//  
//
//  Created by Mättu on 29.11.16.
//
//

#include "genomic_coordinates.hpp"
#define MAXLINESIZE 1000



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
// DOESNT WORK

SearchResults Coordinates::get_search_results(std::string seq_filename,
                                              unsigned int sequence,
                                              unsigned int startpos)
{
    std::ifstream file;
    file.open(seq_filename);

    SearchResults output;
    SearchResult intermediate;
    
    unsigned int coord_id(0);
    unsigned int position(startpos);
    
    std::string output_description("Sequence: ");
    
    // Moves to start of desired sequence
    for (unsigned int i(0); i<sequence; ) {
        while (file.ignore(MAXLINESIZE, '>')) {
            i++;
            getline(file, output.description);
        }
    }
    // Skips comments
    while (file.peek() == ';') {
        file.ignore(MAXLINESIZE, '\n');
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


//-------------------------------------------------------------------------
std::vector <double> Coordinates::position_score(SearchResults input, unsigned int seq_startpos)
{
    std::vector <double> output;
    
    unsigned int gen_id(0);
    unsigned int seq_id(0);
    
    unsigned int seq_pos;
    unsigned int seq_length;
    unsigned int gen_pos;
    unsigned int gen_length;
    
    double score_intermed(0);
    
    while (seq_id < input.searchResults.size())
    {
        
        seq_pos = input.searchResults[seq_id].position;
        seq_length = input.searchResults[seq_id].sequence.size();
        gen_pos = start_pos[gen_id];
        gen_length = length[gen_id];

        // DEBUG
        std::cout << "seq_id " << seq_id << std::endl;
        std::cout << "seq_pos " << seq_pos << std::endl;
        std::cout << "seq_length " << seq_length << std::endl;
        std::cout << "gen_id " << gen_id << std::endl;
        std::cout << "gen_pos " << gen_pos << std::endl;
        std::cout << "gen_length " << gen_length << std::endl;
        std::cout << "\n --- \n" << std::endl;
        
        // No overlap
        if (gen_pos + gen_length < seq_pos)
        {
            gen_id++;
        }
        else if (gen_pos > seq_pos + seq_length)
        {
            output.push_back(score_intermed);
            score_intermed = 0;
            seq_id++;
        }
        
        // Overlaps
        else if (gen_pos < seq_pos and gen_pos + gen_length >= seq_pos + seq_length)
        {
            score_intermed = score[gen_id];
            output.push_back(score_intermed);
            score_intermed = 0;
            seq_id++;
        }
        
        // RETHINK!
        else if (gen_pos < seq_pos and gen_pos + gen_length <= seq_pos + seq_length)
        {
            gen_id++;
            score_intermed += score[gen_id] * (gen_pos + gen_length - seq_pos) / seq_length;
        }
        else if (gen_pos > seq_pos and gen_pos + gen_length <= seq_pos + seq_length)
        {
            gen_id++;
            score_intermed += score[gen_id] * gen_length / seq_length;
        }
        else if (gen_pos > seq_pos and gen_pos + gen_length >= seq_pos + seq_length)
        {
            score_intermed += score[gen_id] * (seq_pos + seq_length - gen_pos) / seq_length;
            output.push_back(score_intermed);
            score_intermed = 0;
            seq_id++;
        }
    }
    
    return output;
}








