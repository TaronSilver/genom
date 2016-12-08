#include <QMessageBox>

#include "askBaseProb.hpp"
#include "matrixFromSequence.hpp"
#include "resultsWindow.hpp"
#include "sequenceFromMatrix.hpp"
#include "user_interaction.hpp"
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
std::string ask_name_fasta() {
    return Window::getFastaLocation();
}



//-------------------------------------------------------------------------
// There's a better function for this

std::string ask_name_matrix() {
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
    return Window::getOutputName();
}

//----------------------------------------------------------------------
void Cout_NewSeq(std::string new_sequence)
{
    std::cout <<"Creation of a new sequence: " << new_sequence << std::endl;
}

//----------------------------------------------------------------------
BP_FILL CoutCin_AskBaseProb() {
    int choice = askBaseProb::getBaseChoiceFinal();

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
        }
        return BP_FILL::AllEqual;
}
//----------------------------------------------------------------------
double CoutCin_AskBaseProb0(char C) {
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
    unsigned int answer=askBaseProb::getMatrixChoice();

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
        return MATRIX_TYPE::logMatrix;
}


//----------------------------------------------------------------------

bool ask_matrix_from_sequences_weighed() {
    return sequenceFromMatrix::isEM();
}


//----------------------------------------------------------------------

bool ask_matrix_from_search_matches() {
    return  sequenceFromMatrix::getBool();
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

//----------------------------------------------------------------------

std::string ask_coordinate_filename() {
    std::string answer;
    std::cout << "What file would you like to open for the genomic coordinates." << std::endl;
    std::cin >> answer;
    return answer;
}


//----------------------------------------------------------------------

bool ask_line_description_present() {
    bool answer;
    std::cout << "Is a descritpion of the coordinates present in the third question?" << std::endl;

    while (not(std::cin >> answer)) {
        std::cout << "Error: Invalid input. Please try again." << std::endl;
    }
    return answer;
}


//----------------------------------------------------------------------

Association_Table associate_genomic_with_sequences(std::vector<std::string> coordinate_description,
                                                   std::vector<std::string> sequence_description) {
    Association_Table output;
    unsigned int coord_intermed;
    unsigned int seq_intermed;
    unsigned int startpos_intermed;

    if (coordinate_description.size() == 1 and sequence_description.size() == 1) {
        while (true) {
            std::cout << "At what position of the genomic coordinates does the sequence " <<
            std::endl << "start?" << std::endl;

            if (std::cin >> startpos_intermed) {
                break;
            }
            std::cout << "Error, please try again." << std::endl;

        }
        return {{0, 0, startpos_intermed}};
    }

    std::cout << "The following coordinates could be found in the given files: " << std::endl;
    for (unsigned int id(0); id<coordinate_description.size(); id++) {
        std::cout << "No. "<< id+1 << "\t" << coordinate_description[id] << std::endl;
    }

    std::cout << "The following sequences could be found in the given files: " << std::endl;
    for (unsigned int id(0); id<sequence_description.size(); id++) {
        std::cout << "No. "<< id+1 << "\t" << sequence_description[id] << std::endl;
    }

    if (coordinate_description.size() == sequence_description.size()) {
        bool answer;
        std::cout << "You have as many sequences as genomic coordinates. Would you like to " <<
        std::endl << "analyze them in order?" <<
        std::endl << "Enter 1 for yes, 0 for no." <<
        std::endl;
        std::cin >> answer;
        if (answer) {
            std::cout << "For each sequence, enter its starting position in the genomic " <<
            std::endl << "coordinates. " <<
            std::endl;
            for (unsigned int id(0); id<coordinate_description.size(); id++) {
                while (not(std::cin >> startpos_intermed)) {
                    std::cout << "Error for position " << id << ". Please try again." << std::endl;
                }
                output.push_back({id, id, startpos_intermed});
            }
            return output;
        }
    }

    std::cout << "Which sequences would you like to analyze with which sequences?" <<
    std::endl << "Associate sequences with genomic coordinates by entering first the " <<
    std::endl << "number of the sequence and then the number of the genomic coordinates." <<
    std::endl << "You can combine them any way you'd like. " <<
    std::endl << "As a third value, give the starting position of the sequence in the " <<
    std::endl << "genomic coordinates." <<
    std::endl << "As soon as you are done, enter 0." <<
    std::endl;

    while (true) {
        if(not(std::cin >> seq_intermed >> coord_intermed >> startpos_intermed)) {
            std::cout << "Error, please try again. " << std::endl;
        }
        else if(seq_intermed == 0 or coord_intermed == 0)
            break;
        else {
            output.push_back({coord_intermed-1, seq_intermed-1});
        }
    }
    return output;


}

//----------------------------------------------------------------------
void error_sequence_doesnt_exist() {
    std::cout << "Error: The desired sequence doesn't exist" << std::endl;
}


//----------------------------------------------------------------------

SEQ_SOURCE ask_source_sequence() {
    std::cout << "How would you like to obtain the binding sequences to analyze?" <<
    std::endl << "Enter 1 if you have the binding sequences seperately in a fasta file." <<
    std::endl << "Enter 2 if you have a file with genomic coordinates of the sequences." <<
    std::endl << "Enter 3 if you want to analyze the result of a previous analysis." <<
    std::endl;

    unsigned int answer(0);
    while (true) {
        std::cin >> answer;

        switch (answer) {
            case 1:
                return SEQ_SOURCE::OnlySeq;

            case 2:
                return SEQ_SOURCE::CoordAndSeq;

            case 3:
                return SEQ_SOURCE::FromSearchResult;

            default:
                std::cout << "Invalid input, please try again." << std::endl;
                break;

        }
    }
}

//-----------------------------------------------------------------------
// 							LOGO USER INTERACTION
//-----------------------------------------------------------------------

void logo_in_process()
{
  
}

std::string ask_logo_matrix()
{
  return Window::getMatrixLocation();
}

//-----------------------------------------------------------------------
