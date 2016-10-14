#include <vector>
#include <array>

#include <iostream>

typedef std::array < double,4 > BaseProbabilities;
typedef std::vector<std::vector<double>> ProbMatrix;
typedef std::vector<std::array<double, 4>> LogMatrix;

class Matrix
{
	private:
	LogMatrix logMatrix;
	ProbMatrix probMatrix;
	Matrix(const std::string& fileName); // cobstructor
	void probToLog();
	// add an atribute sequence ???
	
	public :
	/*Method that compute the logMatrix from the probMatrix*/
	void compute_logMatrix (const BaseProbabilities& bp);
	
	/* Returns the probability for a nucleotide in a specific position.
	The first argument corresponds to the column: the nucleotide who interest us.
	The second argument corresponds to the lign: the place of this nucleotide in the sequence of 7 nucleotides.*/
	static double getProbability (char const N, int const l); // Remove static when everything works	
};
