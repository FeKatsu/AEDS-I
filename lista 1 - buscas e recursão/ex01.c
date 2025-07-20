#include <stdio.h>
#define tam 10

int buscaSequencial(int elem, int *vet, int n){
    for (int i=0; i<n; i++){
        if(vet[i]==elem) return i;
    }
    return -1;
}

void main(){
    int vetor[tam]={1,2,3,4,5,6,7,8,9,10};

    printf("%d", buscaSequencial(10, vetor, tam));
}