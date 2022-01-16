#include <stdlib.h>
#include <stdio.h>

void limpa_buffer() {
    int caracter=0;
    do {
    caracter = fgetc(stdin);
    } while (caracter != '\n' && caracter!=EOF);
    if(caracter==EOF)clearerr(stdin);
}

typedef struct Filme
{
    unsigned int indentificador;
    char nome[50];
    char genero[30];
    unsigned short int anoLancamento;
    char nomeDiretor[30];
};

int main(){
    enum week{Mon, Tue, Wed, Thur, Fri, Sat, Sun};
    return 0;
}