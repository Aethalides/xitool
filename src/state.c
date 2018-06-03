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

#include "xitool.h"
#include "state.h"
#include "versionhelp.h"
#include "error.h"
#include "props.h"
#include "resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static Bool convIfInt(int *converted,char *input);

static XIDeviceInfo *getDevice(char *devspec,int numDevices,XIDeviceInfo *devs) {
	
	XIDeviceInfo *out=NULL;
	Bool useId=False;
	
	int *numid=malloc(sizeof(int));
	
	if(numid==NULL)
		return NULL;
	
	useId=convIfInt(numid,devspec);
		
	for(size_t iter=0; iter<numDevices; iter++) {
	
		if(True==useId) {
			
			if(devs[iter].deviceid==*numid) {
			
				out=&devs[iter];
				
				break;
			}
			
		} else {
			
			if(0==strcmp(devspec,devs[iter].name)) {
			
				if(out==NULL) {
				
					out=&devs[iter];
					
				} else {
				
					// matched more than once
					
					out=NULL;
					
					break;
				}
			}
		}
	}
	
	free(numid);
	
	return out;
}

static Bool convIfInt(int *converted,char *input) {

	size_t len=0,iter=0;
	
	if(converted==NULL)
		return False;
	
	if(input==NULL)
		return False;
	
	len=strlen(input);
	
	if(len==0)
		return False;

	if(len>MAX_INT_CONVLENGTH)
		return False;
	
	for(iter=0; iter<len; iter++) {
		if(!isdigit((char) input[iter]))
			return False;
	}
	
	*converted=atoi(input);
	
	return 0<*converted?True:False;
}

static void printOpError(propOpStatus *result,char *devname,int *devid) {
	
	char *format=(char *) "%s device #%d (%s)";
	
	char *stdev=(char *) "Unknown device", *usedev=stdev;
	
	int stdevid=-1; 
	int *dev=&stdevid;
	
	if(result==NULL) {
		
		printWarning("Cannot print operation status; result==NULL");
	
		return;
	}
	
	if(devname!=NULL)
		usedev=devname;
	
	if(devid!=NULL)
		dev=devid;
	
	switch(*result) {
				
		case SUCCESS: {
			
 			break;
		}
			
		case ERROR: {
			
			printMessage(format,"error setting property for",*dev,usedev);
			
			break;
		}
			
		case MISSING_OPERAND: {
			
			printMessage(format,"BUG: operand not set when setting property for",*dev,usedev);
			
			break;
		}
		
		case NOT_FOUND: {
		
			printMessage(format,"property not found for",*dev,usedev);
			
			break;
		}
		
		case NO_DEVICE: {
		
			printMessage(format,"missing device operand for",*dev,usedev);
			
			break;
		}
		
		case NO_VALUE: {
		
			printMessage(format,"missing operand `value' for",*dev,usedev);
			
			break;
		}
		
		case NO_MEMORY: {
		
			printMessage(format,"memory allocation failed for",*dev,usedev);
			
			break;
		}
		
		case UNSUPPORTED_TYPE_FORMAT: {
		
			printMessage(format,"The format of the property is unrecognised/not supported for",*dev,usedev);
			
			break;
		}
		
		case CONVERSION_ERROR: {
		
			printMessage(format,"Type conversion failed; check that provided arguments are suitable for the type of the property for",*dev,usedev);
			
			break;
		}
	} 
}

static int change_state(int state,int argc,char **argv) {
	
	int out=EXIT_FAILURE,processed=0,numdev=0;
	
	Atom devEnabled=getAtom(PROP_DEVICE_ENABLED);

	XIDeviceInfo *devices=NULL, *device=NULL;
	
	if(devEnabled==None) 
		die_with_error("Unable to lookup Atom number for %s property",PROP_DEVICE_ENABLED);

	devices=XIQueryDevice(openDisplay(),XIAllDevices,&numdev);
	
	if(numdev==0)
		die_with_error("No devices found");
	
	for(size_t iter=0; iter<argc; iter++) {
		
		propOpStatus result=ERROR;
		
		device=getDevice(argv[iter],numdev,devices);
		
		if(device==NULL) {
		
			printWarning("Device %s not found or matched more than once",argv[iter]);
			
			continue;
		}
		
		{ 
			size_t length=MAX_INT_CONVLENGTH*2;
			
			char *statestr=malloc(sizeof(char)*(length+1));
			
			if(statestr==NULL)
				die_with_error("Unable to allocate memory for new property state");
			
			memset(statestr,0,length+1);
			
			snprintf(statestr,length,"%d",state);
			
			result=setProperty(devEnabled,device,1,&statestr);

			if(SUCCESS==result) {
			
				processed++;
				
			} else {
				
				printOpError(&result,device->name,&device->deviceid);
			}
			
			free(statestr);
		}
	}
	
	XIFreeDeviceInfo(devices);
	
	out=processed>0&&processed==argc;
	
	return out;
}

int enable(int argc, char **argv) {

	if(0==argc) 
		usage(&enable,"missing operand");
	
	return change_state(1,argc,argv);
}

int disable(int argc, char **argv) {
	
	if(0==argc)
		usage(&disable,"missing operand");
	
	return change_state(0,argc,argv);
}
