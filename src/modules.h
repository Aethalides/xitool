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
