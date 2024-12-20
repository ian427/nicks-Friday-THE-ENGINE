#include "BitMaps.h"

#include <string>
#include "Debug.h" //|2|
#include "SDL.h"
#include "SDL_render.h"
using namespace std;

Bitmap::Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparancy)
{
	
	//DeBug::Log()->printDebug(DeBug::Verbosity::red, "Surface not loaded %s, %d", fileName.c_str(), 1);
	
	//store renderer
	m_pbitmapRenderer = renderer;

	//create bitmap surface
	m_pbitmapSurface = SDL_LoadBMP(fileName.c_str());
	if (!m_pbitmapSurface)
	{
	//error check
		DeBug::Log()->printDebug(DeBug::Verbosity::yellow, "Surface not loaded %s, %d", fileName.c_str(), 2);
		printf("%\n", SDL_GetError());
		

	
	}
	else
	{
		//using tranparancy magenta r==255 g ==0 b 255
		if (useTransparancy)
		{
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);// pass width and height to collider
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
	
		}
		//creating texture
		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pbitmapRenderer, m_pbitmapSurface);
		if (!m_pbitmapTexture)
		{
			//error check
			
			DeBug::Log()->printDebug(DeBug::Verbosity::yellow, "TEXTURE not loaded %s, %d", fileName.c_str(), 2);
			printf("%\n", SDL_GetError());

		}
 
	}
	//store position

	m_x = xpos;
	m_y = ypos;
}

void Bitmap::draw()
{
	//render bitmap
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { m_x , m_y,m_pbitmapSurface->w, m_pbitmapSurface->h };
		SDL_RenderCopy(m_pbitmapRenderer, m_pbitmapTexture, NULL, &destRect);

	}

}
Bitmap::~Bitmap()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);
	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);

}