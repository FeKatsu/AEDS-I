#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int hash(int valor){
    return valor%100;
}

Hash *criaHash(int tam){
    Hash *novaHash = (Hash*)malloc(sizeof(Hash)*tam);

    for(int i=0; i<tam; i++){   
        Lista *novaLista = (Lista*)malloc(sizeof(Lista));
        novaLista->aluno = NULL;
        novaLista->prox = -1;
        novaHash[i] = novaLista;
    }
    return novaHash;
}

void inserir(Hash *tabela, Aluno *aluno){
    int indice = hash(aluno->matricula);

    if(tabela[indice]->aluno!=NULL){
        int i;
        for (i = (indice+1); tabela[i]->aluno!=NULL && i != indice; i = (i + 1) % 100);
        //procura um índice válido se indice já estiver ocupado e avisa caso a tabela hash esteja cheia
        if (i == indice) {
            printf("Tabela hash cheia, não foi possível inserir %s\n", aluno->nome);
            return;
        }

        //atualiza os campos prox
        while(tabela[indice]->prox!=-1){
            indice = tabela[indice]->prox;
        }
        tabela[indice]->prox = i;

        //insere o aluno
        tabela[i]->aluno = aluno;
    }

    else {
        //caso o indice iniciado esteja vazio, apenas insere
        tabela[indice]->aluno = aluno;
    }
}

Aluno *busca(int chave, Hash *tabela){
    int indice = hash(chave);

    while(indice!=-1){
        if(tabela[indice]->aluno->matricula == chave) return tabela[indice]->aluno;
        indice = tabela[indice]->prox;
    }
    return NULL;
}

Hash* copiarLista(Hash* original) {
    Hash* novaHash = criaHash(100);
    
    for(int i=0; i<100; i++){
        if(original[i]->aluno==NULL) continue;
        novaHash[i] = original[i];
    }

    return novaHash;
}

void imprime(Hash *tabela) {
    for(int i=0; i<100; i++){
        if(tabela[i]->aluno==NULL) continue;
        printf("_________________________\n");
        printf("Matricula: %d\n", tabela[i]->aluno->matricula);
        printf("Nome: %s\n", tabela[i]->aluno->nome);
        printf("Soma de Notas: %.2f\n", tabela[i]->aluno->somaNotas);
        printf("Numero de faltas: %d\n", tabela[i]->aluno->numFaltas);
        printf("_________________________\n");
    }
}
