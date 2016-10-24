#include "Matrix.hpp"



Matrix::Matrix(const std::string& fileName) {
    mkProbMatrix(fileName);
}




/*
 
 Commented out because not used at the moment and is producing compiling error. --mattminder

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

*/



MATRIX_TYPE Matrix::mkProbMatrix_type(std::string const& fileName){
	
    //open file containing PWM
    MATRIX_TYPE result;
    std::ifstream PWM;
    PWM.open(fileName);
    
    //send an error if there is a problem opening file
    if (PWM.fail()) {
        
        throw std::string("Error: Cannot read PWM file");
        return MATRIX_TYPE::ERROR;
        
    } else {
        
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
            rowi = { A, C, G, T };
            
           
            //(5) identify the type of the matrix and (6) pushback the new row
            double sum(0.); 
            double max(-100.);
			for(size_t i(0); i<rowi.size(); ++i){
				sum= sum + rowi[i];
				if (rowi[i] > max){ max =rowi[i];}
			}
			if (sum==1.0 and max < 1.0){ Matrix::ppmatrix.push_back(rowi); result = MATRIX_TYPE::PPMatrix; } 
			//the file corresponds to a position probability matrix of absolute probabilities (PPMatrix)
			if (sum > 1.0 and max == 1.0){Matrix::ppmatrix_consensus.push_back(rowi); result = MATRIX_TYPE::PPMatrix_consensus; }
			//the file corresponds to a position probability matrix of  probabilities relative to consensus (PPMatrix_consensus)
			if ( max < 0.){Matrix::pssmatrix.push_back(rowi); result = MATRIX_TYPE::PSSMatrix;}
            //the file corresponds to a position-specific scoring matrix (log of PPM) named PSSMatrix
            if(max >= 0. and sum < 0. ) {Matrix::pssmatrix_minus_constant.push_back(rowi); result = MATRIX_TYPE::PSSMatrix_minus_constant;} //pas top egalite avec zero donc met >= (?)
            //the file corresponds to a position-specific scoring matrix - constant (PSSMatrix_minus_constant)
		}
		PWM.close();
        return result;
	}
	
 }
	


/* Function that tests all combinations of the position weight matrix and fills
 sequenceList with all sequences with a score higher than the specified cutoff.*/

void Matrix::sequenceExtract(double cutoff) {
    
    // Double that sums the current combination
    double score(0.0);
    
    // Variables that represent matrix properties, to avoid unnecessery
    // computations at each iteration, increasing performance.
    unsigned int matrixSize = pssmatrix.size();
    unsigned int matrixLastElement = matrixSize - 1;
    
    // String that saves current nucleotide sequence
    std::string nucleotideSequence = "";
    
    // Vector that iterates through all possible combinations of matrices
    std::vector<int> iterator;
    for(unsigned int i(0); i < pssmatrix.size(); i++) {
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
            score+= pssmatrix[i][iterator[i]];
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

