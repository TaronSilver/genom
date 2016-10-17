#ifndef FILENAME_H
#define FILENAME_H

/*!
 * @class Name
 *
 * @brief DESCRIPTION OF THE CLASS
 */
 
 class Name
 {
	private:
	type_attribute attribute; /*! Brief description  */
	
	
	public:
	/*!
     * @brief DESCRIPTION OF FUNCTION
     *
     * @param INPUT 
     * @return OUTPUT
     */
     output_type function_name1(input_type...);
     
     /*!
     * @brief Constructor
     */
     Name();
     
     /*!
     * @brief Destructor
     */
     ~Env();
     
	/*!
     * @brief No copies
     */
	Name(const Name&) = delete;
	
	/*!
     * @brief DESCRIPTION OF FUNCTION
     */
     void function_name2();
     
	/*!
     * @brief DESCRIPTION OF FUNCTION
     *
     * @param INPUT 
     */
     void function_name3(input_type...);
     
     /*!
     * @brief DESCRIPTION OF FUNCTION
     *
     * @return OUTPUT
     */
     output_type function_name4();
     
};
 
 
 #endif
