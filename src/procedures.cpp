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
    
    SEQ_SOURCE seq_source(ask_source_sequence());
    std::vector<SearchResults> seq_to_analyze;
    
    switch (seq_source) {
        case SEQ_SOURCE::CoordAndSeq:
            seq_to_analyze = seq_source_CoordAndSeq();
            break;
            
        case SEQ_SOURCE::OnlySeq:
            
            break;
            
        case SEQ_SOURCE::FromSearchResult:
            
            break;
            
        default:
            break;
    }
    
    if(ask_binding_length_known())
        Matrix result(binding_length_known(seq_to_analyze));
    else
        binding_length_unknown();
}


//=======================================================================

Matrix binding_length_known(std::vector<SearchResults> seq_to_analyze) {
    Base_Prob base_probabilities = AskBaseProb();
    
    return Matrix(matrix_from_same_length(
                                          seq_to_analyze,
                                          base_probabilities,
                                          ask_matrix_from_sequences_weighed()
                                          ),
                  MATRIX_TYPE::absoluteMatrix);
}


//=======================================================================

void binding_length_unknown() {
  //EM implementation

}

//=======================================================================

std::vector<SearchResults> seq_source_CoordAndSeq() {
    
    std::vector<Coordinates> coordinate_list;
    std::vector<SearchResults> output;
    
    std::string seq_filename = ask_name_fasta();
    
    coordinate_list = read_coordinates(ask_coordinate_filename(),
                                       ask_line_description_present());
    
    std::vector<std::string> sequence_descriptions;
    std::vector<std::string> coordinate_descriptions;
    
    sequence_descriptions = extract_sequence_descriptions(seq_filename);
    coordinate_descriptions = get_descriptions_from_coord_list(coordinate_list);
    
    Association_Table association;
    association = associate_genomic_with_sequences(coordinate_descriptions,
                                                   sequence_descriptions);
    
    
    
    for (unsigned int i(0); i<association.size(); i++) {
        output.push_back(coordinate_list[association[i][COORD]].get_search_results(seq_filename,
                                                                                association[i][SEQ],
                                                                                association[i][START]));
    }
    
    return output;
}

//=======================================================================

std::vector<SearchResults> seq_source_OnlySeq();

//=======================================================================

std::vector<SearchResults> seq_source_FromSearchResult();

//=======================================================================

