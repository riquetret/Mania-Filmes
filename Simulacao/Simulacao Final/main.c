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
    Inicial=0,
    Adicionar=1,
    Editar=2,
    Remover=3,
    Exibir=4,
    Gravar=5,
    Ler=6,
};

void limpa_buffer();
int le_numero(void *numero,double ri, double rf, char t);

int main(){
    Filme vetor[50];
    enum Estados opcao;

    char menu[]=
    "1)Adicionar Filmes\
    \n2)Editar Filmes\
    \n3)Remover Filmes\
    \n4)Exibir Filmes\
    \n5)Gravar Filmes\
    \n6)Ler Filme do Banco";

    while (1)
    {
        printf("Bem-vindo ao forum mania-filmes\n"
           "Digite abaixo qual opcao deseja");
        printf("\n%s\n",menu);

        le_numero(&opcao,1,6,'i');
        system("cls");
        system("clear");
        switch(opcao){
            case Adicionar:
                printf("opcao 1\n");
            break;
            case Editar:
                printf("opcao 2\n");
            break;
            case Remover:
                printf("opcao 3\n");
            break;
            case Exibir:
                printf("opcao 4\n");
            break;
            case Gravar:
                printf("opcao 5\n");
            break;
            case Ler:
                printf("opcao 6\n");
            break;
            default:
                printf("Olhe as opcoes\n");
                opcao=Inicial;
            break;
        } //END SWITCH(OPCAO)
    }//END WHILE(1)
    return 0;
}

/*
Fun��o: Limpa_Buffer
Autor: Baseado em outras pessoas, modificada por Henrique.
Entradas:Stdin
Sa�das: Nenhuma
Retorno: Nenhum

Objetivo: Consumir caracteres
adicionais presentes no stdin.
Se a fun��o encontrar um EOF ela
Reseta o stdin para futuras leituras
*/
void limpa_buffer() {
    char caracter=0;									//Declara char para a leitura
    do {
    caracter = fgetc(stdin);							//Le caracter por caracter ate "zerar" stdin
    } while (caracter != '\n' && caracter!=EOF);		//Se foi encontrado uma quebra de linha ou um erro saia
    if(caracter==EOF)clearerr(stdin);					//Se foi encontrado um EOF, resete stdin
}
/*
Fun��o: le_numero
Autor: Feita por Henrique Soares Costa, github.com/RIQUETRET
Entradas: Ponteiro para o n�mero,intervalos ri e rf, tipo t
Sa�das: o *numero recebe um valor lido pelo teclado
Retorno: Retorna 0 se tudo ocorreu bem

Objetivo: L� o teclado e atribui o valor ao *numero,
contudo o valor lido deve estar entre ri e rf (ri<=valor lido<=rf).
� importante especificar o tipo de variavel com o char t
(se t='d', leia um double do teclado,t='f'' l� float, t='i' l� int,
 caso nenhum desses seja satisfeito ele ir� ler um caracter do teclado)
*/
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
