#include <vector>
#include <array>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>

/* Defines number of different nucleotides in DNA sequnece (always 4) */
#define NUMBER_NUCLEOTIDES 4



typedef std::array < double,4 > BaseProbabilities;
typedef std::vector<std::vector<double>> ProbMatrix;
typedef std::vector<std::array<double, 4>> LogMatrix;
typedef std::vector<std::string> SequenceList;

class Matrix
{
	private:
	LogMatrix logMatrix;
	ProbMatrix probMatrix;
    SequenceList sequenceList;
	Matrix(const std::string& fileName); // cobstructor
	void probToLog();
	// add an atribute sequence ???
	
    
	public :
	
	/*Method that compute the logMatrix from the probMatrix.
	 Baseprobabilities bp is an array with the 4 base reference probability*/
	void compute_logMatrix (const BaseProbabilities& bp);
	
	/* Returns the probability for a nucleotide in a specific position.
	The first argument corresponds to the column: the nucleotide who interest us.
	The second argument corresponds to the lign: the place of this nucleotide in the sequence of 7 nucleotides.*/
	static double getProbability (char const N, int const l); // Remove static when everything works
    
    /* Function that tests all combinations of the position weight matrix and fills
    sequenceList with all sequences with a score higher than the specified cutoff.*/
    void sequenceExtract(double cutoff);
    
    /* Function that accesses the extracted DNA sequences and returns a vector of strings. */
    std::vector<std::string> accessDNASequences();
};
