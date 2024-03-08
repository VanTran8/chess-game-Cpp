#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>

#include "board.h"
#include "pieces.h"
#include "position_history.h"

std::string removeSpace_toupper(std::string& a) {
	for (int i = 0; i < a.length(); i++) {
		if (isspace(a[i])) {
			a.erase(i, 1);
			i--;
		}
		else
			a[i] = toupper(a[i]);
	}
	return a;
}

Board::Board() {
    Turn t = W;

    Pieces* tmp = nullptr;

    Pieces* latestWhiteMove = nullptr; // used for en Passant; ?? = null
    Pieces* lastestBlackMove = nullptr;

    //char inputLocations[];

    vector<Position*> historyMove;
    char control = 'A';
    int promote = 0;

    Pieces* ro1W = new Rook(true, "Ro");
    Pieces* kn1W = new Knight(true, "Kn");
    Pieces* bi1W = new Bishop(true, "Bi");
    Pieces* kiW =  new King(true, "Ki");
    Pieces* quW = new Queen(true, "Qu");
    Pieces* bi2W = new Bishop(true, "Bi");
    Pieces* kn2W = new Knight(true, "Kn");
    Pieces* ro2W = new Rook(true, "Ro");

    Pieces* pa1W = new Pawn(true, "Pa");
    Pieces* pa2W = new Pawn(true, "Pa");
    Pieces* pa3W = new Pawn(true, "Pa");
    Pieces* pa4W = new Pawn(true, "Pa");
    Pieces* pa5W = new Pawn(true, "Pa");
    Pieces* pa6W = new Pawn(true, "Pa");
    Pieces* pa7W = new Pawn(true, "Pa");
    Pieces* pa8W = new Pawn(true, "Pa");


    Pieces* ro1B = new Rook(false, "Ro");
    Pieces* kn1B = new Knight(false, "Kn");
    Pieces* bi1B = new Bishop(false, "Bi");
    Pieces* kiB = new King(false, "Ki");
    Pieces* quB = new Queen(false, "Qu");
    Pieces* bi2B = new Bishop(false, "Bi");
    Pieces* kn2B = new Knight(false, "Kn");
    Pieces* ro2B = new Rook(false, "Ro");

    Pieces* pa1B = new Pawn(false, "Pa");
    Pieces* pa2B = new Pawn(false, "Pa");
    Pieces* pa3B = new Pawn(false, "Pa");
    Pieces* pa4B = new Pawn(false, "Pa");
    Pieces* pa5B = new Pawn(false, "Pa");
    Pieces* pa6B = new Pawn(false, "Pa");
    Pieces* pa7B = new Pawn(false, "Pa");
    Pieces* pa8B = new Pawn(false, "Pa");
}


void Board::reverseMove() {
    setupANewBoard();
    if (historyMove.size() - 1 == 0) {
        historyMove.pop_back();
        paintABoard();
        t = W;
        return;
    }
        
    for (int i = 0; i < historyMove.size() - 1; i++) {
        x1 = historyMove[i]->getX1();
        x2 = historyMove[i]->getX2();
        y1 = historyMove[i]->getY1();
        y2 = historyMove[i]->getY2();
        promote = historyMove[i]->getPromote();
        
        board[y1][x1]->x2 = x2 + 1; 
        board[y1][x1]->y2 = y2 + 1;
        if (board[y1][x1]->colorWhite)
            board[y1][x1]->moveOnTheBoardVer2(blackOnBoard, board);
        else
            board[y1][x1]->moveOnTheBoardVer2(whiteOnBoard, board);
        promoteAPawnVer2(x2, y2, promote);        
    }
    
    historyMove.pop_back();
    
    if (board[y2][x2]->colorWhite) {
        latestWhiteMove = board[y2][x2]; // use for En Passant
        latestWhiteMove->latestMove = true;
        t = B;
    }
    else {
        latestBlackMove = board[y2][x2];
        latestBlackMove->latestMove = true;
        t = W;
        
    }
        
    paintABoard();
}
void Board::setupANewBoard() {
    for (int i = 2; i < 6; i++)
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    board[0][0] = ro1W;
    board[0][1] = kn1W;
    board[0][2] = bi1W;
    board[0][3] = quW; 
    board[0][4] = kiW; 
    board[0][5] = bi2W;
    board[0][6] = kn2W;
    board[0][7] = ro2W;
    
    for (int i = 1; i < 9; i++) {
        board[0][i - 1]->x1 = i;
        board[0][i - 1]->y1 = 1;
        whiteOnBoard.push_back(board[0][i - 1]);
    }
    

    board[1][0] = pa1W;
    board[1][1] = pa2W;
    board[1][2] = pa3W;
    board[1][3] = pa4W;
    board[1][4] = pa5W;
    board[1][5] = pa6W;
    board[1][6] = pa7W;
    board[1][7] = pa8W;
    
    for (int i = 1; i < 9; i++) {
        board[1][i - 1]->x1 = i;
        board[1][i - 1]->y1 = 2;
        whiteOnBoard.push_back(board[1][i - 1]);
    }
    

    board[7][0] = ro1B;
    board[7][1] = kn1B;
    board[7][2] = bi1B;
    board[7][3] = quB; 
    board[7][4] = kiB; 
    board[7][5] = bi2B;
    board[7][6] = kn2B;
    board[7][7] = ro2B;
    
    for (int i = 1; i < 9; i++) {
        board[7][i - 1]->x1 = i;
        board[7][i - 1]->y1 = 8;
        blackOnBoard.push_back(board[7][i - 1]);
    }


    board[6][0] = pa1B;
    board[6][1] = pa2B;
    board[6][2] = pa3B;
    board[6][3] = pa4B;
    board[6][4] = pa5B;
    board[6][5] = pa6B;
    board[6][6] = pa7B;
    board[6][7] = pa8B;
    
    for (int i = 1; i < 9; i++) {
        board[6][i - 1]->x1 = i;
        board[6][i - 1]->y1 = 7;
        blackOnBoard.push_back(board[6][i - 1]);
    }
}
void Board::paintABoard(){
    std::cout << "             a          b          c          d          e          f          g          h\n";
    std::cout << "     __________ __________ __________ __________ __________ __________ __________ __________ \n";
    for (int i = 8; i > 0; i--) {

        if (i % 2 == 0) {
            
            std::cout << "    |          |          |          |          |          |          |          |          |\n";
            std::cout << "   " << i << "|          |**********|          |**********|          |**********|          |**********|" << i << '\n';
            
            std::cout << "    |";
            for (int j = 1; j < 9; j++) {
                if (j % 2 == 1) {
                    if (board[i - 1][j - 1] == nullptr)
                        std::cout << "          |";
                    else if (board[i- 1][j - 1]->colorWhite) {
                        std::cout << "   W." + board[i - 1][j - 1]->name + "   |";
                    } else {
                        std::cout << "   B." + board[i - 1][j - 1]->name + "   |";
                    }

                } else {
                    if (board[i - 1][j - 1] == nullptr)
                        std::cout << "**********|";
                    else if (board[i - 1][j - 1]->colorWhite) {
                        std::cout << "***W." + board[i - 1][j - 1]->name + "***|";
                    } else {
                        std::cout << "***B." + board[i - 1][j - 1]->name + "***|";
                    }
                }
            }
            std::cout << '\n';
            std::cout << "    |          |**********|          |**********|          |**********|          |**********|";
            std::cout << "    |__________|__________|__________|__________|__________|__________|__________|__________|";
        } else {
            
            std::cout << "    |          |          |          |          |          |          |          |          |\n";
            std::cout << "   " << i << "|**********|          |**********|          |**********|          |**********|          |" << i << '\n';
            std::cout << "    |";
            for (int j = 1; j < 9; j++) {
                if (j % 2 == 1) {
                    if (board[i - 1][j - 1] == nullptr)
                        std::cout << "**********|";
                    else if (board[i - 1][j - 1]->colorWhite) {
                        std::cout << "***W." + board[i - 1][j - 1]->name + "***|";
                    } else {
                        std::cout << "***B." + board[i - 1][j - 1]->name + "***|";
                    }

                } else {
                    if (board[i - 1][j - 1] == nullptr)
                        std::cout << "          |";
                    else if (board[i - 1][j - 1]->colorWhite) {
                        std::cout << "   W." + board[i - 1][j - 1]->name + "   |";
                    } else {
                        std::cout << "   B." + board[i - 1][j - 1]->name + "   |";
                    }

                }
            }
            std::cout << '\n';
            std::cout << "    |**********|          |**********|          |**********|          |**********|          |\n";
            std::cout << "    |__________|__________|__________|__________|__________|__________|__________|__________|\n";

        }


    }
    std::cout << "             a          b          c          d          e          f          g          h\n";
}
    
bool Board::moveAPiece(bool print){
     
    if (board[y1][x1] == nullptr) {
        if (print)
            std::cout << "No pieces in the square. Try again\n";
        
        return false;
    }

    if ((t == W && !board[y1][x1]->colorWhite) || (t == B && board[y1][x1]->colorWhite )) {
        if (print)
            std::cout << "You move the wrong side. Try again\n";
        return false;
    } 
    
     
    board[y1][x1]->x2 = x2 + 1; // set x2, y2 of class Pieces - location want to move to (after)
    board[y1][x1]->y2 = y2 + 1; // Pieces.move() in moveWhiteOrBlack...() need use Pieces.x2 .y2; +1 means for real life reading
    
    if (t == W && board[y1][x1]->moveOnTheBoard(blackOnBoard, board, kiW, print)) {
        if (board[y2][x2]->name =="Pa" && (y2 == 0 || y2 == 7)) {
            promote = promoteAPawn(x2, y2);
        }
        else 
            promote = 0;
            
        return true;
    }
    if (t == B && board[y1][x1]->moveOnTheBoard(whiteOnBoard, board, kiB, print)) {
        if (board[y2][x2]->name == "Pa" && (y2 == 0 || y2 == 7)) {
            promote = promoteAPawn(x2, y2);
        }
        else 
            promote = 0;
            
        return true;
    }
    return false;
}

bool Board::atLeast1PossibleMove(Pieces* king){ // king same side
    if (king->colorWhite) {
        for (Pieces* x : whiteOnBoard) {
            if (x->atLeast1PossibleSquare(blackOnBoard, board, king))//
                return true;
        }
    } else
        for (Pieces* x : blackOnBoard) {
            if (x->atLeast1PossibleSquare(whiteOnBoard, board, king))
                return true;
        }
    return false;
}

bool Board::loseWhiteOrBlack(Pieces* king){
    if (king->colorWhite) {
        if (!atLeast1PossibleMove(king)) {
            if (king->theKingIsChecked(blackOnBoard, board, king)) {

                std::cout << "The Black win!!!\n";
                return true;

            } else {

                std::cout << "The game is even!!\n";
                return true;
            }
        }
        
    } else {
        if (!atLeast1PossibleMove(king)) {
            if (king->theKingIsChecked(whiteOnBoard, board, king)) {

                std::cout << "The White win!!!\n";
                return true;

            } else {

                std::cout << "The game is even!!\n";
                return true;
            }
        }
        
    }
    
    if (whiteOnBoard.size() == 1 && blackOnBoard.size() == 1) {
        std::cout << "The game is even\n";
        return true;
    }
    
    return false;
    
}

void Board::promoteAPawnVer2(int x, int y, int n){
    Pieces* a;
    if (board[y][x]->colorWhite) 
        switch (n) {
            case 0:
                return;//RF...................................................
            case 1:
                a = new Rook(true, "Ro");
                break;
            case 2:
                a = new Knight(true, "Kn");
                break;
            case 3:
                a = new Bishop(true, "Bi");
                break;
            case 4:
                a = new Queen(true, "Qu");
                break;
            default:
                a = new Queen(true, "Qu");
        }
    
    else 
        switch (n) {
            case 0: 
                return; //RF.............................................
            case 1:
                a = new Rook(false, "Ro");
                break;
            case 2:
                a = new Knight(false, "Kn");
                break;
            case 3:
                a = new Bishop(false, "Bi");
                break;
            case 4:
                a = new Queen(false, "Qu");
                break;
            default:
                a = new Queen(false, "Qu");

        }
    if (a->colorWhite)
        remove(whiteOnBoard, board[y][x]);
    else
        remove(blackOnBoard, board[y][x]);
    board[y][x] = a;
    a->x1 = x + 1; // set the present location for Pieces
    a->y1 = y + 1;
    
    if (a->colorWhite) 
        whiteOnBoard.push_back(a);
        
    else
        blackOnBoard.push_back(a); 
}

int Board::promoteAPawn(int x, int y){
    std::cout << "Choose a piece to promote\n";
    std::cout << "1. Rook\n2.Knight\n3.Bishop\n4.Queen\n";
    std::cout << "Input a number (1, 2, 3, 4): ";
    int n = getANumber();
    Pieces* a;
    if (board[y][x]->colorWhite) 
        switch (n) {
            case 1:
                a = new Rook(true, "Ro");
                break;
            case 2:
                a = new Knight(true, "Kn");
                break;
            case 3:
                a = new Bishop(true, "Bi");
                break;
            case 4:
                a = new Queen(true, "Qu");
                break;
            default:
                a = new Queen(true, "Qu");
        }
    
    else 
        switch (n) {
            case 1:
                a = new Rook(false, "Ro");
                break;
            case 2:
                a = new Knight(false, "Kn");
                break;
            case 3:
                a = new Bishop(false, "Bi");
                break;
            case 4:
                a = new Queen(false, "Qu");
                break;
            default:
                a = new Queen(false, "Qu");

        }
    if (a->colorWhite)
        remove(whiteOnBoard, board[y][x]);
    else
        remove(blackOnBoard, board[y][x]);
    board[y][x] = a;
    a->x1 = x + 1; // set the present location for Pieces
    a->y1 = y + 1;
    
    if (a->colorWhite) 
        whiteOnBoard.push_back(a);
        
    else
        blackOnBoard.push_back(a);
    return n;//RF....................................................
}

int Board::getANumber(){
    int n;
    do {
        try {
            
            std::cin >> n;
            if (n > 0 && n < 5)
                return n;
            std::cout << "The value is not in the range. Try again: \n";
            
        } catch (...) {
            std::cout << "Invalid value. Input again: ";

        }

    } while (true);
}

void Board::inputThePosition(){
    if (t == W)
        std::cout << "The White side's turn: ";
    
    else 
        std::cout << "The Black side's turn: ";
    std::string a;

    do {
        std::getline(std::cin, a);
        a = removeSpace_toupper(a);
        if (a == "r") { //................................................................................
            control = a;
            break;
        }
        else
            control = "inputPosition";
            
        if (a.length() != 4) {
            std::cout << "Input the right location again, please: ";
        } else {
            
            if (a[0] < 97 || a[0] > 104
                || a[2] < 97 || a[2] > 104
                || a[1] < 49 || a[1] > 56
                || a[3] < 49 || a[3] > 56) {
                std::cout << "Input the right location again, please: ";
            }
            else {
            x1 = a[0] - 96 - 1;
            x2 = a[2] - 96 - 1;
            y1 = a[1] - 48 - 1;
            y2 = a[3] - 48 - 1;
            break;
            }
        }

    } while (true);
}

void Board::reverseFunction() {     
    do {
        if (!historyMove.empty()) {
            if (control == "r") {
                
                    reverseMove();

            } else {
                std::cout << "Press the 'Enter' key to continue to move the pieces\n";
                std::cout << "Press the 'R' key to reverse a move\n";
            }
        }
            
        if (historyMove.empty()) {
            std::cout << "let's start the game\n";
            return;
        }
        std::cout << "Press the 'Enter' key to continue to move the pieces\n";
        std::cout << "Press the 'R' key to reverse another move\n";
        std::getline(std::cin, control);
        removeSpace_toupper(control);           
    } while (control != "");
}

void Board::play(){
    setupANewBoard();
    paintABoard();
    
    
    std::cout << "Press the 'R' key to reverse a move\n"; // ....................................................................................
    std::cout << "Or input the valid before and after position.\n";
    do {
        // RF..........................................................................................................................................
        //reverseFunction();
        if (t == W) {
            if (!loseWhiteOrBlack(kiW)) {

                if (latestWhiteMove != nullptr) { // use for En Passant
                    latestWhiteMove->latestMove = false;
                }

                do {
                    inputThePosition();
                    if (control == "r") { // 1.2
                        reverseFunction();
                        break;
                    }

                } while (!moveAPiece(true));
                if (control == "inputPosition") { // 1.2 - 
                    latestWhiteMove = board[y2][x2]; // use for En Passant
                    latestWhiteMove->latestMove = true;
                    //}
                    historyMove.push_back(new Position(x1, y1, x2, y2, promote)); // RF..................................................................................
                    paintABoard();
                    t = B;
                }
                

            } else {
                reverseFunction();
                if (control == "")
                    break;
            }
                
            
        } else {
            if (!loseWhiteOrBlack(kiB)) {

                if (latestBlackMove != nullptr) {
                    latestBlackMove->latestMove = false;
                }

                do {
                    inputThePosition();
                    if (control == "r") { // 1.2
                        reverseFunction();
                        break;
                    }
//                        else
//                            control = "inputPosition"; // means did input the postions
//                            did insert in the inputThePosition();
                } while (!moveAPiece(true));

                //if (board[y2][x2] != null) { // null pointer exception
                if (control == "inputPosition") { // 1.2  tức là đã input positions
                    latestBlackMove = board[y2][x2];
                    latestBlackMove->latestMove = true;
                    //}
                    historyMove.push_back(new Position(x1, y1, x2, y2, promote)); // RF....................................................................................
                    paintABoard();
                    t = W;
                }
                
            } else {
                reverseFunction();
                if (control == "")
                    break;
            }
            
        }    
        
    } while (true);     
}
