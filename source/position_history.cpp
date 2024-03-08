#include "position_history.h"
    
Position::Position (int x1, int y1, int x2, int y2, int promote) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->promote = promote;
}

int Position::getX1() {
    return x1;
}
int Position::getX2() {
    return x2;
}
int Position::getY1() {
    return y1;
}
int Position::getY2() {
    return y2;
}
int Position::getPromote() {
    return promote;
}

