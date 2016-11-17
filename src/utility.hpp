#ifndef UTILITY_H
#define UTILITY_H

#include "Matrix.hpp"
#include "Sequence.hpp"
#include "user_interaction.hpp"




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






/*!
 * @brief Allows to ask the name of the file we want to open,
 *		  with exception handling
 */
std::vector <Sequence> Initialization();

/*!
 * @brief Allows to ask the name of the fasta file we want to open,
 *		  with exception handling
 *
 * @param name of the file we want to open
 */
void AskNameFasta(std::string& entry_name);

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


/*!
 * @brief Goes through all sequences in the file and returns sequences with a score above 5
 *
 * @param Name of sequence file, Matrix to compare it with, Cutoff
 * @return A vector of all search results (each in one structure SearchResults)
 */
std::vector<SearchResults> analyze_sequence(std::string filename, Matrix matrix, double cutoff);

/*!
 * @brief Translates a list of the enum "nuc" to a string
 *
 * @param A list of nucleotides to be translated
 * @return Nucleotide sequence as a string
 */
std::string sequence_string_from_nuc_list(std::list<nuc>);


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




#endif
