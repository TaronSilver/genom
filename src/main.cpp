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
#include "logo.hpp"



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
	    
	    if (procedure == Logo) {
			logo();
		}
       
       if (procedure == CorrelateResults) {
           correlate_coordinates_with_results(input_search_results());
       }
       
       done();
       
       // Waits with program until next input of user.
       getchar();
       getchar();

	 } while (procedure != Exit);
	
	return 0;
}



/*! \mainpage Welcome!
 *
 * \section intro_sec Presenting DBSAP
 *
 * Welcome to the Doxygen documentation for DBSAP! 
 * 
 * This program will help you by providing the tools necessary to analyse 
 * a DNA sequence or a DNA-binding protein of interest.
 * 
 * In our program you will find three useful functionalities:
 * 
 * (1) You can obtain a probability matrix (or a weighted probability, 
 * logarithmic or weighted logarithmic matrix) from a file containing the 
 * sequences of binding sites you have found. These sequences can be of 
 * a fixed length or of variable length as we have implemented an 
 * algorithm that can identify the consensus sequence length as well as 
 * the sequence.
 * 
 * needed inputs: file with sequences (.fasta, .fas, .fna, .ffn)
 * 
 * (2) You can obtain all the binding positions of a protein to a DNA sequence
 * of your choosing. You may even specify the cutoff value you prefer: 0.25,
 * calculated based on the input sequence or customised by you.
 * 
 * needed inputs: a matrix file (.mat) and
 * a sequence file (.fasta, .fas, .fna, .ffn)
 * 
 * (3) Generate a consensus sequence logo for a DNA protein
 * of your choosing: just give us the file name and we will take care of 
 * the rest.
 * 
 * needed inputs: a probability weight matrix file (.mat)
 *
 * (4) Our last tool correlates binding affinities between a genome file 
 * and your experimental values
 *
 * needed inputs: your affinities, genomic file
 * 
 * We hope you enjoy!
 * 
 * 
 * 
 *
 * \section install_sec Running the program
 * 
 * Our program is easy to use you'll be analysing sequences in no time! Just follow these 3 steps:
 *
 * STEP 1: Clone our github project
 * 
 * --> git clone https://github.com/EPFL-SV-cpp-projects/genom-2.git
 *
 * STEP 2: Make a build folder and build the program
 * 
 * --> mkdir build 
 * 
 * --> cd build
 * 
 * --> cmake ../
 * 
 * --> make
 * 
 * STEP 3: Execute the program (with Qt)
 * 
 * --> ./genom-2
 *
 * without Qt (--> ./Main)
 * 
 * and voilà!
 * 
 * TESTS (in build):
 * 
 * --> ./gtests
 * 
 * \section authors Brought to you by
 * 
 * Angela Saudan, Erica Geneletti, Jérémy Alexandre, Katia Schalk, Lucas 
 * Zweili, Matthias Minder, Marion Perier, Souhail Elaissaoui, 
 * Tristan Vyvyan-Robinson aaaaand Gokcen Nurlu!
 * 
 * 
 */
