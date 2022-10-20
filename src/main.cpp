#include <iostream>
#include <headers/game.hpp>

int main(int argc,char* argv[]){
    Game game("Chess Game C++",SDL_WINDOW_SHOWN);

    SDL_Texture* boardImage=game.loadTexture("res/img/board.jpg");


    int posXMouse=0;
    int posYMouse=0;
    Uint32 click;


    while (game.getGameState()!=GameState::EXIT){
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {

        case SDL_QUIT://Shut down the game
            game.gameStateChange(GameState::EXIT);
            break;

        case SDL_MOUSEBUTTONDOWN://Get mouse position
            int mouseButton=game.mousePress(event.button);
            if (mouseButton==0){
                click=SDL_GetMouseState(&posXMouse,&posYMouse);
            }
            break;
            
        }
        game.run();
    }


    return 0;
}
