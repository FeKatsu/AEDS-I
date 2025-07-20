#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void imprime(int *vet, int tam){
    for(int i=0; i<tam; i++){
        printf("%d ", vet[i]);
    }
}

void troca(int *vet, int a, int b){
    int aux = vet[a];
    vet[a]=vet[b];
    vet[b]=aux;
}

int particao(int *vet, int p, int r){
    int posPivo = p + rand()%(r-p);
    troca(vet, posPivo, r);
    int pivo=vet[r];
    int i = p-1;
    for (int j=p; j<r; j++){
        if(vet[j]<pivo){
            i++;
            troca(vet,i,j);
        }
    }
    troca(vet,i+1,r);
    return i+1;
}

void quickSort(int *vet, int inicio, int fim){
    if(inicio>=fim) return;
    int posPivo=particao(vet, inicio, fim);
    quickSort(vet, inicio, posPivo-1);
    quickSort(vet, posPivo+1, fim);
}

void main(){
    int vet[10]={8,1,0,3,2,9,4,6,5,7};
    quickSort(vet, 0, 10);
    imprime(vet, 10);
}