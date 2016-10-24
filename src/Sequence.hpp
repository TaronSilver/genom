#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <vector>



//std::vector<size_t> Find(const std::string& string_to_find, const std::vector<std::string>& genes, int sequence_in_gene); // find_sequence() returns a vector with all the starting positions of each occurences of the searched thing // souhailelaissaoui


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
     * @brief Finding where a given enyzme can attach itself to our sequence
     *
     * @param enzyme nucleotides
     * @return position(s) where the enzyme can attach itsefl to our sequence
     */
	std::vector<size_t> find_sequence(const std::string& string_to_find);
	

	
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
	
};




#endif
