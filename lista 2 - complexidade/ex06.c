#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    char nome[10];
    int matricula;
    float notaFinal;
}Aluno;

void imprime(Aluno *vet, int n){
    for (int i = 0; i < n; i++) {
        printf("%s ", vet[i].nome);
    }
}

void troca(Aluno *vet, int a, int b){
    Aluno aux = vet[a];
    vet[a]=vet[b];
    vet[b]=aux;
}
void criaVet(Aluno *vet, int n){
        Aluno alunNovo;
        printf("\nnome do aluno: ");
        scanf("%s", alunNovo.nome);
        printf("matricula do aluno: ");
        scanf("%d", &alunNovo.matricula);
        printf("nota final do aluno: ");
        scanf("%f", &alunNovo.notaFinal);
        
        vet[n] = alunNovo;
}

void insertionSort(Aluno *vet, int n){
    for(int i=1; i<n; i++){
        int j=i;
        while(j>0 && vet[j].matricula<vet[j-1].matricula){
            troca(vet, j, j-1);
            j--;
        }
    }
}
void selectionSort(Aluno *vet, int n){
    int menor;
    for(int i=0; i<n-1; i++){
        menor = i;
        for(int j=i; j<n; j++){
            if (vet[j].notaFinal<vet[menor].notaFinal){
                menor=j;
            }
        }
        troca(vet, i, menor);
    }
}

void main(){
    int n;
    printf("valor de n: ");
    scanf("%d", &n);

    Aluno *vetor;
    vetor = (Aluno*)malloc(n*sizeof(Aluno));
    for(int i=0; i<n; i++){
        criaVet(vetor, i);
    }

    printf("\nVetor ordenado pela matricula: \n");
    insertionSort(vetor, n);
    imprime(vetor, n);

    printf("\nVetor ordenado pela nota final: \n");
    selectionSort(vetor, n);
    imprime(vetor, n);
}