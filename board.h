
//#include <bits/stdc++.h>
#include <stdio.h>

typedef long long int ll;

class board{

public :
    board(){};
    // E5 とか座標を受け取り、ビットデータで返す
    ll positionToBit( char y, char x );
    // 置ける範囲を返す
    ll SetableBoard();
    // 変位を求める putから1ずらしたのを返す
    ll Displace( ll put , int flag );
    // yxに駒を置く
    void SetBoard( char y, char x );
    // llで設定もできる
    void SetBoard( ll putpos );
    // 終了判定（パス込）
    bool isEnd();
    // 盤面の出力
    void printBoard();

private :
    ll plpos; // 打ち手
    ll oppos; // 受け手
    int TurnNumber; // ターン数
    int TurnPlayer; // どっちターン 0:o 1:x 最初はoから
    //bit map(board) の使用
    //いろいろ高速かつ簡単にできる
    //右 >>1、左 <<1、下 >>8、上 <<8
};