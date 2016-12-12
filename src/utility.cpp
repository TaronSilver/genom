#include "utility.hpp"
#include <assert.h>

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










//==========================================================================================
// SEQUENCE ANALYSIS
//==========================================================================================
// I am very sorry for the uglyness of this function
//
// TODO: Doesn't work if at position 0; reverse strand doesnt work
// TODO: Progress bar

// Souhail : I deleted the not used functions
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
    //The following variable is commented because it's not used and create warnings - SOuhail
   // bool description(true);


    unsigned int char_counter(0);
    unsigned int length(matrix.get_length());
    unsigned int position_counter(1);
    unsigned int line_size;

    unsigned int print_counter(0);


    int size_of_file;
    size_of_file = filesize(filename);

    //bool first_line(true); // not used ? Souhail
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


        if (entry_file.peek() == '>' or entry_file.peek() == EOF) {
            output.push_back(sequence_matches);
            sequence_matches = SearchResults();

            if(!forwardSequence.empty())
                forwardSequence.clear();
            if(!backwardSequence.empty())
                backwardSequence.clear();

            position_counter = 1;
            char_counter = 0;
            //first_line = false;
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


//==========================================================================================

std::string relativePath(std::string file){
    size_t position(file.find_last_of("/"));
    file=".."+file.substr(position);
    return file;
}


//==========================================================================================

Matrix_Neo matrix_from_same_length_sequences_not_weighted(std::vector<SearchResults>  input, Base_Prob base_prob) {
    Matrix_Neo output_matrix;

    assert(input.size() >= 1);

    unsigned int nb_search_results;
    unsigned int length_sequence( searchResults_same_length(input) );

    if(length_sequence == 0) {
        error_input_sequence();
        return output_matrix;
    }


    char character;

    // Initialization of matrix with proper size, with corresponding baseprob for
    // every nucleotide position
    std::vector <double> line;

    for (unsigned int index(0); index<NUMBER_NUCLEOTIDES; index++) {
        line.push_back(base_prob[index]);
    }

    for (unsigned int index(0); index<length_sequence; index++) {
        output_matrix.push_back(line);
    }

    // Counter for every search result
    for (unsigned int k(0); k<input.size(); k++) {
        nb_search_results = input[k].searchResults.size();

        for (unsigned int i(0); i<nb_search_results; i++) {

            for (unsigned int j(0); j<length_sequence; j++) {
                character = input[k].searchResults[i].sequence[j];
                output_matrix[j][charmap[character]] += 1;
            }
        }
    }

    // Division by sum of each line
    double line_sum = Matrix::sum_of_line(output_matrix[0]);

    for (unsigned int i(0); i<length_sequence; i++) {
        for (unsigned int j(0); j<NUMBER_NUCLEOTIDES; j++) {
            output_matrix[i][j] /= line_sum;
        }
    }





    return output_matrix;
}


//==========================================================================================

Matrix_Neo matrix_from_same_length_sequences_weighted(std::vector<SearchResults>  input, Base_Prob base_prob) {
    Matrix_Neo output_matrix;

    assert(input.size() >= 1);

    unsigned int length_sequence( searchResults_same_length(input) );

    if(length_sequence == 0) {
        error_input_sequence();
        return output_matrix;
    }


    unsigned int nb_search_results;
    double line_min;
    double line_sum;

    char character;

    // Initialization of matrix with proper size, all zero
    for (unsigned int index(0); index<length_sequence; index++) {
        output_matrix.push_back({0,0,0,0});
    }

    // Counter for every search result, score is added for each match
    for (unsigned int k(0); k<input.size(); k++) {

        nb_search_results = input[k].searchResults.size();

        for (unsigned int i(0); i<nb_search_results; i++) {
            for (unsigned int j(0); j<length_sequence; j++) {
                character = input[k].searchResults[i].sequence[j];
                output_matrix[j][charmap[character]] += input[k].searchResults[i].score;
            }
        }
    }


    // If the smallest number is less or equal 0, it is subtracted from all values from the line
    // To avoid havnig a probability of 0, the base probability for each nucleotide is added to
    // each such line (or should we do this to every line?)
    for (unsigned int i(0); i<length_sequence; i++) {
        line_min = Matrix::min_of_line(output_matrix[i]);

        if (line_min<=0) { //modified by Souhail to avoid warnings
            for (unsigned int j(0); j<NUMBER_NUCLEOTIDES; j++) {
                output_matrix[i][j] -= line_min;
                output_matrix[i][j] += base_prob[j];
            }
        }
    }

    // Every value of the line is divided by the sum of each line, yielding a probability
    for (unsigned int i(0); i<length_sequence; i++) {
        line_sum = Matrix::sum_of_line(output_matrix[i]);

        for (unsigned int j(0); j<NUMBER_NUCLEOTIDES; j++) {
            output_matrix[i][j] /= line_sum;
        }
    }

    return output_matrix;
}

//==========================================================================================
Matrix_Neo matrix_from_same_length( std::vector<SearchResults>  input, Base_Prob base_prob, bool weighed ) {

    if (weighed)
        return matrix_from_same_length_sequences_weighted( input, base_prob);
    else
        return matrix_from_same_length_sequences_not_weighted( input, base_prob);

}


//==========================================================================================
unsigned int searchResults_same_length(std::vector<SearchResults> input) {

    unsigned int nb_sequences(input.size());
    unsigned int nb_results;

    assert(nb_sequences);

    unsigned int length_result_0(0);

    for (unsigned int index(0); index<nb_sequences; index++) {
        if(input[index].searchResults.size()) {
            length_result_0 = input[0].searchResults[0].sequence.size();
            break;
        }
    }

    for (unsigned int k(0); k<nb_sequences; k++) {
        nb_results = input[k].searchResults.size();


        for (unsigned int i(0); i<nb_results; i++) {
            if (input[k].searchResults[i].sequence.size() != length_result_0) {
                return false;
            }
        }
    }

    return length_result_0;
}


//==========================================================================================
std::vector <Coordinates> read_coordinates(std::string filename, bool line_description_present) {
    std::ifstream file;
    file.open(filename);

    std::string file_description;
    std::string seq_description;
    std::string seq_descr_intermediate;
    std::string line;

    // File description in first line is disregarded.
    // getline(file, file_description);

    std::vector <Coordinates> output;

    file >> seq_description;
    Coordinates intermediate(file_description, seq_description, line_description_present);
    getline(file, line, '\n');
    intermediate.fillNewLine(line);


    while (file >> seq_descr_intermediate) {
        if (seq_description != seq_descr_intermediate) {
            seq_description = seq_descr_intermediate;
            output.push_back(intermediate);
            intermediate = Coordinates(file_description, seq_description, line_description_present);
        }

        getline(file, line, '\n');
        intermediate.fillNewLine(line);
    }

    output.push_back(intermediate);
    return output;
}


//==========================================================================================

std::vector<std::string> extract_sequence_descriptions(std::string filename) {
    std::ifstream file;
    file.open(filename);

    std::vector<std::string> output;
    std::string intermediate;

    unsigned int streamsize(file.tellg());

    do {
        getline(file, intermediate);
        output.push_back(intermediate);

    } while (file.ignore(streamsize, '>'));

    return output;
}

//==========================================================================================

std::vector<std::string> get_descriptions_from_coord_list(std::vector<Coordinates> coord_list) {
    std::vector<std::string> output;
    for (size_t id(0); id<coord_list.size(); id++) {
        output.push_back(coord_list[id].get_location());
    }
    return output;
}
