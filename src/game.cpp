#include <headers/game.hpp>
#include <iostream>
GameState Game::getGameState(){
    return m_gameState;
};

void Game::gameStateChange(GameState x){
    m_gameState=x;
};



Game::Game(const char* title,Uint32 flags) {
    SDL_Init(SDL_INIT_EVERYTHING);
    int width,height;
    UserScreenSize(width,height);
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width,height, flags);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    m_gameState = GameState::PLAY;
};

Game::~Game() {};

void Game::UserScreenSize(int &width,int &height){
    //fonction retournant rien 
    //la fonction utilise 2 références , pour la longueur et la hauteur de l'écran

    SDL_DisplayMode displaymode;
    if(SDL_GetCurrentDisplayMode(0,&displaymode)!=0){
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        width=1024;
        height=600;
    }
    else{
        width=displaymode.w-100;
        height=displaymode.h-100;
    }

};

void Game::run(){
    display();
    clear();
}

void Game::render(SDL_Texture* tex){
    SDL_Rect src;
    src.x=0;
    src.y=0;
    src.w=1000;
    src.h=1000;

    SDL_Rect dist;
    dist.x=0;
    dist.y=0;
    dist.w=600;
    dist.h=600;

    SDL_RenderCopy(m_renderer,tex,&src,&dist);
};


SDL_Texture* Game::loadTexture(const char* filePath){
    
    SDL_Texture* tex=NULL;
    tex=IMG_LoadTexture(m_renderer,filePath);

    if(tex==NULL){
        std::cout<<"img couldn't load from file path "<<filePath<<" ERROR : "<<SDL_GetError()<<std::endl;
    }
    return tex;

};

void Game::display(){
    SDL_RenderPresent(m_renderer);

}

void Game::clear(){
    SDL_RenderClear(m_renderer);
}

void Game::cleanup(){
    SDL_DestroyWindow(m_window);
}


int& Game::mousePress(SDL_MouseButtonEvent& b){
    static int state;
    if(b.button==SDL_BUTTON_LEFT){
        state=0;//0= left click
    }
    else{
        state=1;//1=right click
    }
    return state;
};