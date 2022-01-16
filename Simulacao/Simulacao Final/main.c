#include <stdlib.h>
#include <stdio.h>

void limpa_buffer() {
    int caracter=0;
    do {
    caracter = fgetc(stdin);
    } while (caracter != '\n' && caracter!=EOF);
    if(caracter==EOF)clearerr(stdin);
}

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
    Imprimir=4,
    Gravar=5,
    Ler=6,
};

int main(){
    enum Estados opcao=5;
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
