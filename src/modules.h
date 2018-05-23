#ifndef MODULES_H
#include "versionhelp.h"
#include "list.h"
#include "stddef.h"

typedef int (*module)(int argc, char **argv);

typedef struct {
	char *modname;
	char *argument_help;
	char *short_description;
	module themodule;
	
} s_module;

static s_module modules[]={
	
	{"list",NULL,"list devices",list},
	
	{"help",NULL,"shows this help screen",help},
	
	{"version",NULL,"shows version and copyright information",version},
	
	{NULL,NULL}
};


module chooseModule(const char* firstArgument);
void printModuleHelp();

#endif
