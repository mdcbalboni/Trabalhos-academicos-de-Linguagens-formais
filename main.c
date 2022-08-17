#include "function.h"

int main()
{
	FILE *f = fopen("pascal.pas", "r"); //abre arquivo com o código pascal
	char arq[999];
	lerFile(arq, f); //carrega dados do arquivo pra variável
	lexicar(arq); //chama a função principal do analisador léxico
	sintaxar(arq); //Chama a função principal do analisador sintático
	fclose(f); //fecha o arquivo de leitura
	printf("\n\nO código submetido está léxicamente e sintaticamente correto\n\n"); //Se chegou até aqui, é pq tá tudo OK
	return EXIT_SUCCESS;
}
