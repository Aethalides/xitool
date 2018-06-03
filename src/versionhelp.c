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

#include "versionhelp.h"
#include "error.h"
#include "modules.h"
#include "xitool.h"
#include "xiversion.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int help(int argc, char **argv) {
	
	char *invoc=getInvocation();
	
	if(invoc==NULL)
		die_with_bug("getInvocation() returned NULL");
	
	fprintf(

		stdout,

		 "Usage: %s COMMAND [OPTIONS]\nInteract with X Input device settings.\n\n",

		 getInvocation()
	);

	printModuleHelp();
	
	return EXIT_FAILURE;
}

int usage(const module mod,const char *error) {

	s_module *currentmod=NULL;
	char* invocation=NULL;
	
	if(mod==NULL)
		die_with_bug("Usage called without module");
	
	if(error==NULL)
		die_with_bug("Usage called without error");
	
	currentmod=getModuleByFunctionPointer(mod);
	
	if(currentmod->themodule==NULL)
		die_with_bug("getModuleByFunctionPointer() returned NULL");
	
	invocation=getInvocation();
	
	if(invocation==NULL)
		die_with_bug("getInvocation() returned NULL");
	
	fprintf(
		
		stderr,
		 
		 "%s: %s\nUsage: %s --%s %s\nTry '%s --help' for more information.\n",
		 
		invocation,error,
			
		invocation,currentmod->longarg,
		 
		currentmod->argument_help,
		 
		invocation
	);
	
	return EXIT_FAILURE;
}

int version(int argc, char **argv) {
	
	const char *ver=VERSION;

	const char *self=PACKAGE_NAME;
	
	const char *author=AUTHOR;
	
	const signed short startyear=START_YEAR;

	const time_t theTime=time(NULL);
	
	char* theYear=malloc(YEAR_LENGTH);

	const struct tm *now=localtime(&theTime);
	
	Display *dpy=NULL;
	
	xiversion result;
	
	if(theYear==NULL)
		die_with_error("Unable to allocate memory");
	
	memset(theYear,0,YEAR_LENGTH);
	
 	if(0<strftime(theYear,YEAR_LENGTH,"%Y",now))
		snprintf(theYear,YEAR_LENGTH,"%s","2018");
	
	fprintf(stdout,"%s %s\nCopyright (C) %d",self,ver,startyear);
	
	if(atoi(theYear)>startyear)
		fprintf(stdout,"-%s",theYear);
	
	fprintf(
		stdout,
		 " %s\n\nThis program may be freely distributed under\nthe terms of the GNU General Public License\nVersion 3 or above.\n\n",
		 author
	);
	
	free(theYear);
	
	dpy=openDisplay();
	
	result=getTestXiVersionDefault(dpy);
	
	if(0>=result.major||0>=result.minor)
		die_with_error("Unable to get negotiate XI Version");
	
	fprintf(
		stdout,"Negotiated XI Version: %d.%d\n",
		 
		result.major,result.minor
	);
	
	closeDisplay();
	
	return EXIT_SUCCESS;
}

int nomodule(int argc,char **argv) {

	if(argc)
		printMessage("Unrecognised command %s",argv[0]);
	
	fprintf(stderr,"Try '%s --help' for more information.\n",getInvocation());
	
	return EXIT_FAILURE;
}
