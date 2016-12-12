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
        enzyme_renewed.save(file_name+".mat",  Ask_Return_Matrix_Type());
    }
}


void enzyme_from_sequences() {
    
    SEQ_SOURCE seq_source(ask_source_sequence());
    std::vector<SearchResults> seq_to_analyze;
    
    switch (seq_source) {
        case SEQ_SOURCE::CoordAndSeq:
            // DOESNT WORK
            seq_to_analyze = seq_source_CoordAndSeq();
            break;
            
        case SEQ_SOURCE::OnlySeq:
            seq_to_analyze = seq_source_OnlySeq();
            break;
            
        case SEQ_SOURCE::FromSearchResult:
            seq_to_analyze = seq_source_FromSearchResult();
            break;
            
        default:
            break;
    }
    
    if (seq_to_analyze.size() == 0) {
        error_no_search_result_read();
        return;
    }
    
    
    std::cout << "HI BEFORE FOR LOOP" << std::endl;
    for (unsigned int h(0); h<seq_to_analyze.size(); h++) {
        for (unsigned int i(0); i<seq_to_analyze[h].searchResults.size(); i++) {
            std::cout << seq_to_analyze[h].searchResults[i].sequence << '\t' << std::endl;
        }

    }
    std::cout << "HI AFTER FOR LOOP" << std::endl;
	

    
    if(searchResults_same_length(seq_to_analyze)) {
        Matrix result(binding_length_known(seq_to_analyze));
        result.save(Ask_Outputfile_Name(), Ask_Return_Matrix_Type());
    }
    else
        binding_length_unknown();
    
    
}


//=======================================================================

std::vector<SearchResults> input_search_results() {
    std::vector <SearchResults> result_list;
    result_list = read_searchresult_file(ask_inputfile_name());
    return result_list;
}


//=======================================================================

void correlate_coordinates_with_results(std::vector <SearchResults> result_list) {
    
    Association_Table associate;
    unsigned int startpos;
    unsigned int coord_id;
    unsigned int seq_id;
    
    std::vector <double> corr_values;
    
    // Initializes vector of coordinates from a file.
    std::vector <Coordinates> coord_list(read_coordinates(ask_coordinate_filename(),
                                                           ask_line_description_present()));
    
    

    do {
        associate = associate_genomic_with_result(get_descriptions_from_coord_list(coord_list),
                                                  result_list);
        coord_id = associate[0][COORD];
        seq_id = associate[0][SEQ];
        startpos = associate[0][START];
        
        corr_values = coord_list[coord_id].position_score(result_list[seq_id], startpos);
        print_results_correlated(result_list[seq_id], corr_values, Ask_Outputfile_Name());

        
    } while (correlate_more());

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
	unsigned int n=0; 
	std::vector<std::string> sequence_list;
	double t=0.0; 
	Matrix_Neo results;
	std::ofstream outputfile;
	double max = 0.0;
	int i = 0;
	int f=0;
	double g = 0.0;

    sequence_list = Initialization_string();
    i = smallest_length(sequence_list);
    n = ask_iterations(i);
    Base_Prob base_probabilities = AskBaseProb();
	max = max_score(sequences_to_PPM(sequence_list,n));
	t = ask_cutoff2(max);
	f = maximum_EM ();
	g = differences_matrices ();
	
	results = EM_algorithm(sequence_list, n, t, base_probabilities, f, g);
	path();
	std::string name = ask_name_output_file();
	outputfile.open(name);
	print_into_file(outputfile, results);
	outputfile.close();
	char c;
	std::cin >> c;
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

std::vector<SearchResults> seq_source_OnlySeq() {
    
    std::vector<SearchResults> output;
    std::string filename;
    
    switch (ask_list_file_type()) {
        case LIST_FILE::Fasta:
            filename = ask_name_fasta();
            output.push_back(read_sequencefile_to_searchresults(filename));
            break;
            
        case LIST_FILE::NormalList:
            filename = ask_inputfile_name();
            output.push_back(read_sequence_list_to_searchresults(filename));
            break;
            
        case LIST_FILE::SeparatedList:
            char delim(ask_separation_character());
            filename = ask_inputfile_name();
            output.push_back(read_char_separated_to_searchresults(filename, delim));
            break;
    }
    
    return output;
}

//=======================================================================

std::vector<SearchResults> seq_source_FromSearchResult() {
    return read_searchresult_file(ask_inputfile_name());
}

//=======================================================================

