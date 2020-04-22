#ifndef _STRING_PROCESSING_H_
#define _STRING_PROCESSING_H_


#include <regex> 
#include <sstream> 
#include <stdio.h>
#include <iostream>
#include <string>



//void processInterval(std::string interval);


//nie moze byc negatywnych?
void processInterval(std::string interval, unsigned int& globalStart, unsigned int& globalEnd) {

	std::regex intervalStart("[-]{0,1}[0-9]+,");
	std::regex intervalEnd(",[-]{0,1}[0-9]+");

	std::string startNum = "";
	std::string endNum = "";

	//TODO: jaki typ long int?
	int intrvlStart = 0;
	int intrvlEnd = 0;

	std::smatch match;

	regex_search(interval, match, intervalStart);

	if (match.empty()) {
		std::cerr << "B³êdnie podany przedzia³!" << std::endl;
		//TODO: exit
	}

	//std::cout << "Znaleziono: " << match.str() << std::endl;
	startNum = match.str().substr(0, match.str().length() - 1);
	//std::cout << "Uzyskano: " << startNum << std::endl;

	regex_search(interval, match, intervalEnd);

	if (match.empty()) {
		std::cerr << "B³êdnie podany przedzia³!" << std::endl;
		//TODO: exit
	}

	//std::cout << "Znaleziono: " << match.str() << std::endl;
	endNum = match.str().substr(1, match.str().length() - 1);
	//std::cout << "Uzyskano: " << endNum << std::endl;


	std::stringstream processNums1(startNum);
	std::stringstream processNums2(endNum);

	//wielokrotne uzycie streama jakis bug ze daje 0 dla endNum
	/*processNums >> intrvlStart;
	processNums.str(endNum);
	processNums >> intrvlEnd;
	*/
	processNums1 >> intrvlStart;
	processNums2 >> intrvlEnd;

	std::cout << "start = " << intrvlStart << "\t| end = " << intrvlEnd << "\n" << std::endl;

	if (intrvlStart > intrvlEnd) { //TODO: czy mo¿e byæ równy
		std::cerr << "Poczatek przedzia³u nie moze byæ wiekszy od konca!" << std::endl;
	}

	globalStart = intrvlStart;
	globalEnd = intrvlEnd;
}

#endif //_STRING_PROCESSING_H_