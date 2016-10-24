#include "Sequence.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

Sequence::Sequence(const std::string sequence_)
:sequence(sequence_)
{
	std::cout <<"Création d'une nouvelle séquence: " <<sequence <<std::endl;
	}

void  Initialization() {
    std::string entry_name;		// This string will contain the name of the file we want to open.
    
    try {
        AskName(entry_name); 
	}
    catch(std::string& err) {
        std::cerr <<"Error: " <<err <<std::endl;
       std:: cerr <<"Program stop. ";
        exit(1); // Stops the program.
	}
    
   std::vector <std::string> sequences(ExtractSequence(entry_name)); 
   for(size_t i(0); i<sequences.size(); ++i){
	   Sequence seq(sequences[i]);
   }
}

void AskName(std::string& entry_name) {
    std::cout <<"Please give the name of your data file: ";
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

std::vector <std::string> ExtractSequence(std::string const entry_name) {
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

std::vector<size_t> Sequence::find_sequence(const std::string& string_to_find) 
		{
			std::vector<size_t> starting_positions; //it's possible to have several matches in the sequence
			size_t starting_position(-1);
			std::cout << "SEARCHING '" << string_to_find << "' in the sequence" << std::endl; 
			do {
					starting_position = sequence.find(string_to_find, starting_position+1); //the function "find" returns the first position of the first character of the first match
					if(starting_position != std::string::npos)
					{
						starting_positions.push_back(starting_position);
						std::cout << starting_positions.size() << " FOUND starting at char " << starting_position << std::endl;
					}
				} while (starting_position != std::string::npos);
			std::cout << " SCAN FINISHED " << starting_positions.size() << " occurences found" << std::endl;
			return starting_positions;
		}

std::vector<double> Sequence::get_probabilities()
{
	std::vector<double> result;
	result.push_back(baseProbabibilityA);
	result.push_back(baseProbabibilityC);
	result.push_back(baseProbabibilityG);
	result.push_back(baseProbabibilityT);
	
	return result;
}

void Sequence::calc_BaseProb() {
	double size_seq(sequence.size());
	
	baseProbabibilityA = (static_cast<double>(find_sequence("A").size()))/size_seq;	// division entiere ??????
	baseProbabibilityT = (static_cast<double>(find_sequence("T").size()))/size_seq;	// division entiere ??????
	baseProbabibilityC = (static_cast<double>(find_sequence("C").size()))/size_seq;	// division entiere ??????
	baseProbabibilityG = (static_cast<double>(find_sequence("G").size()))/size_seq;	// division entiere ??????
	
}

