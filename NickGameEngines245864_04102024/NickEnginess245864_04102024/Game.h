#ifndef  GAME_H
#define GAME_H
#include <SDL.h>
#include<stdio.h>

class Game
{
private:
  SDL_Window* m_Window;
  SDL_Renderer* m_Window;
  
public:
  Game();
  ~Game();

  void SetDisplayColour(void);

};
#endif // ! GAME_H

