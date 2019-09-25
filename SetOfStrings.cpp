#include "SetOfStrings.h"

using namespace std;

/*
 * Returns the total number of elements in the set.
 */
int SetOfStrings::size() const {
    return (int) elements.size();
}

/*
 * Inserts an element into the set.
 */
void SetOfStrings::insertElement(string s)
{
    if(!isMember(s)){
        elements.push_back(s);
    }
}

/*
 * Returns a specific element from the set.
 * Returns "" if nothing to return.
 */
string SetOfStrings::returnElement(int index) const
{
	if(index > size() || index < 0) return "";
	return elements.at(index);
}

/*
 * Finds a specific element.
 * Returns true if exist, otherwise false.
 */
bool SetOfStrings::isMember(string s) const
{
	if (find(elements.begin(), elements.end(), s) != elements.end()){
		return true;
	}
	else{
		return false;
	}
}

/*
 * Returns true if the Set is empty, otherwise false.
 */
bool SetOfStrings::isEmpty() const{
    if (this->elements.size() == 0)
        return true; 
    else 
        return false;
}

/*
 * Outputs all elements within the Set. Might be handy for debugging Set content.
 */
void SetOfStrings::print() const {
	cout << "{";
	for (unsigned int i = 0; i < elements.size(); i++) {
		cout << elements[i];
		if ( (i+1) < elements.size() ) {
			cout << ", ";
		}
	}
	cout << "}";
}

/*
 * Returns true if this Set is equal to the "otherSet", otherwise returns false.
 */
bool SetOfStrings::operator==(const SetOfStrings &otherSet) const {
	if (this->size() != otherSet.size()) {
        return false;
    } else {
        for (unsigned i = 0; i < this->size(); i++) {
            if (!otherSet.isMember(this->elements[i])) {
                return false;
            }          
        }
    }

    return true;
}


/*
 * Performs the Set Union operation of this Set with the otherSet.
 */
SetOfStrings SetOfStrings::operator||(const SetOfStrings &otherSet) const {
    SetOfStrings resultSet;
    for (unsigned i = 0; i < this->elements.size(); i++) {
        resultSet.insertElement(this->elements[i]);
    }

    for (unsigned i = 0; i < otherSet.size(); i++) {
        if (!resultSet.isMember(otherSet.elements[i])) {
            resultSet.insertElement(otherSet.elements[i]);
        }
    }

    return resultSet;
}

/*
 * Performs the Set Intersection operation of this Set with the otherSet
 */
SetOfStrings SetOfStrings::operator&&(const SetOfStrings &otherSet) const {
    SetOfStrings resultSet;
    for (unsigned i = 0; i < this->elements.size(); i++) {
        if (otherSet.isMember(this->elements[i])) {
            resultSet.insertElement(this->elements[i]);
        }
    }

    return resultSet;
}
