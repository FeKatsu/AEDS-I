#include <stdio.h>
#define TAM 10

void imprime(int *vet, int x){
    for (int i=0; i<x; i++){
        printf("%d ",vet[i]);
    }
}

void buscaSeq(int *vet, int tam, int elem, int *resp, int *cont){
    for(int i=0; i<tam; i++){
        if(vet[i]==elem) {
            resp[*cont]=i;
            *cont+=1;
        }
    }
}

void buscaBin(int *vet, int n, int f, int *resp, int *cont){
    int j=1, i=0;
    int meio;
    while (i<=n){  
        meio = (i+n)/2;
        if(vet[meio]==n) { 
            while(vet[meio-j]==n){
                j--;
            }
            j--;
            while(vet[meio+j]==n){
                resp[*cont]=meio+j;
                j++; *cont+=1;
            }
            return;
        }
        if (vet[meio]>n) n=meio-1;
        if (vet[meio]<n) i=meio+1;
    }
}

void main(){
    int vet[TAM]={1,2,2,2,3,4,5,6,7,8};
    int respS[TAM];
    int respB[TAM];
    int tamRespS=0, tamRespB=0;

    buscaSeq(vet, TAM, 2, respS, &tamRespS);
    imprime(respS, tamRespS);

    printf("\n");
    buscaBin(vet, 2, TAM, respB, &tamRespB);
    imprime(respB, tamRespB);
}