/*
 * recommender_system.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: jacob
 */

//Include Statements

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <fstream>
#include <string>
#include <stdlib.h>

//The namespace that will be used: std and ublas

using namespace std;

using namespace boost::numeric::ublas;

matrix<double> DATA_MATRIX (NULL, NULL); //Initializes the data matrix to a matrix of doubles with dimensions NULL by NULL in order to save storage space.

//This function returns a matrix filled with data from a text file for the recommender system to process.

void getDataMatrix(const string fileName) {

	string line; //The current line read from the file is stored here

	string tmp; //This string will be used later on as a temporary storage for substrings when parsing lines of the text file;

	int ROWS = 0; //The number of rows in the returned matrix. This number will be adjusted below based off of input from the text file.

	int COLUMNS = 0; /*The number of columns in the returned matrix. This number will be adjusted below based off of input from the text file.
					   COLUMNS is initialized to 1 because it is incremented based off of the number of spaces in a line of the text file
					   which falls short by 1 of the amount of columns of data.*/

	ifstream file; //Invoking ifstream

	file.open((fileName).c_str()); /*Opening the file. The fileName variable is converted into a C string so it can be passed as an argument
									 to the open() function*/

	/*This loop goes through each line of the file and increments ROWS by 1 every line that is read in order to set ROWS to the number of rows
	  of data.*/

	while(getline(file, line)) {

		++ROWS;

	}

	/*This for loop goes through the last line of the file (the most recent one read) and increments COLUMNS every time a whitespace is
	  detected in order to measure the number of columns of data. The reason COLUMNS was set to 1 above is because, for example, if the
	  number of columns of data is 3, a line in the text file will contain 3 values but only two spaces (value value value). Setting
	  COLUMNS to 1 compensates for the mismatch between the number of values in a line and the number of spaces in a line*/

	for(int i = 0; i < line.length(); i++) {

		if(isspace(line.at(i)))
			++COLUMNS;
	}

	file.clear();
	file.seekg(0);

	DATA_MATRIX.resize(ROWS, COLUMNS, true); /*Resizes the matrix to the proper number of rows and columns of data in the data file, as well as preserves
										 	   existing data in the matrix.*/

	//This set of for loops takes all of the numeral values inside of the data file and puts them into elements of the data matrix in the proper order.

	for(unsigned int i = 0; i < DATA_MATRIX.size1(); i++) {

		getline(file, line); //Retrieves the next line in the data file

		for(unsigned int j = 0; j < DATA_MATRIX.size2(); j++) {

			DATA_MATRIX (i, j) = atof(line.std::string::substr(0, line.find_first_of(" ")).c_str()); /*Casts the first numeral value in the retrieved line to a
																									   double and puts it into the proper element of the data
																									   matrix.*/

			line.erase(0, line.find_first_of(" ") + 1); /*Removes the first numeral value in the retrieved line so the next numeral value in the retrieved line
			 	 	 	 	 	 	 	 	 	 	 	  is considered the new first numeral value in the retrieved line and the current loop can be repeated.*/

		}

	}


	file.close();  //Closing the file

}

int main () {

	getDataMatrix("test.txt"); //Retrieves data from the data file and puts it into the data matrix

	cout << DATA_MATRIX; //Prints the dimensions and the values inside of DATA_MATRIX for testing if the getDataMatrix function works properly

	return 0; //Returning 0

}
