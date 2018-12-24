//#include <bits/stdc++.h>
#include <stdio.h>

typedef long long unsigned int ll;

class board{

public :
    board(){
        printf("Welcome to Othello World!\n");
        printf("Initialize...");

        this->plpos = 0x0000000810000000;
        this->oppos = 0x0000001008000000;
        // ***********0x1121314151617181;

        printf("complete!\n");
    }

    // E5 とか座標を受け取り、ビットデータで返す
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

    // 置ける範囲を返す
    ll SetableBoard(){
        //番人を活用
        //
        // 横の番人
        ll horizenWatcher = this->oppos & 0x7e7e7e7e7e7e7e7e;
        // 縦の番人
        ll verticalWatcher = this->oppos & 0x00FFFFFFFFFFFF00;
        // 斜の番人 (縦&横)
        ll bothWatcher = this->oppos & 0x007e7e7e7e7e7e00;
        //
        // 空きのマス(1:空き)
        ll blackBoard = ~( this->oppos | this->plpos );

        // 一時データ
        ll tmp;
        // 返り値データ
        ll reversible = 0;

        // チェックだ！ {{{
        // 例　左
        // 敵01111010 (番人済)
        // 自00000100
        // 自を左にずらして
        // 敵01111010
        // 自00001000
        // 当たったら残す
        // 仮00001000 <- tmp
        // あとはtmoを左にずらし、当たったら...を繰り返す(6回)
        // 01111000 (最終形)
        // 最後に置く場所がblankなら設置可能となり、返り値に加える
        // (なんでこんなのおもいつくの)
        // }}}
        // すごい長いチェック {{{
        // 左
        tmp = horizenWatcher & (this->plpos << 1);
        tmp |= horizenWatcher & (tmp << 1);
        tmp |= horizenWatcher & (tmp << 1);
        tmp |= horizenWatcher & (tmp << 1);
        tmp |= horizenWatcher & (tmp << 1);
        tmp |= horizenWatcher & (tmp << 1);
        reversible |= blackBoard & (tmp << 1);
        // 右
        tmp = horizenWatcher & (this->plpos >> 1);
        tmp |= horizenWatcher & (tmp >> 1);
        tmp |= horizenWatcher & (tmp >> 1);
        tmp |= horizenWatcher & (tmp >> 1);
        tmp |= horizenWatcher & (tmp >> 1);
        tmp |= horizenWatcher & (tmp >> 1);
        reversible |= blackBoard & (tmp >> 1);
        // 下
        tmp = verticalWatcher & (this->plpos << 8);
        tmp |= verticalWatcher & (tmp << 8);
        tmp |= verticalWatcher & (tmp << 8);
        tmp |= verticalWatcher & (tmp << 8);
        tmp |= verticalWatcher & (tmp << 8);
        tmp |= verticalWatcher & (tmp << 8);
        reversible |= blackBoard & (tmp << 8);
        // 上
        tmp = verticalWatcher & (this->plpos >> 8);
        tmp |= verticalWatcher & (tmp >> 8);
        tmp |= verticalWatcher & (tmp >> 8);
        tmp |= verticalWatcher & (tmp >> 8);
        tmp |= verticalWatcher & (tmp >> 8);
        tmp |= verticalWatcher & (tmp >> 8);
        reversible |= blackBoard & (tmp >> 8);
        // 左下
        tmp = bothWatcher & (this->plpos << 9);
        tmp |= bothWatcher & (tmp << 9);
        tmp |= bothWatcher & (tmp << 9);
        tmp |= bothWatcher & (tmp << 9);
        tmp |= bothWatcher & (tmp << 9);
        tmp |= bothWatcher & (tmp << 9);
        reversible |= blackBoard & (tmp << 9);
        // 左上
        tmp = bothWatcher & (this->plpos >> 7);
        tmp |= bothWatcher & (tmp >> 7);
        tmp |= bothWatcher & (tmp >> 7);
        tmp |= bothWatcher & (tmp >> 7);
        tmp |= bothWatcher & (tmp >> 7);
        tmp |= bothWatcher & (tmp >> 7);
        reversible |= blackBoard & (tmp >> 7);
        // 右下
        tmp = bothWatcher & (this->plpos << 7);
        tmp |= bothWatcher & (tmp << 7);
        tmp |= bothWatcher & (tmp << 7);
        tmp |= bothWatcher & (tmp << 7);
        tmp |= bothWatcher & (tmp << 7);
        tmp |= bothWatcher & (tmp << 7);
        reversible |= blackBoard & (tmp << 7);
        // 右上
        tmp = bothWatcher & (this->plpos >> 9);
        tmp |= bothWatcher & (tmp >> 9);
        tmp |= bothWatcher & (tmp >> 9);
        tmp |= bothWatcher & (tmp >> 9);
        tmp |= bothWatcher & (tmp >> 9);
        tmp |= bothWatcher & (tmp >> 9);
        reversible |= blackBoard & (tmp >> 9);
        // }}}

        return reversible;

    }

    void printBoard(){
        for( ll i = 1; i != 0; i<<=1 ){
            // 先手o　後手x　ブランク-
            if( i & plpos ) printf ("o");
            else if( i & oppos ) printf ("x");
            else printf ("-");
            // 程よく改行
            if( i & 0x8080808080808080 ) printf("\n");
        }
    }

private :
    ll plpos;
    ll oppos;
    //bit map(board) の使用
    //いろいろ高速かつ簡単にできる
    //右 >>1、左 <<1、下 >>8、上 <<8
};

int main(){

    board Board;
    Board.printBoard();

}
