#include <stdio.h>

int fib(int *cont, int num){
   *cont=*cont+1;
   if (num<=2) return 1;
   return fib(cont, num-1)+fib(cont, num-2);
}

void main(){
    int contador = 0, x;
    printf("quantos elementos vai ter a sequenecia de fibonacci?\n");
    scanf("%d",&x);
    for(int i=1; i<=x;i++){
        printf("%d ", fib(&contador,i));
    }
    printf("\ncontador: %d", contador);
}