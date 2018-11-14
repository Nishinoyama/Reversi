
#include <cstdio>
#include "board.h"

int main(){
    
    board B;

    int a,b;
    int cnt = 0;
    while(1){
        B.show();
        scanf("%d %d", &a, &b);
        cnt += B.set(1+cnt%2,a,b);
    }
    int aaaaa;
    scanf( "%d", aaaaa );

    return 0;
}