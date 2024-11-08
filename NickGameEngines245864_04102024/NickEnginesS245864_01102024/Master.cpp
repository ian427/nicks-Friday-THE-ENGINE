
#include <SDL.h>
#include <iostream>
#include <cmath>
#include "Game.h"
#include "Input.h"
#include "Debug.h"//|1|

#include "EventHandler.h"
#include "Entity2.hpp"

#undef main 

using namespace std;


int main(int argc, char* argv[])
{	
	//DeBug::Log()->printDebug(DeBug::Verbosity::note, "entered Main , %d",  1);

	Bird TestBird;
	EventSystem eventSyetem;
	eventSyetem.AddListener(&TestBird);

	eventSyetem.AddEvent(TEST_EVENT, new Event("hello world"));


	eventSyetem.HandelEvents();
	
	Game* game = new Game(); // creates new game
	Input* input = new Input();
	
	if (game && input)
	{
		Uint8 r = 50, g = 127 ,b = 50, a = 255;// background colour
		
		while (!input->KeyIsPressed(KEY_ESCAPE))
			
		{
			input->Update();
			//DeBug::Log()->printDebug(DeBug::Verbosity::red, "looping %s, %d", 0);
			if (input->KeyIsPressed(KEY_R))
			{
				r++;
					if (r++ > 255) r = 0;
					//DeBug::Log()->printDebug(DeBug::Verbosity::note, "Red pressed %s, %d",  1);
			}
			if (input->KeyIsPressed(KEY_G))
			{
				g++;
				if (g++ > 255)g = 0;

			}
			if (input->KeyIsPressed(KEY_B))
			{
				b++;
				if (b++ > 255) b = 0;

			}

			game->SetDisplayColour(r, g, b, a);//show display
			game->Update();
		}
		//destructors

	}
	delete input;
	input = nullptr;

    delete game;
    game = nullptr;
	return 0 ;
	
}
