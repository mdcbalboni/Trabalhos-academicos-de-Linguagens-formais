all:
	clear
	gcc -Wall -c function.c
	gcc -Wall -c main.c
	gcc function.o main.o -o lex
	@echo
	@echo Compilou
	@echo
