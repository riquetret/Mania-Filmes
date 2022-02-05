#include <stdio.h>
#include <string.h>


typedef struct { //declaração da struct
    char nome[51];
    char genero[31];
    int anoLancamento;
    char nomeDiretor[31];
}Filme;

int imprimeFilmes(Filme *ptr,int posicao,int tam);

int main(){ // main somente para fazer o basico do programa
    int x;
    Filme teste[3];

    strcpy(teste[0].nome,"Harry Potter");
    strcpy(teste[0].genero,"Fantasia");
    teste[0].anoLancamento = 2001;
    strcpy(teste[0].nomeDiretor,"Alfonso Cuaron");

    printf("Qual Funcao deseja utilizar?\n");
    printf("Funcao 1: ImprimeFilme\n");
    printf("Digite o numero da funcao:");
    scanf("%d",&x);
    if(x == 1){
        printf("\n");
        imprimeFilmes(&teste[0],1,3);
    }

    return 0;
}

/*
Função: ImprimeFilme
Autor: Pedro Carneiro Rabetim
Objetivo: ler do teclado qual filmes serão impresso(ou no caso todos)
imprimir todos os dados de um filme expecífico ou de todos
*/

int imprimeFilmes(Filme *ptr,int posicao,int tam){

    int n;

    printf("Digite o numero do filme que gostaria de imprimir seus dados,\n");
    printf("ou -1 para imprimir todos\n");

    if(posicao == -1){
        for(n=0;n<tam;n++){
            printf("Nome:");
            puts(ptr[n].nome);
            printf("Genero:");
            puts(ptr[n].genero);
            printf("Ano:");
            printf("%d\n",ptr[n].anoLancamento);
            printf("Diretor:");
            puts(ptr[n].nomeDiretor);
            printf("Posicao:%d",n+1);
        }
        }else{
            printf("Nome:");
            puts(ptr[posicao-1].nome);
            printf("Genero:");
            puts(ptr[posicao-1].genero);
            printf("Ano:");
            printf("%d\n",ptr[posicao-1].anoLancamento);
            printf("Diretor:");
            puts(ptr[posicao-1].nomeDiretor);
            return 0;
    }

    return n+1;
}
