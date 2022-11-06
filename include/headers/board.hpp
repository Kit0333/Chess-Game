#pragma once

#include <game.hpp>
class Board{
public:
    Board();
    ~Board();
    int getBoardN(int y,int x);
    int trace(int &x1,int&y1,int&x2,int&y2);
    int canBeAttacked(int ennemyPawnType,int ennemyX,int ennemyY ,int thisX,int thisY,int thisPawnType,Game Game);
    void modify(int newNum,int x,int y);
    bool isKingAlive(Game game)const;
    void restartBoard(void);
   
           

private:
    int *m_board;
    Pawn *m_pawn;
    Pawn *m_bishop;
    Pawn *m_knight;
    Pawn *m_rook;
    Pawn *m_queen;
    Pawn *m_king;
};