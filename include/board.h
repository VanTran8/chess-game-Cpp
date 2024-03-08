#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>


#include "pieces.h"
#include "position_history.h"

using std::vector;

enum Turn {B, W};

std::string removeSpace_toupper(std::string& a);

class Board {
public:
    Pieces* board[8][8];

    Board();
    void play();

private:
    int x1, x2, y1, y2;
    Turn t;// = W;

    Pieces* tmp;// = nullptr;

    Pieces* latestWhiteMove;// = nullptr; // used for en Passant; ?? = null
    Pieces* latestBlackMove;// = nullptr;

    //char inputLocations[];

    vector<Position*> historyMove;
    std::string control;// = "ahihi";
    int promote;// = 0;

    vector<Pieces*> whiteOnBoard;
    vector<Pieces*> blackOnBoard;

    Pieces* ro1W;
    Pieces* kn1W;
    Pieces* bi1W;
    Pieces* kiW;
    Pieces* quW;
    Pieces* bi2W;
    Pieces* kn2W;
    Pieces* ro2W;

    Pieces* pa1W;
    Pieces* pa2W;
    Pieces* pa3W;
    Pieces* pa4W;
    Pieces* pa5W;
    Pieces* pa6W;
    Pieces* pa7W;
    Pieces* pa8W;


    Pieces* ro1B;
    Pieces* kn1B;
    Pieces* bi1B;
    Pieces* kiB;
    Pieces* quB;
    Pieces* bi2B;
    Pieces* kn2B;
    Pieces* ro2B;

    Pieces* pa1B;
    Pieces* pa2B;
    Pieces* pa3B;
    Pieces* pa4B;
    Pieces* pa5B;
    Pieces* pa6B;
    Pieces* pa7B;
    Pieces* pa8B;


    void reverseFunction();
    void reverseMove();
    void setupANewBoard();
    void paintABoard();
    bool moveAPiece(bool print);
    bool atLeast1PossibleMove(Pieces* king);
    bool loseWhiteOrBlack(Pieces* king);
    void promoteAPawnVer2(int x, int y, int n);
    int promoteAPawn(int x, int y);
    int getANumber();
    void inputThePosition();

};

#endif