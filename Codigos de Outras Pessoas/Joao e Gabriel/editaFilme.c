#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*struct Filme                             //j� tem na main
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

    struct Filme filmes_lidos[50]; //chama a struct j� estabelecida com o vetor de filmes com 50 posi��es

    int i; //declara��o da vari�vel para usar no la�o
    int pos; //declara��o da vari�vel para ser a posi��o que o usu�rio deseja editar

    printf("Vetor de filmes:"); //exibe o vetor de filmes original

    for(i=0; i<50; i++)
    {
        printf("\nIdentificador do filme: %d", filmes_lidos[i].identificador);
        printf("\nNome do filme: %s", filmes_lidos[i].nome);
        printf("\nG�nero do filme: %d", filmes_lidos[i].genero);
        printf("\nAno de lan�amento: %d", filmes_lidos[i].anoLan�amento);
        printf("\nDiretor do filme: %s", filmes_lidos[i].nomeDiretor);
    }

    printf("\n\nDigite a posicao do vetor desejada para editar:"); //pede a posi��o desejada do vetor que o usu�rio deseja editar
    scanf("%d", &pos); //armazena essa posi��o na vari�vel "pos"

    for(i=0; (i > 50) || (i < 0); i++){ //garante que o valor escrito pelo usu�rio esteja sempre entre 0 e 50
        printf("Posi��o inv�lida. Digite uma entre 0 e 50:");
        scanf("%d", &pos);
    }

    printf("\nPosicao escolhida: %d", pos);

    for(i=0; i<50; i++) //usando o la�o para percorrer todo o vetor
    {
        if(i == pos) //ao achar a posi��o desejada pelo usu�rio, � pedido para inserir os dados do filme desejado, armazenando os valores nas vari�veis da struct
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
        if(i == pos) //se a posi��o "i" do vetor for igual � posi��o que o usu�rio fez a edi��o de filmes, � printado o novo filme inserido
        {
            printf("\nIdentificador do filme: %d", filmes_lidos[pos].identificador);
            printf("\nNome do filme: %s", filmes_lidos[pos].nome);
            printf("\nG�nero do filme: %d", filmes_lidos[pos].genero);
            printf("\nAno de lan�amento: %d", filmes_lidos[pos].anoLan�amento);
            printf("\nDiretor do filme: %s", filmes_lidos[pos].nomeDiretor);
        }
        else // se n�o, � exibido os filmes do vetor original de cada posi��o "i"
        {
            printf("\nIdentificador do filme: %d", filmes_lidos[i].identificador);
            printf("\nNome do filme: %s", filmes_lidos[i].nome);
            printf("\nG�nero do filme: %d", filmes_lidos[i].genero);
            printf("\nAno de lan�amento: %d", filmes_lidos[i].anoLan�amento);
            printf("\nDiretor do filme: %s", filmes_lidos[i].nomeDiretor);
        }
    }


}
