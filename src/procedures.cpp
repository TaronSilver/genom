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
    std::vector <double> base_prob(AskBaseProb());
    
    std::string file_name_matrix;

    Matrix enzyme(ask_name_matrix(), base_prob);

	std::string file_name(Ask_Outputfile_Name());
    // DEBUG_
    //enzyme.print_log_matrix();

    std::vector<SearchResults> enzyme_matches;
    enzyme_matches = analyze_sequence_opt2(ask_name_fasta(), enzyme, ask_cutoff());

    for (unsigned index(0); index < enzyme_matches.size(); index++) {
        print_results(enzyme_matches[index],file_name);
    }
    
    if(ask_matrix_from_search_matches()) {
        Matrix enzyme_renewed(matrix_from_same_length(enzyme_matches, base_prob, ask_matrix_from_sequences_weighed()),MATRIX_TYPE::absoluteMatrix);
        
        enzyme_renewed.save(Ask_Outputfile_Name(),  Ask_Return_Matrix_Type());
    }
}


void enzyme_from_sequences() {
    if(ask_binding_length_known()){
        binding_length_known();
    }
    else binding_length_unknown();
}


void binding_length_known() {
    std::vector <Sequence> sequence_list;
    sequence_list = Initialization();
    Matrix enzyme(generate_PWM_from_Seq_list(sequence_list, false),absoluteMatrix);
    std::string file_name(Ask_Outputfile_Name());
    enzyme.save(file_name, absoluteMatrix);
}

void binding_length_unknown() {
  //EM implementation

}
