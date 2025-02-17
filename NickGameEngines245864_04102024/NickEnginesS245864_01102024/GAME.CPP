#include <SDL.h>
#include <iostream>
#include "Game.h"
#include "Entity2.hpp" 
#include "Profiler.h" 

#include "Debug.h" //|4|
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"
#include <filesystem>

 Game::Game(EventSystem* eventSytem)
 {  
     srand(time(NULL));
    this->eventSystem = eventSytem;
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
        screenWidth, //Width in pixels
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
    FrameTimeStack frameTime;


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

    
    phi = new Physics();
    //eventSystem->AddEvent(APPLY_GRAVITY, new Event("Gravity"));

    int tempx = 10;
    
   
    //////// create all objects
     
   for (int i =0; i < 4; i++)
   { 
          int y;
     
          y = rand() % (600 - 300 + 1) + 300;//between 300,600

          BottomPipe1 = new Pipe( false, m_Renderer, tempx, y);
     Entitys.push_back(BottomPipe1);
     Pipes.push_back(BottomPipe1);    // pushing the pointer into the vector
    
     TopPipe1 = new Pipe(true, m_Renderer, tempx, (y - 800));
      Entitys.push_back(TopPipe1);
      Pipes.push_back(TopPipe1);

     tempx += screenWidth/4+1;

    }
   

   Flappy = new Bird(m_Renderer, 100,380);
   eventSystem->AddListener(Flappy);
   Entitys.push_back(Flappy);
     //read in the font
    m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf",15); //04-02
    m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf",50); //04-02   

    Floor = new Ground(m_Renderer, 0, 620);
 
    Entitys.push_back(Floor);
    Celling = new UI(m_Renderer,0,0);

    Entitys.push_back(Celling);
 
    
    //calculates raduius that we sould do a collision check in 

   
    /*
    for (int i = 0; i < Entitys.size(); i++)
    {
        float A = Entitys[i]->transform.GetPosition().x;
        float B = Entitys[i]->transform.GetPosition().y;
        //Entitys[i]->Radius = (sqrt((A * A) + (B * B))) / 2;
        Entitys[i]->Radius = 100;//TODO save bitmap size to plug in
    }
   */

 }


 Game::~Game()
 {
     delete phi;
     Physics* phi = nullptr;
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
       
        // SDL_Delay(16);//milli seconds //may be needed back
       


     }


 }
 void Game::UpdateText(std::string msg, int x, int y, TTF_Font* font, SDL_Colour colour)
 {
     SDL_Surface* surface = nullptr;
     SDL_Texture* texture = nullptr;

     int texW = 0;
     int texH = 0;
    

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
     if (currentScene == TESTSCENE)
     {
         FrameTimeStack FrameTime;
         ImGui::NewFrame();
         ImGui_ImplSDL2_NewFrame(m_Window);
         bool show = true;
         //ShowExampleAppleDockSpace(&show);


         ImGui::Begin("Editor");
         ImGui::BeginChild("Content Window", ImVec2(), true);
         //ImGui::BeginTable("Content browser", 3);

         for (int i = 0; i < content.size(); i++)
         {
             ImGui::PushID(i);

             ImGui::ImageButton((ImTextureID)content[i]->GetTextureRef(), { 100,100 });


             //for dragging
             
             if (ImGui::BeginDragDropSource())
             {
                  AssetMousDrag = content[i];
                 ImGui::Image((ImTextureID)content[i]->GetTextureRef(), { 100,100 });
                 ImGui::EndDragDropSource();
             }
             
             ImGui::PopID();
             ImGui::SameLine();
         }

         //ImGui::EndTabItem();

         ImGui::EndChild();
         ImGui::End();


         if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && AssetMousDrag != nullptr)
         {

             int x, y;
             SDL_GetMouseState(&x, &y);
             BaseEntity* b = new BaseEntity(m_Renderer, AssetMousDrag->FileName, x, y, true);
             //Bitmap* s = new Bitmap(m_Renderer, AssetMousDrag->FileName, x, y, true);
             //s->Transfrom.ParentSet(GameWindow::Instance().GetHirarcy());
             SceanHierarchy.push_back(b);

             AssetMousDrag = nullptr;
         }



         ImGui::ShowDemoWindow(nullptr);
         ImGui::Begin("Editor");
         ImGui::BeginChild("Content Window", ImVec2(), true);
         
        //for contents of assets file creat a dragable

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

         ImGui::EndTabItem();
         
         ImGui::EndChild();
         ImGui::End();
       
         for (Bitmap* path : content)
         {


             BaseEntity* SelectedObject = new BaseEntity(m_Renderer,path->FileName,1,1,false);
             ImGui::Begin(string("Selected Object" + std::to_string(SelectedObject->ID)).c_str());

             int posTemp[2];
             posTemp[0] = SelectedObject->transform.GetPosition().x;
             posTemp[1] = SelectedObject->transform.GetPosition().y;


             char buff[255]{};
             strncpy_s(buff, SelectedObject->ObjectName.c_str(), sizeof(buff) - 1);
             ImGui::InputText("Name:", buff, sizeof(buff));
             SelectedObject->ObjectName = buff;

             ImGui::Text(SelectedObject->ObjectName.c_str());
             ImGui::DragInt2("X", posTemp);

             SelectedObject->transform.SetPosition(vec3(posTemp[0], posTemp[1], 0));
             //SelectedObject->SetX(posTemp[0]);
             //SelectedObject->SetY(posTemp[1]);

             if (ImGui::Button("Close"))
             {
                 SelectedObject->IsSelected = false;
             }

             ImGui::End();
             
             ImGui::Begin("Scene Hirarcy", 0, ImGuiWindowFlags_NoMove);
             ImGui::SetWindowPos({ 0,200 });
             ImGui::SetWindowSize({ 150, 720 - 200 });
             BaseEntity* sceneRoot = new BaseEntity(m_Renderer, "assets/Trigger.bmp/", 0, 620, true);
             for (BaseEntity* gameObject : SceanHierarchy)
             {
                 if (ImGui::TreeNode(gameObject->ObjectName.c_str()))
                 {
                     ImGui::TreePop();
                    
                 }
             }
             ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
             bool isNodeOpen = ImGui::TreeNodeEx("Scene", nodeFlags, "Scene");
             if (isNodeOpen)
             {
                 //cout << bitmap->ObjectName.c_str() << endl;
                 //I_GUIWindow::SelectedObject = .ObjectName;
                
                 for (int i = 0; i < sceneRoot->Children.size(); i++)
                 {
                     BaseEntity* child;
                     child->Draw();

                 }
                 ImGui::TreePop();
             }

             ImGui::End();
             
         }
        
         ImGui::Begin("Frametime");
         FrameTime.Push(io.DeltaTime * 1000);
         ImGui::PlotLines("frame", FrameTime.FramTimeQ.data(),
             FrameTime.Capacity);
            char Buffer[64];
             printf(Buffer, sizeof Buffer, "%f ms",
                 FrameTime.AverageTime());
             ImGui::Text(Buffer);
             ImGui::End();
         ImGui::Render();
         ImGuiSDL::Render(ImGui::GetDrawData());
         

     }
     else if (currentScene == GAMEOVER)
     {
         ImGui::NewFrame();
         ImGui_ImplSDL2_NewFrame(m_Window);
         ImGui::Begin(".");
         bool clicked = ImGui::Button("Restart", ImVec2(0, 0));
         if (clicked)
         {
             currentScene = GAME;
             
         }
         ImGui::End();
         
         ImGui::Render();
         ImGuiSDL::Render(ImGui::GetDrawData());
         
     }
     else if (currentScene == GAME)
     {
       

         std::cout << "frame \n";

         if (isInPlay ==false)// resets positions flappy and pipes on restart
         {
             Flappy->transform.SetPosition(vec3(320, 240, 0));
             int  y;
             int tempx = 10;
             for (int i = 0; i <Pipes.size(); i = i + 2)
             {    
                 

                 if (Pipes[i]->topPipe == true)//if bottom pipe
                 {
                     y = rand() % (600 - 300 + 1) + 300;
                     Pipes[i]->transform = vec3{ tempx,(y - 800), 0.0f };
                     if(Pipes[i + 1]->topPipe == false){  Pipes[i+1]->transform = vec3{ tempx, y, 0.0f };}
                   
                 }
              
                     tempx += screenWidth / 4 + 1;

             }

             
             isInPlay = true;

         }
         else
         {
             //////////////////////////////////////////GAMELOOP//////////////////////////////////////////////////
             eventSystem->HandelEvents();
             int  y=720;
             for (int i = 0; i < Pipes.size(); i++)
             {

                 if (Pipes[i]->transform.GetPosition().x <= 0)
                 {    //top pipe
                     if (Pipes[i]->topPipe == true)
                     {
                         Pipes[i]->transform = vec3{ screenWidth,(y - 800), 0.0f };
                     }
                     else
                     {
                         y = rand() % (600 - 300 + 1) + 300;
                         Pipes[i]->transform = vec3{ screenWidth, y, 0.0f };
                     }

                 }

             }

             score = +0.001f;
             scoretxt += std::to_string(score);

             //collision check/////////////////////////////////////////////////////////////
             for (int i = 0; i < Entitys.size(); i++)
             {
                 if (!(Entitys[i] == Flappy))
                 {
                     if (Flappy->CollisionCheck(Entitys[i]))
                     {
                         currentScene = GAMEOVER;
                         isInPlay = false;
                         //endGame
                     }

                 }

             }


             for (int i = 0; i < Entitys.size(); i++)
             {
                 Entitys[i]->ApplyContinuousMoment();

             }

             for (int i = 0; i < Entitys.size(); i++)
             {
                 Entitys[i]->Draw();
             }
             ////draw text
             UpdateText(scoretxt, 50, 640, m_pSmallFont, { 0,0,0 });

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
             //  //phi->Move(Flappy->transform, vec3(1, -1, 0));

         }
     }

        
     SDL_RenderPresent(m_Renderer);

     SDL_Delay(16);//milliseconds
 }

 


     