#ifndef MATRIX_HPP
#define MATRIX_HPP

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



/*!
 * @class Matrix
 *
 * @brief attributes and methods for probability and log matrices
 */

enum MATRIX_TYPE { absoluteMatrix, relativeMatrix, logMatrix, logConstMatrix, ERROR};
typedef std::array < double,4 > BaseProbabilities;
typedef std::vector<std::array<double, 4> > NewMatrix;
typedef std::vector < double > SimpleVector;
typedef std::vector<std::string> SequenceList;
typedef std::vector<std::vector<double> > Matrix_Neo;



class Matrix
{
	private:
    SequenceList sequenceList;	/*! vector containing all motifs of prob > cutoff prob */
	/*!
     * @brief initialisation of logMatrix from probMatrix
     */
	Matrix_Neo absoluteMatrix; /*! vector containing the probability for each nucleotide in each position of the motif */
	Matrix_Neo relativeMatrix; /*! position probability matrix of  probabilities relative to consensus */
    Matrix_Neo logMatrix; /*! array with log(probability/base probability) for each nucleotide in each position */
	Matrix_Neo logConstMatrix;	 /*! position-specific scoring matrix ( named logMatrix) - constant */
   
    
	void probToLog();
    
    /*!
     * @brief Function that initializes matrix from string.
     *
     * @param Name of the input matrix file
     * @return 1 if success, 0 if error
     */

    
	public: 
    /*!
     * @brief Constructor, initialises probMatrix
     *
     * @param Name of input probability matrix
     */

	
	MATRIX_TYPE init_Matrix_type(std::string const& fileName);
	   
	public :
    
    Matrix(const std::string& fileName); // constructor

    /*!
     * @brief returns size of motif (from the probMatrix size)
     *
     * @return int corresponding to length of motif
     */
	int getMatrixRowCount(); 

	/*!
     * @brief get value in probMatrix
     *
     * @param char corresponding to nucleotide in cap locks, int for position in motif 
     * @return double with prob for that nucleotide in position
     */
	static double getProbability (char const N, int const pos); // Remove static when everything works
    	/* Returns the probability for a nucleotide in a specific position.
	The first argument corresponds to the column: the nucleotide who interest us.
	The second argument corresponds to the lign: the place of this nucleotide in the sequence of 7 nucleotides.*/
	

    /*!
     * @brief tests all combinations of the position weight matrix and fills
    sequenceList with all sequences with a score higher than the specified cutoff
     *
     * @param double of cutoff value
     */
    void sequenceExtract();


	
	/*Method that compute the logMatrix from the absoluteMatrix.
	 Baseprobabilities bp is an array with the 4 base reference probability, we calcul our log with it to be more precise*/
	void compute_abs_logMatrix (const BaseProbabilities& bp);
	
	/*Method that compute the absoluteMatrix from the logMatrix*/
	void compute_log_absoluteMatrix (const BaseProbabilities& bp);
	
	/*Method that compute the relativeMatrix from the absoluteMatrix*/
	void compute_abs_relativeMatrix();
	
	/*Method that compute the absoluteMatrix from the relativeMatrix*/
	void compute_rel_absoluteMatrix();
	
	/*Method that compute the relativeMatrix from the logConstMatrix*/
	void compute_relativeMatrix_from_logConstMatrix();
	
	/*Method that compute the logConstMatrix from the relativeMatrix*/
	void compute_logConstMatrix_from_relativeMatrix();
	
	/*Method that compute the logConstMatrix from the logMatrix*/
	void compute_logConstMatrix_from_logMatrix();
	
	/* Find the minimal values of each row of the logMatrix*/
	SimpleVector logMatrix_min_values();
	
	/*Calcul the sum we need to pass from the relative to the absolute matrix*/
	SimpleVector calcul_sum();
	
	/*Find the maximum value of the line we need to pass from the absolute to the relative matrix*/
	SimpleVector max_values();
    
	

    
    /* Function that tests all combinations of the position weight matrix and fills
    sequenceList with all sequences with a score higher than the specified cutoff.*/
    
    void sequenceExtract(double cutoff);
	
    /*!
     * @brief accesses the extracted DNA sequences and returns a vector of strings
     *
     * @return ??? author of this ???
     */
    std::vector<std::string> accessDNASequences();
    
    
};

#endif
