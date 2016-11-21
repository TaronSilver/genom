#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include <list>


//std::vector<size_t> Find(const std::string& string_to_find, const std::vector<std::string>& genes, int sequence_in_gene); // find_sequence() returns a vector with all the starting positions of each occurences of the searched thing // souhailelaissaoui

struct Seq_and_pos {
	std::string sequence;
	unsigned int position;
};

class Sequence
{
	public:
	/*!
     * @brief Constructor
     */
	Sequence(const std::string sequence);
	
	/*!
     * @brief Getter for exterior acces 
     * 
     * @return vector of probabilities
     */
	std::vector<double> get_probabilities();
	
	/*!
     * @brief Finding where a given enyzme can attach itself to our sequence, saves result in
     *        file specified in outputfile
     * @param enzyme nucleotides, outputfile
     * @return position(s) where the enzyme can attach itsefl to our sequence
     */
    std::vector<Seq_and_pos> find_sequence(const std::string& string_to_find, std::ofstream& outputfile);
	

    
    /*!
     * @brief Returns the nucleotide sequence of a specified length at a specified position
     *
     * @param The starting position, the length of the sequence to extract
     * @return string containing the desired sequence
     */
    std::string access_sequence_pos(unsigned int position, unsigned int length);
    
    
    /*!
     * @brief Returns the length of the sequence
     *
     * @param The starting position, the length of the sequence to extract
     * @return unsinged int containing sequence length
     */
    unsigned int length();
    
	
	/*!
     * @brief DESCRIPTION OF FUNCTION
     *
     * @param INPUT 
     * @return 
     */
	//std::vector<size_t> Find(const std::string& string_to_find, 
	//const std::vector<std::string>& genes, int sequence_in_gene); // find_sequence() returns a vector with all the starting positions of each occurences of the searched thing // souhailelaissaoui
	
	/*!
     * @brief Calculates the probability of each nucleotide A,C,G and T
     *        in our sequence
     */
	void calc_BaseProb();
	
    /* BRIEF...*/
    std::string TranslateSeq(const std::string& Seq); //function that translate a sequence.
    
    
	private:
	double baseProbabibilityA;
	double baseProbabibilityC;
	double baseProbabibilityG;
	double baseProbabibilityT;
	
	const std::string sequence;
	
	/*!
     * @brief counts number of given nucleotides in the sequence
     *
     * @param nucleotide (A, C, G, T) 
     * @return number of times it appears
     */
	unsigned get_nucleotide_count(const char N);
	
	/*!
     * @brief sets probabilities to correct values
     *
     * @param base probabilities for nucleotides A, C, G and T
     */
	void setBaseProbs(double baseProbA, double baseProbC, double baseProbG, double baseProbT);

	/*!
     * @brief asks user what base probability to used and implements choice
     */
	void AskBaseProb();
	
};





#endif
