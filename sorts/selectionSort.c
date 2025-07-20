#include <stdio.h>

void imprime(int *vet, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", vet[i]);
    }
}

void troca(int *vet, int a, int b)
{
    int aux = vet[a];
    vet[a] = vet[b];
    vet[b] = aux;
}

void selectionSort(int *vet, int tam)
{
    int menor;
    for (int i = 0; i < tam - 1; i++)
    {
        menor = i;
        for (int j = i; j < tam; j++)
        {
            if (vet[j] < vet[menor])
            {
                menor = j;
            }
        }
        troca(vet, i, menor);
    }
}

void main()
{
    int vet[3] = {3,1,2};
    selectionSort(vet, 3);
    imprime(vet, 3);
}