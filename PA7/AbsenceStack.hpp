#include <stack>
#include <iostream>

using std::stack;
using std::string;
//use standard std stack and coresponding functions to record absences

//standard std::stack
template<class T, class Container = std::deque<T>>
class absenceStack {

public:
	//includes push, pop, peek, etc.
	//explicit definition not neccessary, included in std stack
private:
	Container container; //to access private functions

};