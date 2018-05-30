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
#include "table.h"

static s_colour colouriseListFields(XIDeviceInfo *devinfo,unsigned char info_field) {
	
	s_colour out={-1,-1};
	
	switch(info_field) {
		
		case XDEVID: {
	
			if(XIMasterPointer==devinfo->use||XIMasterKeyboard==devinfo->use)
				return getColourForId(devinfo->deviceid);
			
			break;
		}
		
		case XDEVMASTER: {
		
			return getColourForId(devinfo->attachment);
			
			break;
		}
	}
			
	return out;
}

int list(int argc, char **argv) {
	
	Display *dpy=openDisplayNegotiateVersion();
	
	int numdev;

	XIDeviceInfo *devices;

	setColumnColouriser(colouriseListFields);
	
	devices=XIQueryDevice(dpy,XIAllDevices,&numdev);

	if(0==numdev) {
		
		XIFreeDeviceInfo(devices);
		
		die_with_error("No X input devices found");
	}

	printTableHeader();
	
	for(int devcounter=0; devcounter<numdev; devcounter++) {

		switch(devices[devcounter].use) {
			
			case XIMasterPointer: 
			case XIMasterKeyboard: 
			case XIFloatingSlave: {
			
				printTableRow(&devices[devcounter]);

				if(devices[devcounter].use!=XISlaveDetached) {
					
					// find dependents 
					
					for(int iter=0; iter<numdev; iter++) {
					
						if(devices[iter].attachment==devices[devcounter].deviceid &&
						   (devices[iter].use==XISlavePointer||devices[iter].use==XISlaveKeyboard))
							
							printTableRow(&devices[iter]);
					}
				}
				
				break;
			}
			
		}
	}
	
	printf("found %d device%s\n",numdev,1!=numdev?"s":"");
	
	XIFreeDeviceInfo(devices);
	
	closeDisplay();
	
	freeColours();
	
	return EXIT_SUCCESS;
}