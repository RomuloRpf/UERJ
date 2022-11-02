#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
using namespace std;

//NOME TOKENS
#define AND 250;
#define BREAK 251;
#define DO 252;
#define ELSE 253;
#define ELSEIF 254;
#define END 255;
#define FALSE 256;
#define FOR 257;
#define FUNCTION 258;
#define IF 259;
#define IN 260;
#define LOCAL 261;
#define NIL 262;
#define NOT 263;
#define OR 264;
#define REPEAT 265;
#define RETURN 266;
#define THEN 267;
#define TRUE 268;
#define UNTIL 269;
#define WHILE 270;
#define ID 271;
#define NUM 272;
#define DEL_OP 273;
#define STRING 274;


//ATRIBUTOS
#define LT 262;
#define LE 263;
#define EQ 264;
#define NE 265;
#define GT 266;
#define GE 267;



struct Token{
 int nome_token;
 int atributo;
};



int estado = 0;
int partida = 0;
int cont_sim_lido = 0;
char *code;


char *readFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *code;
	int n = 0;
	int c;

	if(file == NULL) return NULL;

	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	code = new char (f_size);

	while ((c = fgetc(file))!= EOF)
	{
		code[n++] = (char) c;
	}
	code[n] = '\0';
	return code;
}




int falhar()
{
	switch(estado)
	{
	case 0: partida = 9; break;

	case 9: partida = 12; break;

	case 12: partida = 20; break;

	case 20: partida = 25; break;

	case 25:
		//retornar msg de erro
		printf("Erro encontrado no código\n");
		cont_sim_lido++;
		break;

	default: printf("Erro do compilador");
	}
	return(partida);
}

Token proximo_token()
{
	Token token;
	char c;
	while(code[cont_sim_lido] != EOF)
	{
		switch(estado)
		{
			case 0:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else if(c == '<') estado = 1;
				else if(c == '=') estado = 5;
				else if(c == '>') estado = 6;
				else
					{
					 estado = falhar();
					}
				break;

			case 1:
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(c == '=') estado = 2;
				else if(c == '>') estado = 3;
				else estado = 4;
				break;

			case 2:
				cont_sim_lido++;
				printf("<relop, LE>\n");
				token.nome_token = RELOP;
				token.atributo = LE;
				estado = 0;
				return(token);
				break;

			case 3:
				cont_sim_lido++;
				printf("<relop, NE>\n");
				token.nome_token = RELOP;
				token.atributo = NE;
				estado = 0;
				return(token);
				break;

			case 4:
				cont_sim_lido++;
				printf("<relop, LT>\n");
				token.nome_token = RELOP;
				token.atributo = LT;
				estado = 0;
				return(token);
				break;

			case 5:
				cont_sim_lido++;
				printf("<relop, EQ>\n");
				token.nome_token = RELOP;
				token.atributo = EQ;
				estado = 0;
				return(token);
				break;

			case 6:
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if(c == '=') estado = 7;
				else estado = 8;
				break;

			case 7:
				cont_sim_lido++;
				printf("<relop, GE>\n");
				token.nome_token = RELOP;
				token.atributo = GE;
				estado = 0;
				return(token);
				break;

			case 8:
				cont_sim_lido++;
				printf("<relop, GT>\n");
				token.nome_token = RELOP;
				token.atributo = GT;
				//ATENÇÃO - CORREÇÃO: foi acrescentado o comando "estado = 0;"
				estado = 0;
				return(token);
				break;

			case 9:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado */
					estado = falhar();
				}

				break;

				/*implementar ações para os estados 10, 11, 12*/

			case 12:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado */
					estado = falhar();
				}
				break;

				/*implementar ações para os estados 13-19*/

			case 20:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado */
					estado = falhar();
				}
				break;

				/*implementar ações para os estados 21-24*/

			case 25:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado */
					estado = falhar();
					token.nome_token = -1;
					token.atributo = -1;
					return(token);
				}
				break;
		}

	}
	token.nome_token = EOF;
	token.atributo = -1;
	return(token);
}




int main ()
{
	Token token;
    code = readFile("programa.txt");
    token = proximo_token();
    token = proximo_token();
    //...


}
