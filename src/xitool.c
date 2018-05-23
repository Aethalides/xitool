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
