#include "modules.h"

#include "error.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


static size_t getLongestModuleName() {
	
	size_t out=0,cur=0;
	
	s_module *theModules=modules;
	
	while(theModules->modname) {
	
		cur=strlen(theModules->modname);
		
		if(cur>out)
			out=cur;
		
		++theModules;
	}
	
	return out;
}

void printModuleHelp() {
	
	s_module *theModules=modules;
	
	const char *padding="                                                    ";
	
	const unsigned int longest=getLongestModuleName();
	
	unsigned int current=0,padlen=0;
		
	while(NULL!=theModules->modname) {
	
		current=strlen(theModules->modname);
		
		padlen=longest-current;
		
		if(0>padlen) 
			padlen=0;
		
		fprintf(
			stdout,
			
			"%s%*.*s %s\n%*.*s %s\n",
		 
			theModules->modname,
		 
			padlen,padlen,padding,
		
			theModules->argument_help==NULL?"":theModules->argument_help,
		 
			longest,longest,padding,
		 
			theModules->short_description
		);
		
		++theModules;
	}
	
}

module chooseModule(const char* firstArgument) {
	
	s_module *theModules=modules;

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
	
	while(0==strncmp("-",argument,1)) 
		++argument;
	
	while(theModules->modname) {
	
		char first=(char) theModules->modname[0];
		
		if(0==strcmp(argument,theModules->modname) ||
		   0==strcmp(argument,&first)) {
		
			mod_out=theModules->themodule;
			
			break;
		}
		
		++theModules;
	}
	
	if(origargumentlocation!=NULL)
		free(origargumentlocation);
	
	return mod_out;
}