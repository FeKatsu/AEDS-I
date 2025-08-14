#include <stdio.h>
typedef struct contVal
{
    int retorna;
    int contador;
}Saida;

Saida buscaBin(int elem, int *vet, int n){
    int inicio = 0;
    Saida saida1;
    saida1.contador=0;
    while (inicio<=n){       
        saida1.contador++;
        saida1.retorna = (inicio+n)/2;
        if (vet[saida1.retorna]==elem) return saida1;
        if (vet[saida1.retorna]>elem) n=saida1.retorna-1;
        if (vet[saida1.retorna]<elem) inicio=saida1.retorna+1;
    }
    saida1.retorna = -1;
    return saida1;
}

Saida buscaSequencial(int elem, int *vet, int n){
    Saida saida2;
    saida2.contador=0;
    for (int i=0; i<n; i++){
        saida2.contador++;
        if(vet[i]==elem) return saida2;
    }
    saida2.retorna = -1;
    return saida2;
}

void main(){
    int vet100[100];
    int vet1000[1000];
    for (int i=0; i<100; i++){
        vet100[i]=i;
    }
    for (int i=0; i<1000; i++){
        vet1000[i]=i;
    }

    printf("Vetor 100:\n");
    Saida buscaB100 = buscaBin(99, vet100, 100);
    Saida buscaS100 = buscaSequencial(99, vet100, 100);
    printf("Busca binaria:\nIndice: %d\nContador: %d\n\n", buscaB100.retorna, buscaB100.contador);
    printf("Busca sequencial:\nIndice: %d\nContador: %d\n\n", buscaS100.retorna, buscaS100.contador);

    printf("Vetor 1000:\n");
    Saida buscaB1000 = buscaBin(999, vet1000, 1000);
    Saida buscaS1000 = buscaSequencial(999, vet1000, 1000);
    printf("Busca binaria:\nIndice: %d\nContador: %d\n\n", buscaB1000.retorna, buscaB1000.contador);
    printf("Busca sequencial:\nIndice: %d\nContador: %d\n\n", buscaS1000.retorna, buscaS1000.contador);
}