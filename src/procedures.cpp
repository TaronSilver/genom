//
//  procedures.cpp
//  
//
//  Created by Mättu on 15.11.16.
//
//

#include "procedures.hpp"


void enzyme_on_sequence() {
    
    system("Clear");
    
    std::string file_name_matrix;
    
    Matrix enzyme(ask_name_matrix());
    
    std::vector<SearchResults> enzyme_matches;
    enzyme_matches = analyze_sequence(ask_name_fasta(), enzyme, ask_cutoff());
    
    for (unsigned index(0); index < enzyme_matches.size(); index++) {
        print_results(enzyme_matches[index]);
    }

}
