#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct item{
    int dado;
    struct item* pai;
    struct item* prox;
    int rank;
}Item;

Item* criaItem(int dado){
    Item* novo = (Item*) malloc(sizeof(Item));
    novo->dado = dado;
    novo->pai = NULL;
    novo->prox = NULL;
    return novo;
}

void makeSet(Item* item){
    item->pai = item;
    item->prox = item;
    item->rank = 0;
}

Item* find(Item* i){
    if(i!=i->pai){
        i->pai = find(i->pai);
    }
    return i->pai;
}

void unionSets(Item* x, Item* y){
    Item* sx = find(x);
    Item* sy = find(y);

    Item* aux = sx->prox;
    sx->prox = sy->prox;
    sy->prox = aux;

    //sy->pai = sx;
    if(sx->rank > sy->rank){
        sy->pai = sx;
    }else{
        sx->pai = sy;
        if(sx->rank == sy->rank){
            sy->rank++;
        }
    }
}

void print(Item* x){
    Item* aux = find(x);
    do{
        printf("%d, ",aux->dado);
        aux = aux->prox;
    }while(aux!=find(x));
    printf("\n");

}

int main(){
    // Item* i1 = criaItem(1);
    // Item* i2 = criaItem(2);
    // Item* i3 = criaItem(3);
    // Item* i4 = criaItem(4);
    // makeSet(i1);
    // makeSet(i2);
    // makeSet(i3);
    // makeSet(i4);
    // unionSets(i1,i3);
    // unionSets(i3,i2);
    // printf("%d,rank:%d\n ",find(i1)->dado,find(i1)->rank);
    // printf("%d,rank:%d\n ",find(i2)->dado,find(i2)->rank);
    // printf("%d,rank:%d\n ",find(i3)->dado,find(i3)->rank);
    // printf("%d,rank:%d\n ",find(i4)->dado,find(i4)->rank);
    // print(i2);
    // print(i3);


    // Item* vet[10];
    // for(int i = 0;i<10;i++){
    //     vet[i] = criaItem(i);
    //     makeSet(vet[i]);
    // }
    // srand(time(NULL));
    // for(int i = 0;i<5;i++){
    //     int k = rand()%10;
    //     int l = rand()%10;
    //     unionSets(vet[k],vet[l]);
    // }
    // for(int i = 0;i<10;i++){
    //     print(vet[i]);
    // }

    int numMaquinas;
    scanf("%d",&numMaquinas);
    Item** vet = (Item**) malloc(numMaquinas*sizeof(Item*));
    for(int i = 0;i<numMaquinas;i++){
        vet[i] = criaItem(i);
        makeSet(vet[i]);
    }
    int i,j;
    scanf("%d",&i);
    while(i!=-1){
        scanf("%d",&j);
        unionSets(vet[i],vet[j]);
        scanf("%d",&i);
    }

    int* vetAux = (int*) malloc(numMaquinas*sizeof(int));
    int numConjuntos = 0;
    for(int i = 0;i<numMaquinas;i++){
        if(vetAux[i] == 0){
            numConjuntos++;
            Item* rep = find(vet[i]);
            for(int j = 0;j<numMaquinas;j++){
                if(vetAux[j] == 0 && rep == find(vet[j])){
                    vetAux[j] = 1;
                }
            }
        }
        
    }
    printf("Numero de conjuntos: %d\n",numConjuntos);

    return 0;
}