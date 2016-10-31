#ifndef UTILITY_H
#define UTILITY_H

#include "Matrix.hpp"
#include "Sequence.hpp"



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

#endif
