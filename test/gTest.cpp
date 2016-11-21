#include "gtest/gtest.h"
#include "../src/Matrix.hpp"
#include "../src/utility.hpp"
#include "../src/Sequence.hpp"
#include <iostream>
#include <string>
#include <fstream>

/*! I use the constructor to initialise the four 4 different matrix.
 * This matrix will be use to check if our function work as expected because 
 * the different values test are the value we expect for the corresponding
 *  matrix when we applied the different function.
 */
Matrix_Neo r({{0.259260,0.000000,0.148148,1.000}});
Matrix ma_matrice_1(r, relativeMatrix);

Matrix_Neo a({{0.184211,0.000,0.105263, 0.710526}});
Matrix ma_matrice_2(a, absoluteMatrix);

Matrix_Neo lm({{-0.440569,MINUSINFINI,-1.247930,1.506960}});
Matrix ma_matrice_3(lm,logMatrix);

Matrix_Neo lcm({{-1.947529,MINUSINFINI,-2.754889,0.000}});
Matrix ma_matrice_4(lcm,logConstMatrix);

std::vector<double> value_test_1({1.407408});
std::vector<double> value_test_2({0.710526});
std::vector<double> value_test_3({1.40741});
std::vector<double> value_test_4({1.506960});	

std::vector<double> BP({{0.25,0.25,0.25,0.25}});

std::vector<std::string> nucleotide_sequences ({{"AACGT", "CCGTA", "AATCG", "CCGTA"}});
unsigned int position = 2;

Sequence one ("AACG");
Sequence two ("CCGT");
Sequence three ("AATC");
Sequence four ("CCGT");
std::vector<Sequence> sequence_list ({one, two, three, four});
bool entire_sequence = true;

std::vector<double> value_test_5 ({0.0,0.25,0.5,0.25});

Matrix_Neo value_test_6 ({{0.5,0.5,0.0,0.0},{0.5,0.5,0.0,0.0},{0.0,0.25,0.5,0.25},{0.0,0.25,0.25,0.5}});

/*!
 *@brief Function testing if calcul_sum() returns the expected value, using a relativematrix
 */
TEST (calcul_sum_Test, PositiveSum)
{
	ASSERT_EQ(value_test_1,ma_matrice_1.calcul_sum());
}
/*!
 *@brief Function testing if max_values() returns the max value of the line, using an absoluteMatrix
 */
TEST (max_values_Test, MaxValueabsoluteMatrix)
{
	ASSERT_EQ(value_test_2,ma_matrice_2.max_values());
}
/*!
 *@brief Function testing if sum_pow2logConstMatrix() returns the expected value, using a logConstMatrix
 */
TEST (sum_pow2logConstMatrix_Test, Positivepow )
{
	
	ASSERT_TRUE(std::abs(value_test_3[0] - ma_matrice_4.sum_pow2logConstMatrix()[0]) < 0.0001);
}

/*!
 *@brief Function testing if logMatrix_max_values() return the max value of the line, using a logMatrix
 */
TEST (logMatrix_max_values_Test, MaxValuelogMatrix)
{
	ASSERT_EQ(value_test_4,ma_matrice_3.logMatrix_max_values());
}


/*!
 *@brief Function testing if compute_abs_logMatrix() returns the good logConstMatrix
 */
TEST (compute_abs_logMatrix_test, goodrelativeMatrix)
{
	for(int j = 0 ; j< 4 ;++j)
	{
	ASSERT_TRUE(std::abs(lm[0][j] - ma_matrice_2.get_abs_logMatrix(BP)[0][j]) < 0.0001);
	}
} 


/*!
 *@brief Function testing if compute_log_absoluteMatrix returns the good logConstMatrix
 */
TEST (compute_log_absoluteMatrix_test, goodabsoluteMatrix)
{
	for(int j = 0 ; j< 4 ;++j)
	{
	ASSERT_TRUE(std::abs(a[0][j] - ma_matrice_3.get_log_absoluteMatrix(BP)[0][j]) <0.0001);
	}
} 

/*!
 *@brief Function testing if compute_relativeMatrix_from_logConstMatrix() returns the good relativeMatrix
 */
TEST (compute_relativeMatrix_from_logConstMatrix_test, goodrelativeMatrix)
{
	
	for(int j = 0 ; j< 4 ;++j)
	{
	ASSERT_TRUE(std::abs(r[0][j] - ma_matrice_4.compute_relativeMatrix_from_logConstMatrix()[0][j]) < 0.0001);
	}
} 

/*!
 *@brief Function testing if compute_absoluteMatrix_from_logConstMatrix() returns the good logConstMatrix
 */
TEST (compute_absoluteMatrix_from_logConstMatrix_test, goodabsoluteMatrix)
{
	ma_matrice_4.sum_pow2logConstMatrix();
	
	for(int j = 0 ; j< 4 ;++j)
	{
	ASSERT_TRUE(std::abs(a[0][j]- ma_matrice_4.compute_absoluteMatrix_from_logConstMatrix()[0][j]) < 0.0001);
	}
} 

/*!
 *@brief Function testing if compute_logConstMatrix_from_logMatrix() returns the good logConstMatrix
 */
TEST (compute_logConstMatrix_from_logMatrix_test, goodlogConstMatrix)
{
	ma_matrice_3.logMatrix_max_values();
	
	for(int j = 0 ; j< 4 ;++j)
	{
	ASSERT_TRUE(std::abs(lcm[0][j] - ma_matrice_3.compute_logConstMatrix_from_logMatrix()[0][j]) < 0.0001);
	}
} 



//-------------------------------------------- gTests Failed

/*!
 *@brief Function testing if compute_abs_relativeMatrix() returns the good relativeMatrix
 */
TEST (compute_abs_relativeMatrix_test, goodrelativeMatrix)
{
	ma_matrice_2.max_values();
	
	for(int j = 0 ; j< 4 ;++j)
	{
	ASSERT_TRUE(std::abs(r[0][j] - ma_matrice_2.compute_abs_relativeMatrix()[0][j]) <0.0001);
	}
} 

/*!
 *@brief Function testing if compute_rel_absoluteMatrix() returns the good absoluteMatrix
 */
TEST (compute_rel_absoluteMatrix_test, goodabsoluteeMatrix)
{
	ma_matrice_1.calcul_sum();
	
	for(int j = 0 ; j< 4 ;++j)
	{
	ASSERT_TRUE(std::abs(a[0][j]-ma_matrice_1.compute_rel_absoluteMatrix()[0][j]) < 0.0001);
	}
} 

/*!
 *@brief Function testing if compute_logConstMatrix_from_relativeMatrix() returns the good logConstMatrix
 */
TEST (compute_logConstMatrix_from_relativeMatrix_test, goodlogConstMatrix)
{
	for(int j = 0 ; j< 4 ;++j)
	{
	ASSERT_TRUE(std::abs(lcm[0][j] - ma_matrice_1.compute_logConstMatrix_from_relativeMatrix()[0][j]) < 0.0001);
	}
} 

/*!
 *@brief Function testing if "nucleotide_probability" returns the expected value, using nucleotides sequences and a position number
 */
TEST (nucleotide_probability_Test, Good_nucleotide_probability)
{
	ASSERT_EQ(value_test_5,nucleotide_probability(nucleotide_sequences, position));
}

/*!
 *@brief Function testing if "generate_PWM_from_Seq_list" returns the expected value, using nucleotides sequences and a bool variable
 */
TEST (generate_PWM_from_Seq_list_Test, PWM)
{
	ASSERT_EQ(value_test_6,generate_PWM_from_Seq_list(sequence_list, entire_sequence));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
