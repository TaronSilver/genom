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
void binding_length_known();

/* @Brief   Handles everything if the user doesn't know the length of the binding
 *          site
 */
void binding_length_unknown();

//------------------------------------------------------------------------


#endif /* procedures_hpp */
