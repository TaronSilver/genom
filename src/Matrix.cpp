#include "Matrix.hpp"
#include <fstream>
#include <string>
#include <sstream>


void Matrix::compute_logMatrix (const BaseProbabilities& bp)
{
	double x, y;
	logMatrix.resize(proMatrix.size());
	
	for(size_t i(0);i<probMatrix.size;++i)
	{
		for (size_t j(0);j<4;++j)
		{
			y=probMatrix[j];
			x=log2(y/bp[j]);
			logMatrix[i][j] = x;	
		}
	
	}
}

double Matrix::getProbability (char const N, int const l)
{
	if (l<1 or l>7 or N!='A' or N!='T' or N!='G' or N!='C')
	{	
        cerr << "Error : negative line value or invalid nucleotide character" << endl;
    }
	
	ifstream PPM;
	PPM.open("DBP_PPM.mat");
	
	if (PPM.fail())
	{
		cerr << "Error : Cannot read file DBP_PPM.mat" << endl;
		
		return(1); //what should we return in case of error?
		
	} else {
				string line;
				int i(1);
				double A, T, C, G;
				
				while(i<=l)				//obtains the requested line in the PPM stream
				{
					getline(PPM, line);	
					++i;
				}
				
				istringstream values(line);		//copies line into new stream
				values >> A >> C >> G >> T;		//reads new stream and puts values into nucleotide probabilities
				
                PPM.close();
        
				switch (N)                              //returns the requested nucleotide probability
                {
					case 'A':
					return A;
					case 'T':
					return T;
					case 'C':
					return C;
					case 'G':
					return G;
                }
                
                //we have dealt with the case that N is not one of the acceped letters
                //should we put an error message anyway in case there are problems?
            }
}
