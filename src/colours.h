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
#define HAVE_COLOURS_H

#define PRINT_FG_BG_TEMPLATE "\033[38;5;%ldm\033[48;5;%ldm"

#define PR_COL_LEN_f(s) ((sizeof(s)/sizeof(s[0]))-1)

#define PR_COL_LEN PR_COL_LEN_f(PRINT_FG_BG_TEMPLATE)

#define C_BLACK    16 // #000000
#define C_BABBLUE  87 // #5fffff - baby blue
#define C_EINDIGO  93 // #8700ff - electric indigo
#define C_AQUAMAR  85 // #5fffaf - aquamarine
#define C_CHARTRS 118 // #87ff00 - chartreuse
#define C_FUCHIA  201 // #ff00ff
#define C_YELLOW  226 // #ffff00
#define C_WHITE   231 // #ffffff

#define C_BG_DEF C_BLACK
#define C_FG_DEF C_WHITE

#define C_EOL -1

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

char *sprintColour(s_colour *colour);
char *sprintColourForId(int theColour);

void freeColours(void);

#define COLOURLIST_INITIAL_SIZE 2

#endif