
#include <cstdio>
#include "board.h"

int main(){

    board B;
    B.printBoard();
    char PutCoordinate[3];
    ll PutPostion;
    while(true){
        //scanf("%s", PutCoordinate );
        //PutPostion = B.positionToBit(PutCoordinate[0],PutCoordinate[1]);
        PutPostion = B.AutoSetPosition();
        if( PutPostion & B.SetableBoard() ){
            B.SetBoard(PutPostion);
            B.printBoard();
        }
        if( B.isEnd() ){
            break;
        }
    }
    printf("Finish!!\n");
    B.printBoard();
    printf("%llu - %llu\n", B.plNumber() , B.opNumber() );

}
