#ifndef GAME_H
#define GAME_H
#include "SDL_ttf.h"
#include <vector>

class Bitmap;
class SDL_Window;

class Bird;
class Pipe;
class UI;
class Ground;

class Game
{
private:
	SDL_Renderer* m_Renderer;
	SDL_Window *m_Window;
	//SDL_Renderer* m_Renderer;
		bool m_running;
		//bitmaps
		Bitmap* m_monster;
		Bitmap* m_monsterTrans;
		Bitmap* m_monsterTransKeyed;
		
		Bird* Flappy;
		Pipe* TopPipe1;
		Pipe* BottomPipe1;
		std::vector<Pipe*>Pipes;
		UI* Celling;
		Ground* Floor;
		float Time;

		TTF_Font* m_pSmallFont;
		TTF_Font* m_pBigFont;
public:
	Game();
	~Game();
	void SetDisplayColour(int r, int g, int b, int a);

	void UpdateText(std::string msg, int x, int y, TTF_Font* font, SDL_Colour colour);

	void Update(void);

};
#endif

