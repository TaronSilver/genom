#include <vector>
#include <array>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

/* Defines number of different nucleotides in DNA sequnece (always 4) */
#define NUMBER_NUCLEOTIDES 4


enum MATRIX_TYPE { PPMatrix, PPMatrix_consensus, PSSMatrix, PSSMatrix_minus_constant, ERROR};
typedef std::array < double,4 > BaseProbabilities;
typedef std::vector<std::vector<double> > ProbMatrix;
typedef std::vector<std::array<double, 4> > LogMatrix;
typedef std::vector<std::string> SequenceList;

//more precise :
typedef std::vector<std::vector<double> > Matrix_Neo;



class Matrix
{
	private:
	

    SequenceList sequenceList;
    
    //more precise attributs:
    Matrix_Neo ppmatrix;
    Matrix_Neo ppmatrix_consensus;
    Matrix_Neo pssmatrix;
    Matrix_Neo pssmatrix_minus_constant;
    
	void probToLog();
    
    /*!
     * @brief Function that initializes matrix from string.
     *
     * @param Name of the input matrix file
     * @return 1 if success, 0 if error
     */
	
MATRIX_TYPE mkProbMatrix_type(std::string const& fileName);
	//do the same but identy the type of the matrix between :
	//1 : position probability matrix of absolute probabilities (PPMatrix)
	//2 : position probability matrix of  probabilities relative to consensus (PPMatrix_consensus)
	//3 : position-specific scoring matrix (log of PPM) named PSSMatrix
	//4 : position-specific scoring matrix - constant (PSSMatrix_minus_constant)
	
    
	public :
    
    Matrix(const std::string& fileName); // constructor

    
	int getMatrixRowCount(); //{ return probMatrix.size()}
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
