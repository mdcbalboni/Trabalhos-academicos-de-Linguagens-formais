#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////
//		Funções Léxicas
////////
	void lerFile(char[], FILE*);
	void lexicar(char[]);
	void isVocabulary(char[]);	
	void putSpace(char[]);
	void tiraTAB(char[]);
	void desloca(char[], int);
	void getToken(char[]);
	int whoSpecial(char[], int);
	void isKeyword(char[], int);

/////////
//		Funções Sintáticas
////////
	void sintaxar(char[]);
	void erroSintaxe(int);

#endif /* FUNCTION_H */
