#include <stdio.h>
#define N 3
void multiplica(int mat1[][N], int mat2[][N], int mat3[][N], int n, int *contador){
    
    for(int l=0; l<n;l++){
        for(int j=0; j<n;j++){
            for(int i=0; i<n;i++){
                mat3[l][j]+=(mat1[l][i] * mat2[i][j]);
                *contador+=1;
            }
        }
    }
}

void imprime(int mat[][N], int n){
    for (int i = 0; i < n; i++)
    {
        for(int j=0; j<n; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    
}

void main(){
    int cont=0;
    int mat3[N][N]={0};
    int mat1[N][N]={{1,2,3},{4,5,6},{7,8,9}};
    int mat2[N][N]={{1,4,7},{2,5,8},{3,6,9}};
    
    multiplica(mat1,mat2, mat3,N,&cont);
    imprime(mat3, N);
    printf("contador: %d", cont);
}