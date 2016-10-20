#include "Matrix.hpp"



Matrix::Matrix(const std::string& fileName) {
    mkProbMatrix(fileName);
}


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
                y=probMatrix[i][j];
                x=log2(y/bp[j]); /*Calcul the new values we need*/
                logMatrix[i][j] = x;/*Stock this new x values in the logMatrix*/
            }
        }
    }
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

bool Matrix::mkProbMatrix(std::string const& fileName)
{
    //open file containing PWM
    std::ifstream PWM;
    PWM.open("fileName");
    
    //send an error if there is a problem opening file
    if (PWM.fail()) {
        
        throw std::string("Error: Cannot read PWM file");
        return 0;
        
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
            
            //(5) pushback the new row
            Matrix::probMatrix.push_back(rowi);
        }
        
        
        PWM.close();
        return 1;
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
