#include "../include/Sprite.h"
#include "../include/Game.h"
#include <iostream>

using namespace std;

Sprite::Sprite()
{
    texture = nullptr;
}

Sprite::Sprite(string file){
    texture =nullptr;
    Open(file);
}

Sprite::~Sprite(){
    SDL_DestroyTexture(texture);
}

void Sprite::Open(string file){

    Game& instance = Game::GetInstance();

    //Check if texture already exists
    if (texture != nullptr){
        SDL_DestroyTexture(texture);
    }

    //Load texture
    cout<<"Vou tentar abrir a imagem"<<endl;
    texture = IMG_LoadTexture(instance.GetRenderer(), file.c_str());
    cout<<"Se pa consegui abrir 0"<<endl;

    if (texture == nullptr){
        cout<<"Error loading image"<<endl;
        cout<<SDL_GetError()<<endl;
    }
    else{
        cout<<"Se pa consegui abrir"<<endl;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
    cout<<"e agora terminei a open"<<endl;

}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.x=x;
    clipRect.y=y;
    clipRect.w=w;
    clipRect.h=h;
}

void Sprite::Render(int x, int y){
    Game& instance = Game::GetInstance();

    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    SDL_RenderCopy(instance.GetRenderer(), texture, &clipRect, &dstrect);
}

int Sprite::GetWidth(){
    return width;
}

int Sprite::GetHeight(){
    return height;
}

bool Sprite::IsOpen(){
    if (texture != nullptr){
        return true;
    }
    else{
        return false;
    }
}




