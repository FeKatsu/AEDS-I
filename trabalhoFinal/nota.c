#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nota.h"

Nota *criaNota(float nota, float valTotal, int id)
{
    Nota *novaNota = (Nota *)malloc(sizeof(Nota));
    novaNota->id = id;
    novaNota->chave = nota;
    novaNota->total = valTotal;
    novaNota->prox = NULL;
    return novaNota;
}

void insereNota(float notaVar, float notaMax, Aluno *aluno, int id)
{
    Nota *novaNota = criaNota(notaVar, notaMax, id);
    aluno->somaNotas+=notaVar;
    Nota *aux = aluno->notas;
    if(aux==NULL) aluno->notas = novaNota;   
    else{
        while(aux->prox!=NULL){
            aux=aux->prox;
        }
        aux->prox = novaNota;
    } 
}

void criaAvaliacao(Hash *tabela, int *id)
{
    float notaMax, notaVar = -1;
    (*id)++;
    printf("Quanto vale a avaliacao? ");
    scanf("%f", &notaMax);

    for (int i = 0; i < 100; i++)
    {
        if(tabela[i]->aluno==NULL) continue;
        while (notaVar < 0 || notaVar > notaMax)
        {
            printf("Digite a nota do aluno %s ", tabela[i]->aluno->nome);
            scanf("%f", &notaVar);
        }
        insereNota(notaVar, notaMax, tabela[i]->aluno, *id);
        notaVar = -1;
    }
}

void recuperaAvaliacao(int num, Aluno *aluno, Hash* tabela){
    float nota, valTotal;
    Nota *aux;
    //pega um aluno para usar de referência para valTotal
    for(int i=0; i<100; i++){
        if(tabela[i]->aluno==NULL || tabela[i]->aluno->notas==NULL)continue;
        aux = tabela[i]->aluno->notas;
        break;
    }
    for(int i=1; i<=num; i++){
        valTotal = aux->total;
        printf("Digite a nota da avaliacao %d: ", i);
        scanf("%f", &nota);
        insereNota(nota, valTotal, aluno, i);
        aux = aux->prox;
    }    
}

float media(Nota *lista)
{
    float total = 0;
    int contador = 0;
    while (lista != NULL)
    {
        total += lista->chave;
        contador++;
        lista = lista->prox;
    }

    return total / contador;
}
