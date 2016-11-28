//
//  user_interaction.cpp
//
//
//  Created by Mättu on 15.11.16.
//
//

#include "user_interaction.hpp"

#include "askBaseProbability.hpp"
#include "askBool.hpp"
#include "askDouble.hpp"
#include "askPosAndLength.hpp"
#include "resultsWindow.hpp"
#include "saveMatrix.hpp"
#include "saveSequence.hpp"
#include "window.hpp"


//-----------------------------------------------------------------------
double ask_cutoff() {
    askDouble window;
    window.show();
    window.exec();

    return window.getDouble();
}


//-----------------------------------------------------------------------

bool ask_binding_length_known() {
    askBool question;
    question.show();
    question.exec();

    return question.getBool();
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
    return Window::getFastaLocation();
}



//-------------------------------------------------------------------------
// There's a better function for this

std::string ask_name_matrix()
{
    return Window::getMatrixLocation();
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
    outputfile.open(filename);
    unsigned int size = results.searchResults.size();

    outputfile << results.description << std::endl;


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
