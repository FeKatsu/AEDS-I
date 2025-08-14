#include <stdio.h>
#include <stdlib.h>

void fib(int *vet, int tam){
    int cont =0;
    vet[0] = 1;
    vet[1] = 1;
    for (int i=2;i<=tam;i++){
        vet[i]=vet[i-1]+vet[i-2];
        cont++;
    }
}

void imprime(int *vet, int tam){
    for(int i=0; i<tam;i++){
        printf("%d ", vet[i]);
    }
}

void main(){
    int n = 10; //deveria ser um scanf
    int *vet = (int*)malloc(n*sizeof(int));

    fib(vet, n);

    imprime(vet, n);
}