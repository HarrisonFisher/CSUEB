// EvilHangman2.cpp : Defines the entry point for the console application.
//
#define AskFileAndDebug


#include <string>
#include <iostream>
#include "FamilySet.h"
//#include "TreeMap.h"

#include "EvilHangman.h"

using namespace std;

int main()
{
    string file;


    #ifdef AskFileAndDebug
        cout << "Enter file: ";
        cin >> file;				// Can comment out this line and include the following while developing
    #else
        file = "dictionary.txt";  // Convenient to hard code while developing
    #endif

    cout << file << endl;       //DELETE
	while (true) {
	    #ifdef AskFileAndDebug
		    debug = PromptYesNoMessage("Turn debugging on?");
        #else
	        debug = true;
        #endif
		PlayEvilHangman(file);
		if (!PromptYesNoMessage("Would you like to play again? "))
			break;
	}
}

