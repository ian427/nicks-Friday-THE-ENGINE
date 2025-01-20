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
	int GetX();
	int GetY();
	void SetX(int temppos);
	void SetY(int temppos);
	int m_x, m_y , ID;
	bool IsSelected = false;
	std::string FileName;
	std::string ObjectName;

	SDL_Texture* GetTextureRef()
	{
		return m_pbitmapTexture;
	}
};

///////////////////////////NOTES
SDL_rect imagerect.x;
SDL_rect imagerect.y;
SDL_rect imagerect.h;
SDL_rect imagerect.w;
 getx()
{
	return imagerect.x;
}
gety()
{
	return imagerect.y;
}
geth()
{
	return imagerect.h;
}
getw()
{
	return imagerect.w;
}


//log4cplus

for bitmap hierarchy
sdlpoint cursor
cursor.x
cursor.y
int x,y
sdl mouse state
{
	x && y
}
if sdl point in rect object(cousoe, image rect&& mouse clicked)
{

}
draw
if selected = !null
//window area
begin
int[postemp][2]
postemp[1] == getx of selected obj
postemp[1] == gety of selected obj

char buff[255]{};
strncpy(buff,obj->objectname.c_str,sizeof(buff)-1)
imput text ("name"obj->ojectname.data(), 10)
obj -> objectname

imgui text object name.c_str

imgui dragint2("name",postemp)

obi->setx(postemp[1])
obi-> sety(postemp[1])
end

re write
{
	string s 

}