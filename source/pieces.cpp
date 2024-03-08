#include <iostream>
#include <vector>
#include <cmath>

#include "board.h"
#include "pieces.h"
#include "position_history.h"

void remove(vector<Pieces*> &list, const Pieces* value) {
    int i = -1;
    for (Pieces* x : list) {
        i++;
        if (x == value) {
            vector<Pieces*>::iterator a = list.begin() + i;
            list.erase(a);
            return;
        }
            
    }
    std::cout << "The Piece is not in this List of the present pieces on the board\n";
}

// Constructor functions for parent class and 6 child classes (Rook, Knight, Bishop, Queen, King, Pawn)

Pieces::Pieces() {
    bool enPassantCondition = false; // a Pawn move 2 square straight in the first move

    Pieces* tmp = nullptr;
    
    bool latestMove = false; // used for En Passant
    bool firstMove = true; //used for castling
}

Rook::Rook(bool colorWhite, std::string name) {
    this->colorWhite = colorWhite;
    this->name = name;
};

Knight::Knight(bool colorWhite, std::string name) {
    this->colorWhite = colorWhite;
    this->name = name;
}

Bishop::Bishop(bool colorWhite, std::string name) {
    this->colorWhite = colorWhite;
    this->name = name;
}

Queen::Queen(bool colorWhite, std::string name) {
    this->colorWhite = colorWhite;
    this->name = name;
}

King::King(bool colorWhite, std::string name){
    this->colorWhite = colorWhite;
    this->name = name;
}

Pawn::Pawn(bool colorWhite, std::string name) {
    this->colorWhite = colorWhite;
    this->name = name;
}

// ********************finish Constructor functions*****************************

// bool move() functions for 6 child classes (Rook, Knight, Bishop, Queen, King, Pawn)

bool Rook::move() { 
    if ((x2 == x1 && y2 != y1) || (x2 != x1 && y2 == y1)) {
        return true;
    }
    return false;
}

bool Knight::move() {
    if ((abs(x1 - x2) == 1 && abs(y1 - y2) == 2) || (abs(x1 - x2) == 2 && abs(y1 - y2) == 1))
        return true;
    return false;
}

bool Bishop::move() {
    if ((abs(x1 - x2) == abs(y1 - y2)))
        return true;
    return false;
}

bool Queen::move() {
    if ((x2 == x1 && y2 != y1) || (x2 != x1 && y2 == y1) || (abs(x1 - x2) == abs(y1 - y2)))
        return true;
    
    return false;
}

bool King::move() {
    if (firstMove && (x2 == 3 || x2 == 7))  
        return true; // castle
    
    if (x2 == x1 && (y2 == y1 + 1 || y2 == y1 - 1)) 
        return true;
    if (y2 == y1 && (x2 == x1 + 1 || x2 == x1 - 1))
        return true;
    if ((y2 == y1 + 1 || y2 == y1 - 1) && (x2 == x1 + 1 || x2 == x1 - 1))
        return true;
    return false;
}

bool Pawn::move() {
    const int Y1 = 2;
    const int Y2 = 7;
    
    if ((x1 == x2) && abs(y2 - y1) == 2) 
        if ((y1 == Y1 && y2 > y1 && colorWhite) || (y1 == Y2 && y2 < y1 && !colorWhite))
            return true;
        
            
    if ((abs(x1 - x2) == 1 || abs(x1 - x2) == 0) && abs(y2 - y1) == 1) 
        if ((y2 > y1 && colorWhite) || (y2 < y1 && !colorWhite))
            return true;
        
    return false;
}

//******************************finsish bool move() functions*****************************

// bool checkNullSquareBetweenL1L2(Pieces* board[][8]) functions for 6 child classes (Rook, Knight, Bishop, Queen, King, Pawn)


bool Rook::checkNullSquareBetweenL1L2(Pieces* board[][8]) {
    if (x1 == x2) {
        for (int i = y1; abs(i - y2) > 1;) {
            if (y1 > y2) 
                i--;
            else 
                i++;
            
            if (board[i - 1][x1 - 1] != nullptr) 
                return false;    
        }
    } else  { //if (y1 == y2)
        for (int i = x1; abs(i - x2) > 1;) {
            if (x1 > x2)
                i--;
            else 
                i++;
            
            if (board[y1 - 1][i - 1] != nullptr) 
                return false;
        }
    }
    return true;
}

bool Knight::checkNullSquareBetweenL1L2(Pieces* board[][8]) {
    return true;
}

bool Bishop::checkNullSquareBetweenL1L2(Pieces* board[][8]) {
    int i = x1, j = y1;
    for (; abs(i - x2) > 1 && abs(j - y2) > 1;) {
        if (x1 > x2) {
            i--;
        } else {
            i++;
        }
        if (y1 > y2) {
            j--;
        } else {
            j++;
        }
        if (board[j - 1][i - 1] != nullptr) {
            return false;
        }
    }

    return true;
}

bool Queen::checkNullSquareBetweenL1L2(Pieces* board[][8]) {
    if (x1 == x2) {
        for (int i = y1; abs(i - y2) > 1;) {
            if (y1 > y2) {
                i--;
            } else {
                i++;
            }

            if (board[i - 1][x1 - 1] != nullptr) {
                
                return false;
            }
        }
    } else if (y1 == y2) {
        for (int i = x1; abs(i - x2) > 1;) {
            if (x1 > x2) {
                i--;
            } else {
                i++;
            }

            if (board[y1 - 1][i - 1] != nullptr) {
                
                return false;
            }
        }
    } else {
        int i = x1, j = y1;
        for (; abs(i - x2) > 1 && abs(j - y2) > 1;) {
            if (x1 > x2) {
                i--;
            } else {
                i++;
            }

            if (y1 > y2) {
                j--;
            } else {
                j++;
            }

            if (board[j - 1][i - 1] != nullptr) {
                
                return false;
            }
        }
    }
    
    return true;
}

bool King::checkNullSquareBetweenL1L2(Pieces* board[][8]) {
    if (firstMove && (x2 == 3 || x2 == 7)) {
        if ((x2 == 7 && board[y1 - 1][6] == nullptr && board[y1 - 1][5] == nullptr && board[y1 - 1][7]->firstMove) ||
            (x2 == 3 && board[y1 - 1][1] == nullptr && board[y1 - 1][2] == nullptr && board[y1 - 1][3] == nullptr && board[y1 - 1][0]->firstMove))
            return true;    
    
        return false;
    }
    
    return true;
}

bool Pawn::checkNullSquareBetweenL1L2(Pieces* board[][8]) {
    if (x1 == x2) {
        for (int i = y1; abs(i - y2) > 0;) {
            if (y1 > y2) {
                i--;
            } else {
                i++;
            }

            if (board[i - 1][x1 - 1] != nullptr) {
                return false;
            }
        }

        return true;
    }
    return true;
}

//***************bool checkNullSquareBetweenL1L2(Pieces* board[][8]) functions**********************

//bool atLeast1PosibleSquare(vector<Pieces*> enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) functions for 6 child classes (Rook, Knight, Bishop, Queen, King, Pawn)


bool Rook::atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) {
    for (int i = x1 - 1; i > 0; i--) {
        x2 = i;
        y2 = y1;
        
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false)) 
            return true;
        if (board[y2 - 1][x2 - 1] != nullptr) 
            break;
                    
    }
    for (int i = x1 + 1; i < 9; i++) {
        x2 = i;
        y2 = y1;
        
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false)) 
            return true;
        if (board[y2 - 1][x2 - 1] != nullptr) 
            break;
    }

    for (int i = y1 - 1; i > 0; i--) {
        x2 = x1;
        y2 = i;
        
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false)) 
            return true;
        if (board[y2 - 1][x2 - 1] != nullptr) 
            break;
    }

    for (int i = y1 + 1; i < 9; i++) {
        x2 = x1;
        y2 = i;
        
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false)) 
            return true;
        if (board[y2 - 1][x2 - 1] != nullptr) 
            break;
    }

    return false;

}

bool Knight::atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) {
    if (onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 1, y1 - 2) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 1, y1 + 2) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 1, y1 - 2) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 1, y1 + 2) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 2, y1 - 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 2, y1 + 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 2, y1 - 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 2, y1 + 1))
        return true;
    return false;
}

bool Knight::onePossibleSquareSample(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, int n1, int n2){
    if (n1 > 0 && n1 < 9 && n2 > 0 && n2 <9) {
        x2 = n1;
        y2 = n2;
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
            return true;
    }
    return false;
}

bool Bishop::atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) {
    count = 1;
    for (int i = x1 - 1; i > 0; i--) {
        
        int j = y1 - count;
        x2 = i;
        y2 = j;
        if (j < 1)
            break;
        else {
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            if (board[y2 - 1][x2 - 1] != nullptr) 
                break;
                
        }
        count++;   
    }
    count = 1;
    for (int i = x1 - 1; i > 0; i--) {
        
        int j = y1 + count;
        x2 = i;
        y2 = j;
        if (j > 8)
            break;
        else {
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            if (board[y2 - 1][x2 - 1] != nullptr) 
                break;
                
        }
        count++;   
    }
    count = 1;
    for (int i = x1 + 1; i < 9; i++) {
        
        int j = y1 - count;
        x2 = i;
        y2 = j;
        if (j < 1)
            break;
        else {
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            if (board[y2 - 1][x2 - 1] != nullptr) 
                break;
                
        }
        count++;   
    }
    count = 1;
    for (int i = x1 + 1; i < 9; i++) {
        
        int j = y1 + count;
        x2 = i;
        y2 = j;
        if (j > 8)
            break;
        else {
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            if (board[y2 - 1][x2 - 1] != nullptr) 
                break;
                
        }
        count++;   
    }
    return false;
}

bool Queen::atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) {
    for (int i = x1 - 1; i > 0; i--) {
        x2 = i;
        y2 = y1;
        
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false)) 
            return true;
        if (board[y2 - 1][x2 - 1] != nullptr) 
            break;
                    
    }
    for (int i = x1 + 1; i < 9; i++) {
        x2 = i;
        y2 = y1;
        
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false)) 
            return true;
        if (board[y2 - 1][x2 - 1] != nullptr) 
            break;
    }

    for (int i = y1 - 1; i > 0; i--) {
        x2 = x1;
        y2 = i;
        
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false)) 
            return true;
        if (board[y2 - 1][x2 - 1] != nullptr) 
            break;
    }

    for (int i = y1 + 1; i < 9; i++) {
        x2 = x1;
        y2 = i;
        
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false)) 
            return true;
        if (board[y2 - 1][x2 - 1] != nullptr) 
            break;
    }
    
    count = 1;
    for (int i = x1 - 1; i > 0; i--) {
        
        int j = y1 - count;
        x2 = i;
        y2 = j;
        if (j < 1)
            break;
        else {
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            if (board[y2 - 1][x2 - 1] != nullptr) 
                break;        
        }
        count++;   
    }

    count = 1;
    for (int i = x1 - 1; i > 0; i--) {
        
        int j = y1 + count;
        x2 = i;
        y2 = j;
        if (j > 8)
            break;
        else {
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            if (board[y2 - 1][x2 - 1] != nullptr) 
                break;       
        }
        count++;   
    }

    count = 1;
    for (int i = x1 + 1; i < 9; i++) {
        
        int j = y1 - count;
        x2 = i;
        y2 = j;
        if (j < 1)
            break;
        else {
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            if (board[y2 - 1][x2 - 1] != nullptr) 
                break;       
        }
        count++;   
    }

    count = 1;
    for (int i = x1 + 1; i < 9; i++) {
        
        int j = y1 + count;
        x2 = i;
        y2 = j;
        if (j > 8)
            break;
        else {
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            if (board[y2 - 1][x2 - 1] != nullptr) 
                break;        
        }
        count++;   
    }
    return false;
}

bool King::atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) {
    if (onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1, y1 - 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1, y1 + 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 1, y1 - 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 1, y1 + 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 1, y1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 1, y1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 1, y1 - 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 1, y1 + 1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, 2, y1) ||
        onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, 6, y1))
        
        return true;
    return false;
}

bool King::onePossibleSquareSample(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, int k1, int k2) {
    if (k1 > 0 && k1 < 9 && k2 > 0 && k2 <9) {
        x2 = k1;
        y2 = k2;
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
            return true;
    }
    return false;
}

bool Pawn::atLeast1PossibleSquare(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) {
    if (firstMove) {
        x2 = x1;
        if (colorWhite) {
            y2 = 3;
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            y2 = 4;
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
        }
        else {
            y2 = 6;
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
            y2 = 5;
            if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
                return true;
        }       
    }
    else {
        if (colorWhite && (onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 1, y1 + 1) || onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 1, y1 + 1)))
            return true;
        if (!colorWhite && (onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 - 1, y1 - 1) || onePossibleSquareSample(enemyPiecesOnTheBoard, board, king, x1 + 1, y1 - 1)))
            return true;
    }
    return false;
}

bool Pawn::onePossibleSquareSample(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, int p1, int p2) {
    if (p1 > 0 && p1 < 9 && p2 > 0 && p2 < 9) {
        x2 = p1;
        y2 = p2;
        if (moveOnTheBoard(enemyPiecesOnTheBoard, board, king, false))
            return true;
    }
    return false;
}

//*****************************finsih bool atLeast1PosibleSquare(....) functions*********************************

//bool checkTheOtherKing(Pieces* board[][8], Pieces* king) functions for 6 child classes (Rook, Knight, Bishop, Queen, King, Pawn)


bool Rook::checkTheOtherKing(Pieces* board[][8], Pieces* king) {
    for (int i = x1 - 1; i > 0; i--) {
        if (board[y1 - 1][i - 1] != nullptr) {

            if (board[y1 - 1][i - 1] == king) {
                return true;
            }  
            break;

        }
    }
    for (int i = x1 + 1; i < 9; i++) {
        if (board[y1 - 1][i - 1] != nullptr) {

            if (board[y1 - 1][i - 1] == king) {
                return true;
            }                
            break;
        }
    }

    for (int i = y1 - 1; i > 0; i--) {
        if (board[i - 1][x1 - 1] != nullptr) {

            if (board[i - 1][x1 - 1] == king) {
                return true;
            }
            break;

        }
    }

    for (int i = y1 + 1; i < 9; i++) {
        if (board[i - 1][x1 - 1] != nullptr) {

            if (board[i - 1][x1 - 1] == king) {
                return true;
            }                
            break;
        }
    }

    return false;
}

bool Knight::checkTheOtherKing(Pieces* board[][8], Pieces* king) {
    if (checkTheOtherKingSample(board, king, x1 - 1, y1 - 2) ||
        checkTheOtherKingSample(board, king, x1 - 1, y1 + 2) ||
        checkTheOtherKingSample(board, king, x1 + 1, y1 - 2) ||
        checkTheOtherKingSample(board, king, x1 + 1, y1 + 2) ||
        checkTheOtherKingSample(board, king, x1 - 2, y1 - 1) ||
        checkTheOtherKingSample(board, king, x1 - 2, y1 + 1) ||
        checkTheOtherKingSample(board, king, x1 + 2, y1 - 1) ||
        checkTheOtherKingSample(board, king, x1 + 2, y1 + 1))
        return true;
    return false;
}

bool Knight::checkTheOtherKingSample(Pieces* board[][8], Pieces* king, int n1, int n2) { // real-life next location  of the knight
    if (n1 > 0 && n1 < 9 && n2 > 0 && n2 <9 && board[n2 - 1][n1 - 1] == king) {
        return true;
    }
    return false;
}

bool Bishop::checkTheOtherKing(Pieces* board[][8], Pieces* king) {
    count = 1;
    for (int i = x1 - 1; i > 0; i--) {
        
        int j = y1 - count;
        if (j < 1)
            break;
        else {
            if (board[j - 1][i - 1] != nullptr) {
                
                if (board[j - 1][i - 1] == king)
                    return true;
                break;
            }     
        }
        count++;   
    }
    count = 1;
    for (int i = x1 - 1; i > 0; i--) {
        
        int j = y1 + count;
        if (j > 8)
            break;
        else {
            if (board[j - 1][i - 1] != nullptr) {
                
                if (board[j - 1][i - 1] == king)
                    return true;
                break;
            }     
        }
        count++;   
    }
    count = 1;
    for (int i = x1 + 1; i < 9; i++) {
        
        int j = y1 - count;
        if (j < 1)
            break;
        else {
            if (board[j - 1][i - 1] != nullptr) {
                
                if (board[j - 1][i - 1] == king)
                    return true;
                break;
            }     
        }
        count++;   
    }
    count = 1;
    for (int i = x1 + 1; i < 9; i++) {
        
        int j = y1 + count;
        if (j > 8)
            break;
        else {
            if (board[j - 1][i - 1] != nullptr) {
                
                if (board[j - 1][i - 1] == king)
                    return true;
                break;
            }     
        }
        count++;   
    }
    return false;
}

bool Queen::checkTheOtherKing(Pieces* board[][8], Pieces* king) {
    for (int i = x1 - 1; i > 0; i--) {
        if (board[y1 - 1][i - 1] != nullptr) {

            if (board[y1 - 1][i - 1] == king) 
                return true;
            break;

        }
    }
    for (int i = x1 + 1; i < 9; i++) {
        if (board[y1 - 1][i - 1] != nullptr) {

            if (board[y1 - 1][i - 1] == king)
                return true;
            break;
        }
    }

    for (int i = y1 - 1; i > 0; i--) {
        if (board[i - 1][x1 - 1] != nullptr) {

            if (board[i - 1][x1 - 1] == king)
                return true;
            break;

        }
    }

    for (int i = y1 + 1; i < 9; i++) {
        if (board[i - 1][x1 - 1] != nullptr) {

            if (board[i - 1][x1 - 1] == king) 
                return true;
            break;
        }
    }
    count = 1;
    for (int i = x1 - 1; i > 0; i--) {
        
        int j = y1 - count;
        if (j < 1)
            break;
        else {
            if (board[j - 1][i - 1] != nullptr) {
                
                if (board[j - 1][i - 1] == king)
                    return true;
                break;
            }     
        }
        count++;   
    }
    count = 1;
    for (int i = x1 - 1; i > 0; i--) {
        
        int j = y1 + count;
        if (j > 8)
            break;
        else {
            if (board[j - 1][i - 1] != nullptr) {
                
                if (board[j - 1][i - 1] == king)
                    return true;
                break;
            }   
            
        }
        count++;   
    }
    count = 1;
    for (int i = x1 + 1; i < 9; i++) {
        
        int j = y1 - count;
        if (j < 1)
            break;
        else {
            if (board[j - 1][i - 1] != nullptr) {
                
                if (board[j - 1][i - 1] == king)
                    return true;
                break;
            }     
        }
        count++;   
    }
    count = 1;
    for (int i = x1 + 1; i < 9; i++) {
        
        int j = y1 + count;
        if (j > 8)
            break;
        else {
            if (board[j - 1][i - 1] != nullptr) {
                
                if (board[j - 1][i - 1] == king)
                    return true;
                break;
            }     
        }
        count++;   
    }
    
    return false;

}

bool King::checkTheOtherKing(Pieces* board[][8], Pieces* king) {
    if (checkTheOtherKingSample(board, king, x1, y1 - 1) ||
        checkTheOtherKingSample(board, king, x1, y1 + 1) ||
        checkTheOtherKingSample(board, king, x1 - 1, y1 - 1) ||
        checkTheOtherKingSample(board, king, x1 - 1, y1 + 1) ||
        checkTheOtherKingSample(board, king, x1 - 1, y1) ||
        checkTheOtherKingSample(board, king, x1 + 1, y1) ||
        checkTheOtherKingSample(board, king, x1 + 1, y1 - 1) ||
        checkTheOtherKingSample(board, king, x1 + 1, y1 + 1))
        return true;
    return false;
}
bool King::checkTheOtherKingSample(Pieces* board[][8], Pieces* king, int k1, int k2) { // real-life next location  of the king
    if (k1 > 0 && k1 < 9 && k2 > 0 && k2 < 9 && (board[k2 - 1][k1 - 1] == king)) {
        return true;
    }
    return false;
}

bool Pawn::checkTheOtherKing(Pieces* board[][8], Pieces* king) {
    if (colorWhite && (checkTheOtherKingSample(board, king, x1 - 1, y1 + 1) || checkTheOtherKingSample(board, king, x1 + 1, y1 + 1)))
        return true;
    if (!colorWhite && (checkTheOtherKingSample(board, king, x1 - 1, y1 - 1) || checkTheOtherKingSample(board, king, x1 + 1, y1 - 1)))
        return true;
    return false;
}

bool Pawn::checkTheOtherKingSample(Pieces* board[][8], Pieces* king, int x, int y) { // x = x1 +- 1; y = +- 1;
    if (x > 0 && x < 9 && y > 0 && y < 9 && board[y - 1][x - 1] != nullptr && board[y - 1][x - 1] == king)
        return true;
    return false;
        
}

//***********************finsih bool checkTheOtherKing(Pieces* board[][8], Pieces* king) functions****************

// override functions of class Pawn

bool Pawn::moveOnTheBoard(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, bool print) {
    if (move() == false || checkNullSquareBetweenL1L2(board) == false) {
        if (print) 
            std::cout << "You can not move this onec211. Try again\n";
        return false;
    }

    if (x1 == x2) {
        board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
        board[y1 - 1][x1 - 1] = nullptr;
        
        if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = nullptr;
            if (print)
                std::cout << "Your King will be checked. Try again\n";
            return false;
        }
        
        if (print && abs(y2 - y1) == 2)
            this->enPassantCondition = true;
        if (!print) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = nullptr;
        }
    } else {
        if (board[y2 - 1][x2 - 1] != nullptr) {
            if (board[y2 - 1][x2 - 1]->colorWhite == king->colorWhite) {
                if (print) {
                    std::cout << "You can not move this one. Try again\n";
                }
                return false;
            }
    
            // y2x2 bị ăn
            tmp = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
            board[y1 - 1][x1 - 1] = nullptr;
            remove(enemyPiecesOnTheBoard, tmp);

            if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
                board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
                board[y2 - 1][x2 - 1] = tmp;
                enemyPiecesOnTheBoard.push_back(tmp);
                if (print) {
                    std::cout << "Your King will be checked. Try again\n";
                }
                return false;
            }
            // remove the piece killed
            if (!print) {

                board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
                board[y2 - 1][x2 - 1] = tmp;
                enemyPiecesOnTheBoard.push_back(tmp);
            }
        }
        else if (enPassant(enemyPiecesOnTheBoard, board, king, print, x2)) // x2 luon cx dc = x1 +- 1;
            return true;
        else {
            if (print) 
                std::cout << "You can not move this Pawn\n";
            return false;
        }
        
    }
    if (print) {
        board[y2 - 1][x2 - 1]->x1 = x2;
        board[y2 - 1][x2 - 1]->y1 = y2;
    }
    
    return true;
}

void Pawn::moveOnTheBoardVer2(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8]) {
    if (x1 == x2) {
        board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
        board[y1 - 1][x1 - 1] = nullptr;

        if (abs(y2 - y1) == 2)
            enPassantCondition = true;
        else
            enPassantCondition = false;
    } else {
        if (board[y2 - 1][x2 - 1] != nullptr) {
            
            tmp = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
            board[y1 - 1][x1 - 1] = nullptr;
            remove(enemyPiecesOnTheBoard, tmp);

        } else {
            board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
            board[y1 - 1][x1 - 1] = nullptr;
            tmp = board[y1 - 1][x2 - 1];
            board[y1 - 1][x2 - 1] = nullptr;
            remove(enemyPiecesOnTheBoard, tmp);
        } 
        enPassantCondition = false;
    }
    board[y2 - 1][x2 - 1]->firstMove = false;
    board[y2 - 1][x2 - 1]->x1 = x2;
    board[y2 - 1][x2 - 1]->y1 = y2;

}

bool Pawn::enPassant(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, bool print, int a) {
    if (abs(x1 - x2) != 1 || (colorWhite && y1 != 5) || (!colorWhite && y1 != 4))
        return false;
    if (a > 0 && a < 9 && board[y1 - 1][a - 1]->enPassantCondition && board[y1 - 1][a - 1]->latestMove) {
        board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
        board[y1 - 1][x1 - 1] = nullptr;
        tmp = board[y1 - 1][a - 1];
        board[y1 - 1][a - 1] = nullptr;
        remove(enemyPiecesOnTheBoard, tmp);
        if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = nullptr;
            board[y1 - 1][a - 1] = tmp;
            enemyPiecesOnTheBoard.push_back(tmp);
            if (print) {
                std::cout << "Your King will be checked. Try again\n";
            }
            return false;
        }
        if (!print) { 
            enemyPiecesOnTheBoard.push_back(tmp);
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = nullptr;
            board[y1 - 1][a - 1] = tmp;
        } else {
            //if (board [y2 - 1][x2 - 1] != null) { // for not null pointer exception
                board[y2 - 1][x2 - 1]->x1 = x2;
                board[y2 - 1][x2 - 1]->y1 = y2;
        }
        return true;
    }
    if (print) {
        if (!board[y1 - 1][a - 1]->latestMove)
            std::cout << "latest move false\n";
        if (!board[y1 - 1][a - 1]->enPassantCondition)
            std::cout << "enPassant false";
        
    }       
    return false;
        
}

//*********************************finish override functions of class Pawn**********************************************

// override functions of class King

bool King::moveOnTheBoard(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, bool print) {
    if (move() == false || checkNullSquareBetweenL1L2(board) == false) { 
        if (print) 
            std::cout << "You can not move this onec2. Try again\n";
        return false;
    }
    if (firstMove && (x2 == 3 || x2 == 7)) {
        // castle
        if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
            if (print)
                std::cout << "Your king is checked, you can't castle\n";
            return false;
        }
        if (x2 == 7) {
            board[y1 - 1][6] = king;
            board[y1 - 1][5] = board[y1 - 1][7];
            board[y1 - 1][4] = nullptr;
            board[y1 - 1][7] = nullptr;
            
            if(theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
                board[y1 - 1][4] = king;
                board[y1 - 1][7] = board[y1 - 1][2];
                board[y1 - 1][6] = nullptr;
                board[y1 - 1][5] = nullptr;
                if (print)
                    std::cout << "Your King will be checked. Try again\n";
                return false;
            }
            if (!print) {
                board[y1 - 1][4] = king;
                board[y1 - 1][7] = board[y1 - 1][2];
                board[y1 - 1][6] = nullptr;
                board[y1 - 1][5] = nullptr;
            } else {
                king->x1 = 7;
                board[y1 - 1][5]->x1 = 6;
                king->firstMove = false;
                board[y1 - 1][5]->firstMove = false;
            }
            return true;
            
        }
        // x2 == 3
        board[y1 - 1][2] = king;
        board[y1 - 1][3] = board[y1 - 1][0];
        board[y1 - 1][0] = nullptr;
        board[y1 - 1][4] = nullptr;

        if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
            board[y1 - 1][4] = king;
            board[y1 - 1][0] = board[y1 - 1][3];
            board[y1 - 1][2] = nullptr;
            board[y1 - 1][3] = nullptr;
            if (print)
                std::cout << "Your King will be checked. Try again\n";
            return false;
        }
        if (!print) {
            board[y1 - 1][4] = king;
            board[y1 - 1][0] = board[y1 - 1][3];
            board[y1 - 1][2] = nullptr;
            board[y1 - 1][3] = nullptr;
        } else {
            king->x1 = 3;
            board[y1 - 1][3]->x1 = 4;
            king->firstMove = false;
            board[y1 - 1][3]->firstMove = false;
        }
        return true;
    }

    if (board[y2 - 1][x2 - 1] != nullptr) {
        if (board[y2 - 1][x2 - 1]->colorWhite == king->colorWhite) {
            if (print)
                std::cout << "You can not move this one. Try again\n";
            return false;
        }

        // y2x2 bị ăn
        tmp = board[y2 - 1][x2 - 1];
        board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
        board[y1 - 1][x1 - 1] = nullptr;
        remove(enemyPiecesOnTheBoard, tmp);

        if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = tmp;
            enemyPiecesOnTheBoard.push_back(tmp);
            if (print)
                std::cout << "Your King will be checked. Try again\n";
            return false;
        }
        
        
        if (!print) {
            
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = tmp;
            enemyPiecesOnTheBoard.push_back(tmp);
        }
        else {
            king->firstMove = false;
        }
        

    } else {
        board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
        board[y1 - 1][x1 - 1] = nullptr;

        if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = nullptr;
            if (print)
                std::cout << "Your King will be checked. Try again\n";
            return false;
            
        }
        if (!print) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = nullptr;
        } 
        else 
            king->firstMove = false;

    }
    if (print) {
        board[y2 - 1][x2 - 1]->x1 = x2;
        board[y2 - 1][x2 - 1]->y1 = y2;
    }

    return true;
      
}

void King::moveOnTheBoardVer2(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8]) {
    if (firstMove && (x2 == 3 || x2 == 7)) {
        // castle
        if (x2 == 7) {
            board[y1 - 1][6] = board[y1 - 1][x1 - 1]; // king y1 x1
            board[y1 - 1][5] = board[y1 - 1][7];
            board[y1 - 1][4] = nullptr;
            board[y1 - 1][7] = nullptr;
            
            
            board[y1 - 1][6]->x1 = 7;
            board[y1 - 1][5]->x1 = 6;
            board[y1 - 1][6]->firstMove = false;
            board[y1 - 1][5]->firstMove = false;
        } else {
            board[y1 - 1][2] = board[y1 - 1][x1 - 1];
            board[y1 - 1][3] = board[y1 - 1][0];
            board[y1 - 1][0] = nullptr;
            board[y1 - 1][4] = nullptr;
            
            board[y1 - 1][2]->x1 = 3;
            board[y1 - 1][3]->x1 = 4;
            board[y1 - 1][2]->firstMove = false;
            board[y1 - 1][3]->firstMove = false;
        }
    }
    else {
        tmp = board[y2 - 1][x2 - 1];
        board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
        board[y1 - 1][x1 - 1] = nullptr;
        if (tmp != nullptr) {
            remove(enemyPiecesOnTheBoard, tmp);
        }
        board[y2 - 1][x2 - 1]->firstMove = false;
        board[y2 - 1][x2 - 1]->x1 = x2;
        board[y2 - 1][x2 - 1]->y1 = y2;
    }
        
}

//*********************************finish override functions of class King**********************************************

// functions of class Pieces

bool Pieces::moveOnTheBoard(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king, bool print) {
    if (move() == false || checkNullSquareBetweenL1L2(board) == false) { 
        if (print) 
            std::cout <<"You can not move this one. Try again\n";
        return false;
    }
       
    if (board[y2 - 1][x2 - 1] != nullptr) {
        if (board[y2 - 1][x2 - 1]->colorWhite == king->colorWhite) {
            if (print)
                std::cout <<"You can not move this one. Try again\n";
            return false;
        }

        // y2x2 bị ăn
        tmp = board[y2 - 1][x2 - 1];
        board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
        board[y1 - 1][x1 - 1] = nullptr;
        remove(enemyPiecesOnTheBoard, tmp);
       
        if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = tmp;
            enemyPiecesOnTheBoard.push_back(tmp);
            if (print)
                std::cout << "Your King will be checked. Try again22\n"; 

            return false;
        }
        
        if (!print) {
            
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = tmp;
            enemyPiecesOnTheBoard.push_back(tmp);
        }    

    }
    else {
        board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
        board[y1 - 1][x1 - 1] = nullptr;

        if (theKingIsChecked(enemyPiecesOnTheBoard, board, king)) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = nullptr;
            if (print)
                std::cout << "Your King will be checked. Try again\n";
                
            return false;
        }
        if (!print) {
            board[y1 - 1][x1 - 1] = board[y2 - 1][x2 - 1];
            board[y2 - 1][x2 - 1] = nullptr;
        }

    }
    if (print) {
        board[y2 - 1][x2 - 1]->firstMove = false;
        board[y2 - 1][x2 - 1]->x1 = x2;
        board[y2 - 1][x2 - 1]->y1 = y2;
    }
    
    return true;
}

void Pieces::moveOnTheBoardVer2(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8]) {
    tmp = board[y2 - 1][x2 - 1];
    board[y2 - 1][x2 - 1] = board[y1 - 1][x1 - 1];
    board[y1 - 1][x1 - 1] = nullptr;
    if (tmp != nullptr)
        remove(enemyPiecesOnTheBoard, tmp);
    board[y2 - 1][x2 - 1]->firstMove = false;
    board[y2 - 1][x2 - 1]->x1 = x2;
    board[y2 - 1][x2 - 1]->y1 = y2;
}

bool Pieces::theKingIsChecked(vector<Pieces*> &enemyPiecesOnTheBoard, Pieces* board[][8], Pieces* king) {
    for (Pieces* x : enemyPiecesOnTheBoard) {
        if (x->checkTheOtherKing(board, king)) {
            return true;
        }       
    }
    return false;
    
}

//************************************finish functions of class Pieces*************************************************