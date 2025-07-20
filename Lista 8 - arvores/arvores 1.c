#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct no{
    char dado;
    struct no* pai;
    struct no* esq;
    struct no* dir;
}No;

typedef struct arv{
    No* raiz;
}Arv;

typedef struct fila{
    No *vet[100];
    int inicio;
    int fim;
    int numElementos;
}Fila;

Fila* criaFila(){
    Fila* nova = (Fila *) malloc(sizeof(Fila));
    nova->inicio = 0;
    nova->fim = 0;
    nova->numElementos = 0;
    return nova;
}

void enfilera(Fila* f, No* x){
    if(f->numElementos == 100){
        printf("queue overflow!");
        return;
    }
    f->numElementos++;
    f->vet[f->fim++] = x;  
    f->fim = f->fim%100;
}

No* desenfilera(Fila* f){
    if(f->numElementos == 0){
        printf("queue underflow!");
        return NULL;
    }
    f->numElementos--;
    No* x = f->vet[f->inicio++];
    f->inicio = f->inicio%100;
    return x;
}

Arv* criaArvore(){
    Arv* nova = (Arv*) malloc(sizeof(Arv));
    nova->raiz = NULL;
    return nova;
}

No* criaNo(char dado){
    No* novo = (No*) malloc(sizeof(No));
    novo->dado = dado;
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void percursoEmOrdem(No* no){
    if(no == NULL) return;
    percursoEmOrdem(no->esq);
    printf("%d ",no->dado);
    percursoEmOrdem(no->dir);   
}

void percursoPosOrdem(No* no){
    if(no == NULL) return;
    percursoPosOrdem(no->esq);
    percursoPosOrdem(no->dir);
    printf("%d ",no->dado);
}

void percursoPreOrdem(No* no){
    if(no == NULL) return;
    printf("%d ",no->dado);
    percursoPreOrdem(no->esq);
    percursoPreOrdem(no->dir);
}

void percursoLargura(No* no){
    Fila *f = criaFila();
    if(no == NULL) return;
    No* aux = no;
    enfilera(f,aux);
    while(f->numElementos>0){
        aux = desenfilera(f);
        printf("%d ",aux->dado);
        if(aux->esq!=NULL)
            enfilera(f,aux->esq);
        if(aux->dir!=NULL)
            enfilera(f,aux->dir);
    }
}

void insereABB(Arv* arv, int val){
    No* z = criaNo(val);
    
    No* y = NULL;
    No* x = arv->raiz;
    
    while(x!=NULL){
        y = x;
        if(x->dado > z->dado){
            x = x->esq;
        }else{
            x = x->dir;
        }
    }
    z->pai = y;
    if(y == NULL){
        arv->raiz = z;
    }else if(y->dado > z->dado){
        y->esq = z;
    }else{
        y->dir = z;
    }
}

No* insereABBRec(No* no, int val){
    if(no == NULL){
        No* novo = criaNo(val);
        return novo;
    }
    if(val > no->dado){
        no->dir = insereABBRec(no->dir,val);
    }else{
        no->esq = insereABBRec(no->esq,val);
    }
    return no;
}



No* buscaABB(No* no, int val){
    if(no == NULL || no->dado == val)
        return no;
    if(val > no->dado) buscaABB(no->dir,val);
    else buscaABB(no ->esq,val);
}

No* buscaABBIterativa(Arv* arv, int val){
    No* aux = arv->raiz;
    while(aux!=NULL){
        if(aux->dado == val)
            return aux;
        if(aux->dado>val){
            aux = aux->esq;
        }else{
            aux = aux->dir;
        }
    }
    return NULL;
}


int alturaABB(No* no){
    if(no == NULL) return -1;
    int alturaEsquerda = alturaABB(no->esq);
    int alturaDireita = alturaABB(no->dir);
    if(alturaEsquerda > alturaDireita)
        return alturaEsquerda + 1;
    else
        return alturaDireita + 1;
}

No* minimoABB(No* aux){
    if(aux == NULL) return NULL;
    while(aux->esq !=NULL)
        aux = aux->esq;
    return aux;
}

No* maximoABB(No* aux){
    if(aux == NULL) return NULL;
    while(aux->dir !=NULL)
        aux = aux->dir;
    return aux;
}

No* sucessorABB(No* aux){
    return minimoABB(aux->dir);
}

No* antecessorABB(No* aux){
    return maximoABB(aux->esq);
}

void transplantar(Arv* arv, No* u, No* v){
    if(u->pai==NULL){
        arv->raiz = v;
    }else if(u == u->pai->esq){
        u->pai->esq = v;
    }else{
        u->pai->dir = v;
    }
    if(v!=NULL){
        v->pai = u->pai;
    }
}

void deleta(Arv* arv, No* z){
    if(z->esq == NULL){
        transplantar(arv,z,z->dir);
    }else if(z->dir == NULL){
        transplantar(arv,z,z->esq);
    }else{
        No* y = sucessorABB(z);
        if(y->pai != z){
            transplantar(arv,y,y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplantar(arv,z,y);
        y->esq = z->esq;
        y->esq->pai = y;
    }
    free(z);
}

void deletaABB(Arv* arv, int x){
    No* no = buscaABB(arv->raiz,x);
    if(no!=NULL)
        deleta(arv,no);
}

void imprimeNivel(No* no, int nivel){
    if(nivel == 0){
        printf("%d ", no->dado);
        return;
    }
    if(no->esq !=NULL) imprimeNivel(no->esq, nivel-1);
    if(no->dir !=NULL) imprimeNivel(no->dir, nivel-1);
}

void imprimeArvoreLinhas(Arv* arv){
    for(int i = 0;i<= alturaABB(arv->raiz);i++){
        imprimeNivel(arv->raiz,i);
        printf("\n");
    }
}

void imprimeOrganizadoAux(No* no, int nivel){
    if(no == NULL) return;
    printf("|");
    for(int i = 0;i<nivel;i++) printf("-");
    if(no->pai!=NULL){
        if(no->pai->dir == no) printf("D");
        else printf("E");
    }
    printf("%c\n",no->dado);
    imprimeOrganizadoAux(no->esq,nivel+1);
    imprimeOrganizadoAux(no->dir,nivel+1);
}

void imprimeOrganizado(Arv* arvore){
    imprimeOrganizadoAux(arvore->raiz, 0);
}

int contaFolhas(No* no){
    if(no == NULL) return 0;
    if(no->esq == NULL && no->dir == NULL) return 1;
    return contaFolhas(no->esq) + contaFolhas(no->dir);
}

int profundidadeABB(No* no, int x){
    if(no->dado == x){
        return 0;
    }
    if(no->dado > x){
        return 1 + profundidadeABB(no->esq,x);
    }else{
        return 1 + profundidadeABB(no->dir,x);
    }
}

int profundidade(No* no,int x){
    if(no == NULL) return -9999;
    if(no->dado == x) return 0;
    int caminhoDir = profundidade(no->dir,x);
    int caminhoEsq = profundidade(no->esq,x);

    if(caminhoDir > caminhoEsq){
        return caminhoDir + 1;
    }else{
        return caminhoEsq + 1;
    }
}

int diffProf(Arv* arvore, int x, int y){
    int profundidadeX = profundidadeABB(arvore->raiz,x);
    int profundidadeY = profundidadeABB(arvore->raiz,y);
    return abs(profundidadeX - profundidadeY);
}

No* busca(No* no, int x){
    if(no == NULL) return NULL;
    if(no->dado == x) return no;
    No* esq = busca(no->esq,x);
    No* dir = busca(no->dir, x);
    if(esq!=NULL) return esq;
    if(dir!=NULL) return dir;
    return NULL;
}

int ancestralComumAux(No* no, int x, int y){
    if(x>no->dado && y>no->dado) //if(busca(x,no->esq)!=NULL && busca(y,no->esq)!=NULL)
        return ancestralComumAux(no->dir,x,y);
    if(x<no->dado && y < no->dado)
        return ancestralComumAux(no->esq,x,y);
    return no->dado;
}

int ancestralComumBaixo(Arv* arvore, int x, int y){
    if(buscaABB(arvore->raiz,x)!=NULL && buscaABB(arvore->raiz,y)!=NULL){
        return ancestralComumAux(arvore->raiz,x,y);
    }else{
        return -1;
    }
}

int calculaDistancia(Arv* arvore, int x, int y){
    int ancestral = ancestralComumBaixo(arvore,x,y);
    return diffProf(arvore,x,ancestral) + diffProf(arvore,y,ancestral);
}

void insereOrganizado(int vet[], int inicio, int fim, Arv* arvore){
    
    if(inicio>fim) return;
    int meio = (inicio+fim)/2;
    insereABB(arvore,vet[meio]);
    if(inicio == fim ) return;
    insereOrganizado(vet,inicio,meio-1,arvore);
    insereOrganizado(vet,meio+1,fim,arvore);
}
//retorna 1 se é abs, 0 c.c.
int ehABS(No* no){
    if(no==NULL) return 1;
    if(no->esq==NULL && no->dir == NULL) return 1;
    int somaFilhos=0;
    if(no->esq!=NULL) somaFilhos+=no->esq->dado;
    if(no->dir!=NULL) somaFilhos+=no->dir->dado;
    if(somaFilhos == no->dado && ehABS(no->esq) && ehABS(no->dir))
        return 1;
    return 0;
}

int ehABB(No* no){
    if(no==NULL) return 1;
    if(no->esq==NULL && no->dir == NULL) return 1;
    if(no->esq!=NULL)
        if(no->esq->dado > no->dado) return 0;
    if(no->dir!=NULL)
        if(no->dir->dado < no->dado) return 0;
    if(ehABB(no->esq) && ehABB(no->dir))
        return 1;
    return 0;
}

int somaArvore(No* no){
    if(no == NULL) return 0;
    return no->dado + somaArvore(no->esq) + somaArvore(no->dir);
}

int somaCaminho(No* no, int x){
    if(no->dado == x){
        return no->dado;
    }
    if(no->dado > x){
        return no->dado + somaCaminho(no->esq,x);
    }else{
        return no->dado + somaCaminho(no->dir,x);
    }
}

int numMax(No* no){
    if(no == NULL) return 0;
    if(no->esq !=NULL && no->dir!=NULL) return 2;
    if(no->esq!=NULL){
        if(numMax(no->esq) > 1)
            return 2;
        return 1;
    }
    if(no->dir!=NULL){
        if(numMax(no->dir) > 1)
            return 2;
        return 1;
    }
}

int numMin(No* no){
    if(no == NULL) return 0;
    if(no->dir == NULL && no->esq!=NULL) return 1;
    if(no->dir !=NULL && no->esq == NULL) return 1;
    int numFilhosEsq = numMin(no->esq);
    int numFilhosDir = numMin(no->dir);
    if(numFilhosDir == 0 && numFilhosEsq == 0)
        return 2;
    return (numFilhosDir<numFilhosEsq)?numFilhosDir:numFilhosEsq;
}

void refletir(No* no){
    if(no == NULL) return;

    No* aux = no->esq;
    no->esq = no->dir;
    no->dir = aux;

    refletir(no->esq);
    refletir(no->dir);
}


int saoSimilaresAux(No* no1, No* no2){
    if(no1!=NULL && no2!=NULL){
       if(no1->esq ==NULL && no1->dir == NULL){
            if(no2->esq == NULL && no2->dir == NULL){
                return 1;
            }
       }
       if(no1->esq == NULL && no1->dir !=NULL){
            if(no2->esq == NULL && no2->dir !=NULL){
                return saoSimilaresAux(no1->dir,no2->dir);
            }
       }
       if(no1->esq != NULL && no1->dir ==NULL){
            if(no2->esq != NULL && no2->dir ==NULL){
                return saoSimilaresAux(no1->esq,no2->esq);
            }
       }
       if(no1->esq != NULL && no1->dir !=NULL){
            if(no2->esq != NULL && no2->dir !=NULL){
                if(saoSimilaresAux(no1->esq,no2->esq) && saoSimilaresAux(no1->dir,no2->dir))
                    return 1;
            }
       }
    }
    return 0;
}
float resolveArvore(No* no){
    if(no->dado >='0' && no->dado <='9'){
        return (float) no->dado - '0';
    }
    float solucaoEsquerda = resolveArvore(no->esq);
    float solucaoDireita =  resolveArvore(no->dir);
    switch(no->dado){
        case '+': return solucaoEsquerda + solucaoDireita;
        case '-': return solucaoEsquerda - solucaoDireita;
        case '*': return solucaoEsquerda * solucaoDireita;
        case '/': return solucaoEsquerda / solucaoDireita;
    }

}

int main(){
    Arv* arvore = criaArvore();
    // arvore->raiz = criaNo(8);
    // arvore->raiz->esq = criaNo(5);
    // arvore->raiz->dir = criaNo(3);
    // arvore->raiz->esq->esq = criaNo(2);
    // arvore->raiz->esq->dir = criaNo(3);
    // arvore->raiz->dir->esq = criaNo(2);
    // arvore->raiz->dir->dir = criaNo(1);
    // insereABB(arvore,15);
    // insereABB(arvore, 6);
    // insereABB(arvore, 18);
    // insereABB(arvore, 3);
    // insereABB(arvore, 7);
    // insereABB(arvore, 17);
    // insereABB(arvore, 20);
    // insereABB(arvore, 19);
    // srand(time(NULL));
    // for(int i = 0;i<10;i++)
    //     insereABB(arvore,rand()%100);
    // int vet[] = {1,2,3,4,5,6,7,8,9};
    // insereOrganizado(vet,0,8,arvore);
    // imprimeOrganizado(arvore);
    // refletir(arvore->raiz);
    arvore->raiz = criaNo('+');
    arvore->raiz->esq = criaNo('/');
    arvore->raiz->dir = criaNo('*');
    arvore->raiz->esq->esq = criaNo('2');
    arvore->raiz->esq->dir = criaNo('3');
    arvore->raiz->dir->esq = criaNo('2');
    arvore->raiz->dir->dir = criaNo('1');
    imprimeOrganizado(arvore);
    printf("\nSolucao: %f\n",resolveArvore(arvore->raiz));
    return 0;
}