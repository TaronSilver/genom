#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include "Matrix.hpp"
#include "user_interaction.hpp"
#include "genomic_coordinates.hpp"

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

/*!
 * @brief Creates a probability weight matrix from SearchResults with all the same length
 *          Function doesn't weigh the probabilities by the score of each individual sequence
 *
 * @param An instance of SearchResults with all the same length, base probabilities to add as noise
 * @return A regular probability weight matrix (type absoluteMatrix). Matrix of size 0 in case of error.
 */
Matrix_Neo matrix_from_same_length_sequences_not_weighted(std::vector<SearchResults> input, Base_Prob base_prob);


/*!
 * @brief Creates a probability weight matrix from SearchResults with all the same length
 *          Function weighs each probability by the score of each sequence
 *
 * @param An instance of SearchResults with all the same length, base probabilities to add as noise
 * @return A regular probability weight matrix (type absoluteMatrix). Matrix of size 0 in case of error.
 */
Matrix_Neo matrix_from_same_length_sequences_weighted(std::vector<SearchResults> input, Base_Prob base_prob);

/*!
 * @brief Creates a probability weight matrix from a vector of SearchResults with all the same length
 *          Takes bool as argument if it should be weighed by the score or not
 *
 * @param An instance of SearchResults with all the same length
 * @return A regular probability weight matrix (type absoluteMatrix)
 */
Matrix_Neo matrix_from_same_length( std::vector<SearchResults> input, Base_Prob base_prob, bool weighed );

/*!
 * @brief Checks if all search results have the same length, returns this length
 *
 * @param An instance of SearchResults
 * @return The length if yes, false if no or input doesn't contain searchResults
 */
unsigned int searchResults_same_length(std::vector<SearchResults> input);


/*!
 * @brief   Fills a vector of coordinates from a input file
 *
 * @param   The name of the genomic file, a bool saying whether the file contains a column with
 *          information on every sequence.
 * @return  A vector of coordinates.
 */
std::vector <Coordinates> read_coordinates(std::string filename, bool line_description_present);


/*!
 * @brief   Goes through files and extracts all sequence descriptions present
 *
 * @param   The name of the sequence file.
 * @return  A vector of strings with all sequence descriptions.
 */
std::vector<std::string> extract_sequence_descriptions(std::string filename);


/*!
 * @brief   Returns a vector of coordinates
 *
 * @param   The name of the sequence file.
 * @return  A vector of strings with all sequence descriptions.
 */
std::vector<std::string> get_descriptions_from_coord_list(std::vector<Coordinates> coord_list);

#endif
