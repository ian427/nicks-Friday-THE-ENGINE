#ifndef GAME_H
#define GAME_H
#include "SDL_ttf.h"
#include <vector>
#include "physics.h"
#include "EventHandler.h"

class Bitmap;
struct SDL_Window;
struct SDL_Renderer;

class Bird;
class Pipe;
class UI;
class Ground;
class BaseEntity;

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

		Bitmap* AssetMousDrag;
		
		Bird* Flappy;
		Pipe* TopPipe1;
		Pipe* BottomPipe1;
		Pipe* TopPipe2;
		Pipe* BottomPipe2;
		Pipe* TopPipe3;
		Pipe* BottomPipe3;
		Pipe* TopPipe4;
		Pipe* BottomPipe4;
		std::vector<Pipe*>Pipes;
		std::vector<BaseEntity*>Entitys;
		
		std::vector<Bitmap*>content;
		vector<Bitmap*> sceneRoot;//list of objects in scene
		UI* Celling;
		Ground* Floor;
		EventSystem& eventSystem;
		Physics* phi;/////////////////////////
		
		float score = 0;
		std::string scoretxt = "Test Number:  ";

		TTF_Font* m_pSmallFont;
		TTF_Font* m_pBigFont;
public:
	///////////////////error
	Game();
	~Game()
	{
		delete phi;
		Physics* phi= nullptr;
		delete Floor;
		Ground* Floor = nullptr;
		delete Celling;
		UI* Celling = nullptr;
		delete BottomPipe4;
		Pipe* BottomPipe4 = nullptr;
		delete TopPipe4;
		Pipe* TopPipe4 = nullptr;
		delete BottomPipe3;
		Pipe* BottomPipe3 = nullptr;	
		delete TopPipe3;
		Pipe* TopPipe3 = nullptr;
		delete BottomPipe2;
		Pipe* BottomPipe2 = nullptr;
		delete TopPipe2;
		Pipe* TopPipe2 = nullptr;
		delete BottomPipe1;
		Pipe* BottomPipe1 = nullptr;	
		delete TopPipe1;
		Pipe* TopPipe1 = nullptr;
		delete Flappy;
		Bird* Flappy = nullptr;
		delete AssetMousDrag;
		Bitmap* AssetMousDrag = nullptr;
		delete m_monsterTransKeyed;
		Bitmap* m_monsterTransKeyed = nullptr;
		delete m_monsterTrans;
		Bitmap* m_monsterTrans = nullptr;
		delete m_monster;
		Bitmap* m_monster = nullptr;
		delete m_Window;
		SDL_Window* m_Window = nullptr;
		delete m_Renderer;
		SDL_Renderer* m_Renderer = nullptr;

	};
	void SetDisplayColour(int r, int g, int b, int a);

	void UpdateText(std::string msg, int x, int y, TTF_Font* font, SDL_Colour colour);

	void Update(void);

};
#endif

