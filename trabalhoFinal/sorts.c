#include <stdio.h>
#include <string.h>
#include "sorts.h"
void troca(Hash *tabela, int a, int b)
{   

    if (tabela[a]->aluno != NULL && tabela[b]->aluno != NULL) {
        Aluno* aux = tabela[a]->aluno;
        tabela[a]->aluno = tabela[b]->aluno;
        tabela[b]->aluno = aux;
    }
}

void selectionSort(Hash *tabela, int metodo)
{
    int menor;
    for (int i = 0; i < 100; i++)
    {
        if (tabela[i]->aluno == NULL) {
            continue; 
        }
        
        menor = i;
        for (int j = i + 1; j < 100; j++)
        {
            if (tabela[j]->aluno == NULL) {
                continue; 
            }
            
            if (metodo == 2) {  // Ordenar por nome
                if (strcmp(tabela[j]->aluno->nome, tabela[menor]->aluno->nome) < 0) {
                    menor = j;
                }
            } else {  // Ordenar por matrícula 
                if (tabela[j]->aluno->matricula < tabela[menor]->aluno->matricula) {
                    menor = j;
                }
            }
        }
        if (menor != i) {
            troca(tabela, i, menor);
        }
    }
}


Nota *extraiNotas(Hash *tabela, int id)
{
    Nota *inicio = NULL; // Ponteiro para o início da nova lista
    Nota *fim = NULL;    // Ponteiro para o fim da nova lista

    for (int i = 0; i < 100; i++)
    {
        if (tabela[i]->aluno == NULL) continue; 

        Aluno *alunoAux = tabela[i]->aluno;
        Nota *aux = alunoAux->notas;
        while (aux != NULL)
        {
            if (aux->id == id)
            {
                Nota *novaNota = criaNota(aux->chave, aux->total, aux->id);
                if (inicio == NULL)
                {
                    inicio = novaNota;
                    fim = novaNota;
                }
                else
                {
                    fim->prox = novaNota; // Conecta o último nó com a nova nota
                    fim = novaNota;       // Atualiza o ponteiro fim
                }
            }
            aux = aux->prox;
        }
    }
    if (inicio == NULL)
    {
        printf("Nenhuma nota encontrada com o id fornecido.\n");
    }

    return inicio;
}

void trocaNota(Nota *a, Nota *b, Nota **lista)
{
    Nota *inicio = *lista;
    if (a->chave == b->chave)
        return;

    Nota *antA = NULL, *A = inicio;
    Nota *antB = NULL, *B = inicio;

    // Procura pelo nó a e seu anterior
    while (A != NULL && A != a)
    {
        antA = A;
        A = A->prox;
    }

    // Procura pelo nó b e seu anterior
    while (B != NULL && B != b)
    {
        antB = B;
        B = B->prox;
    }

    if (antA != NULL)
        antA->prox = b;
    else
        *lista = b;

    if (antB != NULL)
        antB->prox = a;
    else
        *lista = a;

    // Troca os próximos ponteiros de a e b
    Nota *proxA = a->prox;
    a->prox = b->prox;
    b->prox = proxA;
}

void selectionNota(Nota **lista)
{
    Nota *maior;

    Nota *aux, *i = *lista;
    if (i==NULL || i->prox ==NULL) return;

    while (i != NULL)
    {
        maior = i;
        aux = i;
        while (aux != NULL)
        {
            if (aux->chave > maior->chave)
            {
                maior = aux;
            }
            aux = aux->prox;
        }
        trocaNota(i, maior, lista);
        i = maior;
        i = i->prox;
    }
}


int partition(Hash *tabela, int inicio, int fim, int metodo) {
    // Seleciona o pivot como o último elemento válido no intervalo
    Aluno* pivot = tabela[fim]->aluno;

    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        // Verifica se o elemento atual não é NULL
        if (tabela[j]->aluno != NULL && pivot != NULL) {
            int compara = 0;

            // Escolha do método de ordenação
            if (metodo == 1) {  // Ordenar por soma de notas
                compara = tabela[j]->aluno->somaNotas <= pivot->somaNotas;
            } else if (metodo == 2) {  // Ordenar por nome
                compara = strcmp(tabela[j]->aluno->nome, pivot->nome) <= 0;
            } else {  // Ordenar por matrícula (padrão)
                compara = tabela[j]->aluno->matricula <= pivot->matricula;
            }

            // Se o elemento atual for menor ou igual ao pivot, faz a troca
            if (compara) {
                i++;
                Aluno* temp = tabela[i]->aluno;
                tabela[i]->aluno = tabela[j]->aluno;
                tabela[j]->aluno = temp;
            }
        }
    }

    // Coloca o pivot na posição correta
    Aluno* temp = tabela[i + 1]->aluno;
    tabela[i + 1]->aluno = tabela[fim]->aluno;
    tabela[fim]->aluno = temp;

    return i + 1;  // Retorna o índice onde o pivot foi colocado
}

void quickSort(Hash *tabela, int inicio, int fim, int metodo) {
    if (inicio < fim) {
        // Particiona o array e obtém o índice do pivot
        int pivotIndex = partition(tabela, inicio, fim, metodo);

        // Ordena os elementos antes e depois do pivot
        quickSort(tabela, inicio, pivotIndex - 1, metodo);
        quickSort(tabela, pivotIndex + 1, fim, metodo);
    }
}