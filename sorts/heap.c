#include<stdio.h>
#include<stdlib.h>
#include"heap.h"
#define TAM_MAX 100

Heap* criarHeap(){
    Heap* h = (Heap*) malloc(sizeof(Heap));
    h->tam = 0;
    return h;
}


void troca(int *vet, int i, int j){
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

int heap_max(Heap *h){
    return h->vet[0];
}

int esquerda(int i){
    return 2*i+1;
}
int direita(int i){
    return 2*i+2;
}
int pai(int i){
    return (i-1)/2;
}

void max_heapify(Heap *h, int i){
    int e = esquerda(i);
    int d = direita(i);
    int maior=i;
    if(e < h->tam &&  h->vet[e]>h->vet[maior])
        maior = e;
    if(d< h->tam && h->vet[d] > h->vet[maior])
        maior = d;

    if(maior != i){
        troca(h->vet, i,maior);
        max_heapify(h, maior);
    }
}

int heap_extrai_max(Heap *h){
    if(h->tam == 0){
        printf("Heap vazia!");
        return 0;
    }
    int max = h->vet[0];
    //Excluir o max
    h->vet[0] = h->vet[h->tam-1];
    h->tam--;
    //Maxheapify para corrigir a heap
    max_heapify(h,0);
    return max;
}  
void heap_aumenta_chave(Heap *h, int i, int chave){
    if(chave < h->vet[i]){
        printf("Chave nova menor que a atual!");
        return;
    }
    h->vet[i] = chave;
    while(i>0 && h->vet[pai(i)] < h->vet[i]){
        troca(h->vet,i,pai(i));
        i = pai(i);
    }
}

void heap_insere(Heap *h, int chave){
    if(h->tam == TAM_MAX){
        printf("Heap'está cheia!");
        return;
    }
    h->tam ++;
    h->vet[h->tam - 1] = chave-1;
    heap_aumenta_chave(h,h->tam -1, chave);
}

void heap_imprime(Heap *h){
    for(int i  = 0 ; i<h->tam;i++){
        printf("%d ",h->vet[i]);
    }
    printf("\n");
}

void heapSort(int *vet, int n){
    Heap *h = criarHeap();
    for(int i  = 0;i<n;i++){
        heap_insere(h,vet[i]);
    }
    for(int i = n-1;i>=0;i--){
        vet[i] = heap_extrai_max(h);
    }

}

