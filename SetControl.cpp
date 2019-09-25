#include "SetControl.h"

SetControl::SetControl()
{
	cout <<"Initializing the calculator, please wait! ... \n" << endl;
	
	//instansiate all members
	setUI = new SetUI();
	setModel = new SetOfStrings();
	relationModel = new StringRelation();
}

SetControl::~SetControl()
{
	//dispose all members
	delete setUI;
	delete setModel;
	delete relationModel;
}

bool SetControl::Run()
{			
	#ifdef _DEBUG
		Testing();
		return false; // exit the program after testing
	#endif

	string command;
		
	vector<string> argv;
	//invoke the main user interaction
	while(true)
	{
		
		//show the menu and get user command
		command = setUI->GetCommand();
	
		int argc = 0;
		int i = 0;
		size_t found;
		while((found = command.find(" ",i))!=std::string::npos) {
			argv.push_back(command.substr(i,found-i));
			i = found+1;
		}
		argv.push_back(command.substr(i));

		argc = argv.size();
		for (int a = argc-1; a>=0; a--){
			if (argv.at(a).compare("")==0){
				argv.erase(argv.begin()+a);
			}
		}
		argc = argv.size();

		// if enter is pressed
		if (argc == 0) continue;
		
		// help command execution (Completed)
		if (argv.at(0).compare("help")==0){
			setUI->Help();
		}
		// ls command execution (Completed)
		else if (argv.at(0).compare("ls")==0){
			if (!(argc == 1 || argc == 2)){setUI->printError("argument"); continue;}
			if (argc == 2){
				string cmd(argv[1]);
				cmd = "ls " + cmd;
				system(cmd.c_str());		
			}		
			else system("ls");
		}
		// "clear" shell command for file searching
		else if (argv.at(0).compare("clear")==0){
			system("clear");
			setUI->TopicScreen();
		}
		// open command execution
		else if (argv.at(0).compare("open")==0){
			if (!(argc == 2 || argc == 3)) {setUI->printError("argument"); argv.clear(); continue;}
			SetOfStrings *temps = new SetOfStrings();
			StringRelation *tempr = new StringRelation();
			if (argc == 2) {
				if (!setUI->ReadFromFile(argv.at(1), temps, tempr, false)){
					setUI->printError("file");
					argv.clear();
					continue;
				}
				else{
					setUI->printPass("file");
				}
			}
			else{ //if the file cannot be read
				if (argv.at(2).compare("-v")!=0) {
					setUI->printError("argument");
					argv.clear();
					continue;
					}
				if (!setUI->ReadFromFile(argv.at(1), temps, tempr, (argv.at(2).compare("-v") == 0) ? true:false)) {
					setUI->printError("file");
					argv.clear();
					continue;
				}
				else{
					setUI->printPass("file");
				}
			}			
			setModel = temps;
			relationModel = tempr;				
		}
		// list command execution
		else if (argv.at(0).compare("list")==0){
			if (setUI->ListMembers(setModel)) 
			setUI->ListMembers(relationModel);
		}
		// check command execution
		else if (argv.at(0).compare("check")==0){
			//incorrect argument counts
			if (argc != 2) {setUI->printError("argument"); argv.clear(); continue;}
			if (setModel->size() == 0) {setUI->printError("nograph"); argv.clear(); continue;}
			//flag detection
			if (argv.at(1).compare("-r")==0) setUI->printProperties("reflexive", relationModel->isReflexive());
			else if (argv.at(1).compare("-s")==0) setUI->printProperties("symmetric", relationModel->isSymmetric());
			else if (argv.at(1).compare("-t")==0) setUI->printProperties("transitive", relationModel->isTransitive());
			else if (argv.at(1).compare("-e")==0) setUI->printProperties("equivalence", relationModel->isEquivalence());
			else setUI->printError("argument");
		}
		// exit cmmand execution
		else if (argv.at(0).find("exit")!=string::npos){
			exit(0);
		}
		// eqclass command execution
		else if (argv.at(0).compare("eqclass")==0){
			//incorrect argument counts
			if (argc != 2) {setUI->printError("argument"); argv.clear(); continue;}
			if (setModel->size() == 0) {setUI->printError("nograph"); argv.clear(); continue;}
			if (!relationModel->isEquivalence()) {setUI->printError("equivalence");	argv.clear(); argv.clear(); continue;}
			if (setModel->isMember(argv.at(1))) setUI->printEquivalenceClass(argv.at(1), relationModel->computeEquivalenceClass(argv.at(1)));
			else setUI->printError("member");
		}
		// Command is invalid 
		else{
			setUI->printError("command");
		}
		
		argv.clear();
	}
	
	return true;
}

// This function is compiled only when the debug flag is enabled.
#ifdef _DEBUG
void SetControl::Testing(){
	// here, you can create a scenario, and test the functions more conveniently.
	SetOfStrings *set = new SetOfStrings();
	StringRelation *relation = new StringRelation();
	
	set->insertElement("a");
	set->insertElement("a");
	set->insertElement("b");
	set->insertElement("c");
	
	// debug isMember function
	ASSERT(set->isMember("a")==true, "a is a member");
	ASSERT(set->isMember("b")==true, "b is a member");
	ASSERT(set->isMember("c")==true, "c is a member");
	ASSERT(set->isMember("d")==false, "d is not a member");

	relation->setInput(set);
	relation->insertElement("a,b");
	relation->insertElement("b,c");
	relation->insertElement("a,c");
	
	// debug the relation checking
	ASSERT(relation->isReflexive()==false, "not reflexive"); 
	ASSERT(relation->isSymmetric()==false, "not symmetric"); 
	ASSERT(relation->isTransitive()==true, "is transitive"); // in the skeleton code, this one will fail.
	ASSERT(relation->isEquivalence()==false, "not equivalence");

	// add more elements to the set
	set->insertElement("d");
	set->insertElement("e");
	set->insertElement("f");

	// check the new elements were added
	ASSERT(set->isMember("d")==true, "d is a member");
	ASSERT(set->isMember("e")==true, "e is a member");
	ASSERT(set->isMember("f")==true, "f is a member");
	
	// insert new elements into relation set
	relation->insertElement("b,f");
	relation->insertElement("f,e");
	relation->insertElement("b,e");

	// check relation is still transitive
	ASSERT(relation->isReflexive()==false, "not reflexive");
	ASSERT(relation->isSymmetric()==false, "not symmetric");
	ASSERT(relation->isTransitive()==true, "is transitive");
	ASSERT(relation->isEquivalence()==false, "not equivalence");

	// insert elements to make relation symmetric
	relation->insertElement("b,a");
	relation->insertElement("c,b");
	relation->insertElement("c,a");
	relation->insertElement("f,b");
	relation->insertElement("e,f");
	relation->insertElement("e,b");
	relation->insertElement("d,d");

	// check relation is symmetric and transitive
	ASSERT(relation->isReflexive()==false, "not reflexive");
	ASSERT(relation->isSymmetric()==true, "is symmetric");
	ASSERT(relation->isTransitive()==true, "is transitive");
	ASSERT(relation->isEquivalence()==false, "not equivalence");

	// make relation reflexive
	relation->insertElement("a,a");
	relation->insertElement("b,b");
	relation->insertElement("c,c");
	relation->insertElement("e,e");
	relation->insertElement("f,f");

	// check is reflexive and is equivalence
	ASSERT(relation->isReflexive()==true, "is reflexive");
	ASSERT(relation->isSymmetric()==true, "is symmetric");
	ASSERT(relation->isTransitive()==true, "is transitive");
	ASSERT(relation->isEquivalence()==true, "is equivalence");

	// test equivalence class
	SetOfStrings *eqSetA = new SetOfStrings();
	eqSetA->insertElement("a");
	eqSetA->insertElement("b");
	eqSetA->insertElement("c");

	SetOfStrings *eqSetF = new SetOfStrings();
	eqSetF->insertElement("b");
	eqSetF->insertElement("e");
	eqSetF->insertElement("f");

	// check equivlanece class members added
	ASSERT(eqSetA->isMember("a")==true, "a is member");
	ASSERT(eqSetA->isMember("b")==true, "b is member");
	ASSERT(eqSetA->isMember("c")==true, "c is member");

	ASSERT(eqSetF->isMember("b")==true, "a is member");
	ASSERT(eqSetF->isMember("e")==true, "b is member");
	ASSERT(eqSetF->isMember("f")==true, "c is member");

	// make sure valid equivalence class generated
	ASSERT(*eqSetA==*relation->computeEquivalenceClass("a"), "equivalence class correct");
	ASSERT(*eqSetF==*relation->computeEquivalenceClass("f"), "equivalence class correct");

	// check if eqseta is no longer equivalence class
	eqSetA->insertElement("f");
	ASSERT(eqSetA->isMember("f")==true, "f is member");
	ASSERT(!(*eqSetA==*relation->computeEquivalenceClass("a")), "equivalence class incorrect");

}

#endif
