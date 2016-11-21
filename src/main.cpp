//
//  main.cpp
//  
//
//  Created by Mättu on 20.10.16.
//
//

#include <stdio.h>
#include <string>

#include "procedures.hpp"
#include "user_interaction.hpp"



//-------------------------------------------------------------------------

int main() {
    
    PROCEDURE procedure;
    
    
    
   do {
	    procedure = whatToDo();
	    
	    // What to do if user wants to extract Sequences from a given matrix
	    if (procedure == SequencesFromMatrix) {
	        enzyme_on_sequence();
	    }
	    
	    if (procedure == MatrixFromSequences) {
	        enzyme_from_sequences();
	    }
	 } while (procedure != Exit);
	
	return 0;
}




