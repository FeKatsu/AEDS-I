#include<stdio.h>
#include<stdlib.h>

typedef struct pilha{
    int vet[100];
    int topo;
}Pilha;
Pilha* criaPilha(){
    Pilha* nova = (Pilha*) malloc(sizeof(Pilha));
    nova->topo = -1;
    return nova;
}
void empilha(Pilha* pilha, int x){
    pilha->vet[++pilha->topo] = x;
}
int desempilha(Pilha* pilha){
    if(pilha->topo == -1){
        printf("Stack underflow!");
        return -1;
    }else{
        return pilha->vet[pilha->topo--];
    }
}

void imprimePilha(Pilha* p){
    for(int i = 0; i < p->topo+1;i++){
        printf("%d ",p->vet[i]);
    }
    printf("\n");
}

typedef struct jogo{
    Pilha* pilhas[3];
    int numPecas;
}Jogo;

Jogo* criaJogo(int numPecas){
    Jogo* novo = (Jogo*) malloc(sizeof(Jogo));
    novo->numPecas = numPecas;
    novo->pilhas[0] = criaPilha(numPecas);
    novo->pilhas[1] = criaPilha(numPecas);
    novo->pilhas[2] = criaPilha(numPecas);
    for(int i = 0;i<numPecas;i++){
        empilha(novo->pilhas[0],numPecas-i);
    }
    return novo;
}

void imprimeJogo(Jogo* j){
    printf("\nPilha 1:\n");
    imprimePilha(j->pilhas[0]);
    printf("Pilha 2:\n");
    imprimePilha(j->pilhas[1]);
    printf("Pilha 3:\n");
    imprimePilha(j->pilhas[2]);
}

void moverPeca(Jogo* j, int s, int d){
    int peca = desempilha(j->pilhas[s]);
    empilha(j->pilhas[d], peca);
}
//moverPecas(j,5,0,2,1)
void moverPecas(Jogo *j, int numPecas, int saida, int destino, int aux){
    if(numPecas == 1){
        moverPeca(j,saida,destino);
        //printf("Movendo a peca %d de %d para %d\n",numPecas,saida,destino);
        //imprimeJogo(j);
    }else{
        moverPecas(j,numPecas-1,saida,aux,destino);
        moverPeca(j,saida,destino);
        //printf("Movendo a peca %d de %d para %d\n",numPecas,saida,destino);
        //imprimeJogo(j);
        moverPecas(j,numPecas-1, aux,destino,saida);
    }
}

void terceira(){
    printf("Terceira finalizou");
}

void segunda(){
    terceira();
    printf("Segunda finalizou!");
}

void primeira(){
    primeira();
    printf("Primeira finalizou!");
}


typedef struct pilhachar{
    char* vet;
    int topo;
    int capacidade;
}PilhaChar;

PilhaChar* criaPilhaChar(int capacidade){
    PilhaChar* nova = (PilhaChar*) malloc(sizeof(PilhaChar));
    nova->capacidade = capacidade;
    nova->vet = (char*) malloc(capacidade*sizeof(char));
    nova->topo = -1;
    return nova;
}

int pilhaCharVazia(PilhaChar* pilhaChar){
    if(pilhaChar->topo == -1)
        return 1;
    return 0;
}

void empilhaChar(PilhaChar* pilhaChar, char x){
    if(pilhaChar->topo == pilhaChar->capacidade-1){
        printf("Stack overflow!");
    }else{
        pilhaChar->vet[++pilhaChar->topo] = x;
    }
}

char desempilhaChar(PilhaChar* pilhaChar){
    if(pilhaCharVazia(pilhaChar)){
        //printf("Stack underflow!");
        return -1;
    }else{
        return pilhaChar->vet[pilhaChar->topo--];
    }
}

typedef struct fila{
    int *vet;
    int inicio;
    int fim;
    int capacidade;
    int numElementos;
}Fila;

Fila* criaFila(int capacidade){
    Fila* nova = (Fila *) malloc(sizeof(Fila));
    nova->capacidade = capacidade;
    nova->vet = (int *) malloc(capacidade*sizeof(int));
    nova->inicio = 0;
    nova->fim = 0;
    nova->numElementos = 0;
    return nova;
}

void enfilera(Fila* f, int x){
    if(f->numElementos == f->capacidade){
        printf("queue overflow!");
        return;
    }
    f->numElementos++;
    f->vet[f->fim++] = x;  
    f->fim = f->fim%f->capacidade;
}

int desenfilera(Fila* f){
    if(f->numElementos == 0){
        printf("queue underflow!");
        return -1;
    }
    f->numElementos--;
    int x = f->vet[f->inicio++];
    f->inicio = f->inicio%f->capacidade;
    return x;
}


// Definição da estrutura do nó da lista
typedef struct no{
    int chave;
    struct no* prox;
}No;


typedef struct lista {
  No *cabeca;
} Lista;


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

No* acessa(Lista* l, int indice){
    if(indice<0) return NULL;
    No* aux = l->cabeca;
    int indiceAtual = 0;
    while(indiceAtual<indice && aux!=NULL){
        aux = aux->prox;
        indiceAtual++;
    }
    return aux;
}

void imprimeLista(Lista *l){
    No* aux = l->cabeca;
    while(aux!=NULL){
        printf("%d ",aux->chave);
        aux = aux->prox;
    }
    printf("\n");
}
void excluir(Lista * l, int chave){
    No* aux = l->cabeca;
    No* ant = NULL;
    while(aux != NULL){
        if(aux->chave == chave){
            if(ant!=NULL)
                ant->prox = aux->prox;
            else
                l->cabeca = aux->prox;
            free(aux);
            return;
        }
        ant = aux;
        aux = aux->prox;
    }
}

int hash(int x){
    return x%10;
}

typedef Lista* Hash;

void insere(Hash tabela[], int x){
    insereLista(tabela[hash(x)],x);
}

int busca_hash(Hash tabela[], int x){
    int k = hash(x);

    if (busca(tabela[k],x)!=NULL){
        return k;
    }
    return -1;
}

void alocaHash(Hash vet[], int tam){
    for(int i = 0; i<tam;i++){
            vet[i] = criaLista();
    }
}

void imprimeHash(Hash vet[], int tam){
    for(int i = 0; i<tam;i++){
       printf("\nLinha %d:",i);
       imprimeLista(vet[i]);
    }
}


int detectaColisao(char str[]){
    int caracteres[256] = {};
    for(int i = 0; str[i]!='\0';i++){
       if(caracteres[str[i]]==0){
        caracteres[str[i]]++;
       }else{
        printf("Colidiu!");
        return 1;
       }
    }
    printf("Nao colidiu");
    return 0;
}


int detectaPermutacao(char str1[], char str2[]){
    int tabelaLetras[256] = {};
    for(int i = 0;str1[i]!='\0';i++){
        tabelaLetras[str1[i]] ++;
    }
    for(int i = 0; str2[i]!='\0';i++){
        tabelaLetras[str2[i]] --;
        if(tabelaLetras[str2[i]] < 0){
            printf("Nao e permutacao!");
            return 0;
        }
    }

    for(int i =0;i<256;i++){
        if(tabelaLetras[i]!=0){
            printf("Nao e permutacao");
            return 0;
        }
    }
    printf("E permutacao!");
    return 1;
}

int detectaPermutacaoPalindromo(char str[]){
    int tabelaLetras[256] = {};
    for(int i = 0;str[i]!='\0';i++){
        tabelaLetras[str[i]] ++;
    }
    int chanceDada = 1;
    for(int i = 0;i<256;i++){
        if(tabelaLetras[i]%2 != 0){
            if(chanceDada == 1)
                chanceDada = 0;
            else {
                printf("Nao e permutacao!");
                return 0;
            }
        }
    }
    printf("E permutacao.");
    return 1;
}


void removeDuplicatas(Lista *l){
    Hash tabela[10];
    alocaHash(tabela,10);
    No *p1 = l->cabeca;
    No* ant;
    while(p1!= NULL){
        if(busca_hash(tabela,p1->chave)==-1){
            insere(tabela,p1->chave);
            ant = p1;
            p1 = p1->prox;
        }else{
            ant->prox = p1->prox;
            free(p1);
            p1 = ant->prox;
        }
    }
}

void deletaNo(No* n){
    n->chave = n->prox->chave;
    No* aux = n->prox;
    n->prox = n->prox->prox;
    free(aux);
}

No* retornakEsimoTras(Lista *l, int k){
    No* p1 = l->cabeca;
    No* p2 = l->cabeca;
    for(int i = 0; i<k;i++){
        if(p2 == NULL){
            printf("A lista nao tem %d elementos!\n",k);
            return NULL;   
        }
        p2 = p2->prox;
    }
    while(p2!=NULL){
        p1 = p1->prox;
        p2 = p2->prox;
    }
    return p1;
        
}

int checaPalindromo(Lista *l){
    Pilha* p = criaPilha();
    No* p1 = l->cabeca;
    No* p2 = l->cabeca;
    while(p2!=NULL && p2->prox!=NULL){
        empilha(p,p1->chave);
        p1 = p1->prox;
        p2 = p2->prox->prox;
    }
    if(p2!=NULL){
        p1=p1->prox;
    }
    while(p1!=NULL){
        if(p1->chave == desempilha(p))
            p1 = p1->prox;
        else{
            printf("Nao e palindromo");
            return 0;
        }
    }
    if(p->topo == -1){
        printf("E palindromo");
        return 1;
    }
    printf("Nao e palindromo");
    return 0;
}

typedef struct pilhaMin{
    Pilha* p;
    Pilha* mins;
} PilhaMin;

PilhaMin* criaPilhaMin(){
    PilhaMin* novo = (PilhaMin *) malloc(sizeof(PilhaMin));
    novo->p = criaPilha();
    novo->mins = criaPilha();
    return novo;
}

int espia(Pilha* p){
    return p->vet[p->topo];
}

void empilhaMin(PilhaMin* p, int x){
    if(p->mins->topo==-1){
        empilha(p->mins,x);
        empilha(p->p,x);
    }else{
        empilha(p->p,x);
        if(x<=espia(p->mins)){
            empilha(p->mins,x);
        }
    }
}

int desempilhaMin(PilhaMin* p){
    int x = desempilha(p->p);
    if(x == espia(p->mins)){
        desempilha(p->mins);
    }
    return x;
}

int espiaPilhaMin(PilhaMin *p){
    return espia(p->p);
}

int min(PilhaMin *p){
    return espia(p->mins);
}

typedef struct conjuntoPilhas{
    Pilha* pilhas[10];
    int ultimaPilhaCriada;
    int alturaMaxima;
}ConjuntoPilhas;

ConjuntoPilhas* criaConjuntoPilhas(int alturaMaxima){
    ConjuntoPilhas* novo = (ConjuntoPilhas* ) malloc(sizeof(ConjuntoPilhas));
    novo->pilhas[0] = criaPilha();
    novo->ultimaPilhaCriada = 0;
    novo->alturaMaxima = alturaMaxima;
    return novo;
}

void empilhaConjuntoPilhas(ConjuntoPilhas* p,int x){
    if(p->pilhas[p->ultimaPilhaCriada]->topo == p->alturaMaxima-1){
        p->ultimaPilhaCriada++;
        p->pilhas[p->ultimaPilhaCriada] = criaPilha();
    }
    empilha(p->pilhas[p->ultimaPilhaCriada],x);
}


int desempilhaConjuntoPilhas(ConjuntoPilhas* p){
    int x = desempilha(p->pilhas[p->ultimaPilhaCriada]);
    if(p->pilhas[p->ultimaPilhaCriada]->topo==-1){
        free(p->pilhas[p->ultimaPilhaCriada]);
        p->ultimaPilhaCriada--;
    }
    return x;
}

void invertePilha(Pilha* p){
    Fila* aux = criaFila(100);
    while(p->topo!=-1){
        enfilera(aux,desempilha(p));
    }
    while(aux->numElementos!=0){
        empilha(p,desenfilera(aux));
    }
}



void inverteFila(Fila* f){
    Pilha* aux = criaPilha();
    while(f->numElementos!=0){
        empilha(aux,desenfilera(f));
    }
    while(aux->topo!=-1){
        enfilera(f,desempilha(aux));
    }
}

void imprimeFila(Fila *f){
    for(int i = f->inicio;i<f->fim;i++){
        printf("%d ",f->vet[i]);
    }
    printf("\n");
}

int tamanhoPilha(Pilha *p){
    Pilha *aux = criaPilha();
    int numElementos = 0;
    while(p->topo!=-1){
        empilha(aux,desempilha(p));
        numElementos++;
    }
    while(aux->topo!=-1){
        empilha(p,desempilha(aux));
    }
    return numElementos;
}

int pilhasIguais(Pilha *p1, Pilha *p2){
    Pilha* aux = criaPilha();
    while(p1->topo!= -1){
        int topoP1 = desempilha(p1);
        int topoP2 = desempilha(p2);
        if(topoP1 == topoP2){
            empilha(aux,topoP1);
        }else{
            empilha(p1,topoP1);
            empilha(p2,topoP2);
            break;
        }
    }
    int saoIguais = 0;
    if(p1->topo == -1 && p2->topo == -1){
        saoIguais = 1;
    }
    while(aux->topo!= -1){
        int topoAux = desempilha(aux);
        empilha(p1,topoAux);
        empilha(p1,topoAux);
    }
    return saoIguais;

}

int main(){
    Pilha *p = criaPilha();
    empilha(p,1);
    empilha(p,2);
    empilha(p,3);
    imprimePilha(p);
    printf("\nNumElementos: %d\n",tamanhoPilha(p));
    imprimePilha(p);
    return 0;
}