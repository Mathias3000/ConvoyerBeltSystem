#include <stdio.h>
#include "keyboard.h"

int keyCount;

Keyboard :: Keyboard() {
	printf("Keyboard Konstruktor!\n");	
	kbdd = new kbdDescriptor();
	initKeyboard(kbdd);
	return;
}

Keyboard :: ~Keyboard() {
	pressedKey = 0;
	return;
}

char Keyboard::getPressedKey( )
{
	return getKey(kbdd);

}
