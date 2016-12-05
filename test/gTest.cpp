#include "gtest/gtest.h"
#include "../src/Matrix.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/*!=========== Element we use for Matrix gTests ============*/

Matrix_Neo lm_1({{-0.440569,MINUSINFINI,-1.247930,1.506960},
			     {-0.440569,MINUSINFINI,-1.247930,1.506960}});

Matrix_Neo lm_2({{-2.440569,MINUSINFINI,-3.247930,1.506960 -2},
			   {-2.440569,MINUSINFINI,-3.247930,1.506960 -2}});
			   			     
Matrix_Neo a_1({{0.184211,0.000,0.105263, 0.710526},
			  {0.184211,0.000,0.105263, 0.710526}});
			  
Matrix_Neo r_1({{0.259260,0.000000,0.148148,1.000},
				{0.259260,0.000000,0.148148,1.000}});
			
				
Matrix_Neo lcm_1({{-1.947529,MINUSINFINI,-2.754889,0.000},
				{-1.947529,MINUSINFINI,-2.754889,0.000}});	
											
const std::vector<double> base_probabilities ({0.25,0.25,0.25,0.25});

Matrix ma_matrice_A	(a_1,absoluteMatrix, base_probabilities);

Matrix ma_matrice_R	(r_1,relativeMatrix, base_probabilities);

Matrix ma_matrice_LOG (lm_1,logMatrix,base_probabilities);

//enum MATRIX_TYPE { absoluteMatrix, relativeMatrix, logMatrix, logConstMatrix, ERROR};


/*!======================	Matrix_gTests		========================*/



/*!
 *@brief Function testing if max_of_line(std::vector<double> line) returns as expected the max value of the line.
 */
TEST (max_of_line_Test, Good_MaxValue)
{
	std::vector<double> line_to_be_tested_1 ({0.184211,0.000,0.105263, 0.710526});
	double answer_1(0.710526);
	
	ASSERT_EQ(answer_1,Matrix::max_of_line(line_to_be_tested_1));
}


/*!
 *@brief Function testing if min_of_line(std::vector<double> line) returns as expected the min value of the line.
 */
TEST (min_of_line_Test, Good_MinValue)
{
	std::vector<double> line_to_be_tested_2 ({0.259260,0.000000,0.148148,1.000});
	double answer_2(0.000000);
	
	ASSERT_EQ(answer_2,Matrix::min_of_line(line_to_be_tested_2));
}


/*!
 *@brief Function testing if sum_of_line(std::vector<double> line) returns the expected value.
 */
 
TEST (sum_of_line_Test, Good_Sum)
{
	std::vector<double> line_to_be_tested_3 ({0.259260,0.000000,0.148148,1.000});
	double answer_3(1.407408);
	
	ASSERT_EQ(answer_3, Matrix::sum_of_line(line_to_be_tested_3));
}


/*!
 *@brief Function testing if line_is_reg_ppm(double min, double max, double sum) returns the great bool
 */
TEST (line_is_reg_ppm_Test, Good_Bool)
{
	ASSERT_TRUE(ma_matrice_A.line_is_reg_ppm(1,0.5,1));
}

/*!
 *@brief Function testing if line_is_normed_ppm(double min, double max, double sum)  returns the good bool
 */
TEST (line_is_normed_ppm_Test, Good_Bool)
{

	ASSERT_TRUE(ma_matrice_A.line_is_normed_ppm(1,1,2));

}


/*!
 *@brief Function testing if logMatrix_from_logConstMatrix( Matrix_Neo input_matrix )returns the good logMatrix
 */
TEST (logMatrix_from_logConstMatrix_Test, Good_logMatrix)
{
		   			   
	Matrix ma_matrice_2(lcm_1, logConstMatrix);

	Matrix_Neo result2 = ma_matrice_2.logMatrix_from_logConstMatrix(lcm_1);

	for (int i=0 ; i<2 ; ++i)
		{
			for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(lm_2[i][j] - result2[i][j]) <0.001);
		}

		}
}

/*!
 *@brief Function testing if logMatrix_from_normed_PPM( Matrix_Neo input_matrix ) returns the good logMatrix
 */

TEST (logMatrix_from_normed_PPM_Test, Good_logMatrix)
{
			  
	Matrix_Neo result_3 = ma_matrice_R. logMatrix_from_normed_PPM(r_1);

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(lm_1[i][j] - result_3[i][j]) <0.001);
		}

	}
}


/*!
 *@brief Function testing if logMatrix_from_probMatrix( Matrix_Neo input_matrix ) returns the good logMatrix
 */

TEST (logMatrix_from_probMatrix_Test, Good_logMatrix)
{
			  
	Matrix_Neo result_4 = ma_matrice_A. logMatrix_from_probMatrix(a_1);

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(lm_1[i][j] - result_4[i][j]) <0.001);
		}

	}
}

/*!
 *@brief Function testing if probMatrix_from_logMatrix( Matrix_Neo input_matrix )returns the good absoluteMatrix
 */

TEST (probMatrix_from_logMatrix_Test, Good_absoluteMatrix)
{
			  
	Matrix_Neo result_5 = ma_matrice_A.probMatrix_from_logMatrix(lm_1);

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(a_1[i][j] - result_5[i][j]) <0.001);
		}

	}
}



/*!
 *@brief Function testing if absolute_from_normed_PPM( Matrix_Neo input_matrix  )returns the good absoluteMatrix
 */

TEST (absolute_from_normed_PPM_Test, Good_absoluteMatrix)
{
			  
	Matrix_Neo result_6 = ma_matrice_R.absolute_from_normed_PPM(r_1);

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(a_1[i][j] - result_6[i][j]) <0.001);
		}

	}
}

/*!
 *@brief Function testing if determine_matrix_type(Matrix_Neo input) returns the good MatrixType
 */
TEST (determine_matrix_type_Test, Good_MatrixType)
{
			  
	ASSERT_EQ(MATRIX_TYPE::absoluteMatrix, ma_matrice_A.determine_matrix_type(a_1) );
			
}

// ==== Don't work

/*!
 *@brief Function testing if log_to_matrix returns the good Matrix
 */
TEST (log_to_matrix_Test, Good_Matrix)
{	
	  
	Matrix_Neo result_15 = ma_matrice_LOG.log_to_matrix(lm_1,MATRIX_TYPE::absoluteMatrix);

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(a_1[i][j] - result_15[i][j]) <0.001);
		}

	}
}

/*!
 *@brief Function testing if matrix_to_log(Matrix_Neo input_matrix, MATRIX_TYPE type)returns the good logMatrix
 */
TEST (matrix_to_log_Test, Good_Matrix)
{	

	  
	Matrix_Neo result_15 = ma_matrice_A.matrix_to_log(a_1, MATRIX_TYPE::absoluteMatrix);

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(lm_1[i][j] - result_15[i][j]) <0.001);
		}

	}
}

			

// ====== Test failed

/*!
 *@brief Function testing if logConstMatrix_from_logMatrix( Matrix_Neo input_matrix ) returns the good logConstMatrix
 */
TEST (logConstMatrix_from_logMatrix_Test, GoodlogConstMatrix)
{
	Matrix ma_matrice_1(lm_1, logMatrix);  			  
	Matrix_Neo result_1 = ma_matrice_1.logConstMatrix_from_logMatrix(lm_1);

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(lcm_1[i][j] - result_1[i][j]) <0.05);
		}	
	}
}



/*!
 *@brief Function testing if normed_from_absolute_PPM( Matrix_Neo input_matrix  )returns the good reltiveMatrix
 */
TEST (normed_from_absolute_PPM_Test, Good_relativeMatrix)
{	
		  
	Matrix_Neo result_9 = ma_matrice_A.normed_from_absolute_PPM(a_1);
	

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(r_1[i][j] - result_9[i][j]) <0.001);
		}

	}
}

/*!
 *@brief Function testing if normed_PPM_from_logMatrix( Matrix_Neo input_matrix ) returns the good reltiveMatrix
 */

TEST (normed_PPM_from_logMatrix_Test, Good_relativeMatrix)
{
			  
	Matrix_Neo result_13 = ma_matrice_LOG.normed_PPM_from_logMatrix( lm_1);

	for (int i=0 ; i<2 ; ++i)
	{
		for(int j = 0 ; j< 4 ;++j)
		{
			ASSERT_TRUE(std::abs(r_1[i][j] - result_13[i][j]) <0.001);
		}

	}
}



/*!======================	Sequence_gTests		========================*/



/*!======================	 Utility_gTests		========================*/



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

