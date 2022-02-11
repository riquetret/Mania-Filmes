int leFilmes(Filme *ptr,int tam,FILE *dados, FILE **ptr2)
{
    char leitor[100];                                  //recebe informacoes do ptr2

    dados = fopen("filmes_cadastrados.txt", "w");       //cria vetor filmes cadastrados
    
    

    while (fgets(leitor, 100, ptr2) !=NULL)            // le o que esta ptr2 
    
    fputs(leitor, dados);                               //copia o vetor 'leitor' para o dados

    fclose(dados);                                      // fecha os vetores
    fclose(ptr2);

  

return 0;
}