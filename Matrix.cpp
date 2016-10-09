

// Created by Erica Geneletti and Katia Schalk on 5/10/16



#include "Matrix.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


double Matrix::getProbability (char const N, int const l)
{
	if (l<1 or l>7 or N!='A' or N!='T' or N!='G' or N!='C')
	{	
        std::cerr << "Error : negative line value or invalid nucleotide character" << std::endl;
    }
	
	std::ifstream PPM;
	PPM.open("DBP_PPM.mat");
	
	if (PPM.fail())
	{
		std::cerr << "Error : Cannot read file DBP_PPM.mat" << std::endl;
		
		return(1); //what should we return in case of error?
		
	} else {
				std::string line;
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
