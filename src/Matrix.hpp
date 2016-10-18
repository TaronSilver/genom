#include <vector>
#include <array>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

#include <cmath>

/* Defines number of different nucleotides in DNA sequnece (always 4) */
#define NUMBER_NUCLEOTIDES 4
#define MINUSINFINI -1000.0



typedef std::array < double,4 > BaseProbabilities;
typedef std::vector<std::vector<double> > ProbMatrix;
typedef std::vector<std::array<double, 4> > NewMatrix;
typedef std::vector < double > SimpleVector;

typedef std::vector<std::string> SequenceList;

class Matrix
{
	private:
	
	ProbMatrix logMatrix;
	ProbMatrix absoluteMatrix;
	ProbMatrix relativeMatrix;
	ProbMatrix probMatrix;
    SequenceList sequenceList;
	Matrix(const std::string& fileName); // cobstructor
	void probToLog();
	static std::vector<std::vector<double> > mkProbMatrix(std::string const& fileName);

	
    
	public :
	int getMatrixRowCount(); //{ return probMatrix.size()}
	
	/*Method that compute the logMatrix from the absoluteMatrix.
	 Baseprobabilities bp is an array with the 4 base reference probability, we calcul our log with it to be more precise*/
	void compute_abs_logMatrix (const BaseProbabilities& bp);
	
	/*Method that compute the absoluteMatrix from the logMatrix*/
	void compute_log_absoluteMatrix (const BaseProbabilities& bp);
	
	/*Method that compute the relativeMatrix from the absoluteMatrix*/
	void compute_abs_relativeMatrix();
	
	/*Method that compute the absoluteMatrix from the relativeMatrix*/
	void compute_rel_absoluteMatrix();
	
	/*Calcul the sum we need to pass from the relative to the absolute matrix*/
	SimpleVector calcul_sum();
	
	/*Find the maximum value of the line we need to pass from the absolute to the relative matrix*/
	SimpleVector max_values();
	
	
	
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
