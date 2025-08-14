 #include <stdio.h>
 
int somaAlg(int n){
    if(n/10<1) return n;
    return somaAlg(n/10)+n%10;
}
void main(){
    int x;
    printf("digite um numero inteiro: ");
    scanf("%d",&x);

    printf("%d",somaAlg(x));
}