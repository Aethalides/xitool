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
#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xutil.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "error.h"
#include "resources.h"
#include "modules.h"
#include "versionhelp.h"

/** 
 Functions we need to support:
	enable/disable devices
	find a device with a specific property or name
	
 
 */
int main(int argc,char *argv[]) {

	setInvocation(argv[0]);

	argc--;
	argv++;
	
	module toCall=argc?chooseModule(argv[0]):nomodule;
	
	if(toCall==nomodule) {
		
		return nomodule(argc,argv);
		
	} else {
		
		argc--;
		argv++;
		
		return toCall(argc,argv);
		
	}
	
}
