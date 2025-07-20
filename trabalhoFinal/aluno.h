#ifndef ALUNO_H
#define ALUNO_H

    struct nota;

    typedef struct aluno
    {
        int matricula;
        int anoEntrada;
        int numFaltas;
        float somaNotas;
        char nome[50];
        char curso[50];
        struct nota *notas;
    } Aluno;

    Aluno *criaAluno();
#endif