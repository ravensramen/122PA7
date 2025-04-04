//continue load,,, work on parsing




#ifndef MENU_HPP
#define MENU_HPP

#include "AttendanceTracker.hpp"
#include "List.hpp"
#include "studentData.hpp"

#include <time.h>
#include <ctime>
#include <cstring>

class App {
public:
	//default constructor
	App() {};
	//default destructor
	~App() {};

	void runApp(); //public version of run
private:
	void lineToList(List<Data>& Masterlist, string line); //take each line and add to master list
	void loadMaster(ifstream& masterFile, List<Data>& studentList);
	void parseData(istringstream &inputString, Data &output, bool input);
};

#endif