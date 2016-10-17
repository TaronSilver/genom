/*!
* File naming rules :
*/
my_useful_class.cc
my-useful-class.cc
myusefulclass.cc
myusefulclass_test.cc // as long as anybody can get the idea 

#ifndef FILENAME_H
#define FILENAME_H

/*!
 * @class Name
 *
 * @brief rules that we must use to keep a clean code
 */

class Name 
{
	public:
	/*!
     * Naming  variable rules :
     */
    /*! GODD  */
	int price_count_reader;    // No abbreviation.
	int num_errors;            // "num" is a widespread convention.
	int calc_BaseProb;         // Most people know what "calc" stands for
	/*! BAD */
	int n;                     // Meaningless.
	int nerr;                  // Ambiguous abbreviation.
	int n_comp_conns;          // Ambiguous abbreviation.
	int wgc_connections;       // Only your group knows what this stands for.
	int pc_reader;             // Lots of things can be abbreviated "pc".
	int cstmr_id;              // Deletes internal letters.
	
	const int kDaysInAWeek = 7;// always put k for a constant
	
	private:
	/*!
	 * Naming  funtions rules :
	*/
	AddTableEntry()
	DeleteUrl()
	OpenFileOrDie()            //Clear words, CapinalsForAllWordsUsed
	
};

#endif
