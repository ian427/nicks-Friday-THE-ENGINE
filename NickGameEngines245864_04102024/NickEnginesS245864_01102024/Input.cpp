#include "input.h"
#include "Debug.h "//|3|
void Input::Update(void)
{
	while (SDL_PollEvent(&m_event) != NULL)
	{

		//check keydown
		if (m_event.type == SDL_KEYDOWN)
		{
			//cache code for keypress
			SDL_Keycode keyPressed = m_event.key.keysym.sym;
			
			//update all keys extend
			switch (keyPressed)
			{

			case SDLK_ESCAPE:
				m_keysPressed[KEY_ESCAPE] = true;
				DeBug::Log()->printDebug(DeBug::Verbosity::note, "Shuting Down %s, %d", 3);
				break;
			case SDLK_r:
				m_keysPressed[KEY_R] = true;
				DeBug::Log()->printDebug(DeBug::Verbosity::note, "R key pressed %s, %d", 3);
				break;
			case SDLK_g:
				m_keysPressed[KEY_G] = true;
				break;
			case SDLK_b:
				m_keysPressed[KEY_B] = true;
				break;
			}
		}
		// check for key up
		else if (m_event.type == SDL_KEYUP)
		{
			
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			switch (keyPressed)
			{

			case SDLK_ESCAPE:
				m_keysPressed[KEY_ESCAPE] = false;
				break;
			case SDLK_r:
				m_keysPressed[KEY_R] = false;
				break;
			case SDLK_g:
				m_keysPressed[KEY_G] = false;
				break;
			case SDLK_b:
				m_keysPressed[KEY_B] = false;
				
				break;
			}

		}
    }
}
bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keysPressed[key];
}
Input::Input()//CONSTRUCTOR
{
	for (int i = 0; i < SIZE_OF_KEYS_PRESSED_ENUM;i++)
	{
		m_keysPressed[i] = NULL;
	}
}
Input::~Input()//DESTRUCTOR
{

}

