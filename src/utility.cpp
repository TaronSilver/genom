#include "utility.hpp"

/// Program starting
//-------------------------------------------------------------------------


PROCEDURE whatToDo() {
    // system("Clear");
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


/// Matrix reading
//-------------------------------------------------------------------------


void AskNameMatrix(std::string& entry_name)
{
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
//-------------------------------------------------------------------------



///Sequence
//-------------------------------------------------------------------------



std::vector <Sequence> Initialization()
{
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

void AskNameFasta(std::string& entry_name)
{
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

std::vector <std::string> ExtractSequence(std::string const& entry_name)
{
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

std::vector <double> nucleotide_probability(
    std::vector <std::string> nucleotide_sequences,
    unsigned int position
) {
    
    std::vector <unsigned int> nucleotide_counter(4, 0);
    std::vector <double> probabilities(4, 0);
    // std::array <unsigned int, 4> nucleotide_counter = {0,0,0,0};
    // std::array <double, 4> probabilities;
    
    unsigned int number_sequences(nucleotide_sequences.size());
    
    
    assert(number_sequences>0);
    
    for (unsigned int i(0); i<number_sequences; i++) {
        switch (nucleotide_sequences[i][position]) {
            case 'A':
                nucleotide_counter[0]++;
                break;
            case 'C':
                nucleotide_counter[1]++;
                break;
            case 'G':
                nucleotide_counter[2]++;
                break;
            case 'T':
                nucleotide_counter[3]++;
                break;
            default:
                std::cout << "WARNING, nucleotide " << nucleotide_sequences[i][position]
                          << " not recognized" << std::endl;
                return {0,0,0,0};
                // Better error handling needed!!
        }
    }
    
    for (unsigned int i(0); i < 4; i++) {
        probabilities[i] = (double)nucleotide_counter[i] / (double)number_sequences;
    }
    return probabilities;
}


Matrix_Neo generate_PWM_from_Seq_list(std::vector <Sequence> sequence_list) {
    Matrix_Neo probability_matrix;
    std::vector <std::string> binding_sequences;
    
    unsigned int position;
    unsigned int length;
    unsigned int number_sequences(sequence_list.size());
    
    while (true) {
        std::cout << "At what position is the binding site (starts at 1)?" << std::endl;
        std::cin >> position;
        std::cout << "How long is the binding site?" << std::endl;
        std::cin >> length;
        
        if(position <= 0) {
            std::cout << "Error, binding position must be positive" << std::endl;
        }
        else if(length <= 0) {
            std::cout << "Error, binding site length must be positive" << std::endl;
        }
        else {
            break;
        }
    }
    
    for (unsigned int i(0); i < number_sequences; i++) {
        binding_sequences.push_back(
                                    sequence_list[i].access_sequence_pos(
                                                                         position-1,
                                                                         length
                                                                         )
                                    );
    }
    // Goes through all sequences, extracts binding sites and
    // stores them in vector binding_sequences
    

    for(unsigned int i(0); i < length; i++) {
        probability_matrix.push_back(nucleotide_probability(binding_sequences, i));
    }
    // Goes through every position and calculates probabilities at that position
    
    
    /* FOR TESTING
    for(int i(0); i < probability_matrix.size(); i++) {
        for(int j(0); j < 4; j++) {
            std::cout << probability_matrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
     */
    
    return probability_matrix;
}



