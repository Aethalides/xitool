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
#ifndef HAVE_PROPS_H
#define HAVE_PROPS_H
#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xutil.h>

#define PROP_DEVICE_ENABLED "Device Enabled"

typedef enum {
	
	SUCCESS,
	MISSING_OPERAND,
	NO_DEVICE,
	NO_VALUE,
	NO_MEMORY,
	NOT_FOUND,
	UNSUPPORTED_TYPE_FORMAT,
	CONVERSION_ERROR,
	ERROR
	
} propOpStatus;



Atom getAtom(const char* input);
propOpStatus setProperty(Atom property,XIDeviceInfo *device,int valuecount,char **newValue);
#endif
