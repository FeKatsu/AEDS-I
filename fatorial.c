#include <stdio.h>

int fatorial(int n){
    if (n==0) return 1;

    return(fatorial(n-1)*n);
}

void main(){
    int x;
    scanf("%d",&x);
    printf("%d", fatorial(x));
}