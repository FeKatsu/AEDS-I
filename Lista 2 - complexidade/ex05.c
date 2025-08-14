#include <stdio.h>
#include <stdlib.h>

void imprime(int *vet, int n){
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
}

void criaVet(int *vet, int n){
    for (int i=0; i<n; i++){
        vet[i]=i;
    }
}

int buscaBin(int *vet, int n, int i, int f){
    int meio=(i+f)/2;

    if (vet[meio]==n) return meio;
    if (vet[meio]>n) return buscaBin(vet, n, i, meio-1);
    if (vet[meio]<n) return buscaBin(vet, n, meio+1, f);
}

void insere(int *vet, int elem, int pos, int tam){
    vet = (int *)realloc(vet, tam+1*sizeof(int));

    for (int i=tam+1; i>pos; i--){
        vet[i]=vet[i-1];
    }

    vet[pos]=elem;
}
void main(){
    int n=10;
    int x = 8;
    int *vet;
    vet = (int *)malloc(n*sizeof(int));
    criaVet(vet, n);
    
    int pos = buscaBin(vet, 8, 0, n);
    printf("posicao a ser inserido: %d\n",pos);
    insere(vet, x, pos, n);
    imprime(vet, n+1);
}