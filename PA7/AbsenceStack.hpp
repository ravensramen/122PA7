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
		container.push(date); // using push of the underlying container (std::stack)
	}

private:
	Container container; //to access private functions
};