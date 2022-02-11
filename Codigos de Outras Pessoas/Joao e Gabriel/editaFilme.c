#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*struct Filme                             //já tem na main
{
    unsigned int indentificador;
    char nome[50];
    char genero[30];
    unsigned short int anoLancamento;
    char nomeDiretor[30];
};
*/

int editaFilme(Filme *ptr, int posicao)
{

    struct Filme filmes_lidos[50]; //chama a struct já estabelecida com o vetor de filmes com 50 posições

    int i; //declaração da variável para usar no laço
    int pos; //declaração da variável para ser a posição que o usuário deseja editar

    printf("Vetor de filmes:"); //exibe o vetor de filmes original

    for(i=0; i<50; i++)
    {
        printf("\nIdentificador do filme: %d", filmes_lidos[i].identificador);
        printf("\nNome do filme: %s", filmes_lidos[i].nome);
        printf("\nGênero do filme: %d", filmes_lidos[i].genero);
        printf("\nAno de lançamento: %d", filmes_lidos[i].anoLançamento);
        printf("\nDiretor do filme: %s", filmes_lidos[i].nomeDiretor);
    }

    printf("\n\nDigite a posicao do vetor desejada para editar:"); //pede a posição desejada do vetor que o usuário deseja editar
    scanf("%d", &pos); //armazena essa posição na variável "pos"

    for(i=0; (i > 50) || (i < 0); i++){ //garante que o valor escrito pelo usuário esteja sempre entre 0 e 50
        printf("Posição inválida. Digite uma entre 0 e 50:");
        scanf("%d", &pos);
    }

    printf("\nPosicao escolhida: %d", pos);

    for(i=0; i<50; i++) //usando o laço para percorrer todo o vetor
    {
        if(i == pos) //ao achar a posição desejada pelo usuário, é pedido para inserir os dados do filme desejado, armazenando os valores nas variáveis da struct
        {
            printf("\nDigite o nome do filme desejado para essa posicao:");
            scanf("%s", &filmes_lidos[pos].nome);

            printf("\nDigite o genero do filme desejado:");
            scanf("%s", &filmes_lidos[pos].genero);

            printf("\nDigite o ano de lancamento do filme:");
            scanf("%d", &filmes_lidos[pos].anoLancamento);

            printf("\nDigite o nome do diretor do filme:");
            scanf("%s", &filmes_lidos[pos].nomeDiretor);
        }
    }

    pritnf("Vetor atualizado:"); //exibindo o vetor de filmes atualizado

    for(i=0; i<50; i++) //percorre todo o vetor de filmes
    {
        if(i == pos) //se a posição "i" do vetor for igual à posição que o usuário fez a edição de filmes, é printado o novo filme inserido
        {
            printf("\nIdentificador do filme: %d", filmes_lidos[pos].identificador);
            printf("\nNome do filme: %s", filmes_lidos[pos].nome);
            printf("\nGênero do filme: %d", filmes_lidos[pos].genero);
            printf("\nAno de lançamento: %d", filmes_lidos[pos].anoLançamento);
            printf("\nDiretor do filme: %s", filmes_lidos[pos].nomeDiretor);
        }
        else // se não, é exibido os filmes do vetor original de cada posição "i"
        {
            printf("\nIdentificador do filme: %d", filmes_lidos[i].identificador);
            printf("\nNome do filme: %s", filmes_lidos[i].nome);
            printf("\nGênero do filme: %d", filmes_lidos[i].genero);
            printf("\nAno de lançamento: %d", filmes_lidos[i].anoLançamento);
            printf("\nDiretor do filme: %s", filmes_lidos[i].nomeDiretor);
        }
    }


}
