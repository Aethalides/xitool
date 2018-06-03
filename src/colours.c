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
#include "colours.h"
#include "error.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static const s_colour colours[]={
	//fore,back
	{C_BLACK,C_YELLOW},
	{C_BLACK,C_AQUAMAR},
	{C_BLACK,C_FUCHIA},
	{C_WHITE,C_EINDIGO},
	{C_BLACK,C_BABBLUE},
	{C_BLACK,C_CHARTRS},
	{C_EOL,C_EOL}
};

static size_t colindex=0,array_members=0,array_size=0;

static s_colour_id **colour_id_array;

static int getNextColourId(void) {
	
	if(colours[colindex].forecolour==-1)
		colindex=0;
		
	return colindex++;
}

s_colour getNextColour(void) {

	s_colour out;
	
	int index=getNextColourId();
	
	out.backcolour=colours[index].backcolour;
	out.forecolour=colours[index].forecolour;
	
	return out;
}

static void resizeArray(size_t new_size_members) {
	
	s_colour_id **new_pointer=NULL;

	size_t old_array_size=array_size;
	
	if(new_size_members==array_size)
		return;
	
	if(new_size_members<array_size) {
	
		freeColours();
		
		die_with_error("BUG: cannot downsize array");
	}
	
	if(array_size==0) {
	
		array_members=0;

		new_pointer=calloc(new_size_members,sizeof(s_colour_id*));
		
	} else if(new_size_members>array_size) {
	
		#ifdef _GNU_SOURCE
			
			new_pointer=reallocarray(colour_id_array,sizeof(s_colour_id*),new_size_members);
			
		#else
		
			new_pointer=realloc(colour_id_array,sizeof(s_colour_id*)*new_size_members);
			
		#endif
	}
	
	if(new_pointer==NULL) {
	
		freeColours();
		
		die_with_error("Cannot allocate memory for colour list");
	}
	
	array_size=new_size_members;
	
	colour_id_array=new_pointer;
	
	for(size_t iter=old_array_size; iter<array_size; iter++) {
		
		s_colour_id *memberpointer=malloc(sizeof(s_colour_id));
		
		if(memberpointer==NULL) {
			
			freeColours();

			die_with_error("Cannot allocate memory for colour element #%zu",iter);
		}
		
		colour_id_array[iter]=memberpointer;
		
		colour_id_array[iter]->id=
		 colour_id_array[iter]->colour_id=-1;
	}
}

static s_colour_id *getArrayMemberForId(int id) {

	if(array_size==0) {
	
		resizeArray(COLOURLIST_INITIAL_SIZE);
		
		array_members=1;
		
		colour_id_array[0]->id=id;
		
		return colour_id_array[0];
	}
	
	if(array_members>0) {
		
		for(size_t count=0; count<array_members; count++) {
		
			if(colour_id_array[count]->id==id) {
				
				return colour_id_array[count];
				
			}
		}
	}
	
	if(array_members+1>array_size) 
		resizeArray(COLOURLIST_INITIAL_SIZE+array_size);
	
	colour_id_array[array_members]->id=id;
		
	return colour_id_array[array_members++];
}

s_colour getColourForId(int id) {
	
	s_colour out={C_FG_DEF,C_BG_DEF};
	s_colour_id *storage;
	
	if(-1==id) 
		return out;
	
	storage=getArrayMemberForId(id);

	if(-1==storage->colour_id)
		storage->colour_id=getNextColourId();

 	out.forecolour=colours[storage->colour_id].forecolour;
 	out.backcolour=colours[storage->colour_id].backcolour;
	
	return out;
}

char *sprintColour(s_colour *colour) {

	char *out=NULL;
	
	static int istty=-1;
	
	if(istty==-1)
		istty=isatty(fileno(stdout));
	
	if(0==istty)
		return NULL;
	
	out=malloc(PR_COL_LEN);
	
	if(out==NULL)
		return NULL;
	
	memset(out,0,PR_COL_LEN);
	
	snprintf(
		out,PR_COL_LEN,
		PRINT_FG_BG_TEMPLATE,
		colour->forecolour==-1?C_FG_DEF:colour->forecolour,
		colour->backcolour==-1?C_BG_DEF:colour->backcolour
	);
	
	return out;
}

char *sprintColourForId(int id) {

	s_colour colour=getColourForId(id);;
	
	return sprintColour(&colour);
}

void freeColours(void) {

	if(colour_id_array==NULL) 
		return;
	
	for(size_t iter=0; iter<array_size; iter++)
		free(colour_id_array[iter]);
	
	free(colour_id_array);
	
	colour_id_array=NULL;
	
	array_members=array_size=0;
}