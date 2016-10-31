#include "utility.hpp"

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
