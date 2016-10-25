//
//  main.cpp
//  
//
//  Created by Mättu on 20.10.16.
//
//

#include <stdio.h>
#include <string>

#include "Matrix.hpp"
#include "Sequence.hpp"



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
 * @brief Allows to ask the name of the matrix file we want to open,
 *		  with exception handling
 *
 * @param name of the file we want to open
 */
void AskNameMatrix(std::string& entry_name);


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



//-------------------------------------------------------------------------

int main() {
    std::string file_name_matrix;
    AskNameMatrix(file_name_matrix);
    Matrix enzyme(file_name_matrix);
    
    std::vector <Sequence> sequence_list;
    sequence_list = Initialization();
    
    std::vector <std::string> binding_sites = enzyme.accessDNASequences();
    
    for(unsigned int i(0); i<sequence_list.size(); i++) {
        
        std::cout << "\n \n \n Going through sequence " << i + 1 << std::endl;
        
        for(unsigned int j(0); j<binding_sites.size(); j++) {
            sequence_list[i].find_sequence(binding_sites[j]);
        }
    }
    
    
    
    
    return 0;
}




//-------------------------------------------------------------------------



std::vector <Sequence>  Initialization() {
    std::string entry_name;		// This string will contain the name of the file we want to open.
    
    try {
        AskNameFasta(entry_name);
    }
    catch(std::string& err) {
        std::cerr <<"Error: " <<err <<std::endl;
        std:: cerr <<"Program stop. ";
        exit(1); // Stops the program.
    }
    
    std::vector <Sequence> sequence_list;
    
    std::vector <std::string> sequences(ExtractSequence(entry_name));
    for(size_t i(0); i<sequences.size(); ++i){
        Sequence seq(sequences[i]);
        sequence_list.push_back(seq);
    }
    
    return sequence_list;
}

void AskNameFasta(std::string& entry_name) {
    std::cout <<"Please give the name of your sequence file: ";
    std::cin >>entry_name;
    
    std::ifstream entry(entry_name.c_str());
    
    if (entry.fail()) {
        std::string error("Impossible to read the file:");
        error+=entry_name;
        throw error;
    }
    entry.close(); // Don't you have to close it afterwards?
    
    if(InvalidFormat(entry_name)) {
        throw std::string("Unknown format.");
    }
}

void AskNameMatrix(std::string& entry_name) {
    std::cout <<"Please give the name of your matrix file: ";
    std::cin >>entry_name;
    
    std::ifstream entry(entry_name.c_str());
    
    if (entry.fail()) {
        std::string error("Impossible to read the file: ");
        error+=entry_name;
        throw error;
    }
    entry.close(); // Don't you have to close it afterwards?

}


std::vector <std::string> ExtractSequence(std::string const& entry_name) {
    std::ifstream entry(entry_name.c_str());
    std::string line;
    
    std::vector <std::string> sequences; // That is the object that will be returned.
    
    std::string intermediate_value;
    
    // Reads lines
    while(getline(entry, line)){
        if(line.front()=='>'){
            sequences.push_back(intermediate_value);
            intermediate_value.clear(); }
        //else if(line.front()=='\n'){}
        else {
            
            // Makes DNA Sequence on line all uppercase, allowing for easier search afterwards
            for (auto & c: line) c = toupper(c);
            intermediate_value+=line;
        }
    }
    
    
    
    // Allow to register the last value even though there's no >...
    sequences.push_back(intermediate_value);
    
    // Deletes the first vector created, which is a ghost one. This is just a hack cobbled together, it'd probably be best to correct that in a better way at some point.
    sequences.erase(sequences.begin());
    
    
    // Testing the values by showing them
    /*for(size_t i(0); i<sequences.size(); ++i){
     std::cout <<sequences[i] <<'\n';
     }*/
    
    entry.close(); // Don't you have to close it afterwards?
    return sequences;
}

// Function that checks whether the file extension of the input filename is valid.
// Returns 1 if not valid, 0 if valid.
/*
 The creation of the list generates a compilation error unless flag -c++11, which I have not yet been able to solve
 */
bool InvalidFormat(std::string file_name) {
    
    // Defines list with known file formats
    static const std::vector<std::string> validValues {".fasta", ".fas", ".fna", ".ffn"};
    
    for(unsigned int i = 0; i < validValues.size(); i++) {
        if(file_name.find(validValues[i])!=std::string::npos)
            return 0;
        // Returns 0 if the file extension can be found
    }
    
    return 1;
}
