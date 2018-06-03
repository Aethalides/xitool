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
#ifndef XIERROR_H
#define XIERROR_H

void setInvocation(char *arg0);
char* getInvocation(void);

void printMessage(const char *message_format,...);
void printError(const char *error_format,...);
void printWarning(const char *warning_format,...);
void printNotice(const char *notice_format,...);

void die_with_error(const char *error_format,...);
void die_with_bug(const char *bug_format,...);

#endif