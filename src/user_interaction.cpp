//
//  user_interaction.cpp
//  
//
//  Created by Mättu on 15.11.16.
//
//

#include "user_interaction.hpp"



//-----------------------------------------------------------------------

PROCEDURE whatToDo() {
    
    system("Clear");
    PROCEDURE whatToDo;
    unsigned int answer;
    
    std::cout << "Welcome to our program. What would you like to do? \n";
    std::cout << "Enter 1 to obtain a probability weight matrix from multiple" << std::endl
    << "sequences." << std::endl;
    std::cout << "Enter 2 to obtain all binding positions of a protein from a " << std::endl
    << "probability matrix on a given nucleotide sequence." << std::endl;
    std::cout << "Enter 0 to exit the program." << std::endl;
    
    while (true) {
        std::cin >> answer;
        
        if (answer == 1) {
            whatToDo = MatrixFromSequences;
            break;
        }
        else if (answer == 2) {
            whatToDo = SequencesFromMatrix;
            break;
        }
        else if (answer == 0) {
            whatToDo = Exit;
            break;
        }
        else {
            std::cout << "Unrecognized input. Please try again." << std::endl;
        }
    }
    
    return whatToDo;
    
}


//-----------------------------------------------------------------------
double ask_cutoff() {
    double cutoff;
    std::cout << "What cutoff would you like to use?" << std::endl;
    std::cin >> cutoff;
    return cutoff;
}


//-----------------------------------------------------------------------
std::string ask_name_fasta()
{
    std::string entry_name;
    
    while (true) {
        std::cout <<"Please give the name of your sequence file: ";
        std::cin >> entry_name;
        
        std::ifstream entry(entry_name.c_str());
        
        if (entry.fail()) {
            std::cout << "Impossible to read the file, please try again. " << std::endl;
            continue;
        }
        
        if(InvalidFormat(entry_name)) {
            std::cout << "Unknown file format, please try again. " << std::endl;
            continue;
        }
        
        entry.close();
        break;
    }
    
    return entry_name;
}



//-------------------------------------------------------------------------


std::string ask_name_matrix()
{
    std::string entry_name;
    std::cout <<"Please give the name of your matrix file: ";
    std::cin >> entry_name;

    std::ifstream entry(entry_name.c_str());

    
    if (entry.fail()) {
        std::string error("Impossible to read the file: ");
        error+=entry_name;
        throw error;
    }
    entry.close(); // Don't you have to close it afterwards?
    return entry_name;
}
//-------------------------------------------------------------------------


//-----------------------------------------------------------------------
bool InvalidFormat(std::string file_name)
{
    
    // Defines list with known file formats
    static const std::vector<std::string> validValues {".fasta", ".fas", ".fna", ".ffn"};
    
    for(unsigned int i = 0; i < validValues.size(); i++) {
        if(file_name.find(validValues[i])!=std::string::npos)
            return 0;
        // Returns 0 if the file extension can be found
    }
    
    return 1;
}
