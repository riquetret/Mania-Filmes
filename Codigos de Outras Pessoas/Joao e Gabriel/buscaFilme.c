#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct { //declara��o da struct junto com a mudan�a do nome sruct Filme para apenas Filme
    int identificador;
    char nome[51];
    char genero[31];
    int anoLancamento;
    char nomeDiretor[31];
}Filme;

int leFilmes(Filme *ptr,int tam,FILE *dados);
int buscaFilme(Filme *ptr,FILE *ptr2,char *nome_filme);

int buscaFilme(Filme *ptr,FILE *ptr2,char *nome_filme)
{

    int posicao_do_identificador = 0;
    int i;
    int *aux;
    char filmes_lidos[50];
    char filme_usuario[50];
    int continuar = 1, continuar2 = 2;

    fseek(ptr2, 0, SEEK_SET);

    for(i=0; i<50; i++)
    {
        if(fseek(*ptr2, 50, SEEK_SET))
            return -1;

        while (continuar == 1)
        {
            if ((filme_usuario[i] == '\n') && (filme_usuario[i+1] == 'i'))
            {
                while (continuar == 2)
                {
                    if
                    ((filme_usuario[i] == '\n') && (filme_usuario[i+1] == 'n'))
                    {
                        fgets(filme_usuario, sizeof(filme_usuario), stdin);
                        if (strcpy((filme_usuario) && (filmes_lidos) == 0))
                        {
                            filmes_lidos = *aux;
                            aux = posicao_do_identificador;
                        }
                        else
                        {
                            continuar = 2;
                        }
                    }
                }
            }
            continuar = 1;
        }
        leFilmes(Filme *ptr, posicao_do_identificador, FILE *arquivo);
    }
}

int leFilmes(Filme *ptr, posicao_do_identificador, FILE *arquivo){

char filmes_castrados[50];


if (strcpy((filme_usuario) && (filmes_lidos) == 0)) {

posicao_do_identificador = filmes_castrados

}
else{
    return -1;
}
return 0;
}
