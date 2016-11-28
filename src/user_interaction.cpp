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

unsigned int ask_position() {
    
	unsigned int position;

	while (true) {   
	    std::cout << "At what position is the binding site (starts at 1)?";
	    std::cin >> position;
	    
	    if (position <= 0) {
			std::cout << "Position must be positive" << std::endl;
			continue;
		}
		
		break;
	}
    
    return position;
    
}

//-----------------------------------------------------------------------

unsigned int ask_length() {
    
    unsigned int length;
    while (true) {  
	    std::cout << "How long is the enzyme binding site? ";
	    std::cin >> length;
	    
	    if (length <= 0) {
			std::cout << "Lenght must be positive" << std::endl;
			continue;
		}
		
		break;
	}
	    
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
    
    while (true) {
	    std::cout <<"Please give the name of your matrix file: ";
	    std::cin >> entry_name;
	    
	    std::ifstream entry(entry_name.c_str());
	
	    
	    if (entry.fail()) {
	        std::cout << "Impossible to read the file, please try again." << std::endl;
	        continue;
	    }
	    
	    if (InvalidFormatMat(entry_name)) {
			std::cout << "Unknown file format, please try again." << std::endl;
			continue;
		}
	    
	    entry.close();
	    break;
	}

    return entry_name;
}
//-------------------------------------------------------------------------

bool InvalidFormatMat(std::string file_name)
{
	if (file_name.find(".mat") != std::string::npos)
	{
		return 0;
	}
	else return 1;
}

//-----------------------------------------------------------------------
bool InvalidFormat(std::string file_name)
{
    
    // Defines list with known file formats
    static const std::vector<std::string> validValues {".fasta", ".fas", ".fna", ".ffn"};
    
    for(unsigned int i = 0; i < validValues.size(); i++) {
        if(file_name.find(validValues[i])!= std::string::npos)
            return 0;
        // Returns 0 if the file extension can be found
    }
    
    return 1;
}
//-----------------------------------------------------------------------
void nucleotide_warning(char c)
{
	std::cout << "WARNING, nucleotide " << c
                          << " not recognized" << std::endl;
}

//-----------------------------------------------------------------------
void print_progress(int position, int filesize) {
    
    static int nextPrint(0);
    static int increment(filesize/1000000);
    
    if(position >= nextPrint) {
        
        std::cout << (double)position / (double)filesize * 100 << "%" << std::endl;
        nextPrint += increment;
    }
}


//==========================================================================================
void print_results(SearchResults results, std::string filename) {
    std::ofstream outputfile;
    outputfile.open(filename, std::ios_base::app);
    unsigned int size = results.searchResults.size();
    
    outputfile << results.description << std::endl;
    std::cout << "HELLO" << std::endl;
    
    for (unsigned int i(0); i < size; i++) {
        outputfile << results.searchResults[i].sequence << " found at position "
                   << results.searchResults[i].position << " in "
                   << results.searchResults[i].direction << " direction with the score "
                   << results.searchResults[i].score << std::endl;
    }
    outputfile.close();
}


//==========================================================================================
void print_results(SearchResults results) {
    unsigned int size = results.searchResults.size();
    
    std::cout << results.description << std::endl;
    
    
    for (unsigned int i(0); i < size; i++) {
        std::cout << results.searchResults[i].sequence << " found at position "
                << results.searchResults[i].position << " in "
                << results.searchResults[i].direction << " direction with the score "
                << results.searchResults[i].score << std::endl;
    }
}

//==========================================================================================
std::string Ask_Outputfile_Name() {
	std::string filename;
	
	std::cout <<"What would you like to call your outpufile?"<< std::endl;
	std::cin>>filename;
	
	return filename; 
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
