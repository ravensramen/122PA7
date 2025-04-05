#include "AbsenceStack.hpp"
using std::string;


class Data {
private:
    // all student fields
    int recordNumber;
    int idNumber;
    string name;
    string email;
    int credits;
    string major;
    string level;

    int numAbsences;
    absenceStack<string> absences;  // stack holding absences

public:
    // default constructor
    Data() {
        recordNumber = 0;
        idNumber = 0;
        name = "";
        email = "";
        credits = 0;
        major = "";
        level = "";
        numAbsences = 0;
    }

    // copy constructor (deep copy for the stack)
    Data(const Data& other) {
        this->recordNumber = other.recordNumber;
        this->idNumber = other.idNumber;
        this->name = other.name;
        this->email = other.email;
        this->credits = other.credits;
        this->major = other.major;
        this->level = other.level;

        this->numAbsences = other.numAbsences;

        // deep copy of the absence stack
        this->absences = other.absences;  
    }

    // copy assignment operator (deep copy for the stack)
    Data& operator=(const Data& other) {
        if (this != &other) {  // self-assignment check
            this->recordNumber = other.recordNumber;
            this->idNumber = other.idNumber;
            this->name = other.name;
            this->email = other.email;
            this->credits = other.credits;
            this->major = other.major;
            this->level = other.level;

            this->numAbsences = other.numAbsences;

            // deep copy of the absence stack
            this->absences = other.absences;  
        }
        return *this;
    }

    // destructor (std stack handles dealloc)
    ~Data() {}

    // setters and getters for each field...

    void setRecordNumber(int num) {
        this->recordNumber = num;
    }

    int getRecordNumber(void) const {
        return this->recordNumber;
    }

    void setIdNumber(int num) {
        this->idNumber = num;
    }

    int getIdNumber(void) const {
        return this->idNumber;
    }

    void setName(string newName) {
        this->name = newName;
    }

    string getName(void) const {
        return this->name;
    }

    void setEmail(string newEmail) {
        this->email = newEmail;
    }

    string getEmail(void) const {
        return this->email;
    }

    void setCredits(int newCredits) {
        this->credits = newCredits;
    }

    int getCredits(void) const {
        return this->credits;
    }

    void setMajor(string newMajor) {
        this->major = newMajor;
    }

    string getMajor(void) const {
        return this->major;
    }

    void setLevel(string newLevel) {
        this->level = newLevel;
    }

    string getLevel(void) const {
        return this->level;
    }

    void setNumAbsences(int num) {
        this->numAbsences = num;
    }

    int getNumAbsences(void) const {
        return this->numAbsences;
    }

    void setAbsenceDate(const string& absence) {
        this->absences.pushAbsence(absence);  // insert absence date on top of stack
    }

    // getter for the absence stack (returns the stack by reference)
    const absenceStack<string>& getAbsences(void) const {
        return this->absences;
    }

    // setter for the absences stack
    void setAbsences(const absenceStack<string>& absences) {
        this->absences = absences;  
    }
};