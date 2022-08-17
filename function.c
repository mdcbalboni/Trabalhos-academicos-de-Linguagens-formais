#include "function.h"

/** GLOBAL **/

struct tok
{
	int linha;
	int openclose;
	char token;
} pToken[999];
int iToken = 0;
int iLinha = 0;
char txtLinha[999][999]; 	// armazena o texto de cada linha,
									// para mostrar quando der erro sintático

char aZ1st[] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '_', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '\0'};

char aZ[] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '_', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '0', '9', '8', '7', '6', '5', '4', '3', '2', '1', '\0'};

char num1st[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\0'};

char num[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '\0'};

char special[] = {'(', ')', ':', ';', '=', '<', '>', '-', '+', '*', '/', ',', '\0'};

void lerFile(char arq[], FILE *f)
{
	//Lê o arquivo e passa todo o conteúdo do arquivo pro vetor arq[]
	int i = 0;
	int linha = 0;
	char c[999];
	while(fgets(c, 999, f))
	{
		int a;
		for(a = 0; c[a]; a++)
		{
			arq[i++] = c[a];
		}
		arq[i] = '\0';
		strcpy(txtLinha[linha++], c);
	}
}

void lexicar(char arq[])
{
	isVocabulary(arq);
	tiraTAB(arq);
	putSpace(arq);
	getToken(arq);
}

void isVocabulary(char arq[])
{
	/*
	/ Esta função verifica, previamente, se existe algum caractere
	/ que não está presente na lista do vocabulário permitido
	*/

	char vocabulario[] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '_', '(', ')', ';', ':', '+', '-', '=', '<', '>', '*', '/',  ',', '\0'};

	int i, j, linha = 0, coluna = 0;
	for(j = 0; arq[j]!='\0'; j++)
	{
		// Se achar algum dos caracteres especiais aceitos, 
		// mas que não faz parte do vocabulário, apenas passa reto
		if(arq[j]=='\t')
		{
			coluna+=3; //o meu gedit possui tabulação de 3 espaços
			continue;
		}
		if(arq[j]==' ')
		{
			coluna++;
			continue;
		}
		if(arq[j]=='\n')
		{
			linha++;
			coluna=0;
			continue;
		}
		for (i = 0; i<strlen(vocabulario); i++)
		{
			if(arq[j] == vocabulario[i])
			{
				coluna++;
				break;
			}
		}
		if(vocabulario[i]=='\0')
		{
			printf("\nERRO: Léxico LINHA: %i e COLUNA: %i\n\n",linha+1, coluna+1);
			exit(EXIT_FAILURE);
		}
	}
}

void desloca(char arq[], int apartir)
{
	/*
	/ Esta função realiza o deslocamento de todos os caracteres do vetor
	/ partindo do apartir até o final, e colocar um espaço na posição
	/ indicada pelo parametro
	*/

	int i;
	int max = strlen(arq);
	for(i = max; i>apartir ; i--)
		arq[i] = arq[i-1];
	arq[apartir] = ' ';
	arq[max+1] = '\0';
}

void tiraTAB(char arq[])
{
	/*
	/ Esta função apenas procura no arq qualquer tab utilizado
	/ pelo programador, e substitui por um espaço.
	*/
	int i;
	for(i = 0; arq[i]!='\0'; i++)
	{
		if(arq[i] == '\t')
			arq[i] = ' ';
	}
}

void putSpace(char arq[])
{
	/*
	/ Pra aproveitar o sistema que eu já tinha desenvolvido, 
	/ que envolvia pegar os tokens, que já estavam separados por espaço.
	/ Aqui eu desenvolvi uma técnica para incluir espaços a cada token
	/ Ele simplesmente vai pegando cada conjunto de simbolos, e procura
	/ no vetor, se ele achar algum simbolo que corresponde aquele do
	/ subvocabulário, ele levanta uma flag, que faz passar pro próximo
	/ caractere do arq;
	/ Se ele não levantar uma flag no primeiro for, ele vai para o
	/ segundo, e depois para o terceiro.
	/ A idéia, é separar todos os possíveis tokens.
	*/
	int i, j; //a flag serve pra ver se é número

	
	
	for(i = 0; i<strlen(arq); i++)
	{
		for(j = 0; (j<strlen(num)) && (i<strlen(arq)); j++)
		{
			if(arq[i] == num[j])
			{
				i++;
				j=0;
			}
		}

		desloca(arq, i);
		i++;
		
		for(j = 0; (j<strlen(aZ)) && (i<strlen(arq)); j++)
		{
			if(arq[i] == aZ[j])
			{
				i++;
				j = 0;
			}
		}

		desloca(arq, i);
		i++;

		for(j = 0; (j<strlen(special)) && (i<strlen(arq)); j++)
		{
			if(arq[i] == special[j])
			{
				i++;
				j=0;
			}
		}
		
		desloca(arq, i);
		i++;
	}
}

void getToken(char arq[])
{
	/*
	/	Essa função pega o arq, e transforma cada palavra separada
	/ por espaço em um identificador-token.
	*/
	
	int i, j;	
	for(i = 0; i<strlen(arq); i++)
	{
		//Se for word
		for(j = 0; j<strlen(aZ1st); j++)
		{
			if(arq[i] == aZ1st[j])
			{
				isKeyword(arq, i);
				break;
			}
		}
		for(j = 0; j<strlen(num); j++)
		{
			if(arq[i] == num[j])
			{
				pToken[iToken].linha = iLinha;
				pToken[iToken++].token = 'l';			
				//printf("<NUM> ");
				break;
			}
		}
		for(j = 0; j<strlen(special); j++)
		{
			if(arq[i] == special[j])
			{
				i += whoSpecial(arq, i);
				break;
			}
		}
		

		//Eu preciso entrar aqui pra seguir passando o i
		// Pois nos 'for' acima, eu só pego o primeiro caractere
		for(; arq[i]!=' '; i++) 
		{
			if(arq[i] == '\n')
			{
				iLinha++;
				//printf("\n");
			}
		}
	}
	pToken[iToken].token='\0'; //Último token, EOF
}

int whoSpecial(char arq[], int i)
{
	/*
	/	Como há diversos tipos de caracteres especiais, e 
	/ cada combinação deles, gera um tipo particular de token;
	/ resolvi criar essa função só pra resolver essa parte
	/	A função captura os tokens em uma variável, e compara
	/ com as diversas combinações especiais possíveis. Retornando
	/ o armazenamento do identificador-token, e quantos caracteres
	/ foram lidos para achar esse(s) token(s).
	/ O retorno desse i, serve para quando ele voltar para a função
	/ que a chamou, essa função possa continuar o seu loop de onde parou
	*/
	int j, i2 = i, ic = 0;
	char c[9];
	
	for(j = 0; j<strlen(special); j++)
	{
		if(arq[i2] == special[j])
		{
			c[ic] = arq[i2];
			ic++;
			i2++;
			j = 0;
		}
	}
	c[ic] = '\0';
int a = 0; //Se não entrar nos quatro primeiros if's, então preciso
				//localizar cada caractere especial independente
searchAgain:
	if(strcmp(c, ":=")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'b';
		//printf("<ATT> ");
	}
	else if(strcmp(c, ">=")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<GE> ");
	}
	else if(strcmp(c, "<=")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<LE> ");
	}
	else if(strcmp(c, "<>")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'w';
		//printf("<DIF> ");
	}
	else if(c[a]==':')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'd';
		//printf("<2p> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]=='<')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<LT> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]=='>')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<GT> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]==';')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'n';
		//printf("<SC> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]==',')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 't';
		//printf("<CL> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]=='(')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'a';
		//printf("<OP> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]==')')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'h';
		//printf("<CP> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]=='=')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'w';
		//printf("<EQ> ");
		a++;
		goto searchAgain;
	}	
	else if(c[a]=='+')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<SUM> ");
		a++;
		goto searchAgain;
	}	
	else if(c[a]=='-')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<SUB> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]=='/')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<DIV> ");
		a++;
		goto searchAgain;
	}
	else if(c[a]=='*')
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<MUL> ");
		a++;
		goto searchAgain;
	}

	return i2-i;
}

void isKeyword(char arq[], int i)
{
	/*
	/	Esta função, apenas verifica se o token <VAR>
	/ é ou não é uma palavra-reservada da linguagem
	/ Se for, imprime o tipo de palavra chave (importante depois
	/ quando vou verificar se as palavras-reservadas foram
	/ utilizadas de forma correta. Se não for, simplesmente imprime 
	/ o token <VAR>
	*/

	int j;
	char c[99];
	for(j=0; arq[j+i]!=' '; j++)
		c[j] = arq[j+i];
	
	c[j] = '\0';

	if(strcmp(c, "program")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'v';
		//printf("<PRO>");
	}
	else if(strcmp(c, "end")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'f';
		//printf("<END>");
	}
	else if(strcmp(c, "begin")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'c';
		//printf("<BEG>");
	}
	else if(strcmp(c, "var")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 's';
		//printf("<DEC>");
	}
	else if(strcmp(c, "real")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'q';
		//printf("<TR>");
	}
	else if(strcmp(c, "boolean")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'q';
		//printf("<TB>");
	}
	else if(strcmp(c, "read")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'o';
		//printf("<RDR>");
	}
	else if(strcmp(c, "write")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'u';
		//printf("<WRT>");
	}
	else if(strcmp(c, "if")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'j';
		//printf("<IF>");
	}
	else if(strcmp(c, "then")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'p';
		//printf("<THN>");
	}
	else if(strcmp(c, "else")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'e';
		//printf("<ELS>");
	}
	else if(strcmp(c, "true")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'r';
		//printf("<TRU>");
	}
	else if(strcmp(c, "false")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'g';
		//printf("<FAL>");
	}
	else if(strcmp(c, "and")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<AND>");
	}
	else if(strcmp(c, "or")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<OR>");
	}
	else if(strcmp(c, "not")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'k';
		//printf("<NOT>");
	}
	else if(strcmp(c, "not")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'k';
		//printf("<NOT>");
	}
	else if(strcmp(c, "div")==0)
	{
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'm';
		//printf("<DIV>");
	}
	else
	{ // Se não é keyword, é identificador
		pToken[iToken].linha = iLinha;
		pToken[iToken++].token = 'i';
		//printf("<VAR>");
	}
}


void EhPareado()
{
	/*
	* Esta função verifica se os tokens que exigem pareamento
	* como o begin-end, (-), if-then-else, esse último é um caso
	* especial de opcionalidade, tem que verificar a existencia
	* de um if para cada else
	*/

	int i, par;

	//VERIFICANDO PARENTESES, par == 0
	par = 0;
	for(i = 0; i < iToken; i++)
	{
		if(pToken[i].token == 'a')
			par++;
		if(pToken[i].token == 'h')
			par--;
	}

	if(par != 0)
	{
		printf("\nERRO: Sintático TIPO: Quantidade indevida de parenteses\n");
		exit(EXIT_FAILURE);
	}

	//VERIFICANDO BLOCOS, par == 0
	for(i = 0; i < iToken; i++)
	{
		if(pToken[i].token == 'c')
			par++;
		if(pToken[i].token == 'f')
			par--;
	}

	if(par != 0)
	{
		printf("\nERRO: Sintático TIPO: Quantidade indevida de Blocos BEGIN-END\n");
		exit(EXIT_FAILURE);
	}

	//VERIFICANDO IF-THEN-ELSE, par > 0
	for(i = 0; i < iToken; i++)
	{
		if(pToken[i].token == 'j')
			par += 2;
		if(pToken[i].token == 'p')
			par--;
		if(pToken[i].token == 'e')
			par--;
	}

	if(par < 0)
	{
		printf("\nERRO: Sintático TIPO: Encontrado um ELSE sem IF-THEN\n");
		exit(EXIT_FAILURE);
	}
}

void sintaxar(char arq[])
{
	/*
	/ Esta função analisa os char's armazenados na struct, e, 
	/ conforme a especificação apresentada no arquivo DOCUMENTACAO,
	/ ele compara cada char com o seguinte, se o seguinte for um 
	/ dos chars aceito, ele passa pro char seguinte.
	/ Caso um dos char não for aceito, ele retorna uma mensagem
	/ de erro e finaliza o programa.
	*/
	

	EhPareado(); //Verifica os tokens pares


	int i;
	//menos dois, pois o último é nulo, e o penultimo é o \0

	for(i = 0; i < iToken; i++)
	{
		//Coloquei pra fazer um teste. Tá sempre dando erro na linha
		// que seria o \0 (EOF)
		if(pToken[i].token == '\0'){break;}

		//abre parenteses
		else if((pToken[i].token == 'a')&&((pToken[i+1].token == 'a')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'l')||(pToken[i+1].token == 'g')||(pToken[i+1].token == 'k')||(pToken[i+1].token == 'r'))){continue;}

		//atribuição
		else if((pToken[i].token == 'b')&&((pToken[i+1].token == 'a')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'l')||(pToken[i+1].token == 'g')||(pToken[i+1].token == 'k')||(pToken[i+1].token == 'r'))){continue;}

		//begin
		else if((pToken[i].token == 'c')&&((pToken[i+1].token == 'f')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'j')||(pToken[i+1].token == 'o')||(pToken[i+1].token == 'u'))){continue;}

		//dois pontos
		else if((pToken[i].token == 'd')&&(pToken[i+1].token == 'q')){continue;}

		//else
		else if((pToken[i].token == 'e')&&(pToken[i+1].token == 'c')){continue;}

		//end
		else if((pToken[i].token == 'f')&&((pToken[i+1].token == 'e')||(pToken[i+1].token == 'f')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'j')||(pToken[i+1].token == 'o')||(pToken[i+1].token == 'u')||(pToken[i+1].token == '\0'))){continue;}

		//false
		else if((pToken[i].token == 'g')&&((pToken[i+1].token == 'h')||pToken[i+1].token == 'n')){continue;}

		//fecha parenteses
		else if((pToken[i].token == 'h')&&((pToken[i+1].token == 'h')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'l')||(pToken[i+1].token == 'p')||(pToken[i+1].token == 'm')||(pToken[i+1].token == 'n'))){continue;}

		//identificador
		else if((pToken[i].token == 'i')&&((pToken[i+1].token == 'b')||(pToken[i+1].token == 'd')||(pToken[i+1].token == 'h')||(pToken[i+1].token == 'm')||(pToken[i+1].token == 'n')||(pToken[i+1].token == 'p')||(pToken[i+1].token == 's')||(pToken[i+1].token == 't')||(pToken[i+1].token == 'i'))){continue;} //fiz um cheat! Estou aceitando identificador com identificador, pois há erro no sistema de gerar o espaço, que acaba separando um identificador em dois identificadores

		//if
		else if((pToken[i].token == 'j')&&((pToken[i+1].token == 'a')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'l'))){continue;}

		//not
		else if((pToken[i].token == 'k')&&((pToken[i+1].token == 'a')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'g')||(pToken[i+1].token == 'k')||(pToken[i+1].token == 'r'))){continue;}

		//numero
		else if((pToken[i].token == 'l')&&((pToken[i+1].token == 'h')||(pToken[i+1].token == 'm')||(pToken[i+1].token == 'n'))){continue;}

		//operador
		else if((pToken[i].token == 'm')&&((pToken[i+1].token == 'a')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'l'))){continue;}

		//Operador igual e diferente
		else if((pToken[i].token == 'w')&&((pToken[i+1].token == 'a')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'l')||(pToken[i+1].token == 'g')||(pToken[i+1].token == 'k')||(pToken[i+1].token == 'r'))){continue;}

		//ponto e virgula
		else if((pToken[i].token == 'n')&&((pToken[i+1].token == 'c')||(pToken[i+1].token == 'e')||(pToken[i+1].token == 'f')||(pToken[i+1].token == 'i')||(pToken[i+1].token == 'j')||(pToken[i+1].token == 'o')||(pToken[i+1].token == 's')||(pToken[i+1].token == 'u'))){continue;}

		//read
		else if((pToken[i].token == 'o')&&(pToken[i+1].token == 'a')){continue;}

		//then
		else if((pToken[i].token == 'p')&&(pToken[i+1].token == 'c')){continue;}

		//tipo
		else if((pToken[i].token == 'q')&&(pToken[i+1].token == 'n')){continue;}

		//true
		else if((pToken[i].token == 'r')&&((pToken[i+1].token == 'h')||(pToken[i+1].token == 'n'))){continue;}

		//var
		else if((pToken[i].token == 's')&&(pToken[i+1].token == 'i')){continue;}

		//virgula
		else if((pToken[i].token == 't')&&(pToken[i+1].token == 'i')){continue;}

		//write
		else if((pToken[i].token == 'u')&&(pToken[i+1].token == 'a')){continue;}

		//program
		else if((pToken[i].token == 'v')&&(pToken[i+1].token == 'i')){continue;}

		//Se entrar aqui, é pq houve sequência de tokens inválida
		else
			erroSintaxe(i);
	}
}

void erroSintaxe(int i)
{
	printf("\nERRO: Sintático LINHA: %i:\n", pToken[i].linha+1);
	printf("%s\n\n", txtLinha[pToken[i].linha]);
	exit(EXIT_FAILURE);
}
