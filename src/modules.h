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
#ifndef HAVE_MODULES_H
#define HAVE_MODULES_H

typedef int (*module)(int argc, char **argv);

#include "versionhelp.h"
#include "list.h"
#include "state.h"

#define SHORTARGLEN 3

#define HELP_FOOTER \
   "<device> number       --> interpret as device id number\n<device> alphanumeric --> interpret as device name\n"

   
typedef struct {
	char *longarg;
	char shortarg;
	char *argument_help;
	char *short_description;
	module themodule;
	
} s_module;

module chooseModule(const char* firstArgument);
s_module *getModuleByFunctionPointer(module fp);
void printModuleHelp(void);

#endif
