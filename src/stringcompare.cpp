//
//  stringcompare.cpp
//  
//
//  Created by Mättu on 03.10.16.
//
//


#include <iostream>
#include <string>
using namespace std;


bool function() {
    
    return 0;
}

int main() {
    
    string DNA = "GATACA";
    // Test DNA sequence, to be replaced with file input
    
    string input;
    // DNA sequence for which is searched
    
    size_t position = 0;
    // Defines starting position of program
    
    cout << "Please enter DNA Sequence. \n";
    getline(cin, input);
    
    do  {
        position=DNA.find(input, position);
        
        if(position == string::npos) { // if no more matches
            cout << "End of search. \n";
            return 0;
        }
        position++;
        
        // Increments position to avoid endless loop, also ensures that
        // output position starts with 1, and not 0.
        cout << "Found at position " << position << "\n";
        
    } while (position != string::npos);
    
    
    
    return 0;
}
