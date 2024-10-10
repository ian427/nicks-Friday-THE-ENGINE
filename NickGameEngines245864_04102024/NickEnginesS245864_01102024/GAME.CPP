#include <SDL.h>
#include <iostream>
#include "Game.h"
#include "BitMaps.h"


 Game::Game()
{  
     
    m_Window = nullptr;
    m_Renderer = nullptr;

    //start up
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();//04-02

    //CreateWindow
    m_Window = SDL_CreateWindow(
        "Main Window",
        250, // XPosition
        50, // YPosition
        640, //Width in pixels
        480,  //height pixels
        0 //behaviour flags
    );
    if (!m_Window)
    {
        printf("WINDOW initialsation FAILED\n"), SDL_GetError();
        printf("PRESS ANY KEY\n");
        getchar();
        return;

    }

        m_Renderer = SDL_CreateRenderer(
        m_Window, //links to window
        -1,      // indexes render driver
        0         //behaviour flags
    );
    if (!m_Renderer)
    {
        printf("RENDERER initialsation FAILED\n"), SDL_GetError();
        printf("PRESS ANY KEY\n");
        getchar();
        return;

    }
    m_monster = new Bitmap(m_renderer < "assets/monster.bmp", 100, 100);
    m_monsterTrans = new Bitmap(m_renderer < "assets/monster.bmp", 200, 100);
    m_monsterTransKeyed = new Bitmap(m_renderer < "assets/monster.bmp", 300, 100); #

     //red in the font
    m_pSmallFont = TTF_OpenFont("assets/DejavuSans.ttf",15); //04-02
    m_pBigFont = TTF_OpenFont("assets/DejavuSans.ttf",50); //04-02    

    // destroy in reverse creation order
    if (m_Renderer)
    {
        SDL_DestroyRenderer(m_Renderer);
    }
    if (m_Window)
    {
        SDL_DestroyWindow(m_Window);

    }
   

 }

 Game::~Game()
 {
     if (m_monsterTransKeyed)
         deleten m_monsterTransKeyed;
     if (m_monsterTrans)
         deleten m_monsterTrans;
     if (m_monster)
         deleten m_monster;
     TTF_CloseFont(m_pBigFont);
     TTF_CloseFont(m_pSmallFont);

 }



 void Game::SetDisplayColour(void)
 {
     if (m_Renderer)
        
     { 
         
         int result = SDL_SetRenderDrawColor(
             m_Renderer, //target renderer
             255, 0, 0, 255  //r,g,b,alpha
             );
         //wipe display
         SDL_RenderClear(m_Renderer);
         //present whats drawn
         SDL_RenderPresent(m_Renderer);
         //pause 5 seconds
         SDL_Delay(16);//milli seconds
       


     }


 }
 void Game::UpdateText(string msg, int x, int y, TTF_Font font, SDL_Colour colour);
 {
     SDL_Surface* surface = nullptr;
     SDL_Texture* texture = nullptr;

     int texW = 0;
     int texH = 0;
     //SDL_colour color = {0,0,0}
     //char msg [100}
     //sprintf_s(msg,"Checks:%d",m_checkTally

     surface = TFF_RenderText_Solid(font, msg.c_str(), colour);
     if (!surface)
     {
         //error check
         printf("Surface font  not loaded ,file\n",);
         printf("%\n", SDL_GetError());

     }
     else
     {
         texture = SDL_CreateTextureFromSurface(m_renderer, surface);
         i
       if (!texture)
       {
             //error check
             printf("TEXTURE font not loaded ,file\n", fileName.c_str());
             printf("%\n", SDL_GetError());

       }
       else
       {
           SDL_QueryTexture(texture, Null, Null, &texW, &texH);
           SDL_Rect textRect = { x,y,texW,texH };

           SDL_RenderCopy(m_renderer, texture, NULL, &textRect);

       }

     }
     if(texture)
         SDL_DestrotTexture(texture)
         if (surface)
             SDL_DestrotSurface(surface)


 }
 void Game::Update(void)
 {
     CheckEvents();
     SDL_RenderClear(m_Renderer);
     //show bitmaps
     m_monster ->draw();
     m_monsterTrans->draw();
     m_monsterTransKeyed->draw();


     //draw text
     UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
     UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0,0,255 });

     char char array[] = "Big White";
     UpdateText(char_array, 50, 140, m_pBigFont, { 0,255,0 });

     string myString = "Big Green";
     UpdateText(myString, 50, 70, m_pBigFont, { 0,255,0 });

     int testNumber = 1234 ;
     string testString = "Test Number:  ";
     testString += to_string(testNumber);
     UpdateText(testString, 50, 210, m_pBigFont, { 255,255,255 });

     SDL_RendererPresent(m_renderer);

     SDL_Delay(16);//milliseconds

 }
