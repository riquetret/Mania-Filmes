#include <stlib.h>
#include <stdio.h>
/*
Uma struct chamada Filme
– A struct Filme ´e um registro que armazena as informa¸c˜oes de um filme da base. Ela possui os
seguintes atributos:
∗ identificador - ´e um n´umero que deve ser ´unico para cada filme e deve ser atribu´ıdo automati-
camente.
∗ nome - m´aximo 50 caracteres.
∗ genero - m´aximo 30 caracteres.
∗ anoLancamento - deve ser um n´umero entre 1900 e 2021.
∗ nomeDiretor - m´aximo 30 caracteres.
– Vocˆe pode acrescentar outros atributos se achar necess´ario.
*/
typedef struct Filme
{
    unsigned int indentificador;
    char nome[50];
    char genero[30];
    unsigned short int anoLancamento;
    char nomeDiretor[30];
};

int maint(){
    
    return 0;
}