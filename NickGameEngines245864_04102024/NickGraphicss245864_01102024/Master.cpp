
#include <SDL.h>
#include <iostream>
#include <cmath>
#include<Game.h>
#undef main 

using namespace std;


int main(int argc, char* argv[])
{
	Game* game = new Game(); // creates new game

	if (game)
	{
		game->SetDisplayColour();//show display
		delete game;
		game = nullptr
	}

	return 0 ;
	
}