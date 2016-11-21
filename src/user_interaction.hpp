//
//  user_interaction.hpp
//  
//
//  Created by Mättu on 15.11.16.
//
//

#ifndef user_interaction_hpp
#define user_interaction_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class SearchResult {
public:
    std::string sequence;
    unsigned int position;
    double score;
    char direction;
};

class SearchResults {
public:
    std::string description;
    std::vector<SearchResult> searchResults;
};



enum PROCEDURE { MatrixFromSequences, SequencesFromMatrix, Exit };

//-----------------------------------------------------------------------


/*!
 * @brief Asks what the user wants to do
 *
 * @return Answer of type PROCEDURE
 */
PROCEDURE whatToDo();


/*!
 * @brief Ask the user for the cutoff, returns said cutoff
 *
 * @return cutoff value specified by user
 */
double ask_cutoff();

/*!
 * @brief Ask the user if the binding site length is known
 *
 * @return true if known, false if not.
 */
bool ask_binding_length_known();

/*!
 * @brief Ask the user for the length of the enzyme binding site
 *
 * @return Length of binding site
 */
unsigned int ask_length();

/*!
 * @brief Ask the user for the position of the enzyme binding site
 *
 * @return position of binding site
 */
unsigned int ask_position();

/*!
 * @brief Ask the user for the filename; checks filename; returns filename
 *
 * @return name of the file the user would like to open
 */
std::string ask_name_fasta();


/*!
 * @brief Allows to ask the name of the matrix file we want to open,
 *		  with exception handling
 *
 * @return Name of the file to open
 */
std::string ask_name_matrix();


/*!
 * @brief Checks if the matrix file is valid 
 *
 * @param name of the file we want to open
 * @return 0 if format is valid of 1 if not
 */
bool InvalidFormatMat(std::string file_name);


/*!
 * @brief Checks if the file if valid
 *
 * @param name of the file we want to open
 * @return 0 if format is valid of 1 if not
 */
bool InvalidFormat(std::string file_name);

/*!
 * @brief   Prints out current progress
 * @param   Current position, current filesize
 */
void print_progress(int position, int filesize);


/*!
 * @brief Prints search results to file
 *
 * @param Search results, filename
 */
void print_results(SearchResults results, std::string filename);


/*!
 * @brief Prints search results to terminal
 *
 * @param Search results
 */
void print_results(SearchResults results);

/*!
 * @brief warns that there is a problematic char
 *
 * @param character causing problem
 */
void nucleotide_warning(char c);



//-----------------------------------------------------------------------


#endif /* user_interaction_hpp */
