//
//  main.cpp
//  
//
//  Created by Mättu on 20.10.16.
//
//

#include <stdio.h>
#include <string>

#include "Matrix.hpp"
#include "Sequence.hpp"
#include "utility.hpp"


//-------------------------------------------------------------------------

int main() {
    
    PROCEDURE procedure;
    
    while (true) {
        procedure = whatToDo();
        
        // What to do if user wants to extract Sequences from a given matrix
        if (procedure == SequencesFromMatrix) {
            system("Clear");
            
            std::string file_name_matrix;
            AskNameMatrix(file_name_matrix);
            Matrix enzyme(file_name_matrix);
            
            std::vector <Sequence> sequence_list;
            sequence_list = Initialization();
            
            std::vector <std::string> binding_sites = enzyme.accessDNASequences();
            
            std::ofstream outputfile;
            std::string output_filename;
            
            std::cout << "What file would you like to save the results to?" << std::endl;
            std::cin >> output_filename;
            
            // Adds format if none specified (-> if there is no point in the string)
            if(output_filename.find(".")==std::string::npos) {
                output_filename += ".txt";
            }
            
            outputfile.open(output_filename);
            
            for(unsigned int i(0); i<sequence_list.size(); i++) {
                
                std::cout << "\n \n \n Going through sequence " << i + 1 << std::endl;
                
                for(unsigned int j(0); j<binding_sites.size(); j++) {
                    sequence_list[i].find_sequence(binding_sites[j], outputfile);
                }
            }
            
            outputfile.close();
            
            std::cout << "Would you like to create a new probability weight matrix " << std::endl
                      << "based on your results? " << std::endl
                      << "Enter 1 for yes" << std::endl
                      << "Enter 0 for no" << std::endl;
            
            bool saveoutput;
            std::cin >> saveoutput;
            
            if(saveoutput) {
                Matrix new_PWM(matrix_from_sequence_results(output_filename), absoluteMatrix);
                new_PWM.save_matrix_loop();
            }
            
            
        }
        
        if (procedure == MatrixFromSequences) {
            system("Clear");
            std::vector <Sequence> sequence_list;
            sequence_list = Initialization();
            
            Matrix enzyme(generate_PWM_from_Seq_list(sequence_list, false),absoluteMatrix);
            enzyme.save_matrix_loop();
            
            
        }
        
        if (procedure == Exit) {
            break;
        }
        
    }
    
    
    return 0;
}


//-----------------------------------------------------------------------


