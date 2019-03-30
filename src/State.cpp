#include "../include/State.h"
#include "dirent.h"

using namespace std;

State::State()
{

    quitRequested = false;

    bg.Open("assets/img/ocean.jpg");
    music.Open("assets/audio/stageState.ogg");
    music.Play();
}

void State::LoadAssets(){
    //Load things the game need
}

void State::Update(float dt){
    quitRequested = SDL_QuitRequested();
}

void State::Render(){
    bg.Render(0,0);
}

bool State::QuitRequested(){
    return quitRequested;
}
