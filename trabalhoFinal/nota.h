#ifndef NOTA_H
#define NOTA_H

    #include "hash.h"
    typedef struct nota {
        int id;
        float total;
        float chave;
        struct nota *prox;
    } Nota;    

    Nota *criaNota(float nota, float valTotal, int id);
    void insereNota(float notaVar, float notaMax, Aluno *aluno, int id);
    void criaAvaliacao(Hash *tabela, int *id);
    void recuperaAvaliacao(int num, Aluno *aluno, Hash* tabela);
    float media(Nota *lista);
#endif