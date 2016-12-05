#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <list>
#include <cmath>
#include <map>
#include <algorithm>

/* Defines number of different nucleotides in DNA sequnece (always 4) */
#define NUMBER_NUCLEOTIDES 4
#define MINUSINFINI -1000.0

typedef enum {A, C, G, T, N} nuc;


/*!
 * @class Matrix
 *
 * @brief attributes and methods for probability and log matrices
 */

enum MATRIX_TYPE { absoluteMatrix, relativeMatrix, logMatrix, logConstMatrix, ERROR};

typedef std::vector<std::vector<double> > Matrix_Neo;
typedef std::vector<double> Base_Prob;

typedef struct BindingSequence {
    std::string sequence;
    double score;
} BindingSequence;




class Matrix
{
	private:
    
    //=======================================================================
    //                            PRIVATE ATTRIBUTES
	
    Matrix_Neo logMatrix;
    unsigned int length;
    std::vector<double> base_prob;
   
    
    
    //=======================================================================
    //                            PRIVATE FUNCTIONS
    
    /*!
     * @brief initialisation of logMatrix from probMatrix
     */
	void probToLog();
    

    //-----------------------------------------------------------------------
    // MATRIX CONVERSIONS
    
    
  

    
   

    
   
    


    
    
    
    
	public:
    //=======================================================================
    //                            PUBLIC FUNCTIONS
    
    /*!
     * @brief   Opens up file (checks if possible), gives out matrix stocked in file
     *
     * @param   Name of the file containing the matrix
     *
     * @return  Matrix in file, in type Matrix_Neo
     */
    static Matrix_Neo read_matrix(std::string const& fileName);
    
    /*!
     * @brief   Converts a log matrix to a given matrix type
     *
     * @param   The matrix to convert, and the type to convert it to
     *
     * @return  The converted matrix
     */
    Matrix_Neo log_to_matrix(Matrix_Neo input_matrix, MATRIX_TYPE type);
    
     /*!
     * @brief   Converts a matrix of a given type to a log matrix
     *
     * @param   The matrix to convert, and the type of the inserted matrix
     *
     * @return  The converted matrix
     */
    Matrix_Neo matrix_to_log(Matrix_Neo input_matrix, MATRIX_TYPE type);
    
     /*!
     * @brief   Converts a normalized probability weight to an absolute probability
     *          weight matrix
     *
     * @param   The matrix to convert
     *
     * @return  The converted matrix
     */
    Matrix_Neo absolute_from_normed_PPM( Matrix_Neo input_matrix  );
    
    /*!
     * @brief   Converts a probability weight matrix to a logarithmic
     *          matrix, using attribute base probabilities
     *
     * @param   The matrix to convert
     *
     * @return  The converted matrix
     */
    Matrix_Neo logMatrix_from_probMatrix( Matrix_Neo input_matrix );
    
    //-----------------------------------------------------------------------
    // CONSTRUCTORS

    /*!
     * @brief Constructor of matrix from file
     *
     * @param Name of input probability matrix
     */
    Matrix(const std::string& fileName,
           const std::vector<double> base_prob = {1, 1, 1, 1});
    
    
    
    /*!
     * @brief Constructeur matrix from vector
     *
     * @param Name of input probability matrix
     */
    Matrix(Matrix_Neo input_matrix, MATRIX_TYPE type,
           const std::vector<double> = {1, 1, 1, 1});
    
    
    //-----------------------------------------------------------------------
    // GETTER FUNCTIONS
    
    /*!
     * @brief Getter for logMatrix
     *
     * @return log Matrix
     */
    Matrix_Neo get_logMatrix();

    
    /*!
     * @brief Getter for base probabilities
     *
     * @return log Matrix
     */
    std::vector<double> get_base_probabilities();
    
    
    /*!
     * @brief 	getter for length of matrix
     *
     * @return length
     */
    unsigned int get_length();
    
        
    //-----------------------------------------------------------------------
    // COMPUTING FUNCTIONS
	/*!
     * @brief   Converts a normed probability weight matrix to a logarithmic
     *          matrix, using attribute base probabilities
     *
     * @param   The matrix to convert
     *
     * @return  The converted matrix
     */
    Matrix_Neo logMatrix_from_normed_PPM( Matrix_Neo input_matrix );

    /*!
     * @brief 	Returns score of a sequence based on the log matrix. 
     *          If nucleotide is N, it is disregarded
     *
     * @param   List of enum nuc, being a nucleotide sequence
     *
     * @return  score
     */
    double sequence_score(std::list<nuc> sequence);
    
        //-----------------------------------------------------------------------
    // SAVING MATRIX

    /*!
     * @brief 	Saves the matrix to a specified file
     *
     * @param   Name of the file to save it to, type to save it as
     *
     */
void save(std::string fileName, MATRIX_TYPE type);

    
    
    //-----------------------------------------------------------------------
    // DEBUGGING FUNCTIONS
    /*!
     * @brief   Function that prints out a matrix to terminal. To be used 
     *          for debugging
     */
    void print_log_matrix();
    
    
    
    
        /*!
     * @brief   Gives the maximum value of a line
     *
     * @param   A line of a matrix, made as a vector of doubles
     *
     * @return  Minimum value found in the line
     */
    static double max_of_line(std::vector<double> line);
    
    
    /*!
     * @brief   Gives the minimum value of a line
     *
     * @param   A line of a matrix, made as a vector of doubles
     *
     * @return  Minimum value found in the line
     */
    static double min_of_line(std::vector<double> line);

    
    /*!
     * @brief   Adds up values in a line
     *
     * @param   A line of a matrix, made as a vector of doubles
     *
     * @return  Sum of the values in the line
     */
    static double sum_of_line(std::vector<double> line);
    
    
   /*!
     * @brief   Converts a normalized log matrix to a regular log matrix using the
     *          attribute base probabilities
     *
     * @param   The matrix to convert
     *
     * @return  The converted matrix
     */
    Matrix_Neo logMatrix_from_logConstMatrix( Matrix_Neo input_matrix );

    
    /*!
     * @brief   Converts a normalized position weight matrix to a regular position 
     *          weight matrix
     *
     * @param   The matrix to convert
     *
     * @return  The converted matrix
     */
    Matrix_Neo normed_from_absolute_PPM( Matrix_Neo input_matrix );

    
    /*!
     * @brief   Converts a normalized logarithmic  matrix to a regular logarithmic
     *          matrix, using the attribut base probabilities
     *
     * @param   The matrix to convert
     *
     * @return  The converted matrix
     */
    Matrix_Neo logConstMatrix_from_logMatrix( Matrix_Neo input_matrix );

    /*!
     * @brief   Converts a normalized logarithmic matrix to a normalized
     *          probability weight matrix, using the attribut base probabilities
     *
     * @param   The matrix to convert
     *
     * @return  The converted matrix
     */
    Matrix_Neo normed_PPM_from_logMatrix( Matrix_Neo input_matrix );
    
    
    
	/*!
     * @brief   Converts any log matrix to a probability matrix using the
     *          attribute base probabilities
     *
     * @param   The matrix to convert
     *
     * @return  The converted matrix
     */
    Matrix_Neo probMatrix_from_logMatrix( Matrix_Neo input_matrix );

    
    
    //-----------------------------------------------------------------------
    // DETERMINE TYPE

    /*!
     * @brief   Determines the type of a matrix
     *
     * @param   Matrix of which the type is to be determined
     *
     * @return  Type of the matrix
     */
    MATRIX_TYPE determine_matrix_type(Matrix_Neo input_matrix);
    

    
    /*!
     * @brief   Checks if line values correspond to a regular
     *          probability weight matrix
     *
     * @param   the minimum, the maximum and the sum of the line
     *
     * @return  1 if they correspond, 0 if not
     */
    static bool line_is_reg_ppm(double min, double max, double sum);

    
    /*!
     * @brief   Checks if line values correspond to a weighed
     *          probability weight matrix
     *
     * @param   the minimum, the maximum and the sum of the line
     *
     * @return  1 if they correspond, 0 if not
     */
    static bool line_is_normed_ppm(double min, double max, double sum);

        
    
    
    
    
    
    
    
    
    
    
    
// NON EXECUTED FUNCTIONS
#if 0
    



    /*!
     * @brief Saves specified matrix type to specified file
     */
    void save_matrix();
    
    /*!
     * @brief Allows user to save multiple matrice types to multiple files
     */
    void save_matrix_loop();
    
    /*!
     * @brief initialise the matrix that is in the file filename 
     *
     * @param the name of the file to open
     */
	MATRIX_TYPE init_Matrix_type(std::string const& fileName);
	 
	 /*!
     * @brief Fill all the matrixes 
     *
     * @param Type of the already filled matrix
     */  
	void fill_Matrix(MATRIX_TYPE type);

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
	static double getProbability (char const N, int const pos);
    	
    /*!
     * @brief 	tests all combinations of the position weight matrix and fills
				sequenceList with all sequences with a score higher than the specified cutoff
     *
     * @param double of cutoff value
     */
    void sequenceExtract();

	/*!
     * @brief Method that compute the logMatrix from the absoluteMatrix
     *
     * @param 	Baseprobabilities bp is an array with the 4 base reference probability
     * 			we calcul our log with it to be more precise
     */
	void compute_abs_logMatrix (const BaseProbabilities& bp);
	

	Matrix_Neo get_abs_logMatrix(const BaseProbabilities& bp);
	
	/*Method that compute the absoluteMatrix from the logMatrix*/
	void compute_log_absoluteMatrix (const BaseProbabilities& bp);
	
	Matrix_Neo get_log_absoluteMatrix(	const BaseProbabilities& bp);
	
	/*Method that compute the relativeMatrix from the absoluteMatrix*/
	Matrix_Neo compute_abs_relativeMatrix();
	
	/*Method that compute the absoluteMatrix from the relativeMatrix*/
	Matrix_Neo compute_rel_absoluteMatrix();
	
	/*! Method that computes the relativeMatrix from the logConstMatrix */
	Matrix_Neo compute_relativeMatrix_from_logConstMatrix();
	
	/*! Method that computes the logConstMatrix from the relativeMatrix */
	Matrix_Neo compute_logConstMatrix_from_relativeMatrix();
   
    /*! Method that computes the logConstMatrix from the logMatrix */
	Matrix_Neo compute_logConstMatrix_from_logMatrix();
	
	/*! Method that computes the absoluteMatrix from the logConstMatrix */
	Matrix_Neo compute_absoluteMatrix_from_logConstMatrix();

	/*!
     * @brief Method that finds the maximal values for each row of the logMatrix
     *
     * @return a vector with all the maximal values of each row of the logMatrix 
     */
	SimpleVector logMatrix_max_values();  

	/*!
     * @brief Method that computes the sum of (2 power each element of one row of the logConstMatrix) for each row
     *
     * @return a vector with the sum of (2 power each element of one row of the logConstMatrix) for each row
     */
	SimpleVector sum_pow2logConstMatrix();
	
	/*!
     * @brief Calculates the sum we need to pass from the relative to the absolute matrix
     *
     * @return ???
     */
	SimpleVector calcul_sum();
	
	/*!
     * @brief Find the maximum value of the line we need to pass from the absolute to the relative matrix
     *
     * @return ???
     */
	SimpleVector max_values();
    
    /*!
     * @brief 	Function that tests all combinations of the position weight matrix and fills
				sequenceList with all sequences with a score higher than the specified cutoff
     *
     * @param ???
     */
    void sequenceExtract(double cutoff);
	
    /*!
     * @brief accesses the extracted DNA sequences and returns a vector of strings
     *
     * @return ???
     */
    std::vector<std::string> accessDNASequences();
    
    
#endif
    
};

#endif



/*
 - What to do if matrix type isn't regognized
 
 
 
 
 */


