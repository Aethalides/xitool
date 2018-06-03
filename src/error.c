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
#include "error.h"

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *invocation=NULL;

#ifdef _GNU_SOURCE
static void __attribute__ ((format (printf, 2, 0))) printMessageVa(const char *type,const char *error_format,va_list *args)  {
#else
static void printMessageVa(const char *type,const char *error_format,va_list *args)  {
#endif
		
	char *theFormat=NULL;
	
	#ifndef _GNU_SOURCE
		size_t length=strlen(error_format);
		
		theFormat=malloc(sizeof(char)*length+1);
		
		if(theFormat!=NULL) {
			
			memset(theFormat,0,length);
		
			strcpy(theFormat,error_format);
		}
		
	#else
		if(-1==asprintf(&theFormat,"%s",error_format))
			theFormat=NULL;
	#endif
	
	if(NULL!=theFormat)
		theFormat[strcspn(theFormat, "\n")] = 0;
	
	if(NULL!=invocation) 
		fprintf(stderr,"%s: ",invocation);
	
	if(strlen(type))
		fprintf(stderr,"%s: ",type);
	
	vfprintf(stderr,NULL==theFormat?error_format:theFormat,*args);

	fprintf(stderr,"\n");
	
	free(theFormat);
}

void setInvocation(char *arg0) {
	
	invocation=arg0;
}

char* getInvocation(void) {

	return invocation;
}

#ifdef _GNU_SOURCE
void __attribute__ ((format (printf, 1, 0))) printMessage(const char *message_format,...) {
#else
void printMessage(const char *message_format,...) {
#endif
	
	va_list args;
	
	va_start(args,message_format);
	
	printMessageVa("",message_format,&args);
	
	va_end(args);
}

#ifdef _GNU_SOURCE
void __attribute__ ((format (printf, 1, 0))) printError(const char *error_format,...) {
#else
void printError(const char *error_format,...) {
#endif
	
	va_list args;
	
	va_start(args,error_format);
	
	printMessageVa("ERROR",error_format,&args);
	
	va_end(args);
}

#ifdef _GNU_SOURCE
void __attribute__ ((format (printf, 1, 0))) printNotice(const char *notice_format,...) {
#else
void printNotice(const char *notice_format,...) {
#endif
	
	va_list args;
	
	va_start(args,notice_format);
	
	printMessageVa("NOTICE",notice_format,&args);
	
	va_end(args);	
}

#ifdef _GNU_SOURCE
void __attribute__ ((format (printf, 1, 0))) printWarning(const char *warning_format,...) {
#else
void printWarning(const char *warning_format,...) {
#endif
	
	va_list args;
	
	va_start(args,warning_format);
	
	printMessageVa("WARNING",warning_format,&args);
	
	va_end(args);	
}

#ifdef _GNU_SOURCE
_Noreturn void __attribute__ ((format (printf, 1, 0))) die_with_error(const char *error_format,...) {
#else
void die_with_error(const char *error_format,...) {
#endif
	va_list args;
	
	va_start(args,error_format);
	
	printMessageVa("ERROR",error_format,&args);
	
	va_end(args);
	
	exit(EXIT_FAILURE);
}
#ifdef _GNU_SOURCE
_Noreturn void __attribute__ ((format (printf, 1, 0))) die_with_bug(const char *bug_format,...) {
#else
void die_with_bug(const char *bug_format,...) {
#endif
	va_list args;
	
	va_start(args,bug_format);
	
	printMessageVa("BUG",bug_format,&args);
	
	va_end(args);
	
	exit(EXIT_FAILURE);
}