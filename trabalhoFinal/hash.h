#ifndef HASH_H
#define HASH_H

    #include "aluno.h"

    typedef struct lista
    {
        Aluno *aluno;
        int prox;
    } Lista;

    typedef Lista *Hash;

    int hash(int valor);
    Hash *criaHash(int tam);
    void inserir(Hash *tabela, Aluno *aluno);
    Aluno *busca(int chave, Hash *tabela);
    Hash* copiarLista(Hash* original);
    void imprime(Hash *tabela);
#endif