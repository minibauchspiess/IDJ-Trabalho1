
#include <iostream>

#include "../include/Game.h"



#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"

using namespace std;

Game* Game::instance;

Game::Game (string title, int width, int height){

    //Making sure that onli one instance of the Class will be created (Singleton)
    if (instance != nullptr){
        cout<< "There's already one instance in use"<<endl;
    }
    else{
        Game::instance = this;
    }

    cout << "instance created"<<endl;

    //Initializing the SDL libraries
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){   //Check if the SDL library was correctly initialized
        cout<<SDL_GetError()<<endl;
        exit(EXIT_FAILURE);
    }

    //Initializing SDL_image library
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0){
        cout<<"No file format was loaded succesfuly. Aborting."<<endl;
        exit(EXIT_FAILURE);

    }

    //Initializing SDL_mix library
    Mix_Init(MIX_INIT_FLAC|MIX_INIT_OGG|MIX_INIT_MP3);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
        cout<<"Not able to perform Mix_OpenAudio() succesfuly"<<endl;
        exit(EXIT_FAILURE);
    }
    Mix_AllocateChannels(32);


    //Creating window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window == nullptr){
        cout<<"Failed window creation"<<endl;
        exit(EXIT_FAILURE);
    }


    //Creating renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr){
        cout<<"Failed renderer creation"<<endl;
        exit(EXIT_FAILURE);
    }


    //Creating a State instance
    state = new State;
    if (state==nullptr){
        cout<<"Fi, por algum motivo o state ta nulo"<<endl;
    }
}

Game::~Game(){
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(Game::window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


Game& Game::GetInstance(){

    if (instance == nullptr){
        instance = new Game("Daniel Bauchspiess - 15/0078901", 1024, 600);
    }
    return  *instance;
}

State& Game::GetState(){
    return *state;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}


void Game::Run(){
    //Loop to continue the game
    cout<<"voltando entao, vou entrar agora no loop"<<endl;
    while(state->QuitRequested() == false){
        //cout<<"yes, to aqui dentro"<<endl;
        state->Update(33);
        state->Render();

        //cout<<"passei do update E do Render"<<endl;

        SDL_RenderPresent(renderer);
        SDL_Delay(33);
        //cout<<"e agora finalizo o loop"<<endl;
    }
    cout<<"o quitRequested de state ta em "<<state->QuitRequested()<<endl;
}


