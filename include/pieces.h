#ifndef PIECES_H
#define PIECES_H

#include <iostream>
#include <vector>

using std::vector;



class Pieces {
public:
    int x1, y1, x2, y2; // location present/before and after move
    //Pieces(bool colorWhite, std::string name);
    Pieces();
    virtual bool move() = 0; // abstract
    virtual bool checkNullSquareBetweenL1L2(Pieces* board[][8]) = 0; // abstract
    virtual bool moveOnTheBoard(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, bool print);
    virtual void moveOnTheBoardVer2(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8]);
    virtual bool atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) = 0; // abstract
    virtual bool checkTheOtherKing(Pieces* board[][8], Pieces* king) = 0; // abstract
    virtual bool theKingIsChecked(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king);


//protected:
    bool colorWhite;
    std::string name;
    

    bool enPassantCondition;// = false; // a Pawn move 2 square straight in the first move

    Pieces* tmp;// = nullptr;
    int count;

    bool latestMove;// = false; // used for En Passant
    bool firstMove;// = true; //used for castling

};

class Rook : public Pieces {
public:
    Rook(bool colorWhite, std::string name);

    bool move();
    bool checkNullSquareBetweenL1L2(Pieces* board[][8]);
    bool atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king);
    bool checkTheOtherKing(Pieces* board[][8], Pieces* king);
};

class Knight : public Pieces {
public:
    Knight(bool colorWhite, std::string name);

    bool move();
    bool checkNullSquareBetweenL1L2(Pieces* board[][8]);
    bool atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king);
    bool checkTheOtherKing(Pieces* board[][8], Pieces* king);
    
    bool onePossibleSquareSample(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, int n1, int n2);
    bool checkTheOtherKingSample(Pieces* board[][8], Pieces* king, int n1, int n2);  // real-life next location  of the knight
};

class Bishop : public Pieces {
public:
    Bishop(bool colorWhite, std::string name);

    bool move();
    bool checkNullSquareBetweenL1L2(Pieces* board[][8]);
    bool atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king);
    bool checkTheOtherKing(Pieces* board[][8], Pieces* king);
};

class Queen : public Pieces {
public:
    Queen(bool colorWhite, std::string name);

    bool move();
    bool checkNullSquareBetweenL1L2(Pieces* board[][8]);
    bool atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king);
    bool checkTheOtherKing(Pieces* board[][8], Pieces* king);
};

class King : public Pieces {
public:
    King(bool colorWhite, std::string name);

    bool move();
    bool checkNullSquareBetweenL1L2(Pieces* board[][8]);
    bool atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king);
    bool checkTheOtherKing(Pieces* board[][8], Pieces* king);

    bool onePossibleSquareSample(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, int k1, int k2);
    bool checkTheOtherKingSample(Pieces* board[][8], Pieces* king, int k1, int k2); // real-life next location  of the king

    bool moveOnTheBoard(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, bool print);
    void moveOnTheBoardVer2(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8]);
};

class Pawn : public Pieces {
public:
    Pawn(bool colorWhite, std::string name);

    bool move();
    bool checkNullSquareBetweenL1L2(Pieces* board[][8]);
    bool atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king);
    bool checkTheOtherKing(Pieces* board[][8], Pieces* king);

    bool onePossibleSquareSample(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, int p1, int p2);
    bool checkTheOtherKingSample(Pieces* board[][8], Pieces* king, int x, int y); // x = x1 +- 1; y = +- 1;

    bool moveOnTheBoard(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, bool print);
    void moveOnTheBoardVer2(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8]);

    bool enPassant(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, bool print, int a); // int a is the present x of the enemy pawn; a is x2!!
};
void remove(vector<Pieces*> &list, const Pieces* value);

#endif