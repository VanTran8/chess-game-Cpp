#ifndef POSITION_HISTORY_H
#define POSITION_HISTORY_H

class Position {
public:
    Position (int x1, int y1, int x2, int y2, int promote);

    int getX1();
    int getX2();
    int getY1();
    int getY2();
    int getPromote();

private:
    int x1, y1, x2, y2;
    int promote;


};

#endif