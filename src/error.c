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
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *invocation=NULL;

static void printMessageVa(const char *type,const char *error_format,va_list *args) {
	
	size_t length=strlen(error_format);
	
	char *theFormat=malloc(sizeof(char)*length+1);
	
	if(theFormat!=NULL) {
		
		memset(theFormat,0,length);
	
		strcpy(theFormat,error_format);
	
		theFormat[strcspn(theFormat, "\n")] = 0;
	}
	
	if(NULL!=invocation) 
		fprintf(stderr,"%s: ",invocation);
	
	if(strlen(type))
		fprintf(stderr,"%s: ",type);
	
	vfprintf(stderr,NULL==theFormat?error_format:theFormat,*args);

	fprintf(stderr,"\n");
	
	if(NULL!=theFormat) free(theFormat);
}

void setInvocation(char *arg0) {
	
	invocation=arg0;
}

char* getInvocation() {

	return invocation;
}

void printMessage(const char *message_format,...) {
	
	va_list args;
	
	va_start(args,message_format);
	
	printMessageVa("",message_format,&args);
	
	va_end(args);
}

void printError(const char *error_format,...) {
	
	va_list args;
	
	va_start(args,error_format);
	
	printMessageVa("ERROR",error_format,&args);
	
	va_end(args);
}

void printNotice(const char *notice_format,...) {
	
	va_list args;
	
	va_start(args,notice_format);
	
	printMessageVa("NOTICE",notice_format,&args);
	
	va_end(args);	
}

void printWarning(const char *warning_format,...) {
	
	va_list args;
	
	va_start(args,warning_format);
	
	printMessageVa("WARNING",warning_format,&args);
	
	va_end(args);	
}

void die_with_error(const char *error_format,...) {

	va_list args;
	
	va_start(args,error_format);
	
	printMessageVa("ERROR",error_format,&args);
	
	va_end(args);
	
	exit(EXIT_FAILURE);
}
