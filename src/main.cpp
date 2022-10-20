#include <iostream>
#include <headers/game.hpp>

int main(int argc,char* argv[]){
    Game game("Premier jeu C++",SDL_WINDOW_SHOWN);

    SDL_Texture* terrain=game.loadTexture("res/img/Terrain.jpg");
    SDL_Texture* taupe=game.loadTexture("res/img/Taupe.jpg");


    int posXMouse=0;
    int posYMouse=0;
    Uint32 click;


    SDL_color whiteColor={255,255,255}


    //gestion Temps
    int lastTime=0;
    int currentTime=0;
    


    while (game.getGameState()!=GameState::EXIT){
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            game.gameStateChange(GameState::EXIT);
            break;

        case SDL_MOUSEBUTTONDOWN:
            int mouseButton=game.mousePress(event.button);
            if (mouseButton==0){
                click=SDL_GetMouseState(&x,&y);
            }
            break;
            
        }
        game.run();
    }


    return 0;
}