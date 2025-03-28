#include "Menu.hpp"

void App::runApp() {

	ifstream courseData("classlist.csv"); //open input file for reading

	int menuChoice = 0;

	while (menuChoice != 7) { //continue to display menu until user decides to exit
		cout << "Welcome to the attendance tracker app! " << endl;

		cout << "Please enter the number coresponding to choice: " << endl;
		cout << "1. Import Attendance List" << endl;
		cout << "2. Load Master List" << endl;
		cout << "3. Store Master List" << endl;
		cout << "4. Mark Absences" << endl;
		cout << "5. Edit Absences" << endl;
		cout << "6. Generate Report" << endl;
		cout << "7. Exit Program" << endl;

		cin >> menuChoice;


		switch (menuChoice) {
		case 1: {
			//import attendance csv file
			if (courseData.is_open()) {
				cout << "Attendance file has been opened properly" << endl;
			}
			cout << "Attendance list successfully inputted!"<<endl;

		}break;
		case 2: {
			//load list into linked list
		}break;
		case 3: {

		}break;
		case 4: {

		}break;
		case 5: {

		}break;
		case 6: {

		}break;
		case 7: {
			system("cls");
			//save and close files properly
			cout << "Byeee...." << endl;
		}break;
		}

	};
}