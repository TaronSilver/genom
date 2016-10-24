#include "Matrix.hpp"


void Matrix::compute_abs_logMatrix (const BaseProbabilities& bp)
{
    if (bp.empty())
    {
        std::cout << "Your BaseProbabilities is empty, we can't compute your logMatrix." << std:: endl;
        
    } else {      
				logMatrix.clear(); /* Be sure the logMatrix is empty*/
				
				SimpleVector new_line;/* Will stock the 4 values of all lines and be added to logMatrix lines by lines*/
				double y;
				
				for(size_t i(0);i<absoluteMatrix.size();++i)
				{	
					new_line.clear();
						
					for (size_t j(0);j<4;++j)/*Read the absoluteMatrix*/
					{
						y=absoluteMatrix[i][j];
                
						if(y<1.0E-100)/* Solve the problem of -infini case*/
						{
							
							new_line.push_back(MINUSINFINI);
					
						} else {
					
									new_line.push_back(log2(y/bp[j])); /*Calcul the new values we need and put it in the new_line*/
								
								}
									
					}
							
					logMatrix.push_back(new_line); /*Stock the line of 4 new values in the logMatrix*/
				
				}
			}	
}	

void Matrix::compute_log_absoluteMatrix (const BaseProbabilities& bp)
{
    if (bp.empty())
    {
        std::cout << "Your BaseProbabilities is empty, we can't compute your logMatrix." << std:: endl;
        
    } else {
				absoluteMatrix.clear(); 
				  
				SimpleVector line;
				double x;
				
				for(size_t i(0);i<logMatrix.size();++i)
				{	
					line.clear();
									
					for (size_t j(0);j<4;++j)/*Read the logMatrix*/
					{
						x=logMatrix[i][j];
                
						if(x<MINUSINFINI)// Solve the problem of -infini cases
						{
							line.push_back(0.0);
					
						} else {
								line.push_back(pow(2,(x/bp[j])));/*Calcul the new values we need*/
							
								}
					}
					
					absoluteMatrix.push_back(line);
					
				}
			}
} 

void Matrix::compute_abs_relativeMatrix()
{
	double p;
	SimpleVector nw_line;
	SimpleVector v = max_values();
					  
	relativeMatrix.clear();
             
	for(size_t i(0);i<absoluteMatrix.size();++i)
	{
		nw_line.clear();
		
		for (size_t j(0);j<4;++j)/*Read the absoluteMatrix*/
		{
					
			p=absoluteMatrix[i][j];
					
			nw_line.push_back(p/v[j]);/*Divide the value in position [i][j] by the max value of his line [i]*/
					
		}
		
		relativeMatrix.push_back(nw_line);
		
	}
				
}								
				
void Matrix::compute_rel_absoluteMatrix()
{	
	double z;
	SimpleVector n_line;
	SimpleVector s=calcul_sum();
	
	absoluteMatrix.clear();
	
	for(size_t i(0);i<relativeMatrix.size();++i)
	{
		n_line.clear();
		
		for (size_t j(0);j<4;++j)
		{
			z=relativeMatrix[i][j];
					
			n_line.push_back(z/s[j]);/*Divide the value in position [i][j] by the max value of his line [i]*/
					
		}
		
		absoluteMatrix.push_back(n_line);
		
		}
}

void Matrix::compute_probMatrix_from_relativeMatrix()
{	
	double z=0.0;
	SimpleVector n_line;
	
	probMatrix.clear();
	
	for(size_t i(0);i<probMatrix.size();++i)
	{
		for (size_t j(0);j<4;++j)
		{
			if(relativeMatrix[i][j] != 0.0) 
			{
				z=probMatrix[i][j];		
				n_line.push_back(log2(z));
							
			} else {
			
				z=MINUSINFINI;	
				n_line.push_back(MINUSINFINI);				
			}
					
		}
		
		probMatrix.push_back(n_line);
		
	}
}

void Matrix::compute_relativeMatrix_from_probMatrix()
{	
	double z=0.0;
	SimpleVector n_line;
	
	relativeMatrix.clear();
	
	for(size_t i(0);i<relativeMatrix.size();++i)
	{
		for (size_t j(0);j<4;++j)
		{
			z=probMatrix[i][j];		
			n_line.push_back(pow(2,z));		
		}
		
		relativeMatrix.push_back(n_line);
		
	}
}

	
void Matrix::compute_probMatrix_from_logMatrix()
{	
	double z=0.0;
	SimpleVector n_line;
	SimpleVector s=logMatrix_min_values();
	
	probMatrix.clear();
	
	for(size_t i(0);i<probMatrix.size();++i)
	{
		for (size_t j(0);j<4;++j)
		{
			if(logMatrix[i][j] != MINUSINFINI) 
			{
				z=logMatrix[i][j];		
							
			} else {
			
				z=MINUSINFINI;					
			}
			
			n_line.push_back(z-s[j]);
		}	
			
		probMatrix.push_back(n_line);
		
	}
}


SimpleVector Matrix::logMatrix_min_values()
{
	SimpleVector values;	
	double value=0.0;
		
	for(size_t i(0);i<logMatrix.size();++i)
	{
		for (size_t j(0);j<4;++j)
		{
			
			if((value != MINUSINFINI) and (value>logMatrix[i][j]))
			{
				value=logMatrix[i][j];					
			}
		}	
		
		values.push_back(value);
			
	}
	
	return values;

}
	          
				
SimpleVector Matrix::calcul_sum()
{
	SimpleVector sums;
	double sum;
	
	for(size_t i(0);i<relativeMatrix.size();++i)
	{
		sum=0.0;
		
		for (size_t j(0);j<4;++j)
		{
			sum += relativeMatrix[i][j];
					
		}
		
		sums.push_back(sum);		
					            
	} 
	   
	return sums;  
}
	
	


SimpleVector Matrix::max_values()
{
	SimpleVector values;	
	double value;
		
	for(size_t i(0);i<absoluteMatrix.size();++i)
	{
		value=0.0;
		
		for (size_t j(0);j<4;++j)
		{
			
		if(value<absoluteMatrix[i][j])
			{
				value=absoluteMatrix[i][j];					
			}
		}	
		
		values.push_back(value);
			
	}
	
	return values;

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



/* Function that tests all combinations of the position weight matrix and fills
 sequenceList with all sequences with a score higher than the specified cutoff.*/

void Matrix::sequenceExtract(double cutoff) {
    
    // Double that sums the current combination
    double score(0.0);
    
    // Variables that represent matrix properties, to avoid unnecessery
    // computations at each iteration, increasing performance.
    unsigned int matrixSize = logMatrix.size();
    unsigned int matrixLastElement = matrixSize - 1;
    
    // String that saves current nucleotide sequence
    std::string nucleotideSequence = "";
    
    // Vector that iterates through all possible combinations of matrices
    std::vector<int> iterator;
    for(unsigned int i(0); i < logMatrix.size(); i++) {
        iterator[i] = 0;
    }
    
    // Vector defining the order of the characters
    std::vector<char> basePosition;
    {
        basePosition[0] = 'A';
        basePosition[1] = 'C';
        basePosition[2] = 'G';
        basePosition[3] = 'T';
    }
    
    
    while(iterator[0]!=NUMBER_NUCLEOTIDES) {
        
        // Adds up scored at specific iteration
        for(unsigned int i(0); i < matrixSize; i++) {
            score+= logMatrix[i][iterator[i]];
        }
        
        // Prints all nucleotid combinations that have score larger than cutoff
        if (score >= cutoff) {
            for(unsigned int i(0); i < matrixSize; i++) {
                nucleotideSequence += basePosition[iterator[i]];
            }
            
            sequenceList.push_back(nucleotideSequence);
            nucleotideSequence = "";
        }
        
        iterator[matrixLastElement]++;
        
        for (unsigned int i(matrixLastElement); i>0; i--) {
            if (iterator[i]==NUMBER_NUCLEOTIDES) {
                iterator[i-1]++;
                iterator[i] = 0;
            }
        }
    }
    
    return;
}

/* Function that accesses the extracted DNA sequences and returns a vector of strings. */
std::vector<std::string> Matrix::accessDNASequences() {
    
    if (sequenceList.empty()) {
        throw "Error : No sequences extracted.";
    }
    
    return sequenceList;
    
}

