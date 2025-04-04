#include "AbsenceStack.hpp"
#include <string>

//more like a struct, just has setters and getters

using std::string;

class Data {

private:
	//all student fields
	int recordNumber;
	int idNumber;
	string name;
	string email;
	int credits;
	string major;
	string level;

	int numAbsences;
	absenceStack <string> absences; //declare an instance of stack holding strings (coresponding to dates)

public:
	//no special definition needed, stacks of STL type handle memory alloc.
	Data() {
		recordNumber = 0;
		idNumber = 0;
		name = "";
		email = "";
		credits = 0;
		major = "";
		level = "";

		numAbsences = 0;
	};

	Data(const Data& other) {
		this->recordNumber = other.recordNumber;
		this->idNumber = other.idNumber;
		this->name = other.name;
		this->email = other.email;
		this->credits = other.credits;
		this->major = other.major;
		this->level = other.level;

		this->numAbsences = other.numAbsences;
	}



	Data& operator=(const Data& other) { //copy overloaded assignment
		if (this != &other) { 
			
			this->recordNumber = other.recordNumber;
			this->name = other.name;
			this->email = other.email;
			this->credits = other.credits;
			this->major = other.major;
			this->level = other.level;

			this->numAbsences = other.numAbsences;
		}

		return *this;
	}

	~Data() {};

	//setters and getters for each field...
	void setRecordNumber(int num) {
		this->recordNumber = num;
	}

	int getRecordNumber(void) {
		return this->recordNumber;
	}

	void setIdNumber(int num) {
		this->idNumber = num;
	}

	int getIdNumber(void) {
		return this->idNumber;
	}

	void setName(string newName) {
		this->name = newName;
	}

	string getName(void) {
		return this->name;
	}

	void setEmail(string newEmail) {
		this->email = newEmail;
	}

	string getEmail(void) {
		return this->email;
	}

	void setCredits(int newCredits) {
		this->credits = newCredits;
	}

	int getCredits(void) {
		return this->credits;
	}

	void setMajor(string newMajor) {
		this->major = newMajor;
	}

	string getMajor(void) {
		return this->major;
	}
	
	void setLevel(string newLevel) {
		this->level = newLevel;
	}

	string getLevel(void) {
		return this->level;
	}

	void setNumAbsences(int num) {
		this->numAbsences = num;
	}

	int getNumAbsences(void) {
		return this->numAbsences; //could also iterate through stack to determine...
	}


	void setAbsenceDate(string absence) {
		this->absences.pushAbsence(absence);  // Insert absence date on top of stack
	}

	// Getter for absences stack
	absenceStack<string> getAbsences(void) const {
		return this->absences;  // Return the entire stack of absences
	}

	// Setter for the absences stack (this assumes the absenceStack type is available)
	void setAbsences(const absenceStack<string>& absences) {
		this->absences = absences;  // Set the stack to a new one
	}
	
};