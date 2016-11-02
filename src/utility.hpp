#ifndef UTILITY_H
#define UTILITY_H

#include "Matrix.hpp"
#include "Sequence.hpp"

enum PROCEDURE { MatrixFromSequences, SequencesFromMatrix, Exit };

/*!
 * @brief Asks what the user wants to do
 *
 * @return Answer of type PROCEDURE
 */
PROCEDURE whatToDo();

/*!
 * @brief Allows to ask the name of the matrix file we want to open,
 *		  with exception handling
 *
 * @param name of the file we want to open
 */
void AskNameMatrix(std::string& entry_name);


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
 * @brief Checks if the file if valid
 *
 * @param name of the file we want to open
 * @return 0 if format is valid of 1 if not
 */
bool InvalidFormat(std::string file_name);

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
 * @param vector of sequences to analyze
 * @return A probability matrix in form of Matrix_Neo, order: A, C, G, T
 */
Matrix_Neo generate_PWM_from_Seq_list(std::vector <Sequence> sequence_list);

#endif
