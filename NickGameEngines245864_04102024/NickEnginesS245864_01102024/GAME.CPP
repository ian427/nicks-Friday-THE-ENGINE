#include <SDL.h>
#include <iostream>
#include "Game.h"
//#include "BitMaps.h"//nuke later
#include "Debug.h" //|4|
#include "Entity2.hpp"
 #include "physics.h"
class Base {
public:
    virtual void display() const { // Virtual function for polymorphism
        
    }

    virtual ~Base() = default; // Virtual destructor for proper cleanup
};
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
        DeBug::Log()->printDebug(DeBug::Verbosity::red, "WINDOW initialsation FAILED %s, %d", 3);
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
        printf("\n"), SDL_GetError();
        DeBug::Log()->printDebug(DeBug::Verbosity::yellow, "RENDERER initialsation FAILED %s, %d", 3);
        printf("PRESS ANY KEY\n");
        getchar();
        return;

    }
    vector<Base*>Entitys;///ask nick
    Bird Flappy;
    Pipe TopPipe1;
    Entitys.push_back(&Flappy);
    Entitys.push_back(&TopPipe1);
    // create all objects
    
   m_monster = new Bitmap(m_Renderer , "assets/monster.bmp", 100, 100);
   // m_monsterTrans = new Bitmap(m_Renderer ,"assets/monster.bmp", 200, 100);
    //m_monsterTransKeyed = new Bitmap(m_Renderer ,"assets/monster.bmp", 300, 100); 
  
    Flappy.Map = new Bitmap(m_Renderer, "assets/Flappy.png", 100, 100);
    TopPipe1.Map = new Bitmap(m_Renderer, "assets/Flappy.png", 100, 100);
     //read in the font
    m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf",15); //04-02
    m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf",50); //04-02   

    //for loop for every obj in scene
    for (int i = 0; i< Entitys.size(); i++)
    {
        Bitmap* map = Entitys[i].Map;
        Bitmap* map = Base*->Flappy->Map;
        Bitmap* map = Flappy.Map;
       
         float A = Entitys[i]->map->m_x;
        float B = Entitys[i]->map.m_y;
        Entitys[i]->Radius = (sqrt((A * A) + (B * B))) / 2;//calculates raduius that we sould do a collision check in 
   
    }
    
   

 }
 
 Game::~Game()
 {
     
     if (m_monsterTransKeyed)
         delete m_monsterTransKeyed;
     if (m_monsterTrans)
         delete m_monsterTrans;
     if (m_monster)
         delete m_monster;
     TTF_CloseFont(m_pBigFont);
     TTF_CloseFont(m_pSmallFont);
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
 void CheckCollisions(float radiusobj, Base Entitys)
{
     
      Physics::AABBIntersection(Collider & Collider1, Collider & Collider2);
}


 void Game::SetDisplayColour(int r, int g, int b, int a)
 {
     if (m_Renderer)
        
     { 
         
         int result = SDL_SetRenderDrawColor(
             m_Renderer, //target renderer
             r, g, b, a  //r,g,b,alpha
             );
         //wipe display
         SDL_RenderClear(m_Renderer);
         //present whats drawn
        // SDL_RenderPresent(m_Renderer);
         //pause 5 seconds
        // SDL_Delay(16);//milli seconds //may be needed back
       


     }


 }
 void Game::UpdateText(std::string msg, int x, int y, TTF_Font* font, SDL_Colour colour)
 {
     SDL_Surface* surface = nullptr;
     SDL_Texture* texture = nullptr;

     int texW = 0;
     int texH = 0;
     //SDL_colour color = {0,0,0}
     //char msg [100}
     //sprintf_s(msg,"Checks:%d",m_checkTally

     surface = TTF_RenderText_Solid(font, msg.c_str(), colour);
     if (!surface)
     {
         //error check
         printf("Surface font  not loaded ,file\n" );
         DeBug::Log()->printDebug(DeBug::Verbosity::note, "WINDOW initialsation FAILED %s, %d", 3);
         printf("%\n", SDL_GetError());

     }
     else
     {
         texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
             if (!texture)
             {
                 //error check
                 
                 DeBug::Log()->printDebug(DeBug::Verbosity::yellow, "TEXTURE font not loaded %s, %d", msg.c_str(), 3);
                 printf("%\n", SDL_GetError());

             }
             else
             {
                 SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
                 SDL_Rect textRect = { x,y,texW,texH };

                 SDL_RenderCopy(m_Renderer, texture, NULL, &textRect);

             }

     }
     if (texture)
     {
         
         SDL_DestroyTexture(texture);
     }
     if (surface)
     {
  
         SDL_FreeSurface(surface);
         
      }


 }
 void Game::Update(void)
 {
     //CheckEvents();
     SDL_RenderClear(m_Renderer);
     //show bitmaps
     Flappy->Map->draw();
     m_monster ->draw();
     m_monsterTrans->draw();
     m_monsterTransKeyed->draw();


     Flappy->flappy_Transform.GetPosition();
       Physics phi;
     //collision check/////////////////////////////////////////////////////////////
     
       CheckCollision(Flappy->Radius,  Entitys);
     

     
    phi.Move(Flappy->flappy_Transform, (1, 0, 0));

     //draw text
    UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
    UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0,0,255 });

     char array[] = "Big White";
     UpdateText(array, 50, 140, m_pBigFont, { 0,255,0 });

     std::string myString = "Big Green";
     UpdateText(myString, 50, 70, m_pBigFont, { 0,255,0 });

     int testNumber = 1234 ;
     std::string testString = "Test Number:  ";
     testString += std::to_string(testNumber);
     UpdateText(testString, 50, 210, m_pBigFont, { 255,255,255 });

    
     SDL_RenderPresent(m_Renderer);

     SDL_Delay(16);//milliseconds

 }
