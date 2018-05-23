/* This file is part of xitool.
Copyright 2018 Andy Pieters
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>. */
#include "xiversion.h"
#include "xitool.h"
#include "resources.h"
#include "error.h"
#include <stdio.h>
#include <string.h>

static int xiversionerrorhandler(Display *theDpy,XErrorEvent *error) {

	char *error_buffer=malloc(ERROR_LENGTH);
	
	if(error_buffer==NULL) {

		printMessage("X Error #%d occurred whilst negotiating supported versions",error->error_code);
		
	} else {
		
		memset(error_buffer,0,ERROR_LENGTH);
		
		XGetErrorText(theDpy,error->error_code,error_buffer,ERROR_LENGTH-1);
	
		printMessage("X Error #%d: %s occurred whilst negotiating supported versions",error->error_code,error_buffer);
		
		free(error_buffer);
	}
	
	return 1;
}

xiversion getTestXiversion(const xiversion *wesupport) {
	
	xerrorhandler orig=XSetErrorHandler(xiversionerrorhandler);
	
	xiversion out={-1,-1};
	
	if(0>=wesupport->major||0>=wesupport->minor) {
	
		die_with_error(
			
			"Invalid value %d.%d for requested XI Version",
				
			wesupport->major,wesupport->minor
		);
	}
	
	int major=wesupport->major;
	int minor=wesupport->minor;
	
	Display *dpy=openDisplay();
	
	int result=XIQueryVersion(dpy,&major,&minor);

	switch(result) {
		
		case Success: {
		
			out.major=major;
			out.minor=minor;
			
			break;
		}
		
		case BadRequest: {
		
			die_with_error(
			
				"We support version %d.%d of the XI protocol, but the server only supports versions up to and including %d.%d",
				
				wesupport->major,wesupport->minor,
				
				major,minor
			);
			
			break;
		}
	}
	
	closeDisplay();
	
	XSetErrorHandler(orig);
	
	return out;
}

xiversion getTestXiVersionDefault() {

	const signed short major=XI_MAJOR_SUPPORTED;
	const signed short minor=XI_MINOR_SUPPORTED;
	
	xiversion request;
	
	request.major=major;
	request.minor=minor;
	
	return getTestXiversion(&request);
	
}

Display *openDisplayNegotiateVersion() {

	Display *dpy=openDisplay();
	
	getTestXiVersionDefault();
	
	return dpy;
}