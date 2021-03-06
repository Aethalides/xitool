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
#ifndef HAVE_XIVERSION_H
#define HAVE_XIVERSION_H

#include "resources.h"

#define ERROR_LENGTH 80

typedef struct {
	signed major;
	signed minor;
} xiversion;

typedef int (*xerrorhandler)(Display *dpy,XErrorEvent *event);

xiversion getTestXiversion(Display *dpy,const xiversion *wesupport);
xiversion getTestXiVersionDefault(Display *dpy);

Display *openDisplayNegotiateVersion(void);

#endif