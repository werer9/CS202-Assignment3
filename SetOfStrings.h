#ifndef SetOfStrings_SetOfStrings_h
#define SetOfStrings_SetOfStrings_h

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

class SetOfStrings{
	
protected:
    vector<string> elements;
    
public:
	// ALREADY COMPLETED
	int size() const;
	bool isMember(string s) const;
	void insertElement(string s);
	string returnElement(int index) const;
	
	/*
	 * You will need to create more methods here
	 * to complete the assignment
	 */

	bool isEmpty() const;
	void print() const;
	bool operator==(const SetOfStrings &otherSet) const;
	SetOfStrings operator||(const SetOfStrings &otherSet) const;
	SetOfStrings operator&&(const SetOfStrings &otherSet) const;
};

#endif


