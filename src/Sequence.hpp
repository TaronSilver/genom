#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <vector>

//void Initialization();
//void AskName(std::string& entry_name);
//std::vector <std::string> ExtractSequence(std::string const& entry_name);
//bool InvalidFormat(std::string file_name);
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
     * @brief Allows to ask the name of the file we want to open,
     *		  with exception handling
     */
	void Initialization();
	
	/*!
     * @brief Allows to ask the name of the file we want to open,
     *		  with exception handling
     *
     * @param name of the file we want to open
     */
	void AskName(std::string& entry_name);
	
	/*!
     * @brief If all the conditions a correct reads te DNA sequence from
     *		  the file
     *
     * @param name of the file we want to open
     * @return Our DNA sequence
     */
	std::vector <std::string> ExtractSequence(std::string const& entry_name);
	
	/*!
     * @brief Checks if the file if valid
     *
     * @param name of the file we want to open
     * @return 0 if format is valid of 1 if not
     */
	bool InvalidFormat(std::string file_name);
	
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
	
	private:
	double baseProbabibilityA;
	double baseProbabibilityC;
	double baseProbabibilityG;
	double baseProbabibilityT;
	
	const std::string sequence;
	
};

#endif
