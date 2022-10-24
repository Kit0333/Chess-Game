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

    void run();
    void clear();
    void display();

private:

    void cleanup();

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

class Board{
public:
    Board();
    ~Board();
    int getBoardN(int y,int x);
    int trace(int &x1,int&y1,int&x2,int&y2);
    int Board::canBeAttacked(int ennemyPawnType,int ennemyX,int ennemyY ,int thisX,int thisY );
    void modify(int newNum,int x,int y);
private:
    int *m_board;
    Pawn *m_pawn;
    Pawn *m_bishop;
    Pawn *m_knight;
    Pawn *m_rook;
    Pawn *m_queen;
    Pawn *m_king;
};
