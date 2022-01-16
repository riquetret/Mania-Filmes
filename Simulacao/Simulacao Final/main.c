#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    unsigned int indentificador;
    char nome[50];
    char genero[30];
    unsigned short int anoLancamento;
    char nomeDiretor[30];
}Filme;

enum Estados{
    MenuInicial=0,
    Adicionar=1,
    Editar=2,
    Remover=3,
    Imprimir=4,
    Gravar=5,
    Ler=6,
};

void limpa_buffer();
int le_numero(void *numero,double ri, double rf, char t);

int main(){
    enum Estados opcao;
    Filme vetor[50];
    le_numero(&opcao,1,6,'i');
    switch(opcao){
        case 1:
            printf("opcao 1\n");
        break;
        case 2:
            printf("opcao 2\n");
        break;
        case 3:
            printf("opcao 3\n");
        break;
        case 4:
            printf("opcao 4\n");
        break;
        case 5:
            printf("opcao 5\n");
        break;
        case 6:
            printf("opcao 6\n");
        break;
        default:
            printf("Olhe as opcoes\n");
        break;
    }
    return 0;
}

void limpa_buffer() {
    char caracter=0;
    do {
    caracter = fgetc(stdin);
    } while (caracter != '\n' && caracter!=EOF);
    if(caracter==EOF)clearerr(stdin);
}

int le_numero(void *numero,double ri, double rf, char t){
    int erro=-1;
    do
    {
        switch (t)
        {
        case 'd':
            erro=scanf("%lf",(double *) numero);
            if(erro==1){
                if( (*(double *) numero) >= ri &&
                (*(double *) numero) <= rf ) continue;
                else erro=0;
            }
            break;
        case 'f':
            erro=scanf("%f",(float *) numero);
            if(erro==1){
                if( (*(float *) numero) >= (float) ri &&
                (*(float *) numero) <= (float) rf ) continue;
                else erro=0;
            }
            break;
        case 'i':
            erro=scanf("%d",(int *) numero);
            if(erro==1){
                if( (*(int *) numero) >= (int) ri &&
                (*(int *) numero) <= (int) rf ) continue;
                else erro=0;
            }
            break;
        default:
            erro=scanf("%c",(char *) numero);
            if(erro==1){
                if( (*(char *) numero) >= (char) ri &&
                (*(char *) numero) <= (char) rf ) continue;
                else erro=0;
            }
            break;
        }
        limpa_buffer();
        printf("\nErro Digite Novamente: ");
    } while (erro<=0);
    limpa_buffer();
    return 0;
}
