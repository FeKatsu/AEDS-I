#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nota.h"
#include "aluno.h"
#include "hash.h"
#include "chamada.h"
#include "sorts.h"
#include "relatorios.h"

int main()
{
    int numAvaliacoes = 0, numChamada = 0;
    
    Hash *tabela = criaHash(100);

    int opt = -1;
    while(opt!=0){
        printf("\nControle de sala de aula:\n0-Sair\n1-Cadastrar aluno\n2-Cadastrar avaliacao\n3-Fazer chamada\n4-Gerar Relatorio aluno\n5-Gerar relatorio de avaliacao\n");
        scanf("%d", &opt);
        switch (opt)
        {
        case 0:            
            break;
        
        case 1:
            Aluno *novo = criaAluno();
    
            inserir(tabela, novo);
            if (numAvaliacoes>0){
                recuperaAvaliacao(numAvaliacoes, novo, tabela);
            }
            if(numChamada>0){
                recuperaChamada(novo, numChamada);
            }
            printf("Aluno cadastrado %s ", novo->nome);
            break;
        case 2:
            criaAvaliacao(tabela, &numAvaliacoes);
            break;
        case 3:
            if(numChamada>18) printf("Numero de aulas maximas cadastradas");
            else{
                chamada(tabela);
                numChamada++;
            } 
            break;
        case 4:
            relatorioAlunos(tabela);
            break;
        case 5:
            relatorioNotas(tabela, numAvaliacoes);
            break;
        default:
            break;
        }
    }
}
