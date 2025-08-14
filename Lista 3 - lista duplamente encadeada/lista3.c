#include <stdio.h>
#include<stdlib.h>

typedef struct no{
    int chave;
    struct no * prox;
    struct no * ant;
}No;

typedef struct lista{
    int contador;
    No* cabeca;
    No* fim;
}Lista;

Lista* criaLista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->cabeca = NULL;
    l->contador = 0;
    l->fim = NULL;
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

No* buscaInd(Lista *l, int i){
    No *aux;
    aux = l->cabeca;
    int j=0;
    while(aux!=NULL && j<i){
        aux = aux->prox;
        j++;
    }
    return aux;
}

void insere(Lista* l, int x, int i){
    No* novo = (No*) malloc(sizeof(No));
    novo->chave = x;
    l->contador+=1;
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
            novo->ant = anterior;
            anterior->prox = novo;
            if(novo->prox!=NULL)
                novo->prox->ant = novo;
        }
    }
    if (i==l->contador-1){
        l->fim=novo;
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
   } else {
    l->fim=removido->ant;
   }
   free(removido);
   l->contador-=1;
}

void troca(Lista *l, int i, int j){
    No *auxA = buscaInd(l, i);
    No *auxB = buscaInd(l, j);

    int auxC;
    auxC = auxA->chave;
    auxA->chave = auxB->chave;
    auxB->chave = auxC;
}

void removeInd(Lista *l, int i){
    No *remove = buscaInd(l, i);

    if (i==0){
        remove->prox->ant = NULL;
        l->cabeca = remove->prox;
    } 

    if (i<l->contador-1 && i>0) {
        remove->ant->prox = remove->prox;
        remove->prox->ant = remove->ant;
    } 
    if(i==l->contador-1){
        remove->ant->prox=NULL;
        l->fim=remove->ant;
    }
    free(remove);
    l->contador--;
}

void trocaNos(Lista *l, int i, int j){
    if(i>j){
        int aux = i;
        i=j;
        j=aux;
    }

    No *auxA = buscaInd(l, i);
    No *auxB = buscaInd(l, j);

    No *auxAend, *auxBend, *noAnt, *noProx;
    auxAend = auxA->prox->ant; 
    auxBend = auxB->ant->prox; 
    if(i==0){
        l->cabeca = auxB;
        noAnt = NULL;
    } else {  
        auxA->ant->prox = auxBend;
        noAnt=auxA->ant;
    }

    if(j==l->contador-1){
        auxA->prox=NULL;
    } else {auxB->prox->ant = auxAend;}

    noProx=auxA->prox;
    auxB->ant->prox = auxAend;
    auxA->prox->ant = auxBend;
    auxA->prox = auxB->prox;
    auxA->ant = auxB->ant;
    auxB->ant = noAnt;
    auxB->prox = noProx;
}

void imprimeInv(Lista *l){
    No *aux = l->fim;
    for (int i=0; i<l->contador;i++){
        printf("%d ", aux->chave);
        aux=aux->ant;
    }
    printf("\n");
}

void eliminaTodos(Lista *l, int x){
    No *aux = l->cabeca;
    for(int i=0; i<l->contador; i++){
        if(aux->chave==x){
            Remove(l, x);
        }
        aux = aux->prox;
    }
}

void imprimeResto(No *no){
    if (no==NULL) return;
    printf("%d ",no->chave);
    imprimeResto(no->prox);
}
void imprimeVet(int *vet, int n){
    for(int i=0; i<n;i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void encVet(Lista *l, int *vet){
    No *aux = l->cabeca;
    for (int i = 0; i < l->contador; i++) {
        vet[i]=aux->chave;
        aux=aux->prox;
    }
}

void vetEnc(Lista *l, int *vet, int n){
    for(int i=0; i<n; i++){
        insere(l, vet[i], i);
    }
}

int main(){
    Lista *l = criaLista();
    insere(l,2,0);
    insere(l,3,1);
    insere(l,4,2);
    insere(l,6,3);
    insere(l,6,4);
    insere(l,8,5);
    insere(l,8,6);
    printf("lista encadeada inicial: ");
    imprime(l);
    printf("\nremove elem de chave 4: ");
    Remove(l,4);
    imprime(l);
    printf("\ntroca elem[2] e elem[0]: ");
    troca(l, 2, 0);
    imprime(l);
    printf("\ntroca elementos [2] e [0] pelos nos: ");
    trocaNos(l, 2, 0);
    imprime(l);
    printf("\nimprime invertido: ");
    imprimeInv(l);
    printf("\neliminia todos elems 6: ");
    eliminaTodos(l, 6);
    imprime(l);

    printf("\nimprime a partir do indice 2: ");
    imprimeResto(buscaInd(l, 2));

    printf("\nnum elementos: %d\n", l->contador);
    printf("\nultimo elemento: %d\n", l->fim->chave);

    printf("\nlista encadeada para vetor: ");
    int *vet1; 
    vet1 = (int *)malloc(l->contador*sizeof(int));
    
    encVet(l, vet1);
    imprimeVet(vet1, l->contador);

    printf("\nvetor para lista encadeada: ");
    int vet2[5]={8,3,0,2,6};
    Lista *l2 = criaLista();
    vetEnc(l2, vet2, 5);
    imprime(l2);
    return 0;
}