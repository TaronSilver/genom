//
//  loadfile.cpp
//  
//
//  Created by Mättu on 03.10.16.
//
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
    

    string filename;
    
    cout << "What file would you like to open? \n";
    getline(cin, filename);
    
    if(string::npos != filename.find("fasta")) {
    // How the contents are treated in case a fasta file is opened
        
        string line1;
        string line2;
        
        ifstream myfile (filename);
        if (myfile.is_open())
        {
            while ( getline (myfile,line1) )
            {
                cout << line1 << '\n';
                getline (myfile,line2);
                cout << line2 << '\n';
            
                // The two lines are read and saved only for the time of the loop.
                // Therefore the objects should be initiated at this point.
            }
            myfile.close();
        }
        else cout << "Unable to open file \n";
    }
    
    
    if(string::npos != filename.find("mat")) {
        // How the contents are treated in case a mat file (matrix) is opened
        
        string line;
        
        ifstream myfile (filename);
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
            {
                cout << line << '\n';
                
                // Here will be defined how the lines are treated.
                
            }
            myfile.close();
        }
        else cout << "Unable to open file \n";
    }
    
    
        
        
    
    
    return 0;
}
