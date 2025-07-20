#include<stdio.h>
#include<stdlib.h>
typedef struct unionFind{
    int *X;
    int tam;
}UnionFind;

UnionFind* criaUF(int tam){
    UnionFind* uf = (UnionFind*) malloc(sizeof(UnionFind));
    uf->X = (int*) malloc(tam*sizeof(int));
    for(int i = 0;i<tam;i++) uf->X[i] = -1;
    uf->tam = tam;
    return uf;
}

void makeSet(UnionFind* uf, int x){
    uf->X[x] = x;
}

int find(UnionFind* uf, int x){
    return uf->X[x];
}

void print(UnionFind* uf, int x){
    for(int z = 0; z<uf->tam;z++){
        if(uf->X[z] == uf->X[x]){
            printf("%d, ",z);
        }
    }
    printf("\n");
}

void unionUF(UnionFind* uf, int i, int j){
    for(int z = 0; z<uf->tam;z++){
        if(uf->X[z] == uf->X[j])
            uf->X[z] = uf->X[i];
    }
}

int main(){
    UnionFind* uf = criaUF(10); //0,1,2,3,4,5,6,7,8,9
    for(int i = 0;i<10;i++) makeSet(uf,i);
    printf("%d ",find(uf,3));
    unionUF(uf,3,7);
    printf("\n%d, %d \n",find(uf,3),find(uf,7));
    unionUF(uf,7,4);
    print(uf,3);
    return 0;
}