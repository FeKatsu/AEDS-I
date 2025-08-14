#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição da estrutura do nó da lista
typedef struct no{
    int chave;
    struct no* prox;
}No;


typedef struct lista {
  No *cabeca;
} Lista;


typedef Lista* Hash;

Lista * criaLista(){
    Lista* novaLista = (Lista*) malloc(sizeof(Lista));
    novaLista->cabeca = NULL;
    return novaLista;
}

void insereLista(Lista *l, int chave){
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->prox = l->cabeca;
    l->cabeca = novoNo;
}

No* busca(Lista* l, int chave){
    No* aux = l->cabeca;
    while(aux != NULL){
        if(aux->chave == chave){
            return aux;
        }
        aux = aux->prox;
    }
    return aux;
}

void imprimeLista(Lista *l){
    No* aux = l->cabeca;
    while(aux!=NULL){
        printf("%d ",aux->chave);
        aux = aux->prox;
    }
}


int h(int x){
    return x%100;
}

int h2(int x){
    float A = 0.618;
    return floor(100*(x*A - floor(x*A)));
}

int h3(int x){
    int somaDigitos = 0;
    while(x!=0){
        somaDigitos += x%10;
        x = x/10;
    }
    return somaDigitos%100;
}
void insereHash(Hash tabela[], int x){
    insereLista(tabela[h(x)],x);
}

int buscaHash(Hash tabela[],int x){
    return busca(tabela[h(x)],x)==NULL?0:1;
}

void insereHashLinear(int tabela[], int x){
    int i = h(x);
    while(tabela[i%100] != 0){
        i++;
    }
    tabela[i%100] = x;
}

int buscaHashLinear(int tabela[],int x){
    int i = h(x);
    while(tabela[i%100] != 0 && tabela[i%100]!=x)
        i++;
    return tabela[i%100];
}

// Função principal
int main() {
    // srand(2);
    // int tabelaHashLinear[100] = {};
    // int numColisoes = 0;
    // for(int i = 0;i<50;i++){
    //     int val = rand()%1000;
    //     printf("%d ",val);
    //     insereHashLinear(tabelaHashLinear,val,&numColisoes);
    // }
    // printf("\nNum colisoes: %d",numColisoes);

    int v1[50] = {};
    int v2[100] = {};
    for(int i = 0;i<50;i++){
        v1[i] = i+1;
        v2[i] = i+1;
        v2[50+i] = 50+i+1;
    }
    v1[30] = 107;
    int numColisoes = 0;
    int tabelaHashLinear[100] = {};
    for(int i = 0;i<100;i++){
        printf("Inserindo %d\n",v2[i]);
        insereHashLinear(tabelaHashLinear,v2[i]);
    }
    for(int i = 0;i<50;i++){
        printf("Buscando %d\n",v1[i]);
        if(buscaHashLinear(tabelaHashLinear,v1[i]) == 0){
            printf("v1 nao esta contido em v2!");
            return 0;
        }
    }
    printf("v1 esta contido em v2!");

    return 0;
}