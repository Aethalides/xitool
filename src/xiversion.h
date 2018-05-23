#ifndef HAVE_XIVERSION_H
#include "resources.h"

#define ERROR_LENGTH 80

typedef struct {
	signed major;
	signed minor;
} xiversion;

typedef int (*xerrorhandler)(Display *dpy,XErrorEvent *event);

xiversion getTestXiversion(const xiversion *wesupport);
xiversion getTestXiVersionDefault();

#define HAVE_XIVERSION_H
#endif