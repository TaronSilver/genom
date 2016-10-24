#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <vector>

/*!
 * @class Sequence
 *
 * @brief The Sequence class allows the manipulation of sequences we can extract from fasta files.
 */


/*!
     * @brief The Initialization function asks the name of the file we want to open and does an exception handling in the case the file couldnt be found. 
     * If the file could be found, it will create sequence objects that we will then be able to use.
     */
void Initialization();

/*!
     * @brief This function is the one actually asking the name and throwing an error message in case of problem.
     * It also calls the InvalidFormat to verify the file format.
     *
     * @param This string stores the name of the file. 
     */
void AskName(std::string& entry_name);

/*!
     * @brief This function takes the strings from the file we want to open and stores them in a vector.
     *
     * @param The file's name. 
     * @return A vector containing all strings of interest present in the file. It doesnt store the line following a '>' and ignore backspaces.
     */
std::vector <std::string> ExtractSequence(std::string const entry_name);

	/*!
     * @brief Controls if the file is of a correct, "known", type.
     * Accepted types are ".fasta", ".fas", ".fna", ".ffn".
     */
bool InvalidFormat(std::string file_name);


class Sequence
	{
		public:
		
	/*!
     * @brief Constructor of the Sequence class. It allocates a string to its sequence. 
     * The underscore is here to differentiate between the parameters and the class's attribute.
     * For control purpose it shows the allocated sequence.
     */
		Sequence(const std::string sequence_);

		
	/*!
     * @brief Probabilities' getter.
     *
     * @return A vector containing all the different nucleotidic probabilities.
     */
		std::vector<double> get_probabilities();
		
		
	/*!
     * @brief Search for a specific string in a sequence.
     *
     * @param A string containing the sequence to find. 
     * @return A vector containing all positions at which the seuence was found.
     */
		std::vector<size_t> find_sequence(const std::string& string_to_find);
		
		
		private:
		double baseProbabibilityA;	/*! Corresponds to the number of base (A, C, G, T) over the number of bases present in our sequence. */
		double baseProbabibilityC;
		double baseProbabibilityG;
		double baseProbabibilityT;
		
		const std::string sequence; /*! This string stores the actual sequence we extracted from a fasta file, for example.  */
		
		
	/*!
     * @brief This function calculates the ratio of every base in the sequence.
     */
		void calc_BaseProb();
	};

#endif
