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
#ifndef VERSIONABOUTHELP_H
#define VERSIONABOUTHELP_H

#include "modules.h"

#define YEAR_LENGTH 5

int help(int argc, char **argv);
int version(int argc, char** argv);
int usage(const module module,const char* error);
int nomodule(int argc,char **argv);

#endif
