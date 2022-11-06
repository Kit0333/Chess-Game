#pragma once

#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>

enum class GameState{PLAY,EXIT};
enum class Player{J1,J2};

class Game{
public:
    Game(const char* title,Uint32 flags,int &width,int &height);
    ~Game();

    SDL_Texture* loadTexture(const char* filePath);
    void render(SDL_Texture* tex,int x=0,int y=0,int w=1024,int h=600);
    GameState getGameState();
    int& mousePress(SDL_MouseButtonEvent& b);
    void gameStateChange(GameState x);
    
    Player getActualPlayer();
    void playerSwitch();
    int selectNewPawn(int x,int y,int screenWidth,int screenHeight);

    void run();
    void clear();
    void display();
    void cleanup();
private:


    void UserScreenSize(int&width, int &height);
    Player m_player;
    GameState m_gameState;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};
class Pawn{
public:
    Pawn(int type);
    ~Pawn();

private:
    int m_type;
    const char* m_info;
};
