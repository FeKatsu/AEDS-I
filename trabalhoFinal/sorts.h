#ifndef SORTS_H
#define SORTS_H

    #include "nota.h"

    void troca(Hash *tabela, int a, int b);
    void selectionSort(Hash *tabela, int metodo);

    Nota *extraiNotas(Hash *tabela, int id);
    void trocaNota(Nota *a, Nota *b, Nota **lista);
    void selectionNota(Nota **lista);

    int partition(Hash *tabela, int inicio, int fim, int metodo); 
    void quickSort(Hash *tabela, int inicio, int fim, int metodo);
#endif