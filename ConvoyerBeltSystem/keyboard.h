
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

extern "C" {
#include "gpio.h"

}

class Keyboard
{
	
public:
	Keyboard();
	~Keyboard();
	char getPressedKey();
	
private:
	kbdDescriptor* kbdd;
	char pressedKey;
};

#endif // KEYBOARD_H_
