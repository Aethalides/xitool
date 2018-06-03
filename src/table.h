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
#ifndef HAVE_TABLE
#define HAVE_TABLE

#include "colours.h"
#include <string.h>
#include <X11/extensions/XInput2.h>

#define ALIGN_NONE 0
#define ALIGN_LEFT 1
#define ALIGN_RIGHT 2
#define ALIGN_CENTER 4

#define XDEVID 0
#define XDEVNAME 1
#define XDEVTYPE 2
#define XDEVCLASS 3
#define XDEVMASTER 4
#define XDEVSTATE 5

typedef s_colour (*colourise)(XIDeviceInfo *devinfo,unsigned char info_field);

typedef struct {
	char *name;
	size_t width;
	unsigned char info_field;
	unsigned char align;
} table_column;

typedef struct {
	size_t len_header;
	size_t len_separator;
} header_row_length;

void  printTableHeader(void);
void  printTableRow(XIDeviceInfo *rowdata);

char* sprintTableHeader(void);
char* sprintTableRow(XIDeviceInfo *rowdata);
char* sprintTableCell(XIDeviceInfo *rowdata,table_column *column);

int   setColumnColouriser(colourise colouriser);

#endif
