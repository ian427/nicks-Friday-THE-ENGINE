#pragma once
#include "SDL.h"

enum KEYS_PRESSED_LIST
{
	KEY_ESCAPE, KEY_R, KEY_G, KEY_B,KEY_SPACE, SIZE_OF_KEYS_PRESSED_ENUM //must be at the end
};

class Input
{
public:
	void Update(void);
	bool KeyIsPressed(KEYS_PRESSED_LIST key);
	Input();
	~Input();
private:
	SDL_Event m_event;
	bool m_keysPressed[SIZE_OF_KEYS_PRESSED_ENUM];


};
