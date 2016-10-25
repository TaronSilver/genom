#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

/* Defines number of different nucleotides in DNA sequnece (always 4) */
#define NUMBER_NUCLEOTIDES 4


/*!
 * @class Matrix
 *
 * @brief attributes and methods for probability and log matrices
 */
 
#define NUMBER_NUCLEOTIDES 4
typedef std::array < double,4 > BaseProbabilities;
typedef std::vector<std::vector<double> > ProbMatrix;
typedef std::vector<std::array<double, 4> > LogMatrix;
typedef std::vector<std::string> SequenceList;

class Matrix
{
	private:

	LogMatrix logMatrix;	/*! array with log(probability/base probability) for each nucleotide in each position */
	ProbMatrix probMatrix;	/*! vector containing the probability for each nucleotide in each position of the motif, from file */
    SequenceList sequenceList;	/*! vector containing all motifs of prob > cutoff prob */
	
	/*!
     * @brief initialisation of logMatrix from probMatrix
     */
	void probToLog();
    
    /*!
     * @brief Function that initializes matrix from string.
     *
     * @param Name of the input matrix file
     * @return 1 if success, 0 if error
     */
    bool mkProbMatrix(std::string const& fileName);

    
	public: 
    /*!
     * @brief Constructor, initialises probMatrix
     *
     * @param Name of input probability matrix
     */
    Matrix(const std::string& fileName);

    /*!
     * @brief returns size of motif (from the probMatrix size)
     *
     * @return int corresponding to length of motif
     */
	int getMatrixRowCount();
    
    /*!
     * @brief initialises logMatrix attribute from probMatrix attribute
     *
     * @param array with base probabilities (for A,C,G,T) calculated by sequence
     */
	void compute_logMatrix (const BaseProbabilities& bp);
	
	/*!
     * @brief get value in probMatrix
     *
     * @param char corresponding to nucleotide in cap locks, int for position in motif 
     * @return double with prob for that nucleotide in position
     */
	double getProbability (char const N, int const pos);
    
    /*!
     * @brief tests all combinations of the position weight matrix and fills
    sequenceList with all sequences with a score higher than the specified cutoff
     *
     * @param double of cutoff value
     */
    void sequenceExtract();
    
    /*!
     * @brief accesses the extracted DNA sequences and returns a vector of strings
     *
     * @return ??? author of this ???
     */
    std::vector<std::string> accessDNASequences();
};

#endif
