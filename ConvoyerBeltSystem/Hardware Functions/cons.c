/*
File: cons.c
Author: HP
As of: 2919-10-17
*/

#include "cons.h"
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/*
Function: openConsole
Parameter: a struct of type consDescriptor
Returns: 0 on succes, -1 on error, including error output
Does: Opens a file with the specified name in the home directory
of the user debian (/home/debian)
*/
int openConsole(consDescriptor* cons) {
	char myFilename[MAX_FILENAME];
	sprintf(myFilename, "../../../../../%s", cons->fileName);
	cons->myFd = fopen(myFilename, "w");
	if (cons->myFd == NULL) {
		perror("fopen");
		return -1;
	}
	return 0;
}

/*
Function: clearConsole
Parameter: a struct of type consDescriptor
Returns: 0 on succes, -1 on error, including error output
Does: Clears the console for displaying new info
*/
extern int clearConsole(consDescriptor* cons) {
	int retVal;
	retVal = fputs("\f", cons->myFd);
	if (retVal < 0) {
		perror("fputs");
		return -1;
	}
	retVal = fflush(cons->myFd);
	if (retVal < 0) {
		perror("fputs");
		return -1;
	}
	return 0;
}

/*
Function: writeLineToConsole
Parameter: a struct of type consDescriptor and a pointer to the string to be written
Returns: 0 on succes, -1 on error, including error output
Does: Writes the given string and moves to the next line
The maximum lenght is given by MAX_CONS_LEN
*/
extern int writeLineToConsole(consDescriptor* cons, char * myString) {
	int retVal;
	char myBuf[MAX_CONS_LEN];
	sprintf(myBuf, "%s\r\n", myString);
	retVal = fputs(myBuf, cons->myFd);
	if (retVal < 0) {
		perror("fputs");
		return -1;
	}
	retVal = fflush(cons->myFd);
	if (retVal < 0) {
		perror("fputs");
		return -1;
	}
	return 0;
}

/*
Function: closeConsole
Parameter: a struct of type consDescriptor
Returns: 0 on succes, -1 on error, including error output
Does: Closes the file "conssoleFile.txt"
*/
extern int closeConsole(consDescriptor* cons) {
	int retVal;
	retVal = fclose(cons->myFd);
	if (retVal < 0) {
		perror("fclose");
		return -1;
	}
	return 0;
}
