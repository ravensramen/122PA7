#ifndef MENU_HPP
#define MENU_HPP

#include "AttendanceTracker.hpp"
#include "List.cpp"
#include "studentData.hpp"

class App {
public:
	//default constructor
	App() {};
	//default destructor
	~App() {};

	void runApp(); //public version of run
private:
	void lineToList(List<Data>& Masterlist, string line); //take each line and add to master list

};

#endif