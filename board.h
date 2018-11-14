
#include <map>

#ifndef BOARD_H
#define BOARD_H

class board{

public :
    board();
    ~board();
    int set( int color, int x, int y);
    void show();

private :
    int block[10][10] = {{}};
    char block_char[10] = {};

};

#endif // BOARD_H