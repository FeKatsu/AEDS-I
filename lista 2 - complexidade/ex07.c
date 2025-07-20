#include <stdio.h>
#define N 4

void imprime(int *vet, int n){
    for (int i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }
}

void merge3(int *vet1, int *vet2, int *vet3,int n,int *resultado){
    int i=0, j=0, k=0, l=0;

    while(i<n && j<n && k<n){
        if(vet1[i]<vet2[j] && vet1[i]<vet3[k]){
            resultado[l]=vet1[i];
            i++; l++;
        }
        if(vet2[j]<vet1[i] && vet2[j]<vet3[k]){
            resultado[l]=vet2[j];
            j++; l++;
        }
        if(vet3[k]<vet2[j] && vet3[k]<vet1[i]){
            resultado[l]=vet3[k];
            k++; l++;
        }
    }
    while(i<n && j<n && k>=n){
        if(vet1[i]<vet2[j]){
            resultado[l]=vet1[i];
            i++; l++;
        } else{
            resultado[l]=vet2[j];
            j++; l++;
        }
    }
    while(j<n && k<n && i>=n){
        if(vet3[k]<vet2[j]){
            resultado[l]=vet3[k];
            l++; k++;
        } else{
            resultado[l]=vet2[j];
            j++; l++;
        }
    }
    while(i<n && k<n && j>=n){
        if(vet3[k]<vet1[i]){
            resultado[l]=vet3[k];
            l++; i++;
        } else{
            resultado[l]=vet1[1];
            k++; l++;
        }
    }

    while(i<n){
        resultado[l]=vet1[i];
        i++; l++;
    }
    while(j<n){
        resultado[l]=vet2[j];
        j++; l++;
    }
    while(k<n){
        resultado[l]=vet3[k];
        k++; l++;
    }
}

void main(){
    int vet1[N]={1,3,7,10};
    int vet2[N]={2,6,8,11};
    int vet3[N]={4,5,9,12};
    int resultado[3*N];
    merge3(vet1, vet2, vet3, N, resultado);
    imprime(resultado, 3*N);
}