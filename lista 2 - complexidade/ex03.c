#include <stdio.h>

void criaVet(int *vet, int n){
    for (int i=0; i<n; i++){
        vet[i]=i;
    }
}

int rep(int *vet, int n){
    for (int i=0;i<n; i++){
        if(vet[i]==vet[i+1]) return 1;
    }
    return -1;
}

void main(){
    int vetor[10]={0,1,2,3,4,5,6,7,8,9};

    if(rep(vetor, 10)==1) printf("Ha repeticao");
    else printf("nao ha repeticao");
}