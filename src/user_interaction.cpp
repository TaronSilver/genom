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

bool ask_binding_length_known() {
    bool known;
    std::cout << "Do you know the length of the enzyme binding site? " << std::endl
              << "enter 1 for yes, 0 for no. ";
    std::cin >> known;
    return known;
}



//-----------------------------------------------------------------------

unsigned int ask_length() {
    
    unsigned int length;
    std::cout << "How long is the enzyme binding site? ";
    std::cin >> length;
    return length;
    
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
// There's a better function for this

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
//----------------------------------------------------------------------
void Cout_NewSeq(std::string new_sequence)
{
	std::cout <<"Creation of a new sequence: " << new_sequence << std::endl;
}
//----------------------------------------------------------------------
int CoutCin_AskBaseProb()
{
	int choice;
	
	std::cout<<"What base probability would you like to use for the log matrix?"<<std::endl;
	std::cout<<"Enter 1 to use a base probability of 0.25 for all nucleotides"<<std::endl;
	std::cout<<"Enter 2 to use base probabilities calculated from the input sequence"<<std::endl;
	std::cout<<"Enter 0 to use custom base probabilities"<<std::endl;
	
	std::cin>>choice;
	
	return choice;	
}
//----------------------------------------------------------------------
double CoutCin_AskBaseProb0(char C)
{
	double baseProb;
	
	std::cout << "Enter the base probability for "<< C ;
	std::cin >> baseProb;
	
	return baseProb;
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
