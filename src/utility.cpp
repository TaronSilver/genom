#include "utility.hpp"

#define LINE_SIZE 5000

std::map< char, nuc > charmap{
    {'A', A}, {'a', A},
    {'C', C}, {'c', C},
    {'G', G}, {'g', G},
    {'T', T}, {'t', T},
    {'N', N}, {'n', N},
    {'-', N}, {'.', N}
};

std::map< char, nuc > complementmap{
    {'A', T}, {'a', T},
    {'C', G}, {'c', G},
    {'G', C}, {'g', C},
    {'T', A}, {'t', A},
    {'N', N}, {'n', N},
    {'-', N}, {'.', N}
};

std::map< nuc, char > backwardsmap {
    {A, 'A'},
    {C, 'C'},
    {G, 'G'},
    {T, 'T'},
    {N, 'N'}
};










///Sequence
//-------------------------------------------------------------------------



std::vector <Sequence> Initialization()
{
    std::string entry_name = ask_name_fasta();

    std::vector <Sequence> sequence_list;

    std::vector <std::string> sequences(ExtractSequence(entry_name));
    for(size_t i(0); i<sequences.size(); ++i){
        Sequence seq(sequences[i]);
        sequence_list.push_back(seq);
    }

    return sequence_list;
}

std::vector <std::string> ExtractSequence(std::string const& entry_name)
{
    std::ifstream entry(entry_name.c_str());
    std::string line;

    std::vector <std::string> sequences; // That is the object that will be returned.

    std::string intermediate_value;

    // Reads lines
    while(getline(entry, line)){
        if(line.front()=='>'){
            sequences.push_back(intermediate_value);
            intermediate_value.clear(); }
        //else if(line.front()=='\n'){}
        else {

            // Makes DNA Sequence on line all uppercase, allowing for easier search afterwards
            for (auto & c: line) c = toupper(c);
            intermediate_value+=line;
        }
    }



    // Allow to register the last value even though there's no >...
    sequences.push_back(intermediate_value);

    // Deletes the first vector created, which is a ghost one. This is just a hack cobbled together, it'd probably be best to correct that in a better way at some point.
    sequences.erase(sequences.begin());


    // Testing the values by showing them
    /*for(size_t i(0); i<sequences.size(); ++i){
     std::cout <<sequences[i] <<'\n';
     }*/

    entry.close(); // Don't you have to close it afterwards?
    return sequences;
}



std::vector <double> nucleotide_probability(std::vector <std::string> nucleotide_sequences, unsigned int position) {

    std::vector <unsigned int> nucleotide_counter(4, 0);
    std::vector <double> probabilities(4, 0);
    // std::array <unsigned int, 4> nucleotide_counter = {0,0,0,0};
    // std::array <double, 4> probabilities;

    unsigned int number_sequences(nucleotide_sequences.size());


    assert(number_sequences>0);

    for (unsigned int i(0); i<number_sequences; i++) {
        switch (nucleotide_sequences[i][position]) {
            case 'A':
                nucleotide_counter[0]++;
                break;
            case 'C':
                nucleotide_counter[1]++;
                break;
            case 'G':
                nucleotide_counter[2]++;
                break;
            case 'T':
                nucleotide_counter[3]++;
                break;
            default:

                nucleotide_warning(nucleotide_sequences[i][position]);
                return {0,0,0,0};
                // Better error handling needed!!
        }
    }

    for (unsigned int i(0); i < 4; i++) {
        probabilities[i] = (double)nucleotide_counter[i] / (double)number_sequences;
    }
    return probabilities;
}


Matrix_Neo generate_PWM_from_Seq_list(std::vector <Sequence> sequence_list, bool entire_sequence) {
    Matrix_Neo probability_matrix;
    std::vector <std::string> binding_sequences;

    unsigned int position;
    unsigned int length;
    unsigned int number_sequences(sequence_list.size());

    if(!entire_sequence) {
        // todo if only a part of the sequence is relevant
            position = ask_position();
            length = ask_length();
    }

    else {
        position = 1;
        length = sequence_list[0].length();
    }

    for (unsigned int i(0); i < number_sequences; i++) {
        binding_sequences.push_back(sequence_list[i].access_sequence_pos(position-1, length));
    }
    // Goes through all sequences, extracts binding sites and
    // stores them in vector binding_sequences


    for(unsigned int i(0); i < length; i++) {
        probability_matrix.push_back(nucleotide_probability(binding_sequences, i));
    }
    // Goes through every position and calculates probabilities at that position


    /* FOR TESTING
    for(int i(0); i < probability_matrix.size(); i++) {
        for(int j(0); j < 4; j++) {
            std::cout << probability_matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
     */

    return probability_matrix;
}


Matrix_Neo matrix_from_sequence_results(std::string filename) {

    std::ifstream entry(filename);
    std::string line;

    std::vector <Sequence> sequences; // That is the object that will be returned.
    std::string nucleotides;


    // Reads lines, converts line to stream, reads the first word and creates a sequence out of it
    while(getline(entry, line)){

        std::istringstream stringstream(line);
        stringstream >> nucleotides;

        Sequence sequence(nucleotides);
        sequences.push_back(sequence);
    }

    entry.close();
    return generate_PWM_from_Seq_list(sequences, true);
}






//==========================================================================================
// SEQUENCE ANALYSIS
//==========================================================================================
// I am very sorry for the uglyness of this function
//
// TODO: Doesn't work if at position 0; reverse strand doesnt work
// TODO: Progress bar

std::vector<SearchResults> analyze_sequence(std::string filename, Matrix matrix, double cutoff) {

    // File to read
    std::ifstream entry_file(filename);

    // Search results of all sequences
    std::vector <SearchResults> output;

    // Search results of one sequence
    SearchResults sequence_matches;

    std::list<nuc> forwardSequence;
    std::list<nuc> backwardSequence;

    bool fill(true);

    char character;

    unsigned int char_counter(0);
    unsigned int length(matrix.get_length());
    unsigned int position_counter(0);
    int size_of_file;
    size_of_file = filesize(filename);
    int size_base_element(size_of_file/100 * sizeof(char));

    bool first_line(true);

    double score;

    while(entry_file.get(character)) {

        print_progress(entry_file.tellg(), size_of_file);

        // Skip if endline is found
        if(character == '\n')
            continue;

        // What to do if current line is description
        if(character == '>' or character == ';') {
            if (!first_line) {
                output.push_back(sequence_matches);
                sequence_matches = SearchResults(); // Reset to 0
                position_counter = 0;
            }

            first_line = false;

            getline(entry_file, sequence_matches.description);
            sequence_matches.description += "\n";
            continue;
        }

        // What to do if the sequence hasn't been filled yet with sufficient characters
        if(fill) {
            forwardSequence.push_back(charmap[character]);
            backwardSequence.push_front(complementmap[character]);
            char_counter++;

            if(char_counter >= length)
                fill = false;
        }

        // Go to next cycle if it is still not full
        if(fill)
            continue;

        // Skips if character is not valid
        if(!valid_character(character))
            continue;

        position_counter++;

        // Updates sequence with the new character
        forwardSequence.pop_front();
        forwardSequence.push_back(charmap[character]);
        backwardSequence.pop_back();
        backwardSequence.push_front(complementmap[character]);

        // What to do if forward is binding
        score = matrix.sequence_score(forwardSequence);

        if(score >= cutoff) {

            SearchResult sequence_match(fill_search_result(forwardSequence, position_counter, score, '+'));
            sequence_matches.searchResults.push_back(sequence_match);
        }

        // What to do if backward is binding
        score = matrix.sequence_score(backwardSequence);

        if(score >= cutoff) {
            SearchResult sequence_match(fill_search_result(backwardSequence, position_counter, score, '-'));
            sequence_matches.searchResults.push_back(sequence_match);
        }
    }

    output.push_back(sequence_matches);

    entry_file.close();
    return output;
}



//==========================================================================================
// Optimized version of the function
//
// TODO: Progress bar

std::vector<SearchResults> analyze_sequence_opt(std::string filename, Matrix matrix, double cutoff) {



    // File to read
    std::ifstream entry_file(filename);

    // Search results of all sequences
    std::vector <SearchResults> output;

    // Search results of one sequence
    SearchResults sequence_matches;

    std::list<nuc> forwardSequence;
    std::list<nuc> backwardSequence;

    bool fill(true);
    bool description(true);


    unsigned int char_counter(0);
    unsigned int length(matrix.get_length());
    unsigned int position_counter(0);
    unsigned int line_size;

    unsigned int print_counter(0);


    int size_of_file;
    size_of_file = filesize(filename);

    bool first_line(true);
    unsigned int index(0);

    double score;

    char line[LINE_SIZE];




    // ----

    while(entry_file.get(line, LINE_SIZE, '\n')) {
        // Sets line_size to amount of characters read in get
        line_size = entry_file.gcount();
        index = 0;

        if (print_counter > 5000) {
            print_progress(entry_file.tellg(), size_of_file);
            print_counter = 0;

        }

        print_counter++;


        if (line[index] == '>' or line[index] == ';') {

            if (!first_line) {
                output.push_back(sequence_matches);
                sequence_matches = SearchResults(); // Reset to 0
            }

            if(!forwardSequence.empty())
                forwardSequence.clear();
            if(!backwardSequence.empty())
                backwardSequence.clear();

            position_counter = 0;
            char_counter = 0;
            first_line = false;
            fill = true;
            sequence_matches.description += line;

        }

        else {
            while (fill) {
                if (valid_character(line[index])) {
                    forwardSequence.push_back(charmap[line[index]]);
                    backwardSequence.push_front(complementmap[line[index]]);
                    char_counter++;

                }

                if(char_counter >= length) {
                    fill = false;
                }


                index++;


            }

            // For initialized sequence
            // What to do if forward is binding
            score = matrix.sequence_score(forwardSequence);

            if(score >= cutoff) {

                SearchResult sequence_match(fill_search_result(forwardSequence, position_counter, score, '+'));
                sequence_matches.searchResults.push_back(sequence_match);
            }

            // What to do if backward is binding
            score = matrix.sequence_score(backwardSequence);

            if(score >= cutoff) {
                SearchResult sequence_match(fill_search_result(backwardSequence, position_counter, score, '-'));
                sequence_matches.searchResults.push_back(sequence_match);
            }


            // For all following combinations
            while (index < line_size) {

                // Skips if character is not valid
                if(valid_character(line[index]))
                {
                    position_counter++;

                    // Updates sequence with the new character
                    forwardSequence.pop_front();
                    forwardSequence.push_back(charmap[line[index]]);
                    backwardSequence.pop_back();
                    backwardSequence.push_front(complementmap[line[index]]);

                    // What to do if forward is binding
                    score = matrix.sequence_score(forwardSequence);

                    if(score >= cutoff) {

                        SearchResult sequence_match(fill_search_result(forwardSequence, position_counter, score, '+'));
                        sequence_matches.searchResults.push_back(sequence_match);
                    }

                    // What to do if backward is binding
                    score = matrix.sequence_score(backwardSequence);

                    if(score >= cutoff) {
                        SearchResult sequence_match(fill_search_result(backwardSequence, position_counter, score, '-'));
                        sequence_matches.searchResults.push_back(sequence_match);
                    }
                }
                index++;
            }

        }

        if(entry_file.peek() == '\n')
            entry_file.get();

    }

    output.push_back(sequence_matches);

    entry_file.close();
    return output;
}




//==========================================================================================
// Even further optimized version of the function, INPROGRESS
//
// TODO: Progress bar

std::vector<SearchResults> analyze_sequence_opt2(std::string filename, Matrix matrix, double cutoff) {

    // File to read
    std::ifstream entry_file(filename);

    // Search results of all sequences
    std::vector <SearchResults> output;

    // Search results of one sequence
    SearchResults sequence_matches;

    std::list<nuc> forwardSequence;
    std::list<nuc> backwardSequence;

    bool fill(true);
    bool description(true);


    unsigned int char_counter(0);
    unsigned int length(matrix.get_length());
    unsigned int position_counter(0);
    unsigned int line_size;

    unsigned int print_counter(0);


    int size_of_file;
    size_of_file = filesize(filename);

    bool first_line(true);
    unsigned int index(0);

    double score;

    char line[LINE_SIZE];
    std::string seq_description;


    // Handles first line
    while (entry_file.peek() == '>' or entry_file.peek() == ';') {
        getline(entry_file, seq_description, '\n');
        sequence_matches.description += seq_description;
    }


    while(entry_file.get(line, LINE_SIZE, '>')) {
        // Sets line_size to amount of characters read in get
        line_size = entry_file.gcount();

        //std::cout << line_size << std::endl;

        index = 0;

        if (print_counter > 10) {
            print_progress(entry_file.tellg(), size_of_file);
            print_counter = 0;

        }
        print_counter++;


        while (fill) {
            if (valid_character(line[index])) {
                forwardSequence.push_back(charmap[line[index]]);
                backwardSequence.push_front(complementmap[line[index]]);
                char_counter++;

            }

            if(char_counter >= length) {
                fill = false;
            }


            index++;


        }

        // For initialized sequence
        // What to do if forward is binding
        score = matrix.sequence_score(forwardSequence);

        if(score >= cutoff) {

            SearchResult sequence_match(fill_search_result(forwardSequence, position_counter -1, score, '+'));
            sequence_matches.searchResults.push_back(sequence_match);
        }

        // What to do if backward is binding
        score = matrix.sequence_score(backwardSequence);

        if(score >= cutoff) {
            SearchResult sequence_match(fill_search_result(backwardSequence, position_counter -1, score, '-'));
            sequence_matches.searchResults.push_back(sequence_match);
        }


        // For all following combinations
        while (index < line_size) {

            // Skips if character is not valid
            if(valid_character(line[index]))
            {
                position_counter++;

                // Updates sequence with the new character
                forwardSequence.pop_front();
                forwardSequence.push_back(charmap[line[index]]);
                backwardSequence.pop_back();
                backwardSequence.push_front(complementmap[line[index]]);

                // What to do if forward is binding
                score = matrix.sequence_score(forwardSequence);

                if(score >= cutoff) {

                    SearchResult sequence_match(fill_search_result(forwardSequence, position_counter -1, score, '+'));
                    sequence_matches.searchResults.push_back(sequence_match);
                }

                // What to do if backward is binding
                score = matrix.sequence_score(backwardSequence);

                if(score >= cutoff) {
                    SearchResult sequence_match(fill_search_result(backwardSequence, position_counter -1, score, '-'));
                    sequence_matches.searchResults.push_back(sequence_match);
                }
            }
            index++;
        }


        if (entry_file.peek() == '>' or entry_file.peek() == EOF) {
            output.push_back(sequence_matches);
            sequence_matches = SearchResults();

            if(!forwardSequence.empty())
                forwardSequence.clear();
            if(!backwardSequence.empty())
                backwardSequence.clear();

            position_counter = 0;
            char_counter = 0;
            first_line = false;
            fill = true;

            while (entry_file.peek() == '>' or entry_file.peek() == ';') {
                getline(entry_file, seq_description);
                sequence_matches.description += seq_description;
            }
        }
    }

    output.push_back(sequence_matches);

    entry_file.close();
    return output;
}










//==========================================================================================
// SHOULD BE MADE AS CONSTRUCTOR

SearchResult fill_search_result(std::list<nuc> sequence, int position_counter, double score, char direction)
{
    SearchResult sequence_match;

    sequence_match.sequence = sequence_string_from_nuc_list(sequence);
    sequence_match.position = position_counter;
    sequence_match.score = score;
    sequence_match.direction = direction;

    return sequence_match;
}

//==========================================================================================
bool valid_character(char character) {
    auto it = charmap.find(character);
    if (it == charmap.end())
    {
        // std::cout << "Unknown character: " << character << ". Character is skipped and ignored\n";
        return false;
    }
    else
        return true;
}


//==========================================================================================
int filesize(std::string filename) {
    std::ifstream in(filename, std::ios::binary | std::ios::ate);
    return in.tellg();
}

//==========================================================================================

std::string sequence_string_from_nuc_list(std::list<nuc> sequence) {
    std::string output;
    std::list<nuc>::iterator iterator;

    for (iterator = sequence.begin(); iterator != sequence.end(); iterator++)
        output += backwardsmap[*iterator];
    return output;
}


std::string relativePath(std::string file){
    size_t position(file.find_last_of("/"));
    file=".."+file.substr(position);
    return file;
}
