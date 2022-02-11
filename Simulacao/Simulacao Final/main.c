#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct
{
    unsigned int identificador;
    char nome[50];
    char genero[30];
    unsigned short int anoLancamento;
    char nomeDiretor[30];
}Filme;

enum Estados{
    Saida=0,
    Adicionar=1,
    Editar=2,
    Remover=3,
    Exibir=4,
    Gravar=5,
    Ler_Banco=6,
};
void limpa_tela();
void limpa_buffer();
int le_numero(void *numero,double ri, double rf, char t);
void inicializa_arquivo(FILE **ptr,char *nome,char *modo);

int adicionaFilme(Filme *ptr,int tam);
int editaFilme(Filme *ptr,int posicao);
int removeFilme(Filme *ptr,int posicao);
int imprimeFilmes(Filme *ptr,int posicao,int tam);
int gravaFilmes(Filme *ptr,int tam,FILE **arq_orig, FILE *arq_dst);
int leFilmes(Filme *ptr,int tam,FILE *dados);
int buscaFilme(Filme *ptr,FILE **ptr2,char *nome_filme);


int main(){
    Filme filmes_lidos[50];                                                         //Cria Vetor de Structs
    enum Estados opcao;                                                             //Declara Enum com estados

    char menu[]=                                                                    //Declara exibição padrão do menu
    "0)Sair do Programa\
    \n1)Adicionar Filmes\
    \n2)Editar Filmes\
    \n3)Remover Filmes\
    \n4)Exibir Filmes\
    \n5)Gravar Filmes\
    \n6)Ler Filme do Banco";

    int posicoes,filmes_adicionados=0,retorno;                                      //Declara posicoes (Para alterar uma posição do vetor), declara filmes_adicionados (para contabilizar quantos filmes já foram adicionados) e por fim declara retorno para analisar o retorno de algumas funções

    char status_do_banco[]="NAO";                                                   //O banco de dados esta aberto? Neste caso nao
    int carrega_do_banco[50];                                                       //Vetor para identificar filmes carregados do banco, exemplo: se um filme do banco foi carregado na posicao 4 do filmes_lidos, então o carrega_do_banco[4] será igual a 1, caso contrário zero
    
    memset(carrega_do_banco,0,sizeof(int)*50);                                      //Resetando o nosso vetor carrega_do_banco
    removeFilme(&filmes_lidos[0],-1);                                               //Vamos resetar o vetor de filmes do programa

    FILE *arquivo;                                                                  //Declara ponteiro de arquivo
    //setlocale(LC_ALL, "Portuguese");

    inicializa_arquivo(&arquivo,"filmes.txt","r+");                                 //Abre o arquivo "filmes.txt" no modo leitura para atualizar

    do
    {
        printf("Bem-vindo ao forum MANIA-FILMES\n");                                    //Mensagens iniciais
        printf("\nSe sua entrada nao for processada, aperte \"enter\" DUAS vezes\n\n");	//Devido ao limpa_buffer que pode tentar ler quando nao ha entradas no buffer do teclado

        printf("Voce carregou filmes do banco de dados? %s",status_do_banco);
        printf("Quantos filme voce ja carregou no sistema? %d (Max 50 Filmes)",filmes_adicionados);

        printf("\n%s\nDigite qual opcao deseja: ",menu);                            //Exibe opções ao usuário
        le_numero(&opcao,0,6,'i');                                                  //Le opção escolhida do menu
        limpa_tela();                                                               //Limpa a tela

        switch(opcao){
            case Adicionar:
                retorno = adicionaFilme(&filmes_lidos[0],filmes_adicionados);       //retorno recebe a quantidade filmes adicionados
                if(retorno==-1)printf("ERRO: O sistema nao suporta a adicao de mais filmes");//Vetor cheio?
                else{
                    filmes_adicionados+=retorno;                                    //Incrementa os filmes_adicionados
                    printf("\nFilmes adicionados com sucesso\n\n");                 //Mostra mensagem ao usuário
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
                //gravaFilmes(&filmes_lidos[0],filmes_adicionados,&arquivo);           //Grava os filmes adicionados ou alterados
                removeFilme(&filmes_lidos[0],-1);                                      //Vamos resetar o vetor de filmes do programa
            break;
            case Ler_Banco:
                while (posicoes==-1)
                {
                    fgets(&filmes_lidos[0].nome[0],50,stdin);                           //Le o filme para procurar
                    limpa_buffer();                                                     //Limpa lixo do teclado
                    filmes_lidos[0].nome[strcspn(filmes_lidos[0].nome, "\n")] = 0;      //Remove \n lido pelo fgets
                    posicoes = buscaFilme(&filmes_lidos[0],&arquivo,&filmes_lidos[0].nome[0]);//Busca o filme digitado
                    if(posicoes==-1)printf("\nErro digite o nome do filme novamente: ");//Erro na buscaFilme
                    else filmes_adicionados=50;                                         //O buscaFilme ja carregou 50 filmes, além do filme escolhido
                }
                break;
        } //END SWITCH(OPCAO)
    }while(opcao);//END WHILE(1)

    fclose(arquivo);
    return 0;
}//END MAIN

void limpa_tela(){
    system("cls");                                                              //Vamos apagar as mensagens iniciais
    system("clear");
    printf("\n\n");
}
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
    *arq=fopen(nome,"r");                                       //Tente abrir o arquivo inicialmente no modo leitura
    if(*arq==NULL){                                             //Se ele não existir ou o programa não ter permissão suficiente, crie ele
        fclose(*arq);                                           //Feche o arquivo por segurança
        *arq=fopen(nome,"w");                                   //Tente então criar o arquivo
        if(*arq=NULL)exit(EXIT_FAILURE);                        //Se a criação nao foi possível finalize o programa e exiba erro
    }
    fclose(*arq);                                               //Fecha o arquivo por segurança
    *arq=fopen(nome,modo);                                      //Reabre o arquivo no modo selecionado
}

/*
Funcao: adicionaFilme
Autor: Lucas Silva e Roginaldo Junior

Objetivo: ler do teclado quantos filmes ser�o adicionados,
requisitar os dados dos filmes e por fim adicionar esses dados
no vetor onde todos os filmes est�o sendo armazenados
*/

int adicionaFilme(Filme *ptr, int tam){ //desenvolvimento do prot�tipo da fun��o adiciona filme
    if(tam>=50)return -1;   //Se o vetor ja estiver cheio retorne erro
    int qt_filmes, i;
    printf("Quantos filmes deseja adicionar? (Digite zero para cancelar a operacao)"); //solicita quantidades de filmes a serem adicionados no vetor
    le_numero(&qt_filmes,0,50,'i');                      //Le a quantidade de filmes que o usuario deseja (De 1 Filme até 50 Filmes)

    if (qt_filmes==0)return 0;                          //Se a pessoa nao quiser adicionar filmes, volte ao programa principal

    else if(qt_filmes+tam>50){   //A pessoa deseja adicionar mais do que o vetor suporta?
        qt_filmes=50-tam;   //Defina então o máximo para ser adicionado, ou seja, quantos espaços vazios eu tenho no vetor para adicionar
        printf("\nALERTA O maximo suportado para adicao de filmes eh:%d\n",qt_filmes);  //Exibe alerta para a pessoa ter ciência
    }
    tam=0;                   //O Tam agora funciona como indicador de quantos filmes ja foram adicionados de fato no vetor 
    for(i=0;i<50;i++){      //Vamos adicionar os filmes no vetor
        if (ptr[i].identificador!=0) continue;  //Caso haja um filme já cadastrado na posicao de memoria pule para a proxima posicao
        if(editaFilme(&(*ptr),i)==-1)break;                  //Adiciona o filme a partir do edita filme e caso a pessoa queira cancelar sai do loop
        tam++;              //Se a pessoa introduziu um filme incremente
    }
   return qt_filmes; //Retorna a quantidade filmes adicionada
}

int editaFilme(Filme *ptr,int posicao){

    printf("Caso queira cancelar a operacao como um todo, digite \"0\" em pelo menos um campo a seguir");

    printf("Digite o nome do %d%c filme: ", posicao,248); //atrelando o nome do filme inserido pelo usuario ao filme colocado no vetor
    fgets(ptr[posicao].nome,50,stdin);    //Le o nome do filme com fgets para nao deixar overflow
    ptr[posicao].nome[strcspn(ptr[posicao].nome, "\n")] = 0;    //Remove \n lido pelo fgets
    limpa_buffer();                 //Remove lixo do teclado
    if(strcmp(ptr[posicao].nome,"0")==0)return -1;

    printf("Digite o genero do %d%c filme: ", posicao,248); //atrelando o genero do filme inserido pelo usuario ao filme colocado no vetor
    fgets(ptr[posicao].genero,30,stdin);  //Le o genero com fgets para nao deixar overflow
    ptr[posicao].genero[strcspn(ptr[posicao].genero, "\n")] = 0;    //Remove \n lido pelo fgets
    limpa_buffer();
    if(strcmp(ptr[posicao].genero,"0")==0)return -1;

    printf("Digite o ano de lancamento do %d%c filme", posicao,248); //atrelando o ano de lancamento do filme inserido pelo usuario
    printf("\nDigite um ano entre 1900 e 2021: ");
    le_numero(&(ptr[posicao].anoLancamento),1900,2021,'i');   //Le ano do filme com fgets para nao deixar overflow
    limpa_buffer();

    printf("Digite o nome do diretor do %d%c filme: ", posicao,248); //atrelando o nome do diretor do filme inserido pelo usuario
    fgets(ptr[posicao].nomeDiretor,30,stdin); //Le o nome do diretor com fgets para nao deixar overflow
    ptr[posicao].nomeDiretor[strcspn(ptr[posicao].nomeDiretor, "\n")] = 0;  //Remove \n lido pelo fgets
    limpa_buffer();
    if(strcmp(ptr[posicao].nomeDiretor,"0")==0)return -1;

    return 0;
}

/*
Funcao: removeFilme
Autor: Lucas Silva e Roginaldo Junior

Objetivo: remover o filme que esta na posicao inserida como
parametro da funcao, 'zerando' o identificador e o ano de lancamento
atribuindo o valor 0 e os demais dados atribuindo o caracter '\0' na
primeira posicao da string.
*/

int removeFilme(Filme *ptr, int posicao){ //desenvolvimento do prototipo da funcao remove filme
    if(posicao<0){                        //Deseja Apagar todo vetor?
        for(int i=50;i--;){
            ptr[i].identificador = 0;             //removendo o identificador atrelado ao filme zerando ele
            strcpy(ptr[i].nome,"Nao Cadastrado");  //removendo o nome atrelado ao filme zerando ele
            strcpy(ptr[i].genero,'\0');           //removendo o genero atrelado ao filme zerando ele
            ptr[i].anoLancamento = 0;             //removendo o ano de lancamento atrelado ao filme zerando ele
            strcpy(ptr[i].nomeDiretor,'\0');      //removendo o nome do diretor atrelado ao filme zerando ele
        }
    }

    ptr[posicao].identificador = 0;             //removendo o identificador atrelado ao filme zerando ele
    strcpy(ptr[posicao].nome,"Nao Cadastrado"); //removendo o nome atrelado ao filme zerando ele
    strcpy(ptr[posicao].genero,'\0');           //removendo o genero atrelado ao filme zerando ele
    ptr[posicao].anoLancamento = 0;             //removendo o ano de lancamento atrelado ao filme zerando ele
    strcpy(ptr[posicao].nomeDiretor,'\0');      //removendo o nome do diretor atrelado ao filme zerando ele

    return 0; //retorno da funcao apos sua conclusao
}

/*
Funcao: ImprimeFilme
Autor: Pedro Carneiro Rabetim
Objetivo: ler do teclado qual filmes ser�o impresso(ou no caso todos)
imprimir todos os dados de um filme expec�fico ou de todos
*/

int imprimeFilmes(Filme *ptr,int posicao,int tam){

    int n;

    printf("Digite o numero do filme que gostaria de imprimir seus dados,\n");
    printf("ou -1 para imprimir todos\n");

    if(posicao == -1){
        for(n=0;n<tam;n++){
            printf("Nome:");
            puts(ptr[n].nome);
            printf("Genero:");
            puts(ptr[n].genero);
            printf("Ano:");
            printf("%d\n",ptr[n].anoLancamento);
            printf("Diretor:");
            puts(ptr[n].nomeDiretor);
            printf("Posicao:%d",n);
        }
        }else{
            printf("Nome:");
            puts(ptr[posicao-1].nome);
            printf("Genero:");
            puts(ptr[posicao-1].genero);
            printf("Ano:");
            printf("%d\n",ptr[posicao-1].anoLancamento);
            printf("Diretor:");
            puts(ptr[posicao-1].nomeDiretor);
            return 0;
    }

    return n;
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
                fprintf(arq_dst,"i: %d\n",ptr->identificador);     //Copia Nome para arquivo destino
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

/*
Função: buscaFilme
Autor: Feita por Henrique Soares Costa, github.com/RIQUETRET
Entradas: O Vetor de filmes(*ptr), O ponteiro para o ponteiro de arquivos(**ptr2)
e por fim o nome do filme desejado (*nome_filme)
Saídas: Seu vetor recebe o filme desejado, se este filme
for encontrado na base de dados
Retorno: Zero se tudo ok ou -1 se nao encontrou o filme

Objetivo: Vasculha o arquivo, lendo linha por linha
quando encontra um nome de filme igual ao desejado,
carrega no vetor com leFilmes() e posteriomente retorna 0
*/

int buscaFilme(Filme *ptr,FILE **ptr2,char *nome_filme)
{
    int posicao_identificador; //Variavel para armazenar a posicao do "i" ou identificador, para que assim possamos reposicionar o ponteiro de arquivos (*ptr2)
    char lido[55];  //Vamos ler linha por linha do nosso arquivo com esse vetor e portanto podemos ter ao máximo 54 caracteres, sendo que isso pode ocorrer quando formos ler o nome, ou seja, "n: \n" + 50 caracteres do nome

    fseek(*ptr2,0,SEEK_SET);    //Posiciona o cursor no inicio para buscar o filme

    while(fgets(lido,55,*ptr2)!=NULL) { //Leia uma linha do arquivo e caso encontre EOF, saia do loop e retorne -1
        if (lido[0]=='i'){                                      //A gente leu um identificador?
            posicao_identificador=ftell(*ptr2)-strlen(lido);    //Vamosa salvar a posição desse identificador no arquivo, para que assim no futuro possamos chamar a função le_filmes, que no caso precisa obrigatoriamente iniciar a leitura no identificador
        }
        else if(lido[0]=='n'){                                  //A gente leu um filme?
            lido[strcspn(lido, "\n")] = 0;                      //Remove \n introduzido pelo fgets
            if(strcmp(&lido[3],nome_filme)==0){                 //O filme lido e o desejado é igual?
                fseek(*ptr2,posicao_identificador,SEEK_SET);    //Reposiciona cursor para identificador deste filme
                //le_filmes()                                   //Le o filme (salva para o vetor de filmes)
                return 0;                                       //Retorna 0 indicando sucesso na busca e salvamento do filme
            }
        }
    }//END while(fgets(lido,55,*ptr2)!=NULL)
    return -1;
}

