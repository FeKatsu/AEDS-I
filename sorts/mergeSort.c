#include <stdio.h>

void imprime(int *vet, int tam){
    for(int i=0; i<tam; i++){
        printf("%d ", vet[i]);
    }
}

void merge(int *vet, int inicio, int meio, int fim){
    int i=0,j=0,k=inicio;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int L[n1], R[n2];
    for(int l = 0; l<n1 ;l++){
        L[l] = vet[inicio+l]; 
    }
    for(int r=0;r<n2;r++){
        R[r] = vet[meio + 1 + r];
    }
    while(i<n1 && j <n2){
        if(L[i]<R[j]){
            vet[k] = L[i];
            i++; k++;
        }else{
            vet[k] = R[j];
            j++;k++;
        }
    }
    while(i<n1){
        vet[k] = L[i];
        k++;i++;
    }
    while(j<n2){
        vet[k] = R[j];
        k++;j++;
    }

}

void mergeSort(int *vet, int inicio, int fim){
    if(inicio>=fim) return;
    int meio = (inicio+fim)/2;
    mergeSort(vet, inicio, meio);
    mergeSort(vet,meio+1,fim);

    merge(vet,inicio,meio,fim);    
}


void main(){
    int vet[10]={1,0,3,9,2,8,4,6,5,7};
    mergeSort(vet, 0, 9);
    imprime(vet, 10);
}