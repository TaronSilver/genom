
class Sequence
	{
		private:
		double baseProbabibilityA;
		double baseProbabibilityT;
		double baseProbabibilityC;
		double baseProbabibilityG;
		const string sequence;
		Sequence(const string sequence);//constructor
		void calc_BaseProb();
		
			 public:
		
		vector<size_t> find_sequence(const string& string_to_find, const vector<string>& genes, int sequence_in_gene);//TODO

	
	};
