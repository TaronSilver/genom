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
 * @brief Checks if the file if valid
 *
 * @param name of the file we want to open
 * @return 0 if format is valid of 1 if not
 */
bool InvalidFormat(std::string file_name);


//-----------------------------------------------------------------------


#endif /* user_interaction_hpp */
