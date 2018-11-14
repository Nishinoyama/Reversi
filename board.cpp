
#include "board.h"
#include <cstdio>

board::board(){

    printf("Welcome to Othello World!\n");

    printf("Initialize...");

    this->block[4][4] = 1;
    this->block[4][5] = 2;
    this->block[5][4] = 2;
    this->block[5][5] = 1;

    this->block_char[0] = '.';        
    this->block_char[1] = 'o';
    this->block_char[2] = 'x';

    /*
    this->block_char.insert(std::make_pair(0,'.'));
    this->block_char.insert(std::make_pair(1,'o'));
    this->block_char.insert(std::make_pair(2,'x'));
    */

    printf("complete!\n");
}

board::~board(){ }

int board::set( int color, int x, int y){
    int serachx = x;
    int serachy = y;
    bool settable = false;
    bool hit = false;

    if( x > 8 || x < 1 || y > 8 || y < 1 ){
        return 0;
    }

    // 右
    for( int leng = 1; leng < 100; leng++ ){
        printf("%d %d %d", serachx, serachy, hit);
        if( block[serachy][serachx+leng] && block[serachy][serachx+leng] != color ){
            printf("hit!\n");
            hit = true;
        }else if( hit && block[serachy][serachx+leng] == color){
            settable = true;
            for( int through = leng; through >= 0; through--)
                block[serachy][serachx+through] = color;
            break;
        }else{
            break;
        }

    }
    // 右上
    hit = false;
    for( int leng = 1; leng < 100; leng++ ){
        if( block[serachy+leng][serachx+leng] && block[serachy+leng][serachx+leng] != color ){
            hit = true;
        }else if( hit && block[serachy+leng][serachx+leng] == color){
            settable = true;
            for( int through = leng; through >= 0; through--)
                block[serachy+through][serachx+through] = color;
            break;
        }else{
            break;
        }
    }
    // 上
    hit = false;
    for( int leng = 1; leng < 100; leng++ ){
        if( block[serachy+leng][serachx] && block[serachy+leng][serachx] != color ){
            hit = true;
        }else if( hit && block[serachy+leng][serachx] == color){
            settable = true;
            for( int through = leng; through >= 0; through--)
                block[serachy+through][serachx] = color;
            break;
        }else{
            break;
        }
    }
    // 左上
    hit = false;
    for( int leng = 1; leng < 100; leng++ ){
        if( block[serachy+leng][serachx-leng] && block[serachy+leng][serachx-leng] != color ){
            hit = true;
        }else if( hit && block[serachy+leng][serachx-leng] == color){
            settable = true;
            for( int through = leng; through >= 0; through--)
                block[serachy+through][serachx-through] = color;
            break;
        }else{
            break;
        }
    }
    // 左
    hit = false;
    for( int leng = 1; leng < 100; leng++ ){
        if( block[serachy][serachx-leng] && block[serachy][serachx-leng] != color ){
            hit = true;
        }else if( hit && block[serachy][serachx-leng] == color){
            settable = true;
            for( int through = leng; through >= 0; through--)
                block[serachy][serachx-through] = color;
            break;
        }else{
            break;
        }
    }
    // 左下
    hit = false;
    for( int leng = 1; leng < 100; leng++ ){
        if( block[serachy-leng][serachx-leng] && block[serachy-leng][serachx-leng] != color ){
            hit = true;
        }else if( hit && block[serachy-leng][serachx-leng] == color){
            settable = true;
            for( int through = leng; through >= 0; through--)
                block[serachy-through][serachx-through] = color;
            break;
        }else{
            break;
        }
    }
    // 下
    hit = false;
    for( int leng = 1; leng < 100; leng++ ){
        if( block[serachy-leng][serachx] && block[serachy-leng][serachx] != color ){
            hit = true;
        }else if( hit && block[serachy-leng][serachx] == color){
            settable = true;
            for( int through = leng; through >= 0; through--)
                block[serachy-through][serachx] = color;
            break;
        }else{
            break;
        }
    }
    // 右下
    hit = false;
    for( int leng = 1; leng < 100; leng++ ){
        if( block[serachy-leng][serachx+leng] && block[serachy-leng][serachx+leng] != color ){
            hit = true;
        }else if( hit && block[serachy-leng][serachx+leng] == color){
            settable = true;
            for( int through = leng; through >= 0; through--)
                block[serachy-through][serachx+through] = color;
            break;
        }else{
            break;
        }
    }
    if( settable ) {
        this->block[y][x] = color;
        printf( "Set!\n" );
    } else {
        printf( "Unsettable\n" );
    }

    return (int)settable;

}

void board::show(){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            if( y == 0 ) printf("%c", '0'+x);
            else if( x == 0 ) printf("%d", y);
            else {
                printf("%c", this->block_char[this->block[y][x]]);   
            }
        }
        printf("\n");
    }
}
