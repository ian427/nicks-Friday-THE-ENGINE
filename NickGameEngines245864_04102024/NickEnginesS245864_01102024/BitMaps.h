#pragma 
#include <string>
#include "SDL_ttf.h"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
//useing namespace std
class ITreeNode
{
	
	std::string ObjectName;

};

class Bitmap
{
private:
	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pbitmapRenderer;
	

public:
	//std::vector<ITreeNode*>Children;
	void addToChildren( Bitmap* newChild);
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
