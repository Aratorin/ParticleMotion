#include <iostream>
#include <SDL.h>
#include "Screen.h"
using namespace std;
using namespace Aratorin;

int main(int argc, char* argv[]) {
	

	Screen screen;
	if (screen.init() == false) {
		cout << "Error initializing SLD." << endl;
	}

	while (true) {
		//Update particles
		//Draw particles
		//Check for messages/events
		if (screen.processEvents() == false) {
			break;
		}
		
	}

	screen.close();

	return 0;
}
