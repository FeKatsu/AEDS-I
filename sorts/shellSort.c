#include <stdio.h>
void imprime(int *vet, int tam){
    for(int i=0; i<tam; i++){
        printf("%d ", vet[i]);
    }
}

void shellSort(int *vet, int size){
    int i, j, value;

    int h=1;

    while(h<size){
        h=3*h+1;
    }

    while (h>0){
        for(i=h;i<size;i++){
            value=vet[i];
            j=i;
            while (j>h-1 && value<=vet[j-h]){
                vet[j]=vet[j-h];
                j=j-h;
            }
            vet[j]=value;
        }
        h=h/3;
    }
}

void main(){
    int vet[10]={8,1,0,3,2,9,4,6,5,7};
    shellSort(vet, 10);
    imprime(vet, 10);
}