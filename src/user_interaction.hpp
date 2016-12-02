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

#include "Matrix.hpp"

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
enum BP_FILL { NotUsed, AllEqual, UserDefined, FromSequence  };

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


/*!
 * @brief Cout: Indicate the creation of a new sequence 
 * @param name of the new sequence
 * 
 */
void Cout_NewSeq(std::string);

/*!
 * @brief Ask the choice ( 0 or 1 or 2 ) corresponding to the question "what we want to do"
 *
 * @return the Choice made by the user, as enum BP_FILL.
 */
BP_FILL CoutCin_AskBaseProb();

/*!
 * @brief Ask the Prob corresponding to the nucleotide.
 *
 * @param the nucleotide needed (A or C or G or T)
 * @return the Prob enter by the user for this nucleotide
 */
double CoutCin_AskBaseProb0(char);

/*!
 * @brief Ask the name for the outputfile 
 *
 * @return Name of the outputfile
 */
std::string Ask_Outputfile_Name();

/*!
 * @brief Handles everything concerning base probabilities, returns a vector of doubles
 *          with the base probabilities
 *
 * @return  Vector with base probabilities
 */
std::vector<double> AskBaseProb();

/*!
 * @brief   Lets the user choose the base probabilities, checks for their 
 *          validity.
 *
 * @return  Vector with base probabilities
 */
std::vector<double> User_Defined_Base_Prob();

/*!
 * @brief   Asks the user as what kind of matrix he wants to save his matrix as.
 *
 * @return  MATRIX_TYPE with the corresponding type
 */
MATRIX_TYPE Ask_Return_Matrix_Type();

/*!
 * @brief   Asks the user if he wants to weigh each sequence by its score for 
 *          the calculation of the matrix
 *
 * @return  1 if yes, else 0
 */
bool ask_matrix_from_sequences_weighed();

/*!
 * @brief   Asks the user if he wants to create a new matrix based on the 
 *          matches found in the previous search
 *
 * @return  1 if yes, else 0
 */
bool ask_matrix_from_search_matches();

/*!
 * @brief   Warns the user that there are either no sequences found or that
 *          they are of different length
 *
 */
void error_input_sequence();

/*!
 * @brief   Informs the user that there was an error reading a coordinate file
 *
 * @param   Line on which it failed
 */

void error_reading_coordiates(unsigned int line);

/*!
 * @brief   Ask the name of a coordinate files
 *
 * @return  Name of user input
 */
std::string ask_coordinate_filename();



//-----------------------------------------------------------------------


#endif /* user_interaction_hpp */
