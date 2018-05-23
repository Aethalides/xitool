#ifndef RESOURCES_H
#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/Xutil.h>
#include <stdlib.h>

Display *openDisplay();
void closeDisplay();

#define RESOURCES_H
#endif