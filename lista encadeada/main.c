#include <stdio.h>
#include<stdlib.h>

typedef struct no{
    int chave;
    struct no * prox;
    struct no * ant;
}No;

typedef struct lista{
    No* cabeca;
    No* fim;
}Lista;

Lista* criaLista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->cabeca = NULL;
    return l;
}

No* busca(Lista* l, int x){
    No* aux;
    aux = l->cabeca;
    while(aux!=NULL && aux->chave != x){
        aux = aux->prox;
    }
    return aux;
}

void insere(Lista* l, int x, int i){
    No* novo = (No*) malloc(sizeof(No));
    novo->chave = x;
    if(i == 0){
        novo->prox = l->cabeca;
        l->cabeca = novo;
        novo->ant = NULL;
        if(novo->prox!=NULL)
            novo->prox->ant = novo;
    }
    else{
        int j = 1;
        No* anterior = l->cabeca;
        while(anterior!=NULL && j<i){
            anterior = anterior->prox;
            j++;
        }
        
        if(anterior == NULL){
            printf("Indice nao existe");
        }else{
            novo->prox = anterior->prox;
            anterior->prox = novo;
            novo->ant = anterior;
            if(novo->prox!=NULL)
                novo->prox->ant = novo;
        }
    }
}

void imprime(Lista * l){
    No* aux = l->cabeca;
    while(aux!=NULL){
        printf("%d ",aux->chave);
        aux = aux->prox;
    }
    printf("\n");
}

void Remove(Lista* l, int x){
   No* removido = busca(l,x);
   if(removido->ant!=NULL){
    removido->ant->prox = removido->prox;
   }else{
    l->cabeca = removido->prox;
   }
   if(removido->prox!=NULL){
    removido->prox->ant = removido->ant;
   }
   free(removido);
}


int main(){
    Lista *l = criaLista();
    insere(l,2,0);
    insere(l,3,0);
    insere(l,4,0);
    insere(l,7,1);
    imprime(l);
    Remove(l,4);
    imprime(l);
    return 0;
}