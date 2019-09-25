#include "SetControl.h"


int main(int argc, const char * argv[])
{
	//create system handler instance
	SetControl* controller = new SetControl();
	
	//run the system
	controller->Run();
	
	//must delete explicitly when "new" is used
	delete controller;
	
	return 0;
}


