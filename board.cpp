//#include <bits/stdc++.h>
#include <stdio.h>
#include <utility>
#include <random>
#include <ctime>

typedef long long unsigned int ll;

char SmallToCap( char A ){
    if( A >= 'a' && A <= 'z' ) A-=0x20;
    return A;
}

class board{

public :
    board(){
        printf("Welcome to Othello World!\n");
        printf("Initialize...");

        this->plpos = 0x0000000810000000;
        this->oppos = 0x0000001008000000;
        // ***********0x1121314151617181;
        this->TurnNumber = 0;
        this->TurnPlayer = 0;

        printf("complete!\n");
    }
    // E5 g3とか座標を受け取り、ビットデータで返す
    ll positionToBit( char x, char y ){
        // y 縦 12345678
        // x 横 ABCDEFGH
        x = SmallToCap(x);
        //入力がちゃんとしているか見る
        if( x<'A' || x>'H' || y<'1' || y>'8' ) return 0;
        // return Bit
        // example : E5 -> 0x0000000008000000
        ll mask = 0x8000000000000000;
        // mask = A1
        mask >>= (x-0x41);
        // mask = N1
        mask >>= (y-0x31) << 3;
        return mask;
    }
    // 置ける範囲を返す
    ll SetableBoard(){
        // 番人を活用
        // 置かないとKGB(ループ)が発生する
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
        // あとはtmpを左にずらし、当たったら...を繰り返す(6回)
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
    // 変位を求める putから1ずらしたのを返す
    ll Displace( ll put , int flag ){
        /*
         * 210
         * 3p7
         * 456
         */
        switch ( flag ){
            case 0:
                return ( put >> 7 ) & 0x00fefefefefefefe;
            case 1:
                return ( put >> 8 ) & 0x00ffffffffffffff;
            case 2:
                return ( put >> 9 ) & 0x007f7f7f7f7f7f7f;
            case 3:
                return ( put >> 1 ) & 0x7f7f7f7f7f7f7f7f;
            case 4:
                return ( put << 7 ) & 0x7f7f7f7f7f7f7f00;
            case 5:
                return ( put << 8 ) & 0xffffffffffffff00;
            case 6:
                return ( put << 9 ) & 0xfefefefefefefe00;
            case 7:
                return ( put << 1 ) & 0xfefefefefefefefe;
            default:
                break;
        }
    }
    // yxに駒を置く （オーバーロード）
    void SetBoard( char y, char x ){
        ll putpos = positionToBit(y,x);
        SetBoard( putpos );
    }
    // llに駒を置く (本番)
    void SetBoard( ll putpos ){
        if( putpos & (this->oppos | this->plpos) ) return;
        // ひっくり返せる位置
        ll revers = 0;
        // ひっくり返そうとする位置(1bit)
        ll mask = 0;
        // ８方向しっかり調べる
        for( int fi = 0; fi < 8; fi++ ){
            // 動的にひっくり返す位置を把握
            ll prerevers = 0;
            mask = Displace( putpos, fi);
            // 敵の駒があるまで繰り返す
            while( mask & this->oppos ){
                // あったらずらして再調査
                prerevers |= mask;
                mask = Displace( mask , fi );
            }
            // 最後の位置が自分の駒ならひっくり返すに追加
            if( mask & this->plpos ){
                revers |= prerevers;
            }
        }
        //ひっくり返すのがないなら何もなく返す
        if( revers == 0 ){
            return;
        }
        // いざひっくり返す
        this->plpos ^= revers | putpos;
        this->oppos ^= revers;
        this->TurnNumber += 1;
        TurnSwap();
    }
    // 番の切り替え
    void TurnSwap(){
        this->TurnPlayer ^= 1;
        std::swap( this->plpos, this->oppos );
    }
    // 終了判定（パス込）
    bool isEnd(){
        if( this->SetableBoard() == 0 ){
            this->TurnSwap();
            if( this->SetableBoard() == 0 ){
                if( TurnPlayer ) this->TurnSwap();
                return true;
            }
        }
        return false;
    }
    // plposの数
    ll plNumber(){
        // 分割統治法で解く
        ll number = this->plpos;
        number = ( number & 0x5555555555555555) + (( number & 0xAAAAAAAAAAAAAAAA ) >> 1);
        number = ( number & 0x3333333333333333) + (( number & 0xCCCCCCCCCCCCCCCC ) >> 2);
        number = ( number & 0x0F0F0F0F0F0F0F0F) + (( number & 0xF0F0F0F0F0F0F0F0 ) >> 4);
        number = ( number & 0x00FF00FF00FF00FF) + (( number & 0xFF00FF00FF00FF00 ) >> 8);
        number = ( number & 0x0000FFFF0000FFFF) + (( number & 0xFFFF0000FFFF0000 ) >> 16);
        number = ( number & 0x00000000FFFFFFFF) + (( number & 0xFFFFFFFF00000000 ) >> 32);
        return number;
    }
    // opposの数
    ll opNumber(){
        // 分割統治法で解く
        ll number = this->oppos;
        number = ( number & 0x5555555555555555) + (( number & 0xAAAAAAAAAAAAAAAA ) >> 1);
        number = ( number & 0x3333333333333333) + (( number & 0xCCCCCCCCCCCCCCCC ) >> 2);
        number = ( number & 0x0F0F0F0F0F0F0F0F) + (( number & 0xF0F0F0F0F0F0F0F0 ) >> 4);
        number = ( number & 0x00FF00FF00FF00FF) + (( number & 0xFF00FF00FF00FF00 ) >> 8);
        number = ( number & 0x0000FFFF0000FFFF) + (( number & 0xFFFF0000FFFF0000 ) >> 16);
        number = ( number & 0x00000000FFFFFFFF) + (( number & 0xFFFFFFFF00000000 ) >> 32);
        return number;
    }
    // 盤面の出力
    void printBoard(){
        printf ("X");
        for( char c = 'A'; c <= 'H'; c++ ){
            printf ("%c", c);
        }
        printf ("\n");
        ll oPos = this->TurnPlayer & 1 ? this->oppos : this->plpos;
        ll xPos = this->TurnPlayer & 1 ? this->plpos : this->oppos;
        ll hPos = this->SetableBoard();
        int yPosNumber = 0;
        for( ll i = 0x8000000000000000; i != 0; i>>=1 ){
            if( i & 0x8080808080808080 ) printf("%d" , ++yPosNumber);
            // 先手o　後手x　ブランク-
            if( i & oPos ) printf ("o");
            else if( i & xPos ) printf ("x");
            else if( i & hPos ) printf ("*");
            else printf ("-");
            // 程よく改行
            if( i & 0x0101010101010101 ) printf("\n");
        }
    }

    // （仮）ランダムにおく座標を返す
    ll AutoSetPosition(){
        std::mt19937 mt(time(0));
        while(1){
            for( ll i = 0x8000000000000000; i != 0;i >>= 1){
                if( this->SetableBoard() & i ){
                    if( mt() % 100 == 0 ){
                        return i;
                    }
                }
            }
        }
    }

private :
    ll plpos; // 打ち手
    ll oppos; // 受け手
    int TurnNumber; // ターン数
    int TurnPlayer; // どっちターン 0:o 1:x 最初はoから
    //bit map(board) の使用
    //いろいろ高速かつ簡単にできる
    //右 >>1、左 <<1、下 >>8、上 <<8
};

int main(){

    board B;
    B.printBoard();
    char PutCoordinate[3];
    ll PutPostion;
    while(true){
        scanf("%s", PutCoordinate );
        PutPostion = B.positionToBit(PutCoordinate[0],PutCoordinate[1]);
        if( PutPostion & B.SetableBoard() ){
            B.SetBoard(PutPostion);
            B.printBoard();
        }
    }
    printf("Finish!!\n");
    B.printBoard();
    printf("%llu - %llu\n", B.plNumber() , B.opNumber() );

}
