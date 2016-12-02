#include "user_interaction.hpp"

#include "matrixFromSequence.hpp"
#include "sequenceFromMatrix.hpp"
#include "resultsWindow.hpp"
#include "saveSequence.hpp"
#include "window.hpp"


//-----------------------------------------------------------------------
double ask_cutoff() {
    return sequenceFromMatrix::getCutoff();
}


//-----------------------------------------------------------------------

bool ask_binding_length_known() {
    return matrixFromSequence::getBool();
}


//-----------------------------------------------------------------------

unsigned int ask_position() {
    return matrixFromSequence::getPosition();
}

//-----------------------------------------------------------------------

unsigned int ask_length() {
    return matrixFromSequence::getLength();
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
    outputfile.open(filename, std::ios_base::app);
    unsigned int size = results.searchResults.size();

    outputfile << results.description << std::endl;
    std::cout << "HELLO" << std::endl;
    
    for (unsigned int i(0); i < size; i++) {
        outputfile << results.searchResults[i].sequence << " found at position "
                   << results.searchResults[i].position +1 << " in "
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
    return matrixFromSequence::getBaseChoiceFinal();
}

//----------------------------------------------------------------------
double CoutCin_AskBaseProb0(char C)
{
	double baseProb;

	std::cout << "Enter the base probability for "<< C ;
	std::cin >> baseProb;

	return baseProb;
}


std::string Ask_Outputfile_Name(){
    return "../"+Window::getOutputName();
}
