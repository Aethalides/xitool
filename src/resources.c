#include "resources.h"
#include "error.h"

static Display *theDisplay=NULL;

void closeDisplay() {

	if(theDisplay!=NULL) {

		XCloseDisplay(theDisplay);
		
		theDisplay=NULL;
	}
}

Display *openDisplay() {

	if(theDisplay==NULL) {
	
		theDisplay=XOpenDisplay(NULL);
		
		if(theDisplay==NULL) {
		
			die_with_error("Unable to open display");
		}
		
		atexit(closeDisplay);
	}
	
	return theDisplay;
}