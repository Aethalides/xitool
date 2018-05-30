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
#include "table.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

static table_column list_table[]={
//       name             width info_field    align     
	{(char*)" id ",           4,XDEVID,     ALIGN_LEFT},
	{(char*)"  type  ",       9,XDEVTYPE,   ALIGN_RIGHT},
	{(char*)" class   ",      9,XDEVCLASS,  ALIGN_LEFT},
	{(char*)"master ",        7,XDEVMASTER, ALIGN_CENTER},
	{(char*)"   device name",60,XDEVNAME,   ALIGN_NONE},
	{NULL,-1,-1,-1}
};

static colourise columnColouriser=NULL;

static size_t countColumns(void);
static header_row_length getHeaderRowLength(void);

static size_t countColumns(void) {

	size_t out=0;
	
	table_column *cols=(table_column*) list_table;
	
	while(cols++->name!=NULL) 
		out++;
	
	return out;
}

static header_row_length getHeaderRowLength(void) {
	
	header_row_length out={0,0};
	
	table_column *cols=(table_column*) list_table;
	
	while(cols->name!=NULL) {
		
		header_row_length row={
			strlen(cols->name),
			cols->width
		};
		
		if(row.len_header>row.len_separator)
			row.len_separator=row.len_header;
		
		out.len_header+=row.len_header;
		out.len_separator+=row.len_separator;
		
		cols++;
	}
	
	return out;
}

int setColumnColouriser(colourise colouriser) {

	columnColouriser=colouriser;
	
	return EXIT_SUCCESS;
}

void printTableHeader(void) {

	char *th=sprintTableHeader();
	
	if(th==NULL) {
	
		die_with_error("Unable to get table header");
	}
	
	fputs(th,stdout);

	free(th);
}

char* sprintTableHeader(void) {
	
	header_row_length header=getHeaderRowLength();
	
	// 2 line breaks + 1 null
	size_t memneeded=sizeof(char)*(header.len_header+header.len_separator+3);
	
	size_t used=0;
	
	char *out=malloc(memneeded);
	
	table_column *cols=(table_column*) list_table;
	
	if(out==NULL)
		die_with_error("Unable to allocate %d byte(s) for table row",memneeded);
	
	memset(out,0,memneeded);
	
	while(cols->name!=NULL) {
	
		size_t usedlen=strlen(cols->name);
		
		memcpy(out+used,cols->name,usedlen);
	
		used+=usedlen;
		
		cols++;
	}
	
	*(out+used++)='\n';
	
	memset(out+used,'-',header.len_separator);

	used+=header.len_separator;
	
	*(out+used++)='\n';
	
	return out;
}

void printTableRow(XIDeviceInfo *rowdata) {

	char *tr=sprintTableRow(rowdata);
	
	if(tr==NULL)
		die_with_error("Unable to get table row");
	
	fputs(tr,stdout);
	
	free(tr);
}


char* sprintTableCell(XIDeviceInfo *rowdata,table_column *column) {
	
	char *out=NULL;
	size_t needed=column->width,used=0;
	s_colour colcolour={-1,-1},defcolour={-1,-1};
	char *rowColour=NULL,*undoRowColour=NULL;
	
	if(columnColouriser!=NULL)
		colcolour=columnColouriser(rowdata,column->info_field);
	
	if(colcolour.backcolour!=-1 && colcolour.forecolour!=-1) {
	
		rowColour=sprintColour(&colcolour);
		
		if(rowColour!=NULL)
			undoRowColour=sprintColour(&defcolour);
	}
	// TODO: alignment of string
	
	if(rowColour!=NULL)
		needed+=strlen(rowColour);
	
	if(undoRowColour!=NULL)
		needed+=strlen(undoRowColour);
	
	out=malloc(sizeof(char)*(needed+1));
	
	if(out==NULL) {
	
		if(rowColour!=NULL)
			free(rowColour);
		
		if(undoRowColour!=NULL)
			free(undoRowColour);
		
		return NULL;
	}
	
	memset(out,'\0',needed+1);
	
	memset(out,' ',needed);
	
	if(NULL!=rowColour) {
		
		size_t collen=strlen(rowColour);
	
		memcpy(out,rowColour,collen);
		
		used+=collen;
		
		free(rowColour);
	}

	switch(column->info_field) {
		
		case  XDEVMASTER:{
		
			size_t written=0;
			
			if(rowdata->use==XIFloatingSlave) {
				
				written=snprintf(out+used,needed-used,"--");
				
			} else {
				
				written=snprintf(out+used,needed-used,"%02d",rowdata->attachment);
			}
			
			used+=written;
			
			*(out+used)=' ';
			
			break;
		}
		
		case XDEVID: {
		
			size_t written=snprintf(out+used,needed-used,"%02d",rowdata->deviceid);

			used+=written;
			
			*(out+used)=' ';
			
			break;
		}
		
		case XDEVTYPE: {
		
			size_t written=snprintf(out+used,needed-used,"%s",rowdata->use==XIMasterPointer||rowdata->use==XISlavePointer?"pointer":"keyboard");
			
			used+=written;
			
			*(out+used)=' ';
			
			break;
		}
		
		case XDEVCLASS: {
		
			size_t written=snprintf(out+used,needed-used,"%s",rowdata->use==XIMasterPointer||rowdata->use==XIMasterKeyboard?"master":"slave");
			
			used+=written;
			
			*(out+used)=' ';
			
			break;
		}
		
		case XDEVNAME: {
			
			size_t written=snprintf(
				
				out+used,needed-used,
				
				"%s%s",
			
				rowdata->use==XIFloatingSlave||rowdata->use==XIMasterPointer||rowdata->use==XIMasterKeyboard
				?"":"  ",
				
				rowdata->name
			);
			
			used+=written;
			
			*(out+used)=' ';
			
			break;
		}
	}
		
	if(undoRowColour!=NULL) {
	
		size_t collen=strlen(undoRowColour);
		
		memcpy(out+used,undoRowColour,collen);
		
		free(undoRowColour);
	}
	
	return out;
}

static void freeCells(char **cells,size_t count) {

	if(count<=0) 
		return;
	
	for(size_t iter=0; iter<count; iter++) {
	
		if(cells[iter]!=NULL)
			free(cells[iter]);
	}
	
	free(cells);
}

char* sprintTableRow(XIDeviceInfo *rowdata) {

	char *out=NULL,*cell=NULL;
	char **cells=NULL;
	size_t rowlen=0,used=0,len=0;
	
	size_t columns=countColumns();
	
	if(0==columns)
		die_with_error("No columns in table");
	
	
	/* construct each field into a char* then add each to the array.
	 * afterwards we know how many bytes to allocate for our output */
	
	cells=malloc(sizeof(char**)*columns);
	
	if(cells==NULL) {
		
		die_with_error("Unable to allocate memory for cell data");
	}
	
	for(size_t iter=0; iter<columns; iter++) {
	
		cell=sprintTableCell(rowdata,&list_table[iter]);
		
		if(cell==NULL) {
		
			freeCells(cells,columns);
			
			die_with_error("Unable to allocate memory for cell #%lu",iter);
		}
		
		rowlen+=strlen(cell);
		
		cells[iter]=cell;
	}
	
	// now we can print everything to output
	
	out=malloc(sizeof(char)*rowlen+2); // line break and zero
	
	if(out==NULL) {
	
		freeCells(cells,columns);
		
		die_with_error("Unable to allocate memory for row");
	}
	
	memset(out,'\0',rowlen+2);
	
	used=0;
	
	for(size_t iter=0; iter<columns; iter++) {
		
		len=strlen(cells[iter]);
		
		memcpy(out+used,cells[iter],len);
		
		used+=len;
	}
	
	out[used++]='\n';
	
	freeCells(cells,columns);
	
	return out;
}