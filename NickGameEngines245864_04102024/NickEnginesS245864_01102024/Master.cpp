
#include <SDL.h>
#include <iostream>
#include <cmath>
#include "Game.h"
#include "Input.h"
#include "Debug.h"
#undef main 

using namespace std;


int main(int argc, char* argv[])
{	
	

	
	Game* game = new Game(); // creates new game
	Input* input = new Input();
	
	if (game && input)
	{
		Uint8 r = 50, g = 127 ,b = 50, a = 255;// background colour
		
		while (!input->KeyIsPressed(KEY_ESCAPE))
		{
			if (input->KeyIsPressed(KEY_R))
			{
				r++;
					if (r++ > 255) r = 0;
				
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
		

	}
	delete input;
	input = nullptr;

    delete game;
    game = nullptr;
	return 0 ;
	
}