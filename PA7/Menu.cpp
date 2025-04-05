
#include "Menu.hpp"

void App::runApp() {

	ifstream courseData;
	courseData.open("classlist.csv"); //open input file for reading

	ifstream masterData;
	masterData.open("masterlist.csv"); //load master list, for reading

	ofstream masterDataOutput;
	masterDataOutput.open("masterlist.csv"); //same as above... but mode for writing

	List<Data> masterList;

	int menuChoice = 0;

	bool updatedAttendance = false; //to insure load not called without changed -> can erase data and lead to nullptrs
	bool customDate = false; //to denote custom date was selected (only used in testing...)


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

			//cout << "Attendance list successfully inputted!"<<endl; for debugging
			//masterList.printList(); //for testing, insures list is linked properly

			system("pause"); //pause to view list/messages before returning to menu
			system("cls");
		}break;
		case 2: {

			if (updatedAttendance == false) {
				cout << "You haven't made any changes...";
				system("pause");
				system("cls");
				break; //don't call if no updates made to attendance (otherwise it destroys list!)

			}
				

			//load recent list changes into linked list
			if (!masterList.isEmpty()) { //insure list object of app is empty
				masterList.destroyList();
			}

			loadMaster(masterData, masterList); //load data into updated list
			updatedAttendance == false; //reset attendance to false if updated, prevents another load until another update
			
			cout << "Updates have been applied";
			system("pause");
			system("cls");

		}break;
		case 3: {
			//store master list into MasterList.csv (masterData)
			if (masterList.isEmpty()) { //precondition: list exists
				cout << "You need to populate your list first silly...";
				return;
			}
			saveMaster(masterDataOutput, masterList); //save all list contents (including absences)
			system("pause");
			system("cls");

		}break;
		case 4: { //mark absences (add to stack)

			string date;

			system("cls");
			if (customDate == false) { 

				date = determineDate();
			}

			else if (customDate == true) {//option to add custom date (mostly for debugging)
				date = determineCustomDate();
			}

			cout << "Today's date is: " << date;
			addAbsences(masterList, date); //checks for empty list, iterates through to add absence

			system("pause");
			system("cls");

			updatedAttendance = true; //allows loading to rewrite old data
			customDate == false; //insures customDate function is set back to false after being run

		}break;
		case 5: {

			system("cls");
			editAbsences(masterList);  // call edit Absences function
			system("pause");
			system("cls");
			break;

		}break;
		case 6: {
			generateReportMenu(masterList); // call the report submenu function
			break;


		}break;
		case 7: {
			system("cls");
			//ifstream and ofstream destructors automatically handle file closing
			cout << "Byeee...." << endl;
		}break;

		case 8: { //super secret 8th option,,, allows custom date input (to test adding more dates)
			system("cls");
			customDate = true;
			cout << "Shhh... you found a secret menu option... to manipute time itself..." << endl;
			cout << "You may now enter a custom date when marking absences..." << endl;
			system("pause");
			system("cls");
		}break;
		}

	};
}

void App::lineToList(List<Data>& masterList, string line) {
	//parce each line >>convert to student node

	istringstream iss(line); //storing line as a stream stream type for parsing

	string inputVal; //blank string to store line components

	Data student; //new data to store each line component

	getline(iss, inputVal, ',');
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

void App::loadMaster(ifstream& masterFile, List<Data>& studentList) {
	string line;  // variable to hold each line of the file

	// check if the file is open		
	if (masterFile.is_open()) {
		//cout << "master file opened successfully" << endl << endl; //for debugging

		// loop through the lines in the file
		while (getline(masterFile, line)) {
			lineToListMaster(studentList, line); //load pre-existing list (with absences)
		}
		cout << "linked list updated to include absences" << endl;

	}
	else {
		cout << "failed to open file, did you save recent absences?" << endl;
	}
}

void App::lineToListMaster(List<Data>& masterList, string line) {
	// similar to lineToList, adds absence number and stack components

	istringstream iss(line); // store line as a stream for parsing
	string inputVal; // blank string to store line components

	Data student; // new Data object to store each line component

	// parse each component
	getline(iss, inputVal, ',');
	student.setRecordNumber(stoi(inputVal));


	getline(iss, inputVal, ',');
	student.setIdNumber(stoi(inputVal));

	string firstName, lastName;
	getline(iss, firstName, ',');
	getline(iss, lastName, ',');

	inputVal = firstName + ',' + lastName;
	student.setName(inputVal); 

	getline(iss, inputVal, ',');
	student.setEmail(inputVal);

	// parse credits, handle audit case
	getline(iss, inputVal, ',');
	if (inputVal == "AU") {
		student.setCredits(-1); // negative value denotes audit
	}
	else {
		student.setCredits(stoi(inputVal));
	}

	getline(iss, inputVal, ',');
	student.setMajor(inputVal);

	getline(iss, inputVal, ',');
	student.setLevel(inputVal);

	getline(iss, inputVal, ',');
	student.setNumAbsences(stoi(inputVal)); 

	// ddd absence dates to the student's absence stack
	for (int i = 0; i < student.getNumAbsences(); ++i) {
		getline(iss, inputVal, ',');
		student.setAbsenceDate(inputVal); // push date onto student's stack
	}

	masterList.insertAtEnd(student); // insert updated student data into the linked list
}

void App::saveMaster(ofstream& masterFile, List<Data>& updatedStudentList)
{
	// open the output file for writing
	if (!masterFile.is_open()) {
		cout << "Failed to open the master file for writing." << endl;
		return;
	}

	// get the head of the linked list
	studentNode<Data>* pTemp = updatedStudentList.getpHead();
	
	// iterate through the list and write each student's data to the file
	while (pTemp != nullptr) {
		// get the student data from the node
		Data student = pTemp->getNodeData();

		
		masterFile << student.getRecordNumber() << ","; 
		masterFile << student.getName() << ","; 
		masterFile << student.getEmail() << ",";  
		masterFile << (student.getCredits() == -1 ? "AU" : std::to_string(student.getCredits())) << ",";  
		masterFile << student.getMajor() << ",";  
		masterFile << student.getLevel() << ",";  
		masterFile << student.getNumAbsences() << ",";  

		
		absenceStack<string> absences = student.getAbsences();  // copy of stack to write dates in correct order

		// check if the absence stack is empty 
		if (!absences.isEmpty()) {
			
			while (!absences.isEmpty()) {
				string date = absences.topAbsence();  
				masterFile << date << ",";  
				absences.popAbsence();  
			}
		}

		// end the line after writing all the data
		masterFile << endl;

		// move to the next student
		pTemp = pTemp->getNext();
	}

	cout << "Master list successfully saved!" << endl;
}


string App::determineDate() {
	// get the current time
	time_t currentTime = time(nullptr);  
	tm localTime; 
	
	localtime_s(&localTime, &currentTime);  

	// format the time as a string (YYYY-MM-DD)
	char buffer[11]; // buffer to store the formatted string
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

	return string(buffer);  // return the formatted string
}

string App::determineCustomDate() {
	string date;
	cout << "Enter date in format: YYYY-MM-DD";
	cin>>date;
	return date;
}

void App::addAbsences(List<Data>& masterList, string date) {
	//iterate through list and prompt to add absence for today's date
	if (masterList.isEmpty()) {
		cout << endl; //spacing
		cout << "Looks like no one's loaded into your class..." << endl << "Your RateMyProfessor score must be rough... or you forgot to Load." << endl << endl;
		return;
	}

	studentNode<Data>* pTemp = masterList.getpHead();

	char absenceIndicator = '\0';

	cout << endl << endl << "Press N to indicate student absence, press Y if they were present: " << endl;

	while (pTemp != nullptr) { //edit absences while not at end of student list
		absenceIndicator = '\0'; //reset absence indicator after each loop
		cout << "Was " << pTemp->getNodeData().getName() << " present today?" << endl;
		cin >> absenceIndicator;
		if (absenceIndicator == 'N' || absenceIndicator == 'n') { //only modify node if prompted

			pTemp->getNodeData().setAbsenceDate(date);  // push the date onto the stack
			int currentAbsences = pTemp->getNodeData().getNumAbsences();
			pTemp->getNodeData().setNumAbsences(currentAbsences + 1); 
		}
		system("cls");
		pTemp = pTemp->getNext(); //iterate onto next node
	}
	cout << "Attendence data successfully updated, see you tomorrow!" << endl;
}

// function to generate a report for all students showing only the most recent absence.
void App::generateRecentAbsenceReport(List<Data>& masterList) {
	if (masterList.isEmpty()) {
		cout << "No students loaded in the list." << endl;
		return;
	}

	cout << "Most Recent Absences:" << endl;

	// iterate through the list, print the most recent absence 
	studentNode<Data>* pTemp = masterList.getpHead();

	while (pTemp != nullptr) {
		Data student = pTemp->getNodeData();
		string mostRecentAbsence = "No absences :)"; // Default message if no absences

		if (!student.getAbsences().isEmpty()) {
			// Get the most recent absence (peek the top of the stack)
			mostRecentAbsence = student.getAbsences().topAbsence();
		}

		cout << "Student: " << student.getName() << ", Most Recent Absence: " << mostRecentAbsence << endl;

		pTemp = pTemp->getNext();

	}

	cout << "End of report." << endl;
}

// function to generate a report for students with absences that match a certain num absences
void App::generateAbsenceThresholdReport(List<Data>& masterList) {
	int threshold;

	cout << "Enter the minimum number of absences: ";
	cin >> threshold;

	if (masterList.isEmpty()) {
		cout << "No students loaded in the list." << endl;
		return;
	}

	cout << "Students with Absences >= " << threshold << " :" << endl;

	// iterate through the list and print students who have absences >= threshold
	studentNode<Data>* pTemp = masterList.getpHead();

	while (pTemp != nullptr) {
		Data student = pTemp->getNodeData();
		int numAbsences = student.getNumAbsences(); // get the number of absences

		if (numAbsences >= threshold) {
			cout << "Student: " << student.getName() << ", Number of Absences: " << numAbsences << endl;
		}

		pTemp = pTemp->getNext();
	}

	cout << "End of report." << endl;
}

void App::generateReportMenu(List<Data>& masterList) {
	int reportChoice = 0;

	// prompt for the type of report the user wants
	cout << "Absence Report Menu:" << endl;
	cout << "Enter 1 to view the most recent absence for all students." << endl;
	cout << "Enter 2 to generate students with a specific absence count." << endl;
	cin >> reportChoice;

	switch (reportChoice) {
	case 1:
		generateRecentAbsenceReport(masterList);
		break;

	case 2:
		generateAbsenceThresholdReport(masterList);
		break;

	default:
		cout << "Invalid choice!" << endl;
		break;
	}
}

// function to search a student by ID or Name
Data* App::searchStudent(List<Data>& masterList) {
	string searchType;
	cout << "Do you want to search by ID or Name? (type your choice): ";
	cin >> searchType;

	if (searchType == "ID") {
		int studentId;
		cout << "Enter student ID: ";
		cin >> studentId;

		studentNode<Data>* pTemp = masterList.getpHead();

		while (pTemp != nullptr) {
			if (pTemp->getNodeData().getIdNumber() == studentId) {
				return &pTemp->getNodeData();  // return the student's data if found
			}
			pTemp = pTemp->getNext();
		}
		cout << "ID not found :( " << endl;
	}
	else if (searchType == "Name") {
		string studentName;
		cout << "Enter student Name: ";
		cin.ignore();  // ignore newline from previous input
		getline(cin, studentName);

		studentNode<Data>* pTemp = masterList.getpHead();
		while (pTemp != nullptr) {
			if (pTemp->getNodeData().getName() == studentName) {
				return &pTemp->getNodeData();  // return the student's data if found
			}
			pTemp = pTemp->getNext();
		}
		cout << "Student not found by Name." << endl;
	}
	else {
		cout << "Invalid search type!" << endl;
	}
	return nullptr;  // return nullptr if no student found
}

void App::editAbsences(List<Data>& masterList) {
	Data* student = searchStudent(masterList);  // get student by ID or Name

	if (student == nullptr) {
		cout << "Student not found. Back to the menu..." << endl;
		return;
	}

	// print the student name and absence history
	cout << "Editing absences for: " << student->getName() << endl;
	cout << "Current absences: " << endl;

	absenceStack<string> absences = student->getAbsences();

	// check if there are any absences to display
	if (absences.isEmpty()) {
		cout << "No absences found for this student." << endl;
	}
	else {
		while (!absences.isEmpty()) {
			cout << absences.topAbsence() << endl;  // display top absence date
			absences.popAbsence();  // remove the top element after displaying it
		}
	}

	// ask the user for the date to remove
	string dateToRemove;
	cout << "Enter the date to remove (YYYY-MM-DD) or type 'none' to skip: ";
	cin >> dateToRemove;

	if (dateToRemove != "none") {
		absenceStack<string> updatedAbsences = student->getAbsences();  // copy of original absences
		bool found = false;

		while (!updatedAbsences.isEmpty()) {
			if (updatedAbsences.topAbsence() == dateToRemove) {
				// F=found the absence, so remove it
				updatedAbsences.popAbsence();
				found = true;
				break;
			}
			else {
				updatedAbsences.popAbsence();
			}
		}

		if (found) {
			student->setAbsences(updatedAbsences);  
			int newAbsenceCount = updatedAbsences.size();  
			student->setNumAbsences(newAbsenceCount);  // update the total number of absences
			cout << "Absence on " << dateToRemove << " has been removed!" << endl;
		}
		else {
			cout << "No absence found on " << dateToRemove << " for this student." << endl;
		}
	}
}

