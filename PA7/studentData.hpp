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
    absenceStack<string> absences;  // Stack holding absences

public:
    // Default constructor
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

    // Copy constructor (deep copy for the stack)
    Data(const Data& other) {
        this->recordNumber = other.recordNumber;
        this->idNumber = other.idNumber;
        this->name = other.name;
        this->email = other.email;
        this->credits = other.credits;
        this->major = other.major;
        this->level = other.level;

        this->numAbsences = other.numAbsences;

        // Deep copy of the absence stack
        this->absences = other.absences;  // assuming absenceStack supports assignment
    }

    // Copy assignment operator (deep copy for the stack)
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

            // Deep copy of the absence stack
            this->absences = other.absences;  // assuming absenceStack supports assignment
        }
        return *this;
    }

    // Destructor (no special cleanup needed as absenceStack will handle it)
    ~Data() {}

    // Setters and getters for each field...
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
        this->absences.pushAbsence(absence);  // Insert absence date on top of stack
    }

    // Getter for the absence stack (returns the stack by reference)
    const absenceStack<string>& getAbsences(void) const {
        return this->absences;
    }

    // Setter for the absences stack (this assumes absenceStack type is available)
    void setAbsences(const absenceStack<string>& absences) {
        this->absences = absences;  // Set the stack to a new one
    }
};