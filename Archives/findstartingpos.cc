// By Souhail Elaissaoui and Marion Perier. 07/10/2016
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<size_t> find(const string& string_to_find, const vector<string>& genes, int sequence_in_gene);

int main() {
	
	return 0; 
}

// find_sequence() returns a vector with all the staring positions of each occurences of the searched thing
vector<size_t> find_sequence(const string& string_to_find, const vector<string>& genes, int sequence_in_tab) 
		{
			vector<size_t> starting_positions; //it's possible to have several matches in the sequence
			size_t starting_position(-1);
			cout << "SEARCHING '" << string_to_find << "' in the sequence number " << sequence_in_tab << " of the tab " << endl; 
			do {
					starting_position = genes[sequence_in_tab].find(string_to_find, starting_position+1); //the function "find" returns the first position of the first character of the first match
					if(starting_position != string::npos)
					{
						starting_positions.push_back(starting_position);
						cout << starting_positions.size() << " FOUND starting at char " << starting_position << endl;
					}
				} while (starting_position != string::npos);
			cout << " SCAN FINISHED " << starting_positions.size() << " occurences found" << endl;
			return starting_positions;
		}


