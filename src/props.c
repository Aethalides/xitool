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
#include "props.h"
#include "resources.h"
#include "error.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>   
#include <stdio.h>
#include <X11/Xatom.h>
#include <bits/stdint-uintn.h>
#include <errno.h>


typedef union {
	uint16_t *ushort;
	uint32_t *ulong;
	unsigned char *chars;
} propUnion;

// if all numbers, we'll assume input is already an Atom
Atom getAtom(const char* input) {
	
	int alldigits=1;
	size_t len=0;
	
	if(NULL==input)
		return None;
	
	len=strlen(input);

	for(size_t iter=0; iter<len; iter++) {
		
		if(!isdigit((char) *(input+iter))) {
			
			alldigits=0;
			
			break;
		}
	}
	
	if(alldigits)
		return atol(input);
		
	return XInternAtom(openDisplay(),input,True);
}

static propOpStatus packInts(propUnion *store,int *size,int *numitems,char **items) {
	
	if(store==NULL  || numitems==NULL || items==NULL 
					|| *numitems<=0   || size==NULL || *size<=0)
		return ERROR;
	
	for(int iter=0; iter<*numitems; iter++) {
	
		errno=0;
		
		switch(*size) {
		
			case 8: {
				
				int result=strtol(items[iter],(char**) NULL,10);
				
				if(errno>0)
					return CONVERSION_ERROR;
				
				store->chars[iter]=result;
				
				break;
			}
			
			case 16: {
			
				uint16_t result=strtoul(items[iter],(char**) NULL,10);
				
				if(errno>0)
					return CONVERSION_ERROR;
				
				store->ushort[iter]=result;
				
				break;
			}
			
			case 32: {
			
				uint32_t result=strtoull(items[iter],(char**) NULL,10);
				
				if(errno>0)
					return CONVERSION_ERROR;
				
				store->ulong[iter]=result;
				
				break;
			}
			
			default: {
			
				return UNSUPPORTED_TYPE_FORMAT;
				
				break;
			}
		}
	}
	
	return SUCCESS;
}

// only for existing props
propOpStatus setProperty(Atom property,XIDeviceInfo *device,int valuecount,char **newValue) {

	Atom returnedType=None;
	int returnedFormat=0;
	unsigned long numItemsAfterRet=0;
	unsigned long bytesAfterRet=0;
	unsigned char *propdata=NULL;
	Status gotProp;
	propUnion dataStore;
	
	dataStore.chars=malloc(sizeof(u_int32_t)*valuecount);

	if(property==None)
		return MISSING_OPERAND;
	
	if(device==NULL)
		return NO_DEVICE;
	
	if(valuecount==0 || newValue==NULL)
		return NO_VALUE;

	if(dataStore.chars==NULL)
		return NO_MEMORY;
	
	gotProp=XIGetProperty(
		openDisplay(),device->deviceid, 
		property, 0,0,
		False, //delete?
		AnyPropertyType,
		&returnedType,&returnedFormat,&numItemsAfterRet,
		&bytesAfterRet,&propdata
	);

	XFree(propdata);

	if(gotProp!=Success)
		return NOT_FOUND;

	/* format is a list of 8, 16, or 32 bit quantities
	 * 16, and 32 bit formats must be cast to unsigned char * for
	 * calling XIChangeProperty
	 * The returned data tells us how to pack everything into an unsigned char array 
	 * before passing it along to XIChangeProperty */
	
	fprintf(
		stderr,
		 "Type for property %ld is %ld; format is %d x %ld item(s)\n",
			property,returnedType,returnedFormat,numItemsAfterRet
	);
	
	fprintf(
		stderr,
		 "Bytes after return: %ld\n",bytesAfterRet
	);
	
	{
		propOpStatus packed=ERROR;
		
		switch(returnedType) {
		
			case XA_INTEGER: {
			
				packed=packInts(&dataStore,&returnedFormat,&valuecount,newValue);
					
				break;
			}
			
			case XA_STRING: {
			
				break;
			}
			
			default: {
			
				// could be a float
				
				break;
			}
		}
		
		if(packed!=SUCCESS) {
			
			free(dataStore.chars);
			
			return packed;
		}
		
		// what to do when success
		
		XIChangeProperty(
			openDisplay(), 
			device->deviceid, 
			property, 
			returnedType, 
			returnedFormat, 
			PropModeReplace,
			dataStore.chars, 
			valuecount
		);
	}
	
	if(dataStore.chars!=NULL)
		free(dataStore.chars);
	
	return SUCCESS;
}