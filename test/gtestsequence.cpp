#include <gtest/gtest.h>
#include "../src/utility.hpp"
#include "../src/Sequence.hpp"
#include <string>
#include <vector>
#include <fstream>


std::vector<size_t> Seqtest = {10,22,34};
Sequence Seq("AAAAAAAAAACCAAAAAAAAAACCAAAAAAAAAACCAAAA");
std::string trouve = ("CC");
std::vector<double> Probtest = {.25,.25,.25,.25};

TEST (Positions_Test, Bonne)
{
	std::ofstream outputfile("testseq");
	//outputfile.open;
    ASSERT_EQ(Seqtest,Seq.find_sequence(trouve,outputfile));
}
 /*!
 *@brief Function testing if max_values() returns the max value of the line, using an absoluteMatrix
*/

TEST (Proba_Test, Bonne)
{
    ASSERT_EQ(Probtest,Seq.get_probabilities());
}
/*!
 *@brief Function testing if sum_pow2logConstMatrix() returns the expected value, using a logConstMatrix
 */
 
TEST (Access_Position_Test, Bonne)
{
    ASSERT_EQ(trouve,Seq.access_sequence_pos(10,2));
}
/*!
 *@brief Function testing if logMatrix_max_values() return the max value of the line, using a logMatrix
*/
TEST (Nucleotide_count_test, Bonne)
{
    ASSERT_EQ(34,Seq.get_nucleotide_count('A'));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
