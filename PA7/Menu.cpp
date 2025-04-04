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
	string line, line2;

	if (!masterFile) {
		cout << "Unable to read master file" << endl;
		return;
	}
	while (masterFile) {
		Data temp;
		getline(masterFile, line);
		istringstream buffer(line);

		if (!line.empty() && line2 != line) {
			parseData(buffer, temp, false); //need to make a generic function for parsing :( (or copy) >:)
			studentList.insertAtEnd(temp);
		}
		line2 = line;
	}

}

void App::parseData(istringstream& inputString, Data& output, bool input)
{
	string token = "Null";
	string tempString; //for naming

	short record = 0;
	int id_nums = 0;

	//Time for adding absences

	struct tm cur;
	struct tm prev;
	prev = { 0,0,0,1,0,0,110,0,0 };

	char tempTime[1024] = { 0 };

	bool absent; //bool to denote absent or not

	if (input == true) { //for inputting from original csv
		for (int type = 1; inputString; type++) {
			getline(inputString, token, ',');
			switch (type) {
			case 1:
				std::stringstream(token) >> record;
				output.setRecordNumber(record);
				break;

			case 2:
				std::stringstream(token) >> id_nums;
				output.setIdNumber(id_nums);
				break;

			case 3:
				tempString = token;
				getline(inputString, token, ',');
				tempString = tempString + ',' + token;
				output.setName(tempString);
				break;

			case 4:
				output.setEmail(token);
				break;

			case 5:
				if (token == "AU") {
					int num = -1;
					output.setCredits(num);
				}
				else {
					output.setCredits(stoi(token));
				}
				break;
			case 6:
				output.setMajor(token);
				break;
			case 7:
				output.setMajor(token);
				break;
			}
		}
	}
	else {
		for (int type = 1; inputString; type++) {
			getline(inputString, token, ',');
			switch (type) {

			case 1:
				std::stringstream(token) >> record;
				output.setRecordNumber(record);
				break;

			case 2:
				std::stringstream(token) >> id_nums;
				output.setIdNumber(id_nums);
				break;

			case 3:
				tempString = token;
				getline(inputString, token, ',');
				tempString = tempString + ',' + token;
				output.setName(tempString);
				break;

			case 4:
				output.setEmail(token);
				break;

			case 5:
				if (token == "AU") {
					int num = -1;
					output.setCredits(num);
				}
				else {
					output.setCredits(stoi(token));
				}
				break;
			case 6:
				output.setMajor(token);
				break;
			case 7:
				output.setMajor(token);
				break;

			default:


				}

			}



		}
	}

}
