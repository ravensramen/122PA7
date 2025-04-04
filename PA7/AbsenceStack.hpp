#include <stack>
#include <iostream>

using std::stack;
using std::string;
//use standard std stack and coresponding functions to record absences

//standard std::stack
template<class T, class Container = std::deque<T>>
class absenceStack {

public:

    void pushAbsence(const string& date) {
        container.push(date);  
    }

private:
    stack<string, Container> container;//to access private functions
};