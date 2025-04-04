#include "Menu.hpp"

void App::runApp() {

	ifstream courseData;
	courseData.open("classlist.csv"); //open input file for reading

	ifstream masterData;
	masterData.open("masterlist.csv"); //load master list


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
			system("cls");
			//import attendance csv file
			if (courseData.is_open()) {
				cout << "Attendance file has been opened properly!" << endl << endl;
			}

			string line; //to parse each line
			while (getline(courseData, line)) { //stores each line to be parsed through until csv nullptr
				lineToList(masterList, line); 
			}	

			//cout << "Attendance list successfully inputted!"<<endl; for debuggin
			masterList.printList(); //for testing, insures list is linked properly

			system("pause"); //pause to view list/messages before returning to menu
			system("cls"); 
		}break;
		case 2: {
			//load list into linked list
			if (!masterList.isEmpty()) { //insure list object of app is empty, or would write to end
				masterList.destroyList();
			}
			loadMaster(masterData, masterList); //load data into updated list


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

	//make a node
	istringstream iss(line); //storing line as a stream stream type for parsing
	
	string inputVal; //blank string to store line components

	Data student; //new data to store each line component

	getline(iss,inputVal,','); //get record num
	student.setRecordNumber(stoi(inputVal));
	
	getline(iss, inputVal, ',');
	student.setRecordNumber(stoi(inputVal));

	string firstName;
	string lastName;
	getline(iss, firstName, ',');
	getline(iss, lastName, ',');

	inputVal = firstName + ',' + lastName;
	student.setName(inputVal);

	getline(iss, inputVal, ',');
	student.setEmail(inputVal);

	getline(iss, inputVal, ',');
	if (inputVal == "AU") {
		student.setCredits(-1); //negative to denote audit
	}
	else student.setCredits(stoi(inputVal)); //if non-audit

	getline(iss, inputVal, ',');
	student.setMajor(inputVal);

	getline(iss, inputVal, ',');
	student.setLevel(inputVal);

	masterList.insertAtEnd(student); 

	//cout << line; //for testing, indicates the line was successfully entered
}

void App::loadMaster(ifstream& masterFile, List<Data> &studentList) {
	string line;  // Variable to hold each line of the file

	// Check if the file is open		
	 if (masterFile.is_open()) {
		cout << "master file opened successfully" << endl << endl; //for debuggin

	// Loop through the lines in the file
		while (getline(masterFile, line)) {
			lineToListMaster(studentList, line); //load pre-existing list (with absences)
		}
		cout << "linked list updated to include absences" << endl;

		}
	else {
		cout << "failed to open file" << endl;
	}
}

void App::lineToListMaster(List<Data>& masterList, string line) {
	// Similar to lineToList, adds absence number and stack components

	istringstream iss(line); // Store line as a stream for parsing
	string inputVal; // Blank string to store line components

	Data student; // New Data object to store each line component

	// Parse record number
	getline(iss, inputVal, ',');
	student.setRecordNumber(stoi(inputVal));

	// (There's a duplicate line setting the record number, so this one should be removed)
	//getline(iss, inputVal, ',');
	//student.setRecordNumber(stoi(inputVal));

	string firstName, lastName;
	getline(iss, firstName, ',');
	getline(iss, lastName, ',');

	inputVal = firstName + ',' + lastName;
	student.setName(inputVal); // Set full name

	// Parse email
	getline(iss, inputVal, ',');
	student.setEmail(inputVal);

	// Parse credits, handle audit case
	getline(iss, inputVal, ',');
	if (inputVal == "AU") {
		student.setCredits(-1); // Negative value denotes audit
	}
	else {
		student.setCredits(stoi(inputVal)); // Otherwise, set regular credits
	}

	// Parse major
	getline(iss, inputVal, ',');
	student.setMajor(inputVal);

	// Parse level
	getline(iss, inputVal, ',');
	student.setLevel(inputVal);

	// Parse the number of absences
	getline(iss, inputVal, ',');
	student.setNumAbsences(stoi(inputVal)); // Set number of absences

	// Add absence dates to the student's absence stack
	for (int i = 0; i < student.getNumAbsences(); ++i) {
		getline(iss, inputVal, ',');
		student.setAbsenceDate(inputVal); // Push date onto student's stack
	}

	// Insert the student into the master list
	masterList.insertAtEnd(student); // Insert updated student data into the linked list
}