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
BP_FILL CoutCin_AskBaseProb()
{
	int choice;
	
    while (true) {
        std::cout << "What would you like to use as the base probabilities for each type of nucleotide in your sequence? " <<
        std::endl << "The base probabilities are used to normalize the logarithmic probability weight matrix. " <<
        std::endl << "Enter 0 to not use any base probabilities"<<
        std::endl << "Enter 1 to use a base probability of 0.25 for all nucleotides"<<
        std::endl << "Enter 2 to use custom base probabilities" <<
        //   std::endl << "Enter 3 to use base probabilities calculated from the input sequence" <<

        std::endl;
        
        std::cin>>choice;
        
        switch (choice) {
            case 2:
                return BP_FILL::UserDefined;
                
            case 1:
                return BP_FILL::AllEqual;
                
            case 0:
                return BP_FILL::NotUsed;

        /*
            case 3:
                return BP_FILL::FromSequence;
        */
                
            default:
                std::cout << "Invalid input, try again. " << std::endl;
        }
        
    }
    
}
//----------------------------------------------------------------------
double CoutCin_AskBaseProb0(char C)
{
	double baseProb;
	
    while (true) {
        std::cout << "Enter the base probability for "<< C ;
        std::cin >> baseProb;

        if(baseProb < 0 || baseProb > 1) {
            std::cout << "Invalid value for base probability. All values "
            << std::endl << "for base probabilities must be between 0 and 1 "
            << std::endl << "and must add up to one."
            << std::endl << "Please try again." << std::endl;
        }
        else
            return baseProb;
    }
	
	return baseProb;
}
//----------------------------------------------------------------------


std::vector<double> AskBaseProb()
{
    switch (CoutCin_AskBaseProb()) {
        case UserDefined:
            return User_Defined_Base_Prob();
            
        case AllEqual:
            return {0.25, 0.25, 0.25, 0.25};

        default:
            return {1, 1, 1, 1};
    }
}



//----------------------------------------------------------------------


std::vector<double> User_Defined_Base_Prob() {
    double A, C, G, T;
    std::vector<double> base_probabilities;
    while(true) {
        
        A = CoutCin_AskBaseProb0('A');
        C = CoutCin_AskBaseProb0('C');
        G = CoutCin_AskBaseProb0('G');
        
        T = 1 - A - C - G;
        
        std::cout << "The value for T is automatically set to " << T << std::endl;
        if(T < 0 || T > 1) {
            std::cout << "Invalid inputs for the base probabilities. " << std::endl
            << "The base probabilities must add up to 1. The sum of the inserted " << std::endl
            << "base probabilities must therefore be smaller than 1." << std::endl;
        }
        else
            return {A, C, G, T};
        
    }

}


//----------------------------------------------------------------------

MATRIX_TYPE Ask_Return_Matrix_Type() {
    unsigned int answer;
    
    while (true) {
        std::cout << "As what kind of matrix do you want to save your matrix as?" <<
        std::endl << "Enter 1 to save as a probability matrix." <<
        std::endl << "Enter 2 to save as a weighted probability matrix." <<
        std::endl << "Enter 3 to save as a logarithmic matrix." <<
        std::endl << "Enter 4 to save as a weighted logarithmic matrix." <<
        std::endl;
        
        std::cin >> answer;
        
        switch (answer) {
            case 1:
                return MATRIX_TYPE::absoluteMatrix;
            case 2:
                return MATRIX_TYPE::relativeMatrix;
            case 3:
                return MATRIX_TYPE::logMatrix;
            case 4:
                return MATRIX_TYPE::logConstMatrix;
        }
        
        std::cout << "Invalid input. Please try again. " << std::endl;
    }
}


//----------------------------------------------------------------------

bool ask_matrix_from_sequences_weighed() {
    bool answer;
    std::cout << "Would you like to weigh each probability by its score " <<
    std::endl << "in order to calculate the probability weight matrix?" <<
    std::endl << "Enter 1 for yes, 0 for no." <<
    std::endl;
    
    std::cin >> answer;
    
    std::cout << "You answered ";
    switch (answer) {
        case true:
            std::cout <<"YES";
            break;
            
        default:
            std::cout <<"NO";
            break;
    }
    std::cout << std::endl;
    return answer;
}


//----------------------------------------------------------------------

bool ask_matrix_from_search_matches() {
    bool answer;
    std::cout << "Would you like to create a new matrix based on the search matches?" <<
    std::endl << "Enter 1 for yes, 0 for no." <<
    std::endl;
    
    std::cin >> answer;
    
    std::cout << "You answered ";
    switch (answer) {
        case true:
            std::cout <<"YES";
            break;
            
        default:
            std::cout <<"NO";
            break;
    }
    std::cout << std::endl;
    return answer;
}


//----------------------------------------------------------------------

void error_input_sequence() {
    std::cout << "Error: Either there was no sequence found to analyze, or the " <<
    std::endl << "sequences to analyze are of different length." << std::endl;
}


//----------------------------------------------------------------------

void error_reading_coordiates(unsigned int line) {
    std::cout << "Error: Reading genomic coordinate files failed on line " << line <<
    std::endl;
}


std::string ask_coordinate_filename() {
    std::string answer;
    std::cout << "What file would you like to open for the genomic coordinates." << std::endl;
    std::cin >> answer;
    return answer;
}

