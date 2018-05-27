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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "resources.h"
#include "xiversion.h"
#include "error.h"
#include "list.h"
#include "colours.h"


int list(int argc, char **argv) {
	
	Display *dpy=openDisplayNegotiateVersion();
	
	int numdev;

	XIDeviceInfo *devices,*originalpointer;

	char *pr_defaultcolour=getColourForPrint(-1);

	originalpointer=devices=XIQueryDevice(dpy,XIAllDevices,&numdev);

	if(0==numdev) {
		
		XIFreeDeviceInfo(devices);
		
		die_with_error("No X input devices found");
	}


	fprintf(stdout,"%s",pr_defaultcolour==NULL?"":pr_defaultcolour);
	
	for(int devcounter=0; devcounter<numdev; devcounter++) {
	
		char *pr_idcolour=NULL,*pr_attachmentcolour=NULL;
		
		if(XIMasterPointer==devices[devcounter].use||XIMasterKeyboard==devices[devcounter].use)
			pr_idcolour=getColourForPrint(devices[devcounter].deviceid);

		pr_attachmentcolour=getColourForPrint(devices[devcounter].attachment);

		fprintf(
			stdout,
			"id=%s%02d%s, name=%s, use=%d, attachment=%s%02d%s, enabled=%s",
			pr_idcolour==NULL?"":pr_idcolour,
			devices[devcounter].deviceid,
			pr_defaultcolour==NULL?"":pr_defaultcolour,
			devices[devcounter].name,
			devices[devcounter].use,
			pr_attachmentcolour==NULL?"":pr_attachmentcolour,
			devices[devcounter].attachment,
			pr_defaultcolour==NULL?"":pr_defaultcolour,
			devices[devcounter].enabled?"enabled":"disabled"
		);
		
		free(pr_idcolour);
		
		free(pr_attachmentcolour);
		
		switch(devices[devcounter].use) {
		
			case XIMasterPointer: 
				fprintf(stdout,", master pointer");
				break;
			case XIMasterKeyboard:
				fprintf(stdout,", master keyboard");
				break;
			case XISlavePointer:
				fprintf(stdout,", slave pointer");
				break;
			case XISlaveKeyboard:
				fprintf(stdout,", slave keyboard");
				break;
			case XIFloatingSlave:
				fprintf(stdout,", unattached");
				break;
				
		}
		
		fprintf(stdout,"\n");
		
	}
	
	printf("found %d device(s)\n",numdev);
	
	XIFreeDeviceInfo(originalpointer);
	
	closeDisplay();
	
	freeColours();
	
	free(pr_defaultcolour);
	
	return EXIT_SUCCESS;
}