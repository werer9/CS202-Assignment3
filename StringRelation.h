#ifndef STRINGRELATION_H_
#define STRINGRELATION_H_

#include "SetOfStrings.h"
#include <vector>
#include <stdio.h>

using namespace std;

class StringRelation : public SetOfStrings{
private:
    SetOfStrings *SetMembers; // stores the members of the set, which the relation is created on.
    
    // ALREADY COMPLETED
    vector<string> makeTokens(string input); // split a string into tokens

public:
	// ALREADY COMPLETED
    void setInput(SetOfStrings *s); 
    
    /* 
     * Assignment Tasks:
     * You are required to complete the following functions.
     * Do not change the function name and interface.
     */
    bool isReflexive();
    bool isSymmetric();
    bool isTransitive();
    bool isEquivalence();
    SetOfStrings *computeEquivalenceClass(string element);
    
};
#endif
