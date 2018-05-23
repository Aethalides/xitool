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
	
	fprintf(

		stdout,

		 "Usage: %s COMMAND [OPTIONS]\nInteract with X Input device settings.\n\n",

		 getInvocation()
	);

	fprintf(
	
		stdout,
		 
		"Commands may optionally be prefixed with a single or a double hyphen,\nand may be shorted to the first letter\n\n"
	);
	
	printModuleHelp();
	
	return 1;
}

int version(int argc, char **argv) {
	
	const char *ver=VERSION;

	const char *self=PACKAGE_NAME;
	
	const char *author=AUTHOR;
	
	const signed short startyear=START_YEAR;
	
	char* theYear=malloc(YEAR_LENGTH);
	
	if(theYear==NULL)
		die_with_error("Unable to allocate memory");
	
	memset(theYear,0,YEAR_LENGTH);
	
	const time_t theTime=time(NULL);
	
	const struct tm *now=localtime(&theTime);
	
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
	
	xiversion result=getTestXiVersionDefault();
	
	if(0>=result.major||0>=result.minor)
		die_with_error("Unable to get negotiate XI Version");
	
	fprintf(
		stdout,"Negotiated XI Version: %d.%d\n",
		 
		result.major,result.minor
	);
	
	return 0;
}

int nomodule(int argc,char **argv) {

	if(argc)
		printMessage("Unrecognised command %s",argv[0]);
	
	fprintf(stderr,"Try '%s --help' for more information.\n",getInvocation());
	
	return 1;
}
