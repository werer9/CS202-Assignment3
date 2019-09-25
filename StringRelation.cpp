#include "StringRelation.h"
#include <unistd.h>

/*
 * Assign SetMembers.
 */
void StringRelation::setInput(SetOfStrings *s)
{
	SetMembers=s;
}

/*
 * It splits a pair "a,b" into a vector of strings "a", "b".
 * Returns the string vector.
 */
vector<string> StringRelation::makeTokens(string pair){
	vector<string> out;
	vector<string>::iterator p;
	char *a = new char [pair.length()+1];
	strcpy(a,pair.c_str());
	char* token = strtok(a,",");
			int index=0;
				while (token != NULL) {
					out.push_back(token);
					token = strtok(NULL, ",");
					index++;
				}
	return out;
}

/*
 * Returns the equivalence class as a set object.
 */
SetOfStrings *StringRelation::computeEquivalenceClass(string element){
	SetOfStrings *out = new SetOfStrings();
	if (this->isEquivalence()) {
		vector<string> tokens;
		for (int i = 0; i < this->size(); i++) {	
			tokens = this->makeTokens(this->returnElement(i));
			if (tokens[1] == element)
				out->insertElement(tokens[0]);
		}
		return out;
	} else {
		return out;
	}
	
}

/*
 * Returns true if the relation is reflexive.
 * Otherwise, returns false.
 */
bool StringRelation::isReflexive(){
	string element;
	vector<string> tokens;
	int matchCount = 0;
	for (int i = 0; i < SetMembers->size(); i++) {
		element = SetMembers->returnElement(i);
		for (int i = 0; i < this->size(); i++) {
			tokens = this->makeTokens(this->returnElement(i));
			if (tokens[0] == element && tokens[1] == element) 
				matchCount++;
		}
	}

	if (matchCount == SetMembers->size()) 
		return true;
	else
		return false;
}

/*
 * Returns true if the relation is symmetric.
 * Otherwise, returns false.
 */
bool StringRelation::isSymmetric(){
	int elementsChecked = 0;
	vector<string> tokens1;
	vector<string> tokens2;
	for (int i = 0; i < this->size(); i++) {
		tokens1 = this->makeTokens(this->returnElement(i));
		if (tokens1[0] == tokens1[1]) {elementsChecked++;} else {
			for (int j = i; j < this->size(); j++) {
				tokens2 = this->makeTokens(this->returnElement(j));
				if (tokens1[0] == tokens2[1] && tokens1[1] == tokens2[0])
					elementsChecked += 2;
			}
		}
		if (elementsChecked == this->size()) 
			return true;
	}

	return false;
}

/*
 * Returns true if the relation is transitive.
 * Otherwise, returns false.
 */
bool StringRelation::isTransitive(){
	vector<string> tokens1;
	vector<string> tokens2;
	vector<string> tokens3;
	bool match = false;
	for (int i = 0; i < this->size(); i++) {
		tokens1 = this->makeTokens(this->returnElement(i));
		if (tokens1[0] != tokens1[1]) {
			for (int j = 0; j < this->size(); j++) {
				tokens2 = this->makeTokens(this->returnElement(i));
				if (tokens1[1] == tokens2[0]) {
					match = false;
					for (int k = 0; k < this->size(); k++) {
						tokens3 = this->makeTokens(this->returnElement(i));
						if (tokens3[0] == tokens1[0] && tokens3[1] == tokens2[1])
							match = true;
					}
					if (match == true) {}
					else {
						return false;
					}
				}
			}
		}
	}
	return true;
}

/*
 * Returns true if the relation is the equivalence relation.
 * Otherwise, returns false.
 */
bool StringRelation::isEquivalence(){
	return this->isTransitive() && this->isReflexive() && this->isSymmetric();
}
