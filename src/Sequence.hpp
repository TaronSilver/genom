#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <vector>

void Initialization();
void ask_name(std::string entry_name);
std::vector <std::string> extract_sequence(std::string const& entry_name);
bool invalid_format(std::string file_name);


class Sequence
	{
		public:
		Sequence(const std::string sequence);//constructor
		
		std::vector<size_t> find_sequence(const std::string& string_to_find, const std::vector<std::string>& genes, int sequence_in_gene);//TODO
		//void initialization(); // Allows to ask the name of the file we want to open, with exception handling
		
		
		private:
		double baseProbabibilityA;
		double baseProbabibilityT;
		double baseProbabibilityC;
		double baseProbabibilityG;
		const std::string sequence_;
		
		void calc_BaseProb();
		//bool invalid_format(std::string file_name); // MattMinder
		//void ask_name(std::string& entry_name); // Actually ask the file's name
		//std::vector <std::string> extract_sequence(std::string const& entry_name); // Returns a vector containing all the different strings contained in the file.
	};

#endif
