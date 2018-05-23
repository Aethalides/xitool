#ifndef XIERROR_H

void setInvocation(char *arg0);
char* getInvocation();

void printMessage(const char *message_format,...);
void printError(const char *error_format,...);
void printWarning(const char *warning_format,...);
void printNotice(const char *notice_format,...);

void die_with_error(const char *error_format,...);

#define XIERROR_H
#endif