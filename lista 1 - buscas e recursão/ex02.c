#include <stdio.h>
#define tam 10
int buscaBin(int elem, int *vet, int n){
    int inicio = 0, meio;
    while (inicio<=n){       
        meio = (inicio+n)/2;
        if (vet[meio]==elem) return meio;
        if (vet[meio]>elem) n=meio-1;
        if (vet[meio]<elem) inicio=meio+1;
    }
    return -1;
}
int buscaBinRecursiva(int elem, int *vet, int a, int b){
    if (a>b) return -1;

    int meio=(a+b)/2;
    if (vet[meio]>elem)return buscaBinRecursiva(elem, vet, a, meio-1);
    if (vet[meio]<elem) return buscaBinRecursiva(elem, vet, meio+1, b);
    if (vet[meio]==elem) return meio;
}

void main(){
    int vetor[tam]={1,2,3,4,5,6,7,8,9,10};
    
    printf("busca binaria: %d\n", buscaBin(10, vetor, tam));
    printf("busca binaria recursiva: %d", buscaBinRecursiva(10, vetor, 0, tam));
}