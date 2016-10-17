#include "Matrix.hpp"


void Matrix::compute_logMatrix (const BaseProbabilities& bp)
{
	if (bp.empty())
	{
		std::cout << "Your BaseProbabilities is empty, we can't compute your logMatrix." << std:: endl;
		
	} else {
				double x, y;
	
				logMatrix.resize(probMatrix.size());/*Give to logMatrix the same size than probMatrix*/
				  
	
				for(size_t i(0);i<probMatrix.size();++i)
				{
					for (size_t j(0);j<4;++j)/*Read the probMatrix*/
						{
							y=probMatrix[j];
							x=log2(y/bp[j]); /*Calcul the new values we need*/
							logMatrix[i][j] = x;/*Stock this new x values in the logMatrix*/
						}
				}
			}
}

double Matrix::getProbability (char const N, int const pos)
{
	//check for valid input
	if (pos<1 or pos>getMatrixRowCount() or N!='A' or N!='T' or N!='G' or N!='C')
	{	
		
        throw std::string("Error: invalid nucleotide or position");
        
    } else {
		
		//define column to look in
		int column;
		switch (N) {
			case 'A':
			column = 0;
			case 'T':
			column = 3;
			case 'C':
			column = 1;
			case 'G':
			column = 2;
		}
		
		return probMatrix[column][pos];
	}
}

static std::vector<std::vector<double> > mkProbMatrix(std::string const& fileName)
{
	//open file containing PWM
	std::ifstream PWM;
	PWM.open("fileName");
	
	//send an error if there is a problem opening file
	if (PWM.fail()) {
		
		throw std::string("Error: Cannot read PWM file");
		
	} else {
		
		//make a matrix to return
		std::vector<std::vector<double> > probMatrix;
		
		//create all variables to be use later
		std::string line;
		std::istringstream values;
		double A, T, C, G;
		std::vector< double > rowi(4);
		
		//push back of rows:
		while (true) {
			
			//(1) make a sting containing ith line
			getline(PWM, line);
			//check if at end of file now
			if (PWM.eof()) break;
			
			//(2) copy line into new stream 
			values.str (line);
			
			//(3) read values and copy into variables
			values >> A >> C >> G >> T;
			
			//(4) make a matrix to pushback for line 1
			rowi[] = { A, C, G, T };
			
			//(5) pushback the new row
			probMatrix.push_back(rowi);
		}

	
		PWM.close();
		return probMatrix;
	}
}
