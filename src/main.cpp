#include <iostream>
#include <headers/game.hpp>
#include <thread>
#include <chrono>

int main(int argc,char* argv[]){
    int userScreenWidth=0;
    int userScreenHeight=0;
    Game game("Chess Game C++",SDL_WINDOW_SHOWN,userScreenWidth,userScreenHeight);

    SDL_Texture* boardImage=game.loadTexture("res/img/board.png");

    //Pawn's images:
    SDL_Texture *pawnImage=game.loadTexture("res/img/pawn.png");
    SDL_Texture *pawnImageChosen=game.loadTexture("res/img/pawnChosen.png");
    SDL_Texture *pawnImageCanBeAttacked=game.loadTexture("res/img/pawnGetAttack.png");

    SDL_Texture *pawn2Image=game.loadTexture("res/img/pawn2.png");
    SDL_Texture *pawn2ImageChosen=game.loadTexture("res/img/pawn2Chosen.png");
    SDL_Texture *pawn2ImageCanBeAttacked=game.loadTexture("res/img/pawn2GetAttack.png");

    //Bishop's images:
    SDL_Texture *bishopImage=game.loadTexture("res/img/bishop.png");
    SDL_Texture *bishopImageChosen=game.loadTexture("res/img/bishopChosen.png");
    SDL_Texture *bishopImageCanBeAttacked=game.loadTexture("res/img/bishopGetAttack.png");

    SDL_Texture *bishop2Image=game.loadTexture("res/img/bishop2.png");
    SDL_Texture *bishop2ImageChosen=game.loadTexture("res/img/bishop2Chosen.png");
    SDL_Texture *bishop2ImageCanBeAttacked=game.loadTexture("res/img/bishop2GetAttack.png");

    //Knight's images:
    SDL_Texture *knightImage=game.loadTexture("res/img/knight.png");
    SDL_Texture *knightImageChosen=game.loadTexture("res/img/knightChosen.png");
    SDL_Texture *knightImageCanBeAttacked=game.loadTexture("res/img/knightGetAttack.png");

    SDL_Texture *knight2Image=game.loadTexture("res/img/knight2.png");
    SDL_Texture *knight2ImageChosen=game.loadTexture("res/img/knight2Chosen.png");
    SDL_Texture *knight2ImageCanBeAttacked=game.loadTexture("res/img/knight2GetAttack.png");

    //Rook's images:
    SDL_Texture *rookImage=game.loadTexture("res/img/rook.png");
    SDL_Texture *rookImageChosen=game.loadTexture("res/img/rookChosen.png");
    SDL_Texture *rookImageCanBeAttacked=game.loadTexture("res/img/rookGetAttack.png");

    SDL_Texture *rook2Image=game.loadTexture("res/img/rook2.png");
    SDL_Texture *rook2ImageChosen=game.loadTexture("res/img/rook2Chosen.png");
    SDL_Texture *rook2ImageCanBeAttacked=game.loadTexture("res/img/rook2GetAttack.png");

    //Queen's images: 
    SDL_Texture *queenImage=game.loadTexture("res/img/queen.png");
    SDL_Texture *queenImageChosen=game.loadTexture("res/img/queenChosen.png");
    SDL_Texture *queenImageCanBeAttacked=game.loadTexture("res/img/queenGetAttack.png");

    SDL_Texture *queen2Image=game.loadTexture("res/img/queen2.png");
    SDL_Texture *queen2ImageChosen=game.loadTexture("res/img/queen2Chosen.png");
    SDL_Texture *queen2ImageCanBeAttacked=game.loadTexture("res/img/queen2GetAttack.png");

    //King's images: 
    SDL_Texture *kingImage=game.loadTexture("res/img/king.png");
    SDL_Texture *kingImageChosen=game.loadTexture("res/img/kingChosen.png");
    SDL_Texture *kingImageCanBeAttacked=game.loadTexture("res/img/kingGetAttack.png");

    SDL_Texture *king2Image=game.loadTexture("res/img/king2.png");
    SDL_Texture *king2ImageChosen=game.loadTexture("res/img/king2Chosen.png");
    SDL_Texture *king2ImageCanBeAttacked=game.loadTexture("res/img/king2GetAttack.png");

    //Default when a case without pawn can be attacked:
    SDL_Texture *blueRect=game.loadTexture("res/img/blueR.png");
    SDL_Texture *redRect=game.loadTexture("res/img/redR.png");

    int posXMouse(0);
    int posYMouse(0);
    Uint32 click;
    Board *board=new Board();
    int actualBoardNum(-1);
    int selectedPawn[2]={-1,-1};
    int xPawn(-1);
    int yPawn(-1);
    bool hasBeenChosed=false;
    bool canAttack;
    int hasBeenChosedNumber(-1);

    

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
                SDL_GetMouseState(&posXMouse,&posYMouse);
                if (posXMouse>840){
                    xPawn=(posXMouse-840)/135;
                    yPawn=posYMouse/135;
                    std::cout<<xPawn<<" "<<yPawn<<std::endl;
                    if(game.getActualPlayer()==Player::J1){
                        //We check which case got clicked on which turn (you can't click on ennemy's pawn on your turn )
                        //So later we can show on which case you can go with the specific pawn
                        if(board->getBoardN(yPawn,xPawn)<7 && board->getBoardN(yPawn,xPawn)!=0 ){
                            /*When nodoy is ready to attack, in selectedPawn we stock x,y of the pawn that we selected to be ready to attack*/
                            selectedPawn[0]=xPawn;
                            selectedPawn[1]=yPawn;
                            hasBeenChosed=true;
                            hasBeenChosedNumber=board->getBoardN(selectedPawn[1],selectedPawn[0]);
                        }
                        else if ((board->getBoardN(yPawn,xPawn)>10 || board->getBoardN(yPawn,xPawn)==0 )&& hasBeenChosed==true&& (xPawn!=selectedPawn[0] || yPawn!=selectedPawn[1])){// we verify if the selected one where we attack is an ennemy or a void case 
                            //One pawn is already selected to attack, now it's the click to attack
                                if(board->canBeAttacked(board->getBoardN(selectedPawn[1],selectedPawn[0]),selectedPawn[0],selectedPawn[1],xPawn,yPawn,board->getBoardN(yPawn,xPawn),game)!=0){//we can attack
                                std::cout<<" the one who attack : "<<board->getBoardN(selectedPawn[1],selectedPawn[0])<<std::endl;
                                board->modify(0,selectedPawn[0],selectedPawn[1]);
                                board->modify(hasBeenChosedNumber,xPawn,yPawn);
                                hasBeenChosed=false;
                                hasBeenChosedNumber=-1;
                                game.playerSwitch();
                                selectedPawn[0]=-1;
                                selectedPawn[1]=-1;
                                }
                        }
                    }
                    
                    if(game.getActualPlayer()==Player::J2){
                        if(board->getBoardN(yPawn,xPawn)>6 && board->getBoardN(yPawn,xPawn)!=0){
                            selectedPawn[0]=xPawn;
                            selectedPawn[1]=yPawn;
                            hasBeenChosed=true;
                            hasBeenChosedNumber=board->getBoardN(selectedPawn[1],selectedPawn[0]);
                            }
                        else if (board->getBoardN(yPawn,xPawn)<7 && hasBeenChosed==true &&(xPawn!=selectedPawn[0]||yPawn!=selectedPawn[1])){
                            if(board->canBeAttacked(board->getBoardN(selectedPawn[1],selectedPawn[0]),selectedPawn[0],selectedPawn[1],xPawn,yPawn,board->getBoardN(yPawn,xPawn),game)!=0){
                                board->modify(0,selectedPawn[0],selectedPawn[1]);
                                board->modify(hasBeenChosedNumber,xPawn,yPawn);
                                hasBeenChosed=false;
                                hasBeenChosedNumber=-1;
                                game.playerSwitch();
                                selectedPawn[0]=-1;
                                selectedPawn[1]=-1;
                                }
                            
                            }
                       }
                      
                }
            }
        //starting rendering
        game.clear();
        //renders the board
        game.render(boardImage,0,0,userScreenWidth,userScreenHeight);
        std::cout<<selectedPawn[0]<<"\n";
        std::cout<<selectedPawn[1]<<"\n";
        //renders the pawn on the board
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                actualBoardNum=board->getBoardN(i,j);
                switch(actualBoardNum){
                    //The side on the bot (white)
                    case 1 :
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==1 &&selectedPawn[1]==i && selectedPawn[0]==j && hasBeenChosed==true){
                            game.render(pawnImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{            
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J2 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,1,game)){
                                    case 0:
                                        game.render(pawnImage,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(pawnImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(pawnImage,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 2:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==2 &&selectedPawn[1]==i && selectedPawn[0]==j && hasBeenChosed==true){
                            game.render(bishopImageChosen,845+(135*j),i*135+5,127,127);
                            
                            hasBeenChosedNumber=board->getBoardN(i,j);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J2 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,2,game)){
                                    case 0:
                                        game.render(bishopImage,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(bishopImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(bishopImage,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 3:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==3 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(knightImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J2 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,3,game)){
                                    case 0:
                                        game.render(knightImage,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(knightImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(knightImage,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 4:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==4 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(rookImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J2 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,4,game)){
                                    case 0:
                                        game.render(rookImage,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(rookImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(rookImage,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 5:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==5 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(queenImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=1 && game.getActualPlayer()==Player::J2 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,5,game)){
                                    case 0:
                                        game.render(queenImage,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(queenImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(queenImage,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 6:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==6 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(kingImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=1 && game.getActualPlayer()==Player::J2 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,6,game)){
                                    case 0:
                                        game.render(kingImage,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(kingImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(kingImage,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 11 :                        
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==11 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(pawn2ImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J1 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,11,game)){
                                    case 0://it return 0 when this
                                        game.render(pawn2Image,845+(135*j),i*135,130,130);
                                        break;
                                        //we check if he can  touch him
                                        //(board->getBoardN(onClickPawn[0]+1,onClickPawn[1]-1)==board->getBoardN(i,j) || board->getBoardN(onClickPawn[0]+1,onClickPawn[1]+1)==board->getBoardN(i,j))
                                        //the code above is a test ,currently I'm not sure about the verification
                                    default:    
                                        game.render(pawn2ImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                                
                            }
                            else{//normal render when this pawn is not the selected one and it can be attacked by ennemy's pawn
                                game.render(pawn2Image,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 12:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==12 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(bishop2ImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J1 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,12,game)){
                                    case 0:
                                        game.render(bishop2Image,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(bishop2ImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(bishop2Image,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 13:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==13 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(knight2ImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J1 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,13,game)){
                                    case 0:
                                        game.render(knight2Image,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(knight2ImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(knight2Image,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 14:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==14 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(rook2ImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J1 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,14,game)){
                                    case 0:
                                        game.render(rook2Image,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(rook2ImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(rook2Image,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 15:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==15 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(queen2ImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J1 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,15,game)){
                                    case 0:
                                        game.render(queen2Image,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(queen2ImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(queen2Image,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 16:
                        if (board->getBoardN(selectedPawn[1],selectedPawn[0])==3 &&selectedPawn[1]==i && selectedPawn[0]==j&& hasBeenChosed==true){
                                game.render(king2ImageChosen,845+(135*j),i*135+5,127,127);
                        }
                        else{
                            if(hasBeenChosedNumber!=-1 && game.getActualPlayer()==Player::J1 ){//we check if this pawn can be attacked
                                switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,16,game)){
                                    case 0:
                                        game.render(king2Image,845+(135*j),i*135,130,130);
                                        break;
                                    default:    
                                        game.render(king2ImageCanBeAttacked,845+(135*j),i*135,130,130);
                                        break;
                                }
                            }
                            else{
                                game.render(king2Image,845+(135*j),i*135,130,130);
                            }
                        }
                        break;
                    case 0://if there is no pawn on this case
                        if(hasBeenChosed==true && hasBeenChosedNumber!=-1 ){
                            switch(board->canBeAttacked(hasBeenChosedNumber,selectedPawn[0],selectedPawn[1],j,i,0,game)){
                                    case 0:
                                        break;
                                    default:    
                                        if(game.getActualPlayer()==Player::J1){
                                            game.render(blueRect,845+(135*j),i*135,130,130);   
                                        }
                                        else{
                                            game.render(redRect,845+(135*j),i*135,130,130);
                                        }
                                        break;
                            }
                        }
                        break; 
            }
        }

    //end of for 
    }
    game.display();
    }
    }
    board->~Board();
    return 0;
}
           
