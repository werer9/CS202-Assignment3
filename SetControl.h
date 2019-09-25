#ifndef _SetControl_h
#define _SetControl_h

#include "SetUI.h"
#include "SetOfStrings.h"
#include "StringRelation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <cctype>

#ifdef _DEBUG
#define ASSERT(condition, message) \
do { \
	if (! (condition)) { \
		std::cerr << "\033[1;31m" << message << "('" #condition "') failed in " << __FILE__ \
		<< " line " << __LINE__ << ". (debugging terminated)\033[0m" << std::endl; \
		exit(1); \
	} \
	else { \
		std::cout << "\033[1;32m" << message << "('" #condition "') passed.\033[0m" << std::endl; \
	} \
} while (false)
#else
// basically do nothing
#define ASSERT(condition, message) do { } while (false)
#endif

class SetControl
{
	private:
		SetUI* setUI;
		SetOfStrings *setModel;
		StringRelation *relationModel;
		
		// For unit testing
		#ifdef _DEBUG
		void Testing();
		#endif
				
	public:
		SetControl();	
		~SetControl();
		
		bool Run();
};
#endif
