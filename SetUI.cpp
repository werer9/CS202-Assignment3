#include "SetUI.h"

SetUI::SetUI()
{
	TopicScreen();
}

// Greet the user and shows the developer name.
void SetUI::TopicScreen()
{
	system("clear");
	cout <<"----------------------------------------------------------------------"<< endl;
	cout <<"Set Calculator. To know available commands, please type 'help'" << endl;
	cout <<"---------------------------------------------------------------------"<< endl;
}

// Print function for equivalence class search
// It follows the traditional mathematical expression, e.g., [0] = {1,2,3,4}
void SetUI::printEquivalenceClass(string member, SetOfStrings* ss)
{
	cout << "  [" << ColorText(member, BLUE) << "] = {";
	int size = 0;
	while (size < ss->size()){
		cout << ColorText(ss->returnElement(size), YELLOW);
		if (size != ss->size()-1) cout << ", ";
		size++;
	}
	cout << "}\n";
}

bool SetUI::ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose)
{
	string line;
	ifstream infile (filename.c_str());
	
	//return false if the file does not exist
	if (!infile.good()) return false;
	if (!infile.is_open()) return false;
	
	getline(infile,line); // Get the first line to extract set members
	if (verbose) cout << ColorText(line, WHITE) << endl;
	line.erase(0,2); // Remove '//' in the line
	line.erase(remove(line.begin(), line.end(), ' '), line.end()); //trim
	
	int i = 0;
	size_t found;
	while((found = line.find(",",i))!=std::string::npos) {
		string temp = line.substr(i,found-i);
		temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end()); //trim
		ss->insertElement(temp);
		i = found+1;	
	}
	string temp = line.substr(i);
	temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end()); //trim
	ss->insertElement(temp);
	getline(infile,line); // To bypass the second line
	sr->setInput(ss); // Add the set information before reading relation for isValid()
	//read the rest of the file.
	while (getline(infile,line)){
		if (verbose) cout << ColorText(line, WHITE) << endl;
		// trim the line
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		if (strcmp(line.c_str(), "") == 0) continue;
		// find } as the finisher for file reading
		if (line.find("}")!=string::npos) break; 
		// fetch set and relation in the line 
		if (!getFromLine(ss, sr, line)) return false;
	}
	infile.close();
	
	return true;
}


bool SetUI::getFromLine(SetOfStrings *ss, StringRelation *sr, string line){
	vector<string> element;
	string relation;
	int i = 0;
	size_t found;
	// string split by using -> as the separator
	while((found = line.find("->",i))!=std::string::npos) {
		string temp = line.substr(i,found-i);
		temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end()); //trim
		relation.append(temp);
		relation.append(",");
		i = found+2;
	}
	// handle the last element
	string temp = line.substr(i,line.find("[",i)-i);
	temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end()); //trim
	temp.erase(remove(temp.begin(), temp.end(), ';'), temp.end()); //remove semicolons
	relation.append(temp);
	sr->insertElement(relation);
	
	return true;
}

//usage: printProperties ("reflexive", true) prints
//"This set of binary relations satisfies reflexive property"
void SetUI::printProperties(string property, bool isProperty)
{
	if (strcmp(property.c_str(), "equivalence") == 0){
		if (isProperty) cout << ColorText("  The relation is equivalence relation\n", GREEN);
		else cout << ColorText("  The relation is not equivalence relation\n", RED);
	}
	else {
		string temp = "  The relation is ";
		if (!isProperty) temp.append("not ");
		temp.append(property);
		if (!isProperty) cout << ColorText(temp, RED) << endl;
		else cout << ColorText(temp, GREEN) << endl;
	}
}

void SetUI::printPass(string reason)
{
	if (strcmp(reason.c_str(), "file") == 0){
		cout << ColorText("  File reading was successful\n", GREEN);
		cout << ColorText("  Please type 'list' to view the information\n", GREEN);
	}
}

void SetUI::printError(string reason)
{
	// error message if the input file does not exist or contains wrong data.
	if (strcmp(reason.c_str(), "file") == 0){
		cout << ColorText("  Error: cannot load the input file\n", RED);
	}
	// error message if the command cannot be understood
	else if (strcmp(reason.c_str(), "command") == 0){
		cout << ColorText("  Error: invalid command\n", RED);
	}
	// error message if the user trying to find the equivalence class for a string that does not have equivalence relation
	else if (strcmp(reason.c_str(), "equivalence") == 0){
		cout << ColorText("  Error: not an equivalence relation\n", RED);
	}
	// error message if the command argument is incorrect
	else if (strcmp(reason.c_str(), "argument") == 0){
		cout << ColorText("  Error: invalid command arguments\n", RED);
	}
	else if (strcmp(reason.c_str(), "member") == 0){
		cout << ColorText("  Error: member does not exist\n", RED);
	}
	else if (strcmp(reason.c_str(), "nograph") == 0){
		cout << ColorText("  Error: no input file is loaded\n", RED);
	}
}

string SetUI::GetCommand()
{
	string commandInput;
	cout << ">> ";

	getline (cin, commandInput);
	return commandInput;
}

//prints the help message (Completed)
void SetUI::Help()
{
	cout << "\n\n";
	cout << left << setw(45) << ColorText(" help", RED) << left << setw(50) << "Show help." << endl << endl;
	cout << left << setw(45) << ColorText(" ls <path> ", RED) << left << setw(50) << "Identical to the ls shell command. If a path is given, then" << endl;
	cout << left << setw(34) << "" << left << setw(50) << "the program returns all the files in that path." << endl << endl;
	cout << left << setw(45) << ColorText(" clear ", RED) << left << setw(50) << "Identical to the clear shell command. Clear the screen." << endl << endl;
	cout << left << setw(45) << ColorText(" open [file_path] <-v>", RED) << left << setw(50) << "Open a file. If the file does not exist, then program returns" << endl;
	cout << left << setw(34) << "" << left << setw(50) << "an error message. If -v (verbose) option is enabled (e.g., open $path/a.txt -v)," << endl;
	cout << left << setw(34) << "" << left << setw(50) << "then each line in the file is printed on console while reading." << endl << endl;
	cout << left << setw(45) << ColorText(" list", RED) << left << setw(50) << "List all the members of set and relation." << endl << endl;
	cout << left << setw(45) << ColorText(" check [OPTION] ", RED) << left << setw(50) << "Check the relation. The option has to be provided. Options are:" << endl << endl;
	cout << left << setw(35) << "" << left << setw(50) << "-r (reflexivity)" << endl;
	cout << left << setw(35) << "" << left << setw(50) << "-s (symmetry)" << endl;
	cout << left << setw(35) << "" << left << setw(50) << "-t (transitivity)" << endl;
	cout << left << setw(35) << "" << left << setw(50) << "-e (equivalence relation)" << endl << endl;
	cout << left << setw(45) << ColorText(" eqclass [VALUE]", RED) << left << setw(50) << "Show equivalence class of the given [VALUE = Set member]." << endl;
	cout << left << setw(34) << "" << left << setw(50) << "If VALUE is not a member of set, then the program returns" << endl;
	cout << left << setw(34) << "" << left << setw(50) << "an error message." << endl << endl;
	cout << left << setw(45) << ColorText(" exit", RED) << left << setw(50) << "Terminate the program." << endl;
	cout << "\n\n";
}

int SetUI::ListMembers(SetOfStrings* model){
	if (model->size() == 0) {
		printError("nograph");
		return 0;
	}
	cout << ColorText("  Set", BLUE) << ": {";
	int size = 0;
	while (size < model->size()){
		cout << ColorText(model->returnElement(size), BLUE);
		if (size != model->size()-1) cout << ", ";
		size++;
	}
	cout << "}\n";
	return 1;
}

int SetUI::ListMembers(StringRelation* model){
	cout << ColorText("  Relation", YELLOW) << ": {";
	int size = 0;
	while (size < model->size()){
		cout << "(" << ColorText(model->returnElement(size), YELLOW) << ")";
		if (size != model->size()-1) cout << ", ";
		size++;
	}
	cout << "}\n";
	return 1;
}

string SetUI::ColorText(string s, COLOR color)
{
	string temp;
	switch (color) {
		case RED: temp = "\033[1;31m" + s + "\033[0m"; break;
		case BLUE: temp = "\033[1;34m" + s + "\033[0m"; break;
		case YELLOW: temp = "\033[1;33m" + s + "\033[0m"; break;
		case GREEN: temp = "\033[1;32m" + s + "\033[0m"; break;
		case MAGENTA: temp = "\033[1;35m" + s + "\033[0m"; break;
		case WHITE: temp = "\033[1;37m" + s + "\033[0m"; break;
		default: temp = "\033[0m" + s; break;
	}
	return temp;
}

