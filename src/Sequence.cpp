#include "Sequence.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

Sequence::Sequence(const std::string new_sequence)
:sequence(new_sequence)
{
	std::cout <<"Creation of a new sequence: " << new_sequence <<std::endl;
    calc_BaseProb();
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
	std::cout << " SCAN FINISHED " << starting_positions.size() << " occurrences found" << std::endl;
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

// Modified, such that every baseProb is .25, for the moment.

void Sequence::calc_BaseProb() {
	double size_seq(sequence.size());
	
    baseProbabibilityA = .25;
    baseProbabibilityC = .25;
    baseProbabibilityG = .25;
    baseProbabibilityT = .25;
    
    /*
	baseProbabibilityA = (static_cast<double>(find_sequence("A").size()))/size_seq; // division entiere ??????
	baseProbabibilityC = (static_cast<double>(find_sequence("C").size()))/size_seq; // division entiere ??????
	baseProbabibilityG = (static_cast<double>(find_sequence("G").size()))/size_seq; // division entiere ??????
	baseProbabibilityT = (static_cast<double>(find_sequence("T").size()))/size_seq; // division entiere ??????
     */

}
