#include "Sequence.hpp"


Sequence::Sequence(const std::string new_sequence)
:sequence(new_sequence)
{
	// std::cout <<"Creation of a new sequence: " << new_sequence <<std::endl;
    calc_BaseProb();
}


std::vector<size_t> Sequence::find_sequence(const std::string& string_to_find) // second loop Do for the inversed string and modified the "cout" (add the + or -)
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
            std::cout << Translated_String << " starting at char " << starting_position <<" +"<< std::endl; //translated_string équivalent au binding spot
        }
    } while (starting_position != std::string::npos);
    

    return starting_positions;
    
    /*
     Doesnt work yet
     
    starting_position = -1;
    
    do {
        starting_position = sequence.length()-sequence.find(Translated_String, starting_position+1)-Translated_String.length(); // second Do() to find the translated string position(total length - the position - the length of the string. because the complementary is inverted)
        if(starting_position != std::string::npos)
        {
            starting_positions.push_back(starting_position);
            std::cout << string_to_find << " starting at char " << starting_position <<" -"<< std::endl; //string_to_find équivalent au binding spot
        }
    } while (starting_position != std::string::npos);
    
    
    std::cout << " SCAN FINISHED " << starting_positions.size() << " occurences found" << std::endl;
    return starting_positions;
    */
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

std::string Sequence::TranslateSeq(const std::string& Seq) // Translate a sequence to its complementary sequence
{
    std::string RevSeq(Seq.length(), ' ');
    
    for(int i=0 ; i < Seq.length() ; i++)
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
    
    return RevSeq;
}

std::string Sequence::access_sequence_pos(unsigned int position, unsigned int length) {
    assert(sequence.size() > position);
    assert(sequence.size() > position + length);
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

