#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "List.hpp"

class App {
private:

    // Helper method to parse and insert lines from the attendance CSV into the master list.
    void lineToList(List<Data>& masterList, std::string line);

    // Helper method to load pre-existing data (with absences) from master file into list.
    void loadMaster(std::ifstream& masterFile, List<Data>& studentList);

    // Helper method to load each line into the master list.
    void lineToListMaster(List<Data>& masterList, std::string line);

    // Helper method to save master list back to master file.
    void saveMaster(std::ofstream& masterFile, List<Data>& updatedStudentList);

    // Helper method to determine the current date.
    string determineDate();

    // Helper method to add absences to the students in the list.
    void addAbsences(List<Data>& masterList);

    // Helper method to generate a report for the most recent absences.
    void generateRecentAbsenceReport(List<Data>& masterList);

    // Helper method to generate a report for students with absences that exceed a threshold.
    void generateAbsenceThresholdReport(List<Data>& masterList);

    // Helper method to display the report menu.
    void generateReportMenu(List<Data>& masterList);

    // Helper method to search for a student by ID or Name.
    Data* searchStudent(List<Data>& masterList);

    // Helper method to edit absences for a student.
    void editAbsences(List<Data>& masterList);

public:
    // Main method to run the app.
    void runApp();
};

#endif // MENU_HPP