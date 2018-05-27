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

#ifndef HAVE_COLOURS_H

#define PR_COL_LEN 24

typedef struct {
	long forecolour;
	long backcolour;
} s_colour;

typedef struct {
	int id;
	int colour_id;
} s_colour_id;

s_colour getNextColour(void);
s_colour getColourForId(int id);

char *getColourForPrint(int theColour);

void freeColours(void);

#define COLOURLIST_INITIAL_SIZE 2

#define HAVE_COLOURS_H
#endif