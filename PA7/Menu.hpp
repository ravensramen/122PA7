#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "List.hpp"

//class method definitions and descriptions in "Menu.cpp"

class App {

private:
    void lineToList(List<Data>& masterList, std::string line);

    void loadMaster(std::ifstream& masterFile, List<Data>& studentList);

    void lineToListMaster(List<Data>& masterList, std::string line);

    void saveMaster(std::ofstream& masterFile, List<Data>& updatedStudentList);

    string determineDate();
    string determineCustomDate();    

    void addAbsences(List<Data>& masterList, string date);

    void generateRecentAbsenceReport(List<Data>& masterList);

    void generateAbsenceThresholdReport(List<Data>& masterList);

    void generateReportMenu(List<Data>& masterList);

    Data* searchStudent(List<Data>& masterList);

    void editAbsences(List<Data>& masterList);

public:
    
    void runApp();
};

#endif 