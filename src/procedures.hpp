//
//  procedures.hpp
//
//
//  Created by Mättu on 15.11.16.
//
//

#ifndef procedures_hpp
#define procedures_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Matrix.hpp"
#include "Sequence.hpp"
#include "utility.hpp"
#include "user_interaction.hpp"

//-----------------------------------------------------------------------

/* @Brief   Handles everything if the user wants to determine on 
 *          what position a given enzyme binds, with given probability
 *          matrix and sequence
 */
void enzyme_on_sequence();


/* @Brief   Handles everything if the user wants to determine
 *          a probability weight matrix from given sequences
 */
void enzyme_from_sequences();

/* @Brief   Handles everything if the user knows the length of the binding
 *          site
 */
Matrix binding_length_known(std::vector<SearchResults> seq_to_analyze);

/* @Brief   Handles everything if the user doesn't know the length of the binding
 *          site
 */
void binding_length_unknown();

/* @Brief   Handles everything if the user wants to extract a list of search results 
 *          from coordinates and a sequence file
 *
 * @return  Returns a list of SearchResults of the found sequences
 */
std::vector<SearchResults> seq_source_CoordAndSeq();

/* @Brief   Handles everything if the user wants to extract a list of search results
 *          from a sequence file. All scores will be set to 1
 *
 * @return  Returns a list of SearchResults of the found sequences
 */
std::vector<SearchResults> seq_source_OnlySeq();

/* @Brief   Handles everything if the user already has a list of search results which
 *          he wants to load into the program
 *
 * @return  Returns a list of SearchResults of the found sequences
 */
std::vector<SearchResults> seq_source_FromSearchResult();


//------------------------------------------------------------------------


#endif /* procedures_hpp */
