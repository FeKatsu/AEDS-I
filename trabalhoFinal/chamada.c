#include <stdio.h>
#include <stdlib.h>
#include "chamada.h"

void chamada(Hash *tabela){
    printf("Chamada\nPara aluno presente, aperte P\nPara aluno ausente, aperte F\n");
    for(int i=0; i<100; i++){
        if(tabela[i]->aluno==NULL) continue;

        char resp = '\n';

        printf("%s: ", tabela[i]->aluno->nome);
        while (resp == '\n') resp = getchar();

        if(resp=='F'||resp=='f') tabela[i]->aluno->numFaltas++;
        if (tabela[i]->aluno->numFaltas >= 10) printf("Aluno reprovado por faltas!\n");
    }
}

void recuperaChamada(Aluno *aluno, int num){
    for(int i=0; i<num; i++){
        char resp = '\n';

        printf("Chamada %d do %s: ", i+1, aluno->nome);
        while (resp == '\n') resp = getchar();

        if (resp == 'F' || resp=='f') aluno->numFaltas++;
        if (aluno->numFaltas >= 10) printf("Aluno reprovado por faltas!");
    }
}