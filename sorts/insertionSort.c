#include <stdio.h>

void imprime(int *vet, int tam){
    for(int i=0; i<tam; i++){
        printf("%d ", vet[i]);
    }
}

void troca(int *vet, int a, int b){
    int aux=vet[a];
    vet[a]=vet[b];
    vet[b]=aux;
}

void insertionSort(int *vet, int tam){
    for(int i=1; i<tam; i++){
        int j=i;
        while(j>0 && vet[j]<vet[j-1]){
            troca(vet, j, j-1);
            j--;
        }
    }
}

void main(){
    int vet[10]={8,1,0,3,2,9,4,6,5,7};
    insertionSort(vet, 10);
    imprime(vet, 10);
}