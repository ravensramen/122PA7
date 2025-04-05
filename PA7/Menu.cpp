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

			if (updatedAttendance == false) break; //don't call if no updates made to attendance

			//load recent list changes into linked list
			if (!masterList.isEmpty()) { //insure list object of app is empty, or would write to end
				masterList.destroyList();
			}

			loadMaster(masterData, masterList); //load data into updated list
			updatedAttendance == false; //reset attendance to false if updated, prevents another load until another update

		}break;
		case 3: {
			//store master list into MasterList.csv (masterData)
			if (masterList.isEmpty()) { //precondition: list exists
				cout << "You need to populate your list first silly...";
				return;
			}
			saveMaster(masterDataOutput, masterList); //save all list contents (including absences)

		}break;
		case 4: { //mark absences (add to stack)

			system("cls");
			string date;
			date = determineDate();

			cout << "Today's date is: " << date;
			addAbsences(masterList); //checks for empty list, iterates through names to add absence

			system("pause");
			system("cls");

			updatedAttendance = true; //allows loading to rewrite old data

		}break;
		case 5: {

			system("cls");
			editAbsences(masterList);  // Call Edit Absences function
			system("pause");
			system("cls");
			break;

		}break;
		case 6: {
			generateReportMenu(masterList); // Call the report submenu function
			break;


		}break;
		case 7: {
			system("cls");
			//save and close files properly
			cout << "Byeee...." << endl;
		}break;
		}

	};
}

void App::lineToList(List<Data>& masterList, string line) {
	//parce each line >>convert to student node

	//make a node
	istringstream iss(line); //storing line as a stream stream type for parsing

	string inputVal; //blank string to store line components

	Data student; //new data to store each line component

	getline(iss, inputVal, ','); //get record num
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
		cout << "failed to open file, did you save recent absences?" << endl;
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


	getline(iss, inputVal, ',');
	student.setIdNumber(stoi(inputVal));

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

void App::saveMaster(ofstream& masterFile, List<Data>& updatedStudentList)
{
	// Open the output file for writing. If the file is not open, print an error message and return.
	if (!masterFile.is_open()) {
		cout << "Failed to open the master file for writing." << endl;
		return;
	}

	// Get the head of the linked list
	studentNode<Data>* pTemp = updatedStudentList.getpHead();

	// Iterate through the list and write each student's data to the file
	while (pTemp != nullptr) {
		// Get the student data from the node
		Data student = pTemp->getNodeData();

		// Write the student's basic information: record number, name, email, etc.
		masterFile << student.getRecordNumber() << ",";  // Record number
		masterFile << student.getName() << ",";  // Full name
		masterFile << student.getEmail() << ",";  // Email
		masterFile << (student.getCredits() == -1 ? "AU" : std::to_string(student.getCredits())) << ",";  // Credits (AU for audit, otherwise regular credits)
		masterFile << student.getMajor() << ",";  // Major
		masterFile << student.getLevel() << ",";  // Level (e.g., freshman, sophomore, etc.)
		masterFile << student.getNumAbsences() << ",";  // Number of absences

		// Now, write the absence dates. We assume the absence dates are stored in a stack (which is your custom class absenceStack).
		absenceStack<string> absences = student.getAbsences();  // Get the absence stack (not std::stack)

		// Check if the absence stack is empty using the custom isEmpty() method
		if (!absences.isEmpty()) {
			// Iterate over the stack and print the dates
			while (!absences.isEmpty()) {
				string date = absences.topAbsence();  // Get the top absence date
				masterFile << date << ",";  // Write each absence date
				absences.popAbsence();  // Remove the top element after writing it
			}
		}

		// End the line after writing all the data for this student
		masterFile << endl;

		// Move to the next student in the list
		
		pTemp = pTemp->getNext();
	}

	// Close the file after writing all data
	masterFile.close();

	cout << "Master list has been successfully saved!" << endl;
}


string App::determineDate() {
	// Get the current time
	time_t currentTime = time(nullptr);  // Get the current time in seconds
	tm localTime; // tm struct to hold the local time

	// Convert the time to local time (safe version)
	localtime_s(&localTime, &currentTime);  // Use localtime_s to safely convert to local time

	// Format the time as a string (e.g., "YYYY-MM-DD")
	char buffer[11]; // Buffer to store the formatted string
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

	return string(buffer);  // Return the formatted string
}

void App::addAbsences(List<Data>& masterList) {
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
			//run logic to add to absence stack
			string date = determineDate();  // Get today's date
			pTemp->getNodeData().setAbsenceDate(date);  // Push the date onto the stack
			int currentAbsences = pTemp->getNodeData().getNumAbsences();  // Get the current number of absences
			pTemp->getNodeData().setNumAbsences(currentAbsences + 1);  // Increment the number of absences


		}

		system("cls");

		pTemp = pTemp->getNext(); //iterate onto next node
	}
	cout << "Attendence data successfully updated, see you tomorrow!" << endl;
}
// Function to generate a report for all students showing only the most recent absence.
void App::generateRecentAbsenceReport(List<Data>& masterList) {
	if (masterList.isEmpty()) {
		cout << "No students loaded in the list." << endl;
		return;
	}

	cout << "Report for Most Recent Absences:" << endl;

	// Iterate through the list and print the most recent absence for each student.
	studentNode<Data>* pTemp = masterList.getpHead();

	while (pTemp != nullptr) {
		Data student = pTemp->getNodeData();
		string mostRecentAbsence = "No absences"; // Default message if no absences

		if (!student.getAbsences().isEmpty()) {
			// Get the most recent absence (peek the top of the stack)
			mostRecentAbsence = student.getAbsences().topAbsence();
		}

		cout << "Student: " << student.getName() << ", Most Recent Absence: " << mostRecentAbsence << endl;
		pTemp = pTemp->getNext();
	}

	cout << "End of report." << endl;
}

// Function to generate a report for students with absences that match or exceed a given threshold.
void App::generateAbsenceThresholdReport(List<Data>& masterList) {
	int threshold;

	cout << "Enter the minimum number of absences to filter students: ";
	cin >> threshold;

	if (masterList.isEmpty()) {
		cout << "No students loaded in the list." << endl;
		return;
	}

	cout << "Report for Students with Absences >= " << threshold << " :" << endl;

	// Iterate through the list and print students who have absences >= threshold
	studentNode<Data>* pTemp = masterList.getpHead();

	while (pTemp != nullptr) {
		Data student = pTemp->getNodeData();
		int numAbsences = student.getNumAbsences(); // Get the number of absences

		if (numAbsences >= threshold) {
			cout << "Student: " << student.getName() << ", Number of Absences: " << numAbsences << endl;
		}

		pTemp = pTemp->getNext();
	}

	cout << "End of report." << endl;
}

void App::generateReportMenu(List<Data>& masterList) {
	int reportChoice = 0;

	// Prompt for the type of report the user wants
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

// Function to search a student by ID or Name
Data* App::searchStudent(List<Data>& masterList) {
	string searchType;
	cout << "Search by (ID/Name): ";
	cin >> searchType;

	if (searchType == "ID") {
		int studentId;
		cout << "Enter student ID: ";
		cin >> studentId;

		studentNode<Data>* pTemp = masterList.getpHead();
		while (pTemp != nullptr) {
			if (pTemp->getNodeData().getIdNumber() == studentId) {
				return &pTemp->getNodeData();  // Return the student's data if found
			}
			pTemp = pTemp->getNext();
		}
		cout << "Student not found by ID." << endl;
	}
	else if (searchType == "Name") {
		string studentName;
		cout << "Enter student Name: ";
		cin.ignore();  // Ignore newline from previous input
		getline(cin, studentName);

		studentNode<Data>* pTemp = masterList.getpHead();
		while (pTemp != nullptr) {
			if (pTemp->getNodeData().getName() == studentName) {
				return &pTemp->getNodeData();  // Return the student's data if found
			}
			pTemp = pTemp->getNext();
		}
		cout << "Student not found by Name." << endl;
	}
	else {
		cout << "Invalid search type!" << endl;
	}
	return nullptr;  // Return nullptr if no student is found
}

void App::editAbsences(List<Data>& masterList) {
	Data* student = searchStudent(masterList);  // Get student by ID or Name

	if (student == nullptr) {
		cout << "Student not found. Returning to menu." << endl;
		return;
	}

	// Print the student's name and absence history
	cout << "Editing absences for: " << student->getName() << endl;
	cout << "Current absences: " << endl;

	absenceStack<string> absences = student->getAbsences();

	// Check if there are any absences to display
	if (absences.isEmpty()) {
		cout << "No absences found for this student." << endl;
	}
	else {
		// Show all absence dates
		while (!absences.isEmpty()) {
			cout << absences.topAbsence() << endl;  // Display the top absence date
			absences.popAbsence();  // Remove the top element after displaying it
		}
	}

	// Ask the user for the absence date to remove
	string dateToRemove;
	cout << "Enter the absence date to remove (YYYY-MM-DD) or type 'none' to skip: ";
	cin >> dateToRemove;

	// If the user wants to remove an absence
	if (dateToRemove != "none") {
		absenceStack<string> updatedAbsences = student->getAbsences();  // Copy of original absences
		bool found = false;

		while (!updatedAbsences.isEmpty()) {
			if (updatedAbsences.topAbsence() == dateToRemove) {
				// Found the absence, so remove it
				updatedAbsences.popAbsence();
				found = true;
				break;
			}
			else {
				updatedAbsences.popAbsence();
			}
		}

		if (found) {
			student->setAbsences(updatedAbsences);  // Update the student's absence stack
			int newAbsenceCount = updatedAbsences.size();  // New number of absences
			student->setNumAbsences(newAbsenceCount);  // Update the total number of absences
			cout << "Absence on " << dateToRemove << " has been removed!" << endl;
		}
		else {
			cout << "No absence found on " << dateToRemove << " for this student." << endl;
		}
	}
}

