#define TAM_MAX 100

typedef struct heap_str{
    int vet[TAM_MAX];
    int tam;
}Heap;

void troca(int *vet, int i, int j);
Heap* criarHeap();
int heap_max(Heap *h);
int esquerda(int i);
int direita(int i);
int pai(int i);
void max_heapify(Heap *h, int i);
int heap_extrai_max(Heap *h);
void heap_aumenta_chave(Heap *h, int i, int chave);
void heap_insere(Heap *h, int chave);
void heap_imprime(Heap *h);
void heapSort(int *vet, int n);

