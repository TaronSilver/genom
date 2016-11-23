#include "Sequence.hpp"
#include "user_interaction.hpp"

Sequence::Sequence(const std::string new_sequence) :sequence(new_sequence)
{
	/*
	std::cout <<"Creation of a new sequence: " << new_sequence << std::endl;
	*/
	Cout_NewSeq(new_sequence);
	AskBaseProb();
}


std::vector<Seq_and_pos> Sequence::find_sequence(const std::string& string_to_find, std::ofstream& outputfile) // second loop Do for the inversed string and modified the "cout" (add the + or -)
{
    std::vector<Seq_and_pos> seq_and_positions; //it's possible to have several matches in the sequence
    ///
    size_t starting_position(-1);
    std::string Translated_String(TranslateSeq(string_to_find));


    // std::cout << "SEARCHING '" << string_to_find << "' in the sequence"<< std::endl;

    do {
        starting_position = sequence.find(string_to_find, starting_position+1); //the function "find" returns the first position of the first character of the first match
        if(starting_position != std::string::npos)
        {
            struct Seq_and_pos found_element;

            found_element.sequence = string_to_find;
            found_element.position = starting_position;

            seq_and_positions.push_back(found_element);
            outputfile << found_element.sequence << " starting at char " << found_element.position +1 <<" +"<< std::endl;//translated_string équivalent au binding spot
        }
    } while (starting_position != std::string::npos);



    starting_position = -1;

    do {
        starting_position = sequence.find(Translated_String, starting_position+1); // second Do() to find the translated string position.
        if(starting_position != std::string::npos)
        {
            struct Seq_and_pos found_element;

            found_element.sequence = string_to_find;
            found_element.position = starting_position;

            seq_and_positions.push_back(found_element);
            outputfile << found_element.sequence << " starting at char " << found_element.position +1  <<" -"<< std::endl; //string_to_find équivalent au binding spot

        }
    } while (starting_position != std::string::npos);

    /*
    std::cout << " SCAN FINISHED " << starting_positions.size() << " occurences found" << std::endl;
    */
    return seq_and_positions;

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
	/*
	int choice;

	std::cout<<"What base probability would you like to use for the log matrix?"<<std::endl;
	std::cout<<"Enter 1 to use a base probability of 0.25 for all nucleotides"<<std::endl;
	std::cout<<"Enter 2 to use base probabilities calculated from the input sequence"<<std::endl;
	std::cout<<"Enter 0 to use custom base probabilities"<<std::endl;

	std::cin>>choice;
	*/
	int choice = CoutCin_AskBaseProb();

	if (choice == 0) {
		/*double baseProbA, baseProbC, baseProbG, baseProbT;*/

		std::vector<double> BaseProbs ={0.0,0.0,0.0,0.0};
		std::vector<char> Base ={'A','C','G','T'};
		/*
		std::cout << "Enter the base probability for A ";
		std::cin >> baseProbA;

		std::cout << "Enter the base probability for C ";
		std::cin >> baseProbC;

		std::cout << "Enter the base probability for G ";
		std::cin >> baseProbG;

		std::cout << "Enter the base probability for T ";
		std::cin >> baseProbT;
		*/
		for(size_t i=0; i<Base.size(); ++i)
		{
			BaseProbs[i] = CoutCin_AskBaseProb0(Base[i]);

		}
		setBaseProbs(BaseProbs[0], BaseProbs[1], BaseProbs[2], BaseProbs[3]);
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
