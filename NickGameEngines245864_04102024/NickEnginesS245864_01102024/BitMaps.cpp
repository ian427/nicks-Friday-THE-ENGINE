#include <string>
#include "BitMaps"


#include "SDL.h"
#include "SDL_renderer.h"
using namespace std;

BitMaps::Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparancy)
//store renderer
mpRenderer = renderer;

//create bitmap surface
m_pbitmapSurface + SDL_LoadBMP(fileName.c_str());
if (!m_pbitmapSurface)
{
	//error check
	printf("Surface not loaded ,file\n", fileName.c_str());
	printf("%\n", SDL_GetError());

}
else
{
	//using tranparancy magenta r==255 g ==0 b 255
	if (useTransparancy)
	{
		uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
		SDL_SetColourKey(mpbitmapSurface, SDL_TRUE, colourKey);

	}
	//creating texture
	m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
	if (!m_bitmapTexture)
	{
		//error check
		printf("TEXTURE not loaded ,file\n", fileName.c_str());
		printf("%\n", SDL_GetError());

	}

}
//store position
m_x = xpos;
m_y = ypos;

void BitMaps::draw()
{
	//render bitmap
	if (m_pbitmapTexture)
	{
		SDL_Rect destResct = { m_x , m_y,m_pbitmapSurface->w, m_pnitmapSurface->h };
		SDL_RenderCopy(m_pRenderer, m_bitmapTexture, NULL, &destrect);

	}

}
Bitmaps::~Bitmap()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);
	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);

}