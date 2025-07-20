#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

int limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return c;
}

Aluno *criaAluno(){    
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    char curso[50];
    char nome[50];
    
    printf("\nQual a matricula do aluno? ");
    scanf("%d", &novoAluno->matricula);
    limpar_buffer();

    printf("\nQual o nome do aluno? ");
    fgets(novoAluno->nome, 50, stdin);
    size_t len = strlen(novoAluno->nome);
    if (len > 0 && novoAluno->nome[len-1] == '\n') {
        novoAluno->nome[len-1] = '\0';
    }

    printf("\nQual o curso do aluno? ");
    fgets(novoAluno->curso, 50, stdin);
    len = strlen(novoAluno->curso);
    if (len > 0 && novoAluno->curso[len-1] == '\n') {
        novoAluno->curso[len-1] = '\0';
    }

    printf("\nQual o ano de entrada do aluno? ");
    scanf("%d", &novoAluno->anoEntrada);

    novoAluno->numFaltas = 0;
    novoAluno->notas = NULL;
    novoAluno->somaNotas = 0;
    
    return novoAluno;
}
