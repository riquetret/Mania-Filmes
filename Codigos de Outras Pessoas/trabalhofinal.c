#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>






typedef struct { //declaração da struct junto com a mudança do nome sruct Filme para apenas Filme
    int identificador;
    char nome[51];
    char genero[31];
    int anoLancamento;
    char nomeDiretor[31];
}Filme;

int adicionaFilme(Filme *ponteiro, int filmes_adicionados); //decalração dos protótipos das funções adiciona filme e remove filme
int removeFilme(Filme *ponteiro, int posicao);

int main(){

    srand(time(NULL));
    Filme vetor[50];
    int i;

    adicionaFilme(vetor, 0);

    for(i=0;i<10;i++){
        printf("\n%d", vetor[i].identificador);
        printf("\n%s", vetor[i].nome);
        printf("\n%s", vetor[i].genero);
        printf("\n%d", vetor[i].anoLancamento);
        printf("\n%s", vetor[i].nomeDiretor);
    }

    removeFilme(vetor, 0);
    removeFilme(vetor, 8);

    printf("\n");

    for(i=0;i<10;i++){
        printf("\n%d", vetor[i].identificador);
        printf("\n%s", vetor[i].nome);
        printf("\n%s", vetor[i].genero);
        printf("\n%d", vetor[i].anoLancamento);
        printf("\n%s", vetor[i].nomeDiretor);
    }

    return 0;
}

/*
Função: adicionaFilme
Autor: Lucas Silva e Roginaldo Junior

Objetivo: ler do teclado quantos filmes serão adicionados,
requisitar os dados dos filmes e por fim adicionar esses dados
no vetor onde todos os filmes estão sendo armazenados
*/

int adicionaFilme(Filme *ponteiro, int filmes_adicionados){ //desenvolvimento do protótipo da função adiciona filme

    float teste = 0.0; //declaração das variáveis utilizadas
    int n = 0, i, j;

    printf("Quantos filmes deseja adicionar? "); //solicita quantidades de filmes a serem adicionados no vetor
    scanf("%f", &teste); //lê do teclado a quantidade de filmes
    fflush(stdin);
    n = (int)teste;

    while((teste - n) !=0 || n > 50 || n < 1){ //validação da entrada do número de filmes a serem adicionados
        printf("O numero inserido nao e valido"); //enquanto o número de filmes a serem adicionados estiver inválido
        printf("\nDigite novamente: ");          //a mensagem "O numero inserido não é válido digite novamente: " será repetida
        scanf("%f", &teste);
        fflush(stdin);
        n = (int)teste;
    }

    for(i = filmes_adicionados; i < n; i++){ //inserção dos dados dos filmes no vetor
        ponteiro[i].identificador = 1 + rand()%999999; //atrelando um identificador a cada filme adicionado
        for(j = 0; j < i; j++){
            if(ponteiro[j].identificador == ponteiro[i].identificador){
                ponteiro[i].identificador++;
            }
        }
        printf("Digite o nome do %d%c filme: ", i+1, 248); //atrelando o nome do filme inserido pelo usuário ao filme colocado no vetor
        scanf("%[^\n]", ponteiro[i].nome);
        fflush(stdin);
        printf("Digite o genero do %d%c filme: ", i+1, 248); //atrelando o genero do filme inserido pelo usuário ao filme colocado no vetor
        scanf("%[^\n]", ponteiro[i].genero);
        fflush(stdin);
        printf("Digite o ano de lancamento do %d%c filme: ", i+1, 248); //atrelando o ano de lançamento do filme inserido pelo usuário
        scanf("%d", &ponteiro[i].anoLancamento);                        //ao filme colocado no vetor
        fflush(stdin);

        while(ponteiro[i].anoLancamento < 1900 || ponteiro[i].anoLancamento > 2021){ //validação da entrada do ano de lançamento do filme
            printf("O ano inserido nao e valido");                                   //inserido pelo usuário
            printf("\nDigite novamente um ano entre 1900 e 2021: ");
            scanf("%d", &ponteiro[i].anoLancamento);
            fflush(stdin);
        }

        printf("Digite o nome do diretor do %d%c filme: ", i+1, 248); //atrelando o nome do diretor do filme inserido pelo usuário
        scanf("%[^\n]", ponteiro[i].nomeDiretor);                     //ao filme colocado no vetor
        fflush(stdin);
    }

   return 0; //retorno da função após sua conclusão
}

/*
Função: removeFilme
Autor: Lucas Silva e Roginaldo Junior

Objetivo: remover o filme que está na posição inserida como
parâmetro da função, 'zerando' o identificador e o ano de lançamento
atribuindo o valor 0 e os demais dados atribuindo o caracter '\0' na
primeira posição da string.
*/

int removeFilme(Filme *ponteiro, int posicao){ //desenvolvimento do protótipo da função remove filme

    ponteiro[posicao].identificador = 0; //removendo o identificador atrelado ao filme zerando ele
    ponteiro[posicao].nome[0] = '\0'; //removendo o nome atrelado ao filme zerando ele
    ponteiro[posicao].genero[0] = '\0'; //removendo o genero atrelado ao filme zerando ele
    ponteiro[posicao].anoLancamento = 0; //removendo o ano de lançamento atrelado ao filme zerando ele
    ponteiro[posicao].nomeDiretor [0]= '\0'; //removendo o nome do diretor atrelado ao filme zerando ele

    return 0; //retorno da função após sua conclusão
}

