#pragma 
#include <string>

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

	int m_x, m_y;

public:
	Bitmap::Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, intypos, bool useTransparancy = false) :
		~Bitmap();
	void draw();

};
