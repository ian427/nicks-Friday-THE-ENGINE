#ifndef GAME_H
#define GAME_H



class SDL_Window;
class SDL_Renderer;
class Game
	class Bitmap
{
private:
	SDL_Window *m_Window;
	SDL_Renderer* m_Renderer;
		bool m_running;
		//bitmaps
		Bitmap* m_monster;
		Bitmap* m_monsterTrans;
		Bitmap* m_monsterTransKeyed;
public:
	Game();
	~Game();
	void SetDisplayColour(void);

};
#endif