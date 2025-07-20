#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nota
{
    int id;
    float total;
    float chave;
    struct nota *prox;
} Nota;

typedef struct aluno
{
    int matricula;
    int anoEntrada;
    int numFaltas;
    float somaNotas;
    char nome[50];
    char curso[50];
    struct aluno *prox;
    Nota *notas;
} Aluno;

typedef struct lista
{
    Aluno *cabeca;
} Lista;

int hash(int x)
{
    return x % 100;
}

Aluno *busca(int chave, int indice, Lista *lista)
{
    Aluno *aux = lista[indice].cabeca;
    while (aux != NULL && aux->matricula != chave)
    {
        aux = aux->prox;
    }
    return aux;
}

void insereAluno(Aluno *aluno, Lista lista[])
{
    int i = hash(aluno->matricula);
    Aluno *p = busca(aluno->matricula, i, lista);
    if (p == NULL)
    {
        Aluno *novo_aluno = (Aluno *)malloc(sizeof(Aluno));
        novo_aluno = aluno;
        novo_aluno->prox = lista[i].cabeca;
        lista[i].cabeca = novo_aluno;
    }
    else
    {
        printf("\nJa existe o aluno: %s\n", p->nome);
    }
}

Aluno *criaAluno(int matricula, int anoEntrada, char curso[50], char nome[50])
{
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    novoAluno->matricula = matricula;
    novoAluno->anoEntrada = anoEntrada;
    strcpy(novoAluno->curso, curso);
    strcpy(novoAluno->nome, nome);
    novoAluno->numFaltas = 0;
    novoAluno->notas = NULL;
    novoAluno->somaNotas = 0;

    return novoAluno;
}

Aluno * alunoNovo(Lista *lista){
    int mat, anoEnt;
            char curso[50];
            char nome[50];

            printf("\nQual a matricula do aluno? ");
            scanf("%d", &mat);
            printf("\nQual o nome do aluno? ");
            scanf("%49s", nome);
            printf("\nQual o curso do aluno? ");
            scanf("%49s", curso);
            printf("\nQual o ano de entrada do aluno? ");
            scanf("%d", &anoEnt);
            Aluno *novoAluno = criaAluno(mat, anoEnt, curso, nome);
            insereAluno(novoAluno, lista);
            return novoAluno;
}

void imprimeNota(Aluno *aluno)
{
    Nota *aux = aluno->notas;

    while (aux != NULL)
    {
        printf("Nota: %.2f\n", aux->chave);
        aux = aux->prox;
    }
}

Nota *criaNota(float nota, float valTotal, int id)
{
    Nota *novaNota = (Nota *)malloc(sizeof(Nota));
    novaNota->id = id;
    novaNota->chave = nota;
    novaNota->total = valTotal;
    novaNota->prox = NULL;
    return novaNota;
}
void insereNota(Aluno **aluno, float nota, float valTotal, int id, Lista *lista)
{
    int matricula = (*aluno)->matricula;
    int i = hash(matricula);
    Aluno *modifica = busca(matricula, i, lista);
    if (modifica == NULL)
    {
        printf("Aluno com matrícula %d não encontrado.\n", matricula);
        return;
    }

    modifica->somaNotas += nota;
    Nota *novaNota = criaNota(nota, valTotal, id);
    Nota *aux = modifica->notas;
    if (aux == NULL)
    {
        modifica->notas = novaNota;
        return;
    }
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->prox = novaNota;
}

void imprime(Lista *lista)
{
    for (int i = 0; i < 100; i++)
    {
        Aluno *aux = lista[i].cabeca;
        while (aux != NULL)
        {
            printf("pos %d: ", i);
            printf("%s\n", aux->nome);
            imprimeNota(aux);
            aux = aux->prox;
        }
    }
}
void criaAvaliacao(Lista lista[], int *id)
{
    float notaMax, notaVar = -1;
    (*id)++;
    printf("Quanto vale a avaliacao? ");
    scanf("%f", &notaMax);

    for (int i = 0; i < 100; i++)
    {
        Aluno *aux = lista[i].cabeca;
        while (aux != NULL)
        {
            while (notaVar < 0 || notaVar > notaMax)
            {
                printf("Digite a nota do aluno %s ", aux->nome);
                scanf("%f", &notaVar);
            }
            insereNota(&aux, notaVar, notaMax, *id, lista);
            notaVar = -1;
            aux = aux->prox;
        }
    }
}

Lista *criaLista(int tam){
    Lista *novaLista = (Lista*)malloc(tam*sizeof(Lista));
    for(int i=0; i<tam; i++) novaLista[i].cabeca = NULL;
    return novaLista;
}

void chamada(Lista *lista)
{
    
    printf("Para aluno presente aperte P \nPara aluno ausente aperte F\n");
    for (int i = 0; i < 100; i++)
    {
        if (lista[i].cabeca == NULL) continue;

        Aluno *aux = lista[i].cabeca;

        while (aux != NULL)
        {
            char x = '\n';
            printf("\npos %d: ", i);
            printf("%s: ", aux->nome);
            while (x == '\n') {
                x = getchar();
            } 

            if (x == 'F' || x=='f')
                aux->numFaltas++;

            if (aux->numFaltas >= 10)
            {
                printf("Aluno reprovado por faltas!");
            }
            aux = aux->prox;
        }
    }
}

Lista *extraiLista(Lista *lista)
{
    Lista *temp = (Lista *)malloc(sizeof(Lista));
    temp->cabeca = NULL;
    Aluno *ultimo = NULL;
    for (int i = 0; i < 100; i++)
    {
        if (lista[i].cabeca == NULL)
            continue;
        Aluno *aux = lista[i].cabeca;
        while (aux != NULL)
        {
            Aluno *novoAluno = criaAluno(aux->matricula, aux->anoEntrada, aux->curso, aux->nome);
            novoAluno->notas = aux->notas;
            novoAluno->somaNotas = aux->somaNotas;
            novoAluno->numFaltas = aux->numFaltas;

            if (temp->cabeca == NULL)
            {
                temp->cabeca = novoAluno;
            }
            else
            {
                ultimo->prox = novoAluno;
            }
            ultimo = novoAluno;
            aux = aux->prox;
        }
    }

    return temp;
}

void imprimeEnc(Lista *listaenc)
{
    Aluno *aux = listaenc->cabeca;
    while (aux != NULL)
    {
        printf("_________________________\n");
        printf("Matricula: %d\n", aux->matricula);
        printf("Nome: %s\n", aux->nome);
        printf("Soma de Notas: %.2f\n", aux->somaNotas);
        printf("Numero de faltas: %d\n", aux->numFaltas);
        printf("_________________________\n");

        aux = aux->prox;
    }
}

Nota *extraiNotas(Lista *lista, int id)
{
    Nota *inicio = NULL; // Ponteiro para o início da nova lista
    Nota *fim = NULL;    // Ponteiro para o fim da nova lista

    for (int i = 0; i < 100; i++)
    {
        if (lista[i].cabeca == NULL)
        {
            continue; // Pula para a próxima iteração se não houver aluno nesta posição
        }
        Aluno *alunoAux = lista[i].cabeca;
        while (alunoAux != NULL)
        {
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
            alunoAux = alunoAux->prox;
        }
    }
    if (inicio == NULL)
    {
        printf("Nenhuma nota encontrada com o id fornecido.\n");
    }
    return inicio;
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

    total = total / contador;

    return total;
}

void separa(Aluno *inicio, Aluno **a, Aluno **b)
{
    Aluno *achaMeio, *achaFim;

    achaMeio = inicio;
    achaFim = inicio->prox;

    while (achaFim != NULL)
    {
        achaFim = achaFim->prox;
        if (achaFim != NULL)
        {
            achaMeio = achaMeio->prox;
            achaFim = achaFim->prox;
        }
    }
    *a = inicio;
    *b = achaMeio->prox;
    achaMeio->prox = NULL;
}
Aluno *merge(Aluno *a, Aluno *b, int metodo)
{
    Aluno *resultado = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    if (metodo == 1)
    {
        if (a->somaNotas <= b->somaNotas)
        {
            resultado = a;
            resultado->prox = merge(a->prox, b, metodo);
        }
        else
        {
            resultado = b;
            resultado->prox = merge(a, b->prox, metodo);
        }
    }
    else
    {
        if (a->numFaltas <= b->numFaltas)
        {
            resultado = a;
            resultado->prox = merge(a->prox, b, metodo);
        }
        else
        {
            resultado = b;
            resultado->prox = merge(a, b->prox, metodo);
        }
    }
    return resultado;
}
void mergeSort(Lista *lista, int metodo)
{
    Aluno *inicio = lista->cabeca;
    Aluno *a;
    Aluno *b;

    if ((inicio == NULL) || (inicio->prox == NULL))
        return;

    separa(inicio, &a, &b);

    Lista listaA;
    listaA.cabeca = a;

    Lista listaB;
    listaB.cabeca = b;

    mergeSort(&listaA, metodo);
    mergeSort(&listaB, metodo);

    lista->cabeca = merge(listaA.cabeca, listaB.cabeca, metodo);
}

void troca(Aluno *a, Aluno *b, Lista *lista)
{
    Aluno *inicio = lista->cabeca;
    if (a->matricula == b->matricula)
        return;

    Aluno *antA = NULL, *A = inicio;
    Aluno *antB = NULL, *B = inicio;

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
        lista->cabeca = b;

    if (antB != NULL)
        antB->prox = a;
    else
        lista->cabeca = a;

    // Troca os próximos ponteiros de a e b
    Aluno *proxA = a->prox;
    a->prox = b->prox;
    b->prox = proxA;
}
void selectionSort(Lista *lista, int metodo)
{
    Aluno *menor;

    Aluno *aux, *i = lista->cabeca;
    if (i==NULL || i->prox ==NULL) return;

    while (i != NULL)
    {
        menor = i;
        aux = i;
        while (aux != NULL)
        {
            if (metodo == 1)
            {
                if (aux->matricula < menor->matricula)
                {
                    menor = aux;
                }
            }
            else
            {
                if (strcmp(aux->nome, menor->nome) < 0)
                    menor = aux;
            }
            aux = aux->prox;
        }
        troca(i, menor, lista);
        i = menor;
        i = i->prox;
    }
}

void relatorioAlunos(Lista *lista)
{
    Lista *listaenc = extraiLista(lista);
    int ordem;
    if(listaenc->cabeca == NULL) {
        printf("Sem alunos cadastrados");
        return;
    }
    
    printf("Ordenar por:\n1: Matricula\n2: Nome\n3: Soma de Notas\n4: Num. faltas:\n");
    scanf("%d", &ordem);
    switch (ordem)
    {
    case 1:
        // organiza por matricula
        selectionSort(listaenc, 1);
        break;
    case 2:
        // organiza por nome
        selectionSort(listaenc, 2);
        break;
    case 3:
        // organiza por soma
        mergeSort(listaenc, 1);
        break;
    case 4:
        // organiza por numero de faltas
        mergeSort(listaenc, 2);
        break;
    default:
        // organiza por matricula
        selectionSort(listaenc, 1);
        break;
    }
    // matricula / nome / soma de notas / numero de faltas
    imprimeEnc(listaenc);
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

void relatorioNotas(Lista *lista, int numAvaliacoes)
{
    if(numAvaliacoes==0) {
        printf("Sem avaliacoes cadastradas");    
        return;
    }
    int id;
    printf("Qual avaliacao voce quer o relatorio? Ha %d avaliacoes\n", numAvaliacoes);
    scanf("%d", &id);
    Nota *notasRel = extraiNotas(lista, id);
    selectionNota(&notasRel);
    Nota *aux = notasRel;
    if(aux != NULL) {
    // nota mínima
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
} else {
    printf("Nenhuma nota encontrada.\n");
}

}

void recuperaAvaliacoes(Aluno *aluno, int num, Lista *lista){
    float nota, valTotal;
    Nota *aux;
    for(int i=0; i<100; i++){
        if(lista[i].cabeca == NULL) continue;
        aux = lista[i].cabeca->notas;
        break;
    }
    for(int i=1; i<=num; i++){
        valTotal = aux->total;
        printf("Digite a nota da avaliacao %d: ", i);
        scanf("%f", &nota);
        insereNota(&aluno, nota, valTotal, i, lista);
        aux = aux->prox;
    }
}

void recuperaChamada(Aluno *aluno, int num){
    for(int i=0; i<num; i++){
        char x = '\n';
        printf("Chamada %s: ", aluno->nome);
            while (x == '\n') {
                x = getchar();
            } 

            if (x == 'F' || x=='f')
                aluno->numFaltas++;

            if (aluno->numFaltas >= 10)
            {
                printf("Aluno reprovado por faltas!");
            }
    }
}
int main()
{
    int numAvaliacoes = 0, numChamada = 0;

    Lista *lista = criaLista(100);
    int opt = -1;
    while(opt!=0){
        printf("\nControle de sala de aula:\n0-Sair\n1-Cadastrar aluno\n2-Cadastrar avaliacao\n3-Fazer chamada\n4-Gerar Relatorio aluno\n5-Gerar relatorio de avaliacao\n");
        scanf("%d", &opt);
        switch (opt)
        {
        case 0:            
            break;
        
        case 1:
            Aluno *novo = alunoNovo(lista);
            if (numAvaliacoes>0){
                recuperaAvaliacoes(novo, numAvaliacoes, lista);
            }
            if(numChamada>0){
                recuperaChamada(novo, numChamada);
            }
            printf("nome: %s", novo->nome);
            break;
        case 2:
            criaAvaliacao(lista, &numAvaliacoes);
            break;
        case 3:
            chamada(lista);
            numChamada++;
            break;
        case 4:
            relatorioAlunos(lista);
            break;
        case 5:
            relatorioNotas(lista, numAvaliacoes);
            break;
        default:
            break;
        }
    }
    //Aluno *novo = criaAluno(101, 2020, "economia", "Rafaela");
    //Aluno *aluno1 = criaAluno(300, 2020, "economia", "Paulo");
    //insereAluno(novo, lista);
    //insereAluno(aluno1, lista);
    //Aluno *novo2 = criaAluno(155, 2020, "economia", "Mateus");
    //insereAluno(novo2, lista);
//
    //insereNota(&aluno1, 8, 10, 0, lista);
    //insereNota(&aluno1, 7, 10, 1, lista);
    //insereNota(&aluno1, 6, 10, 2, lista);
    //insereNota(&aluno1, 5, 10, 3, lista);
//
    //insereNota(&novo, 5, 10, 0, lista);
    //insereNota(&novo, 3, 10, 1, lista);
    //insereNota(&novo, 7, 10, 2, lista);
    //insereNota(&novo, 9, 10, 3, lista);
//
    //insereNota(&novo2, 5, 10, 0, lista);
    //insereNota(&novo2, 3, 10, 1, lista);
    //insereNota(&novo2, 8, 10, 2, lista);
    //insereNota(&novo2, 9, 10, 3, lista);
    //printf("\n");
    // criaAvaliacao(lista, &numAvaliacoes);

//    relatorioAlunos(lista);
//
//    relatorioNotas(lista, numAvaliacoes);

    // Nota *notas = extraiNotas(lista, 2);
    // imprimeTeste(notas);
    // relatorioNotas(lista, numAvaliacoes);

    return 0;
}
