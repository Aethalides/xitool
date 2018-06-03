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

#include "modules.h"
#include "error.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const s_module modules[]={

	{(char*) "list",'l',NULL,(char*) "lists devices",list},
	
	{(char*) "enable",'e',(char*) "<device> [<device> ...]",(char*) "enables device(s) ",enable},
	
	{(char*) "disable",'d',(char*) "<device> [<device> ...]",(char*) "disables device(s) ",disable},

	{(char*) "help",'h',NULL,(char*) "shows this help screen",help},
	
	{(char*) "version",'v',NULL,(char*) "shows version and copyright information",version},
	
	{NULL,'\0',NULL}
};

static size_t getLongestModuleName(void) {
	
	size_t out=0,cur=0;
	
	const s_module *theModules=modules;
	
	while(theModules->longarg) {
	
		cur=strlen(theModules->longarg);
		
		if(cur>out)
			out=cur;
		
		++theModules;
	}
	
	return out;
}

void printModuleHelp(void) {
	
	const s_module *theModules=modules;
	
	const char *padding="                                                    ";
	
	const unsigned int longest=getLongestModuleName();
	
	unsigned int current=0,padlen=0;
		
	while(NULL!=theModules->longarg) {
	
		current=strlen(theModules->longarg);
		
		padlen=longest-current;
		
		if(0>padlen) 
			padlen=0;
		
		fprintf(
			stdout,
			
			"  -%c, --%s%*.*s %s\n%*.*s %s\n\n",
		 
			theModules->shortarg,
		  
			theModules->longarg,
		 
			padlen,padlen,padding,
		
			theModules->argument_help==NULL?"":theModules->argument_help,
		 
			longest,longest,padding,
		 
			theModules->short_description
		);
		
		++theModules;
	}
	
	#ifdef HELP_FOOTER
		fputs(HELP_FOOTER,stdout);
	#endif
}

s_module *getModuleByFunctionPointer(module fp) {
	
	const s_module *theModules=modules;
	
	s_module *out=NULL;
	
	while(theModules->longarg) {
	
		if(fp==theModules->themodule) {
			
			out=(s_module*) theModules;
			
			break;
		}
		
		theModules++;
	}
	
	return out;
}

module chooseModule(const char* firstArgument) {
	
	const s_module *theModules=modules;

	module mod_out=nomodule;
	
	char *argument=malloc(strlen(firstArgument)+1);
	
	char *origargumentlocation=NULL;
	
	if(argument==NULL)
		die_with_error("Unable to allocate memory");
		
	else {
	
		origargumentlocation=argument;
		
		memset(argument,0,strlen(firstArgument));
		
		strcpy(argument,firstArgument);
	}
	
	while(theModules->longarg) {
		
		char *modlongarg=NULL, *modshortarg=NULL;
		
#ifndef _GNU_SOURCE
		size_t shortlen=SHORTARGLEN;
		
		size_t longlen=strlen(theModules->longarg)+3;
		
		modshortarg=malloc(shortlen); // short hyphen+short arg
		
		modlongarg=malloc(longlen); // double hyphen + long arg

		if(modshortarg==NULL || modlongarg==NULL) {
		
			free(modshortarg);
			
			free(modlongarg);
			
			die_with_error("Unable to allocate memory");
		}
		
		memset(modshortarg,0,shortlen);
		memset(modlongarg,0,longlen);
		
		snprintf(modshortarg,shortlen,"-%c",theModules->shortarg);
		snprintf(modlongarg,longlen,"--%s",theModules->longarg);
#else
		if(-1==asprintf(&modshortarg,"-%c",theModules->shortarg))
			die_with_error("unable to allocate memory for short argument checking");

		if(-1==asprintf(&modlongarg,"--%s",theModules->longarg)) {
			
			free(modshortarg);
			
			die_with_error("unable to allocate memory for long argument checking");
		}
		
#endif		
		if(0==strcmp(modshortarg,argument) ||
		   0==strcmp(modlongarg,argument)) {

			free(modshortarg);
			
			free(modlongarg);
			
			mod_out=theModules->themodule;
			
			break;
		}
		
		free(modshortarg);
		
		free(modlongarg);
		
		++theModules;
	}
	
	free(origargumentlocation);
	
	return mod_out;
}