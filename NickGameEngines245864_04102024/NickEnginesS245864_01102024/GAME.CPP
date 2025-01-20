#include <SDL.h>
#include <iostream>
#include "Game.h"
#include "Entity2.hpp" 
//#include "BitMaps.h"//nuke later
#include "Debug.h" //|4|

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"
#include <filesystem>

 Game::Game()
{  
     
    m_Window = nullptr;
   // m_Renderer = nullptr;

    //start up
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();//04-02

    //CreateWindow//make configurable
    m_Window = SDL_CreateWindow(
        "Main Window",
        250, // XPosition
        50, // YPosition
        1280, //Width in pixels
        720,  //height pixels
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
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    SDL_DisplayMode DisplayMode;
    SDL_GetCurrentDisplayMode(0, &DisplayMode);
    ImGuiSDL::Initialize(m_Renderer, DisplayMode.w, DisplayMode.h);
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(m_Window, 0);///behaviour flag 0 ask nick
    /////////////////////////////////////////////////////////////////////// migrate to cpp
    //populates imGui with assets
    std::string path = "./assets";
    
    for (const auto& entry : std::filesystem::directory_iterator(path)) //directory_iterator(path) //recursive_
    {
        if (entry.path().extension() == ".bmp" || entry.path().extension() == ".jpg" || entry.path().extension() == ".png")
        {
            Bitmap* Asset = new Bitmap(m_Renderer, entry.path().string(), 0, 0, true);
            content.push_back(Asset);

        }
        else if (entry.is_directory())
        {
            std::cout << "dir " << entry << std::endl;
        }
        //debug
        std::cout << entry.path() << std::endl;
    }







    ImGui::Begin("Editor");
    ImGui::BeginChild("Content Window", ImVec2(), true);
    //ImGui::BeginTable("Content browser", 3);
    ;
    for (int i = 0; i < content.size(); i++)
    {
        ImGui::PushID(i);

        ImGui::ImageButton((ImTextureID)content[i]->GetTextureRef(), { 100,100 });


        //for dragging
        /*if (ImGui::BeginDragDropSource())
        {
            AssetMousDrag = content[i];
            ImGui::Image((ImTextureID)content[i]->GetTextureRef(), { 100,100 });
            ImGui::EndDragDropSource();
        }*/
        ImGui::PopID();
        ImGui::SameLine();
    }

    //ImGui::EndTabItem();

    ImGui::EndChild();
    ImGui::End();

    eventSystem = new EventSystem();
    phi = new Physics();
    //eventSystem->AddEvent(APPLY_GRAVITY, new Event("Gravity"));


    Celling = new UI();
    
   

    // create all objects
    TopPipe1 = new Pipe(true);
    Entitys.push_back(TopPipe1);    // Push the pointer into the vector
    BottomPipe1 = new Pipe(false);
    Entitys.push_back(BottomPipe1);
   
   Flappy = new Bird(m_Renderer);
   eventSystem->AddListener(Flappy);
   Entitys.push_back(Flappy);
     //read in the font
    m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf",15); //04-02
    m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf",50); //04-02   

    Floor = new Ground();
    Entitys.push_back(Floor);
    Celling = new UI();
    Entitys.push_back(Celling);
 
    
    //calculates raduius that we sould do a collision check in 

   

    for (int i = 0; i < Entitys.size(); i++)
    {
        float A = Entitys[i]->Map->m_x;
        float B = Entitys[i]->Map->m_y;
        Entitys[i]->Radius = (sqrt((A * A) + (B * B))) / 2;
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

     ImGui::NewFrame();
     ImGui_ImplSDL2_NewFrame(m_Window);
     bool show = true;
     //ShowExampleAppleDockSpace(&show);

     
     
     if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && AssetMousDrag != nullptr)
     {
        
         int x, y;
         SDL_GetMouseState(&x, &y);
         Bitmap* s = new Bitmap(m_Renderer, AssetMousDrag->FileName, x, y, true);
         //s->Transfrom.ParentSet(GameWindow::Instance().GetHirarcy());
         sceneRoot.push_back(s);

         AssetMousDrag = nullptr;
     }



     ImGui::ShowDemoWindow(nullptr);
     ImGui::Begin("Editor");
     ImGui::BeginChild("Content Window", ImVec2(), true);
     //ImGui::BeginTable("Content browser", 3);
     //for contents of assets file creat a dragable
     ;
     for (int i = 0; i < content.size(); i++)
     {
         ImGui::PushID(i);

         ImGui::ImageButton((ImTextureID)content[i]->GetTextureRef(), { 100,100 });//bit in window


         /////////////////////////////////For Draging
         if (ImGui::BeginDragDropSource())
         {
             AssetMousDrag = content[i];
             ImGui::Image((ImTextureID)content[i]->GetTextureRef(), { 100,100 }); // thumbnail
             ImGui::EndDragDropSource();
         }
         /////////////////////////////////For Draging
         ImGui::PopID();
         ImGui::SameLine();
     }

     //ImGui::EndTabItem();

     ImGui::EndChild();
     ImGui::End();
     
     for (Bitmap* path)
     {
         if (!path->IsSelected)
             continue;

         Bitmap* SelectedObject = path;
         ImGui::Begin(string("Selected Object" + to_string(SelectedObject->ID)).c_str());

         int posTemp[2];
         posTemp[0] = SelectedObject->GetX();
         posTemp[1] = SelectedObject->GetY();


         char buff[255]{};
         strncpy(buff, SelectedObject->ObjectName.c_str(), sizeof(buff) - 1);
         ImGui::InputText("Name:", buff, sizeof(buff));
         SelectedObject->ObjectName = buff;

         ImGui::Text(SelectedObject->ObjectName.c_str());
         ImGui::DragInt2("X", posTemp);


         SelectedObject->SetX(posTemp[0]);
         SelectedObject->SetY(posTemp[1]);

         if (ImGui::Button("Close"))
         {
             SelectedObject->IsSelected = false;
         }

         ImGui::End();
     }
     ImGui::Render();
     ImGuiSDL::Render(ImGui::GetDrawData());

     //show bitmaps
     
     //_monster ->draw();
     //_monsterTrans->draw();
     //_monsterTransKeyed->draw();
    eventSystem->HandelEvents();

     Flappy->transform.GetPosition();

     
    
    
     /*
     if ((D == Flappy->Radius + Floor->Radius) || (D == Flappy->Radius - Celling->Radius))//circle collision check
     {
         if (phi.AABBIntersection(Flappy->BoxCollider, Celling->BoxCollider))
         {


         }

     }
     for (int i = 0; i < Pipes.size(); i++)
     {
         if ((D == Flappy->Radius + Floor->Radius) || (D == Flappy->Radius - Celling->Radius))//circle collision check
         {
             if (phi.AABBIntersection(Flappy->BoxCollider, Pipes[i]->BoxCollider))
             {


             }

         }

     }*/

     


    //phi->Move(Flappy->transform, vec3(1, -1, 0));
     for (int i = 0; i < Entitys.size(); i++)
     {
         Entitys[i]->Draw();
     }
     ////draw text
     //UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
     //UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0,0,255 });

     //char array[] = "Big White";
     //UpdateText(array, 50, 140, m_pBigFont, { 0,255,0 });

     //std::string myString = "Big Green";
     //UpdateText(myString, 50, 70, m_pBigFont, { 0,255,0 });

     //int testNumber = 1234;
     //std::string testString = "Test Number:  ";
     //testString += std::to_string(testNumber);
     //UpdateText(testString, 50, 210, m_pBigFont, { 255,255,255 });
        //collision check/////////////////////////////////////////////////////////////
     for (int i = 0; i < Entitys.size(); i++){}
     
     
    
      Flappy->CollisionCheck(TopPipe1);
     //m_monster->draw();
      for (int i = 0; i < Entitys.size(); i++)
      { Entitys[i]->ApplyContinuousMoment();}
       
      
    

     SDL_RenderPresent(m_Renderer);

     SDL_Delay(16);//milliseconds
 }

