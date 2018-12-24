
//#include <bits/stdc++.h>
#include <stdio.h>

typedef long long int ll;

class board{

public :
    board(){

        printf("Welcome to Othello World!\n");

        printf("Initialize...");

        this->black = 0x0000000810000000;
        this->white = 0x0000001008000000;
        // ***********0x1121314151617181;

        printf("complete!\n");
    }

    ll positionToBit( char y, char x ){
        // y 縦 12345678
        // x 横 ABCDEFGH
        // return Bit
        // example : E5 -> 0x0000000008000000
        ll mask = 0x8000000000000000;
        // mask = A1
        mask >>= (y-0x41);
        // mask = N1
        mask >>= (x-0x31) << 3;
        return mask;
    }

private :
    ll black;
    ll white;
    //bit map(board) の使用
    //いろいろ高速かつ簡単にできる
};

int main(){

    board Board;

    printf ("%lld\n", Board.positionToBit('A','3'));

}

