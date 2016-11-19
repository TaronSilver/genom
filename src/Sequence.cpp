#include "Sequence.hpp"


Sequence::Sequence(const std::string new_sequence) :sequence(new_sequence) {
	std::cout <<"Creation of a new sequence: " << new_sequence << std::endl;
	AskBaseProb();
}


std::vector<size_t> Sequence::find_sequence(const std::string& string_to_find, std::ofstream& outputfile) // second loop Do for the inversed string and modified the "cout" (add the + or -)
{
    std::vector<size_t> starting_positions; //it's possible to have several matches in the sequence
    size_t starting_position(-1);
    std::string Translated_String(TranslateSeq(string_to_find));
    

    
    
    // std::cout << "SEARCHING '" << string_to_find << "' in the sequence"<< std::endl;
   
    do {
        starting_position = sequence.find(string_to_find, starting_position+1); //the function "find" returns the first position of the first character of the first match
        if(starting_position != std::string::npos)
        {
            starting_positions.push_back(starting_position);
            std::cout << string_to_find << " starting at char " << starting_position+1 <<" +"<< std::endl; //translated_string équivalent au binding spot
            outputfile << string_to_find << " starting at char " << starting_position+1 <<" +"<< std::endl;
        }
    } while (starting_position != std::string::npos);
    

     
    starting_position = -1;
    
    do {
        starting_position = sequence.find(Translated_String, starting_position+1); // second Do() to find the translated string position.
        if(starting_position != std::string::npos)
        {
            starting_positions.push_back(starting_position);
            std::cout << string_to_find << " starting at char " << starting_position+1  <<" -"<< std::endl; //string_to_find équivalent au binding spot
            outputfile << string_to_find << " starting at char " << starting_position+1  <<" -"<< std::endl; //string_to_find équivalent au binding spot

        }
    } while (starting_position != std::string::npos);
    
    /*
    std::cout << " SCAN FINISHED " << starting_positions.size() << " occurences found" << std::endl;
    */
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
	
	double countA, countC, countG, countT;
	double totCount;
	
	countA = get_nucleotide_count('A');
	countC = get_nucleotide_count('C');
	countG = get_nucleotide_count('G');
	countT = get_nucleotide_count('T');
	
	totCount = countA + countC + countG + countT;
	
	setBaseProbs(countA/totCount, countC/totCount, countG/totCount, countT/totCount);
}

std::string Sequence::TranslateSeq(const std::string& Seq) // Translate a sequence to its complementary sequence
{
    std::string RevSeq(Seq.length(), ' ');
    
    for(size_t i=0 ; i < Seq.length() ; i++)
    {
        switch (Seq[i])
        {
            case'A':
                RevSeq[i] = 'T';
                break;
                
            case'C':
                RevSeq[i] = 'G';
                break;
                
            case'G':
                RevSeq[i] = 'C';
                break;
                
            case'T':
                RevSeq[i] = 'A';
                break;
                
            default:
                std::cout<<"Error in the translation"<< std::endl;	
        }
    }

    std::string to_be_reversed(RevSeq);
    std::reverse(to_be_reversed.begin(),to_be_reversed.end());

    return to_be_reversed;
}

std::string Sequence::access_sequence_pos(unsigned int position, unsigned int length) {
    assert(sequence.size() > position);
    assert(sequence.size() >= position + length);
    return sequence.substr(position, length);
    
}

unsigned Sequence::get_nucleotide_count(const char N)
{
	unsigned counter(0);
	for (unsigned i=0; i< sequence.size(); ++i)
	{
		if (sequence[i] == N) 
		{
			counter += 1;
		}
	}
	return counter;
}


void Sequence::setBaseProbs(double baseProbA, double baseProbC, double baseProbG, double baseProbT) {
	baseProbabibilityA = baseProbA;
	baseProbabibilityC = baseProbC;
	baseProbabibilityG = baseProbG;
	baseProbabibilityT = baseProbT;
}

void Sequence::AskBaseProb() {
	
	int choice;
	
	std::cout<<"What base probability would you like to use for the log matrix?"<<std::endl;
	std::cout<<"Enter 1 to use a base probability of 0.25 for all nucleotides"<<std::endl;
	std::cout<<"Enter 2 to use base probabilities calculated from the input sequence"<<std::endl;
	std::cout<<"Enter 0 to use custom base probabilities"<<std::endl;
	
	std::cin>>choice;
	
	if (choice == 0) {
		double baseProbA, baseProbC, baseProbG, baseProbT;
		
		std::cout << "Enter the base probability for A ";
		std::cin >> baseProbA;
		
		std::cout << "Enter the base probability for C ";
		std::cin >> baseProbC;
		
		std::cout << "Enter the base probability for G ";
		std::cin >> baseProbG;
		
		std::cout << "Enter the base probability for A ";
		std::cin >> baseProbT;
		
		double check(baseProbA + baseProbC + baseProbG + baseProbT);
		
		if (check == 1) {
			setBaseProbs(baseProbA, baseProbC, baseProbG, baseProbT);
		} else {
			std::cout << "Base Probabilities need to add up to one" << std::endl;
			AskBaseProb();
		}
	}
	
	else if (choice == 1) {
		setBaseProbs(0.25, 0.25, 0.25, 0.25);
	}
	
	else if (choice == 2) {
		calc_BaseProb();
	}
	
	else {
		std::cerr << "Invalid input for base probability" << std::endl;
		AskBaseProb();
	}
}	

unsigned int Sequence::length() {
    return sequence.length();
}

