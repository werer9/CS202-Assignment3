#ifndef __CalculatorUI__
#define __CalculatorUI__

#include "StringRelation.h"
#include "SetOfStrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

enum COLOR {RED=0, BLUE, GREEN, WHITE, YELLOW, MAGENTA};

class SetUI
{
	private:
		//members functions
		int getch();
		//helper function to enable colour terminal output
		string ColorText(string s, COLOR color);
		//helper function to split a line into strings read from the input file.
		bool getFromLine(SetOfStrings *set, StringRelation *relation, string line);
		
	public:
		SetUI();
		//public methods for basic printing functions
		void TopicScreen();
		void printError(string reason);
		void printPass(string reason);
		void printProperties(string property, bool isProperty);
		void printShortestPath(int distance, string path);
		void Help();
		//get input command
		string GetCommand();
		
		//results printing functions
		int ListMembers(SetOfStrings* model);
		int ListMembers(StringRelation* model);
		void printEquivalenceClass(string member, SetOfStrings* ss);
		
		//methods for reading the input file(s)
		bool ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose);
		
};

#endif
