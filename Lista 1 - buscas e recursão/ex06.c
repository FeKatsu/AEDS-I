#include <stdio.h>

void inverteVet(int *vet, int inicio, int fim){
    if(inicio>fim)return;
    int aux = vet[inicio];
    vet[inicio]=vet[fim];
    vet[fim]=aux;

    inicio+=1;
    fim-=1;
    inverteVet(vet, inicio, fim);
}

void imprime(int *vet, int tam){
    for(int i=0; i<tam;i++){
        printf("%d ", vet[i]);
    }
}

void main(){
    int vetor[10]={1,2,3,4,5,6,7,8,9,10};

    inverteVet(vetor, 0, 9);
    imprime(vetor, 10);
}