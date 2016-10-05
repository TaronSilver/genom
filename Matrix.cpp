

// Created by Erica Geneletti and Katia Schalk on 5/10/16



#include "Matrix.hpp"
#include <fstream>
#include <iostream>
#include <string>

double Matrix::getProbability (char const N, int const l)
{
	if (l<1 or N!=A or N!=T or N!=G or N!=C)
	{	
        cerr << "Error : negative line value or invalid nucleotide character" << endl;
    }
	
	ifstream PPM;
	PPM.open("DBP_PPM.mat");
	
	if (PPM.fail(())
	{
		cerr << "Error : Cannot read file DBP_PPM.mat" << endl;
		
		exit(1); //Call system to stop
		
	} else {
				string line;
				int i(1);
				double A, T, C, G;
				
				while(i<=l)								//obtains the requested line in the PPM stream
				{
					getline(PPM, line);	
					++i;
				}
				
				std::istringstream values(line);		//copies line into new stream
				values >> A >> C >> G >> T;				//reads new stream and puts values into nucleotide probabilities
				
                PPM.close();
        
				switch (N)                              //returns the requested nucleotide probability
                {
					case A:
					return A;
					case T:
					return T;
					case C:
					return C;
					case G:
					return G;
                }
            }
}
