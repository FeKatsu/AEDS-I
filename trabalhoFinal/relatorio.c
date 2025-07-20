#include <stdio.h>
#include <stdlib.h>
#include "relatorios.h"

void relatorioNotas(Hash *tabela, int numAvaliacoes)
{
    if (numAvaliacoes == 0)
    {
        printf("Sem avaliacoes cadastradas");
        return;
    }
    int id;
    printf("Qual avaliacao voce quer o relatorio? Tem %d avaliacoes\n", numAvaliacoes);
    scanf("%d", &id);
    Nota *notasRel = extraiNotas(tabela, id);
    selectionNota(&notasRel);
    Nota *aux = notasRel;
    if (aux != NULL)
    {
        // nota maxima
        printf("Nota maxima: %.2f\n", aux->chave);
        // nota média
        printf("Nota media da avaliacao %d: %.2f\n", id, media(notasRel));
        // percorre até o final para encontrar a nota mínima
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        printf("Menor nota: %.2f\n", aux->chave);

        // todas as notas
        printf("\nTodas as notas:\n");
        while (notasRel != NULL)
        {
            printf("%.2f\n", notasRel->chave);
            notasRel = notasRel->prox;
        }
    }
    else
    {
        printf("Nenhuma nota encontrada.\n");
    }
}

void relatorioAlunos(Hash *tabela)
{
    int ordem;

    //faz uma copia para gerar o relatório
    Hash *copia = copiarLista(tabela); 
    
    printf("Ordenar por:\n1: Matricula\n2: Nome\n3: Soma de Notas\n4: Num. faltas:\n");
    scanf("%d", &ordem);
    switch (ordem)
    {
    case 1:
        // organiza por matricula
        selectionSort(copia, 1);
        break;
    case 2:
        // organiza por nome
        selectionSort(copia, 2);
        break;
    case 3:
        // organiza por soma
        quickSort(copia, 0, 99, 1);
        break;
    case 4:
        // organiza por numero de faltas
        quickSort(copia, 0, 99, 2);
        break;
    default:
        // organiza por matricula
        quickSort(copia, 0, 99, 3);
        break;
    }
    // matricula / nome / soma de notas / numero de faltas
    imprime(copia);
}
