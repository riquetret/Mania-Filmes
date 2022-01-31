#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
};

void limpa_buffer();
int le_numero(void *numero,double ri, double rf, char t);
void inicializa_arquivo(FILE **ptr,char *nome,char *modo);

int adicionaFilme(Filme *ptr,int tam);
int editaFilme(Filme *ptr,int posicao);
int removeFilme(Filme *ptr,int posicao);
int imprimeFilmes(Filme *ptr,int posicao,int tam);
int gravaFilmes(Filme *ptr,int tam,FILE **arq_orig, FILE *arq_dst);
int leFilmes(Filme *ptr,int tam,FILE *dados);
int buscaFilme(char *nome_filme);


int main(){
    Filme filmes_lidos[50];                                                         //Cria Vetor de Structs
    enum Estados opcao;                                                             //Declara Enum com estados
    char menu[]=                                                                    //Declara exibição padrão do menu
    "1)Adicionar Filmes\
    \n2)Editar Filmes\
    \n3)Remover Filmes\
    \n4)Exibir Filmes\
    \n5)Gravar Filmes\
    \n6)Ler Filme do Banco";
    int posicoes,filmes_adicionados=1,retorno;                                      //Declara posicoes (Para alterar uma posição do vetor), declara filmes_adicionados (para contabilizar quantos filmes já foram adicionados) e por fim declara retorno para analisar o retorno de algumas funções
    FILE *arquivo;                                                                  //Declara ponteiro de arquivo
    inicializa_arquivo(&arquivo,"filmes.txt","r+");                                 //Abre o arquivo "filmes.txt" no modo leitura para atualizar

    printf("Bem-vindo ao forum MANIA-FILMES\n");                                    //Mensagens iniciais
    printf("\nSe sua entrada nao for processada, aperte \"enter\" DUAS vezes\n\n");	//Devido ao limpa_buffer que pode tentar ler quando nao ha entradas no buffer

    while (1)
    {


        printf("Deseja editar um filme da base dados ou editar os filmes ja em aberto pelo programa?");
        printf("\nDigite \"d\" para filmes da base de dados ou \"p\" para os abertos: ");

        posicoes=-1;                                                                //Reseta posicoes para nova operação
        if(getchar()<='d'){
            limpa_buffer();                                                         //Limpa a quebra de linha
            while (posicoes==-1)
            {
                fgets(&filmes_lidos[0].nome[0],50,stdin);                           //Le o filme para procurar
                limpa_buffer();                                                     //Limpa lixo do teclado
                filmes_lidos[0].nome[strcspn(filmes_lidos[0].nome, "\n")] = 0;      //Remove \n lido pelo fgets
                //posicoes = buscaFilme(&filmes_lidos[0].nome[0])                   //Busca o filme digitado
                if(posicoes==-1)printf("\nErro digite o nome do filme novamente: ");//Erro na buscaFilme
                else filmes_adicionados=50;                                         //O buscaFilme ja carregou 50 filmes, além do filme escolhido
            }
        }

        printf("\n%s\nDigite qual opcao deseja: ",menu);                            //Exibe opções ao usuário
        le_numero(&opcao,1,5,'i');                                                  //Le opção escolhida

        system("cls");                                                              //Vamos apagar as mensagens iniciais
        system("clear");
        switch(opcao){
            case Adicionar:
                retorno = adicionaFilme(&filmes_lidos[0],filmes_adicionados);       //retorno recebe a quantidade filmes adicionados
                if(retorno!=-1)printf("ERRO: O sistema nao suporta a adicao de mais filmes");//Vetor cheio?
                else{
                    filmes_adicionados+=retorno;                                    //Incrementa os filmes_adicionados
                    printf("Filmes adicionados com sucesso");                       //Mostra mensagem ao usuário
                }
            break;
            case Editar:
                if(posicoes==-1){                                                   //Deseja editar filmes ja carregados no vetor?
                    imprimeFilmes(&filmes_lidos[0],-1,filmes_adicionados);          //Se sim exiba os filmes cadastrados
                    printf("\nQual posicao deseja editar?\n");                      //Pergunta qual posição deseja editar
                    le_numero(&posicoes,1,50,'i');                                  //Le a posição desejada
                    posicoes--;                                                     //Decrementa posicoes para exibir a posicao correta
                }
                imprimeFilmes(&filmes_lidos[0],posicoes,filmes_adicionados);        //Exibe filme escolhido, seja no if acima ou seja na leitura do banco de dados
                editaFilme(&filmes_lidos[0],posicoes);                              //Edita filme escolhido
            break;
            case Remover:
                if(posicoes==-1){                                                   //Deseja remover filmes ja carregados no vetor?
                    imprimeFilmes(&filmes_lidos[0],-1,filmes_adicionados);          //Se sim exiba os filmes cadastrados     
                    printf("\nQual posicao deseja deletar?\n");                     //Pergunta qual posição deseja remmover
                    le_numero(&posicoes,1,50,'i');                                  //Le a posição desejada
                    posicoes--;                                                     //Decrementa posicoes para deletar a posicao correta
                }
                removeFilme(&filmes_lidos[0],posicoes);                             //Remove Filme Escolhido
                filmes_adicionados--;                                               //Tiramos um filme
            break;
            case Exibir:
                if(posicoes==-1)imprimeFilmes(&filmes_lidos[0],-1,filmes_adicionados);  //Deseja exibir todos os filmes?
                else imprimeFilmes(&filmes_lidos[0],posicoes,filmes_adicionados);
            break;
            case Gravar:
                gravaFilme(&filmes_lidos[0],filmes_adicionados,&arquivo);           //Grava os filmes adicionados ou alterados
            break;
            default:
                printf("Por algum motivo voce nao deveria estar aqui\n Vou reiniciar o programa...\n");
            break;
        } //END SWITCH(OPCAO)
    }//END WHILE(1)
    return 0;
}//END MAIN
/*
Função: Limpa_Buffer
Autor: Baseado em outras pessoas, modificada por Henrique.
Entradas:Stdin
Saídas: Nenhuma
Retorno: Nenhum

Objetivo: Consumir caracteres
adicionais presentes no stdin.
Se a função encontrar um EOF ela
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
Função: le_numero
Autor: Feita por Henrique Soares Costa, github.com/RIQUETRET
Entradas: Ponteiro para o número,intervalos ri e rf, tipo t
Saídas: o *numero recebe um valor lido pelo teclado
Retorno: Retorna 0 se tudo ocorreu bem

Objetivo: Lê o teclado e atribui ao *numero,
contudo o valor lido deve estar entre ri e rf (ri<=valor lido<=rf).
É importante especificar o tipo de variavel com o char t
(se t='d', leia um double do teclado,t='f'' lê float, t='i' lê int,
 caso nenhum desses seja satisfeito ele irá ler um char do teclado)
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

/*
Função: inicializa_arquivo
Autor: Feita por Henrique Soares Costa, github.com/RIQUETRET
Entradas: Seu ponteiro de arquivo (**arq), nome do seu arquivo(*nome), modo para abrir (*modo)
Saídas: Seu ponteiro de arquivo
Retorno: Nenhum

Objetivo: Abri o arquivo *nome no modo leitura,
caso o arquivo não exista, a função cria o arquivo.
Posteriomente a função reabre o arquivo no modo especificado (*modo)
*/
void inicializa_arquivo(FILE **arq,char *nome,char *modo){
    *arq=fopen(nome,"r");
    if(*arq==NULL){
        fclose(*arq);
        *arq=fopen(nome,"w");
    }
    fclose(*arq);
    *arq=fopen(nome,modo);
}

/*
Função: gravaFilmes
Autor: Feita por Henrique Soares Costa, github.com/RIQUETRET
Entradas: Struct com informações do filme (*ptr),filmes abertos no vetor (tam),
endereço do arquivo "filmes.txt"(**arq_orig),arquivo de destino (*arq_dst)
Saídas: Um novo arquivo "filmes.txt" atualizado
Retorno: Zero se tudo ok

Objetivo: Cria uma copia de "filmes.txt" atualizando a copia com os valores
do vetor de struct. Feito isso "filmes.txt" é deletado e a copia torna-se
"filmes.txt".
*/
int gravaFilmes(Filme *ptr,int tam,FILE **arq_orig, FILE *arq_dst){
    arq_dst=fopen("filmes_copia.txt","w");                              //Cria uma copia
    long int posicao_atual = ftell(*arq_orig);                          //Recebe a posição do cursor no arquivo de origem
    int j;                                                              //Iterador

    fseek(*arq_orig,0,SEEK_SET);                                        //Coloca o cursor no inicio de arquivo de origem para copiar os elementos acima da "posicao_atual"
    fwrite(&(*(FILE*)arq_orig),1,posicao_atual,arq_dst);                //Copia os elementos acima da "posicao_atual"
    for(j=0;tam--;j=0,ptr++){                                       //Agora é preciso copiar os elementos do nosso vetor de filmes
        for(;j<5;j++){                                                  //Vamos copiar até tamanho ser igual a zero
            switch (j)
            {
            case 1:
                fprintf(arq_dst,"n: %s\n",ptr->nome);               //Copia Nome para arquivo destino
                break;
            case 2:
                fprintf(arq_dst,"g: %s\n",ptr->genero);             //Copia Genero para arquivo destino
                break;
            case 3:
                fprintf(arq_dst,"l: %d\n",ptr->anoLancamento);      //Copia anoLancamento para arquivo destino
                break;
            case 4:
                fprintf(arq_dst,"d: %s\n",ptr->nomeDiretor);        //Copia Nome do diretor para arquivo destino
                break;
            default:
                fprintf(arq_dst,"i: %d\n",ptr->indentificador);     //Copia Nome para arquivo destino
                break;
            }
        }//END FOR (;j<5;j++)
        for(;j<10;){                                                //Eu n sei pq coloquei essa linha :()
            if(fgetc(*arq_orig)=='\n')j++;
        }
    }//END FOR (j=0;tam;tam--,j=0)
    for(;feof(*arq_orig);){                                         //Copia as linhas debaixo do vetor já copiado
        fprintf(arq_dst,"%c",fgetc(*arq_orig));                     //Copia para arquivo de destino
    }
    fclose(*arq_orig);                                              //Feche os ponteiros de arquivo por segurança
    fclose(arq_dst);
    remove("filmes.txt");                                           //Remove o antigo "filmes.txt"
    rename("filmes_copia.txt","filmes.txt");                        //Renomeia o novo para "filmes.txt"
    *arq_orig=fopen("filmes.txt","r+");                             //Abre novamente o ponteiro
    return 0;
}
