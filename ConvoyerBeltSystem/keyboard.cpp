#include <stdio.h>
#include "keyboard.h"

int keyCount;

Keyboard :: Keyboard() {
	printf("Keyboard Konstruktor!\n");	
	return;
}

Keyboard :: ~Keyboard() {
	pressedKey = 0;
	return;
}

char Keyboard::getPressedKey( )
{
	printf(".\n"); //	Instead of printing dots the keyboard could be scanned here
	return pressedKey;
}
