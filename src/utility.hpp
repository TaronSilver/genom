#ifndef UTILITY_H
#define UTILITY_H

#include "Matrix.hpp"
#include "Sequence.hpp"
#include "user_interaction.hpp"




/*!
 * @brief Allows to ask the name of the file we want to open,
 *		  with exception handling
 */
std::vector <Sequence> Initialization();


/*!
 * @brief If all the conditions a correct reads te DNA sequence from
 *		  the file
 *
 * @param name of the file we want to open
 * @return Our DNA sequence
 */
std::vector <std::string> ExtractSequence(std::string const& entry_name);



/*!
 * @brief Gives the probability of all nucleotides at a specified position
 *
 * @param vector of strings with nucleotides to analyze, and the position in which
 *        it should be analyzed (starts at 0)
 * @return a vector of size 4 with the probabilities, order: A, C, G, T
 */
std::vector <double> nucleotide_probability(
    std::vector <std::string> nucleotide_sequences,
    unsigned int position
);


/*!
 * @brief Returns vector of vector with probabilities based on a list of sequences
 *        and specified binding position and length (asked for during function)
 *
 * @param vector of sequences to analyze, a bool whether the entire sequence is
 *        relevant (true), or if only a part of the sequence to be specified
 * @return A probability matrix in form of Matrix_Neo, order: A, C, G, T
 */
Matrix_Neo generate_PWM_from_Seq_list(std::vector <Sequence> sequence_list, bool entire_sequence);


/*!
 * @brief Function that allows for creation of a new Matrix based on the found results,
 *        stored in a txt file
 *
 * @param name of the txt file
 * @return A probability matrix in form of Matrix_Neo, order: A, C, G, T
 */
Matrix_Neo matrix_from_sequence_results(std::string filename);





//==========================================================================================
// SEQUENCE ANALYSIS
/*!
 * @brief Goes through all sequences in the file and returns sequences with a score above 5
 *          Estimated time for PPM.mat on human genome: 3h05, with flag -O2, MacBook Pro, cutoff 5
 *
 * @param Name of sequence file, Matrix to compare it with, Cutoff
 * @return A vector of all search results (each in one structure SearchResults)
 */
std::vector<SearchResults> analyze_sequence(std::string filename, Matrix matrix, double cutoff);


/*!
 * @brief   Goes through all sequences in the file and returns sequences with a score above 5
 *          Optimized version
 *          Estimated time for PPM.mat on human genome: 29min, with flag -O2, MacBook Pro, cutoff 5
 *
 * @param Name of sequence file, Matrix to compare it with, Cutoff
 * @return A vector of all search results (each in one structure SearchResults)
 */
std::vector<SearchResults> analyze_sequence_opt(std::string filename, Matrix matrix, double cutoff);


/*!
 * @brief Goes through all sequences in the file and returns sequences with a score above 5
 *         Optimized version 2
 *          Estimated time for PPM on human genome: 30min, with flag -O2, MacBook Pro, cutoff 5
 *
 * @param Name of sequence file, Matrix to compare it with, Cutoff
 * @return A vector of all search results (each in one structure SearchResults)
 */
std::vector<SearchResults> analyze_sequence_opt2(std::string filename, Matrix matrix, double cutoff);



/*!
 * @brief Fills up a Search result. This should be made as a constructor of the class
 *
 * @param A nuc-list of the sequence, the position, the score and the direction of the result
 * @return A filled class SearchResult
 */
SearchResult fill_search_result(std::list<nuc> sequence, int position_counter, double score, char direction);


/*!
 * @brief Determines if input character is valid (a nucleotide)
 *
 * @param Input character
 * @return true if valid, false if not valid
 */
bool valid_character(char character);


/*!
 * @brief   Determines size of a file
 * @param   Name of file to analyze
 * @return  Number of bytes of file, only approximatively
 */
int filesize(std::string filename);


/*!
 * @brief Translates a list of the enum "nuc" to a string
 *
 * @param A list of nucleotides to be translated
 * @return Nucleotide sequence as a string
 */
std::string sequence_string_from_nuc_list(std::list<nuc>);


/*!
	 * @brief Change an absolute path to a relative one, considering the file is in the main directory of our program.
	 *
	 * @param the absolute path of the file to open
	 * @return the relative patch of the file to ope.n
	 */
std::string relativePath(std::string file);

#endif
