#include <stdio.h>

int mdc(int a, int b){
    if (b==0) return a;
    mdc(b, a%b);
}

void main(){
    printf("mdc: %d", mdc(18, 27));
}