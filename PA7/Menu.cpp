#include "Menu.hpp"

void App::runApp() {

	ifstream courseData;
	courseData.open("classlist.csv"); //open input file for reading

	List<Data> masterList;

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

			string line; //to parse each line
			while (getline(courseData, line)) { //stores each line to be parsed through until csv nullptr

				//funct to convert line to linked list data, should be called multiple times
				lineToList(masterList, line); 

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

void App::lineToList(List<Data> &masterList, string line) {
	//parce each line >>convert to student node
	cout << line; //for testing
	cout << "in lineToList";

	//make a node
	istringstream iss(line); //storing line as a stream stream type for parsing
	
	string inputVal; //blank string to store line components

	Data* student = new Data; //new data to store each line component

	getline(iss,inputVal,','); //get record num
	student->setRecordNumber(stoi(inputVal));
	
	getline(iss, inputVal, ',');
	student->setRecordNumber(stoi(inputVal));

	string firstName;
	string lastName;
	getline(iss, firstName, ',');
	getline(iss, lastName, ',');

	inputVal = firstName + ',' + lastName;
	student->setName(inputVal);

	getline(iss, inputVal, ',');
	student->setEmail(inputVal);

	getline(iss, inputVal, ',');
	if (inputVal == "AU") {
		inputVal = -1; // negative to denote audit
	}
	student->setCredits(stoi(inputVal));

	getline(iss, inputVal, ',');
	student->setMajor(inputVal);

	getline(iss, inputVal, ',');
	student->setLevel(inputVal);
//insert student node into master list

}