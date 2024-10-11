#pragma 
#include <string>
#include "SDL_ttf.h"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
//useing namespace std
class Bitmap
{
private:
	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pbitmapRenderer;


public:
	~Bitmap();
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparancy = false);
	
	void draw();

	int m_x, m_y;
};


//log4cplus