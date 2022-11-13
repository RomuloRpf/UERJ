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
#define FIM -1;


//ATRIBUTOS
#define DOISPF 500; // ..
#define LE 501; // <=
#define EQ 502; // ==
#define NE 503; // ~=
#define GE 504; // >=
#define SemAtrib -1;

bool Block();
bool Stmt();
bool Stmt_1();
bool Stmt_11();
bool Stmt_2();
bool Exps();
bool Exp();
bool Exp_1();
bool PrefixExp();
bool PrefixExp_1();
bool Field();
bool BinOp();
bool Vars();
bool Var();
bool Var_1();
bool Function();
bool FunctionBody();
bool Params();
bool Names();
int erro();

struct Token{
 int nome_token;
 int atributo;
};

Token token;
int linhas = 1;
int estado = 0;
int partida = 0;
int cont_sim_lido = 0;
char *code;
string lexema;
vector<string> tabelaSimbolos;

int p_Reservada(int indice){

    if(indice == 0) {return AND;}
    else if(indice == 1) {return BREAK;}
    else if(indice == 2) {return DO;}
    else if(indice == 3) {return ELSE;}
    else if(indice == 4) {return ELSEIF;}
    else if(indice == 5) {return END;}
    else if(indice == 6) {return FALSE;}
    else if(indice == 7) {return FOR;}
    else if(indice == 8) {return FUNCTION;}
    else if(indice == 9) {return IF;}
    else if(indice == 10) {return IN;}
    else if(indice == 11) {return LOCAL;}
    else if(indice == 12) {return NIL;}
    else if(indice == 13) {return NOT;}
    else if(indice == 14) {return OR;}
    else if(indice == 15) {return REPEAT;}
    else if(indice == 16) {return RETURN;}
    else if(indice == 17) {return THEN;}
    else if(indice == 18) {return TRUE;}
    else if(indice == 19) {return UNTIL;}
    else if(indice == 20) {return WHILE;}
    return 0;
}


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
	fclose(file);
	free(file);
	return code;
}




int falhar()
{
	switch(estado)
	{
	case 0: partida = 2; break; //num

	case 2: partida = 5; break; //id

	case 5: partida = 8; break; //string

	case 8: partida = 20; break; //del

	case 20: //op
		//retornar msg de erro
		cout << "Erro encontrado na linha "<< linhas <<endl;
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
	char aux;
	int count_colA;
	int count_colF;
	while(code[cont_sim_lido] != EOF)
	{
		switch(estado)
		{
		    case 0:  //Estado 0 (NUM)
		        lexema = "";
		        c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n')){
                    if((c == '\n')) linhas +=1;
					estado = 0;
					cont_sim_lido++;
				}
				else if (isdigit(c)){
                    estado = 1;
                    lexema +=c;
				}
				else{
					 estado = falhar();
                }
				break;

            case 1: //Estado 1 (NUM)
                cont_sim_lido++;
                c = code[cont_sim_lido];
                while(isdigit(c)){
                    lexema +=c;
                    cont_sim_lido++;
                    c = code[cont_sim_lido];
                }
                estado = 45;
                break;

            case 45:
                estado = 0;
                cout << "Lexema: " << lexema << " --- token: " << "<num, " << lexema << ">" << endl;
                token.nome_token = NUM;
                token.atributo = stoi(lexema);
                return(token);

            case 2: //Estado 2 (ID)
                lexema = "";
		        c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
				    if((c == '\n')) linhas +=1;
					estado = 0;
					cont_sim_lido++;
				}
				else if (c=='_'){
                    estado = 3;
                    lexema +=c;
				}
				else if (isalpha(c)){
                    estado = 4;
                    lexema +=c;
				}
				else{
                    estado = falhar();
                }
				break;

            case 3: //Estado 3 (ID)
                cont_sim_lido++;
                c = code[cont_sim_lido];
				if(isdigit(c)||isalpha(c)){
				    estado = 4;
				    lexema +=c;
				}
				else{
				    estado = falhar();
                }
                break;

            case 4: //Estado 4 (ID)
                cont_sim_lido++;
                c = code[cont_sim_lido];
                while(isdigit(c)||isalpha(c)||c=='_'){
                    lexema +=c;
                    cont_sim_lido++;
                    c = code[cont_sim_lido];
                }
                estado = 46;
                break;

            case 46:

                estado = 0;
                int i;
                for ( i = 0; i < tabelaSimbolos.size(); i++){
					if(tabelaSimbolos[i]==lexema){
					    if (i<=20){
                            cout << "Lexema: " << lexema << " ---  token: " << "<" << lexema << ",>" << endl;
                            token.nome_token = p_Reservada(i);
                            token.atributo = SemAtrib;
                            return(token);
					    }
					    else{
                            cout << "Lexema: " << lexema << " ---  token: " << "<id," << i << ">" << endl;
                            token.nome_token = ID;
                            token.atributo = i;
                            return(token);
                        }
					}
				}
				tabelaSimbolos.push_back(lexema);
                cout << "Lexema: " << lexema << " ---  token: " << "<id," << i << ">" << endl;
                token.nome_token = ID;
                token.atributo = i;
                return(token);

            case 5: //Estado 5 (String)
                lexema = "";
		        c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n')){
                    if((c == '\n')) linhas +=1;
					estado = 0;
					cont_sim_lido++;
				}
				else if ((c=='"')){
                    estado = 6;
                    lexema +=c;
				}
				else{
					 estado = falhar();
                }
				break;

            case 6: //Estado 6 (String)
                cont_sim_lido++;
                c = code[cont_sim_lido];
                while(c != '"'){
                    lexema +=c;
                    cont_sim_lido++;
                    c = code[cont_sim_lido];
                }
                estado = 7;
                lexema +=c;
                break;

            case 7: //Estado 7 (String)
                estado = 0;
                cont_sim_lido++;
                tabelaSimbolos.push_back(lexema);
                cout << "Lexema: " << lexema << " --- token: " << "<string, " << tabelaSimbolos.size()-1 << ">" << endl;
                token.nome_token = STRING;
                token.atributo = tabelaSimbolos.size()-1 ;
                return(token);

            case 8: // (Delimitadores)
                c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
				    if((c == '\n')) linhas +=1;
					estado = 0;
					cont_sim_lido++;
				}
				else if(c == '(') estado = 9;
				else if(c == ')') estado = 10;
				else if(c == '[') estado = 11;
				else if(c == ']') estado = 12;
				else if(c == '{') estado = 13;
				else if(c == '}') estado = 14;
				else if(c == ';') estado = 15;
				else if(c == ':') estado = 16;
				else if(c == '.') estado = 17;
				else if(c == ',') estado = 47;
				else
				{
				    estado = falhar();
				}
				break;

            case 47:
                cont_sim_lido++;
				cout << "Lexema: , " << " ---  token: " << "<,,>" << endl;
				token.nome_token = 44;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 9:
                cont_sim_lido++;
				cout << "Lexema: ( " << " ---  token: " << "<(,>" << endl;
				token.nome_token = 40;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 10:
                cont_sim_lido++;
				cout << "Lexema: ) " << " ---  token: " << "<),>" << endl;
				token.nome_token = 41;
				token.atributo =  SemAtrib;
				estado = 0;
				return(token);

            case 11:
                cont_sim_lido++;
				cout << "Lexema: [ " << " ---  token: " << "<[,>" << endl;
				token.nome_token = 91;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 12:
                cont_sim_lido++;
				cout << "Lexema: ] " << " ---  token: " << "<],>" << endl;
				token.nome_token = 93;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 13:
                cont_sim_lido++;
				cout << "Lexema: {" << " ---  token: " << "<{,>" << endl;
				token.nome_token = 123;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 14:
                cont_sim_lido++;
				cout << "Lexema: } " << " ---  token: " << "<},>" << endl;
				token.nome_token = 125;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 15:
                cont_sim_lido++;
				cout << "Lexema: ; " << " ---  token: " << "<;,>" << endl;
				token.nome_token = 59;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 16:
                cont_sim_lido++;
				cout << "Lexema: : " << " ---  token: " << "<:,>" << endl;
				token.nome_token = 58;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 17:
                lexema = "" + c;
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c=='.'){
                    estado = 18;
                    lexema +=c;
                }
                else{
                    estado = 19;
                }
                break;

            case 18:
                cont_sim_lido++;
				cout << "Lexema: .." << " ---  token: " << "<del_op,..>" << endl;
				token.nome_token = DEL_OP;
				token.atributo = DOISPF;
				estado = 0;
				return(token);

            case 19:
				cout << "Lexema: ." << " ---  token: " << "<.,>" << endl;
				token.nome_token = 46;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 20: // operadores
                c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
				    if((c == '\n')) linhas +=1;
					estado = 0;
					cont_sim_lido++;
				}
				else if(c == '+') estado = 21;
				else if(c == '*') estado = 22;
				else if(c == '/') estado = 23;
				else if(c == '^') estado = 24;
				else if(c == '=') estado = 25;
				else if(c == '~') estado = 26;
				else if(c == '<') estado = 27;
				else if(c == '>') estado = 28;
				else if(c == '-') estado = 29;
				else if(c == '!') estado = 44;
				else
				{
				    estado = falhar();
				}
				break;

            case 21:
                cont_sim_lido++;
				cout << "Lexema: +" << " ---  token: " << "<+,>" << endl;
				token.nome_token = 43;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 22:
                cont_sim_lido++;
				cout << "Lexema: *" << " ---  token: " << "<*,>" << endl;
				token.nome_token = 42;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 23:
                cont_sim_lido++;
				cout << "Lexema: /" << " ---  token: " << "</,>" << endl;
				token.nome_token = 47;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 24:
                cont_sim_lido++;
				cout << "Lexema: ^" << " ---  token: " << "<^,>" << endl;
				token.nome_token = 94;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 25:
                lexema = "" + c;
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c=='='){
                    estado = 30;
                    lexema +=c;
                }
                else{
                    estado = 31;
                }
                break;

            case 26:
				lexema = "" + c;
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c=='='){
                    estado = 32;
                    lexema +=c;
                }
                else{
                    estado = falhar();
                }
                break;

            case 27:
                lexema = "" + c;
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c=='='){
                    estado = 33;
                    lexema +=c;
                }
                else{
                    estado = 34;
                }
                break;

            case 28:
                lexema = "" + c;
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c=='='){
                    estado = 35;
                    lexema +=c;
                }
                else{
                    estado = 36;
                }
                break;

            case 29:
                lexema = "" + c;
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c=='-'){
                    estado = 38;
                    lexema +=c;
                }
                else{
                    estado = 37;
                }
                break;

            case 30:
                cont_sim_lido++;
				cout << "Lexema: ==" << " ---  token: " << "<del_op,==>" << endl;
				token.nome_token = DEL_OP;
				token.atributo = EQ;
				estado = 0;
				return(token);

            case 31:
                cout << "Lexema: =" << " ---  token: " << "<=,>" << endl;
				token.nome_token = 61;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 32:
                cont_sim_lido++;
				cout << "Lexema: ~=" << " ---  token: " << "<del_op,~=>" << endl;
				token.nome_token = DEL_OP;
				token.atributo = NE;
				estado = 0;
				return(token);

            case 33:
                cont_sim_lido++;
				cout << "Lexema: <=" << " ---  token: " << "<del_op,<=>" << endl;
				token.nome_token = DEL_OP;
				token.atributo = LE;
				estado = 0;
				return(token);

            case 34:
				cout << "Lexema: <" << " ---  token: " << "<<,>" << endl;
				token.nome_token = 60;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 35:
                cont_sim_lido++;
				cout << "Lexema: >=" << " ---  token: " << "<del_op,>=>" << endl;
				token.nome_token = DEL_OP;
				token.atributo = GE;
				estado = 0;
				return(token);

            case 36:
                cout << "Lexema: >" << " ---  token: " << "<>,>" << endl;
				token.nome_token = 62;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 37:
                cout << "Lexema: -" << " ---  token: " << "<-,>" << endl;
				token.nome_token = 45;
				token.atributo = SemAtrib;
				estado = 0;
				return(token);

            case 38:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c=='['){
                    estado = 41;
                }
                else{
                    estado = 39;
                }
                break;

            case 39:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                while(c != '\n'){
                    cont_sim_lido++;
                    c = code[cont_sim_lido];
                }
                linhas +=1;
                estado = 40;
                break;

            case 40:
                estado = 0;
                cont_sim_lido++;
                break;

            case 41:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c=='['){
                    estado = 42;
                }
                else{
                    estado = 39;
                }
                break;

            case 42:
                count_colA = 1;
                count_colF = 0;
                cont_sim_lido++;
                c = code[cont_sim_lido];
                while(true){
                    if (c=='['){
                        aux = code[cont_sim_lido+1];
                        if (aux=='['){
                            count_colA +=1;
                            cont_sim_lido += 2;
                            c = code[cont_sim_lido];
                        }
                    }
                    else if (c==']'){
                        aux = code[cont_sim_lido+1];
                        if (aux==']'){
                            count_colF +=1;
                            if (count_colA == count_colF){
                                estado = 43;
                                break;
                            }
                            cont_sim_lido += 2;
                            c = code[cont_sim_lido];
                        }

                    }
                    else{
                        cont_sim_lido++;
                        c = code[cont_sim_lido];
                    }
                }
                break;

            case 43:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if (c==']'){
                    estado = 40;
                }
                else{
                    estado = falhar();
                }
                break;

            case 44:
                cout << "Lexema: !" << " ---  token: " << "<!,>" << endl;
                token.nome_token = FIM;
                token.atributo = SemAtrib;
                return(token);

		} // fim switch
	} // fim while
	token.nome_token = EOF;
	token.atributo = -1;
	return(token);
}

bool Block(){
    cout << "Block"<<endl;
    token = proximo_token();
    if (token.nome_token == 271|| token.nome_token == 40|| token.nome_token == 258|| token.nome_token == 252|| token.nome_token == 270||
        token.nome_token == 259||  token.nome_token == 266|| token.nome_token == 251|| token.nome_token == 257|| token.nome_token == 261) {
            while (true) {
                Stmt();
                if (token.nome_token != 59) {
                    cout << "Na linha " << linhas << " ';' era o caractere esperado" << endl;
                    erro();
                }
                token = proximo_token();
                if ((token.nome_token == -1) && (token.atributo == -1)) {
                    return true;
                }
                else if (token.nome_token != 271 && token.nome_token != 40 && token.nome_token != 258 && token.nome_token != 252 && token.nome_token != 270 &&
                         token.nome_token != 259 &&  token.nome_token != 266 && token.nome_token != 251 && token.nome_token != 257 && token.nome_token != 261) {
                            break;
                }
            }
    }
    else if ((token.nome_token == -1) && (token.atributo == -1)) {
        return true;
    }
    else {
        erro();
    }
    cout << "Desempilha Block"<<endl;
    return true;
}

bool Stmt(){
    cout << "Stmt"<<endl;
    if (token.nome_token == 271 || token.nome_token == 40) {
        Vars();
        token = proximo_token();
        if ( token.nome_token != 61) {
            cout << "Na linha " << linhas << "'=' era esperado" << endl;
            erro();
        }
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
            token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
            token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274 ) {
                Exps();
        }
        else {
            erro();
        }
    }
    else if (token.nome_token == 258) {
            Function();
    }
    else if ( token.nome_token == 252) {
        Block();
        token = proximo_token();
        if ( token.nome_token != 255) {
            cout <<"Na linha "<< linhas << " end era o comando esperado" << endl;
            erro();
        }
    }
    else if (token.nome_token == 270) {
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
            token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
            token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274 ) {
                Exp();
            }
        else{
                erro();
        }
        if (token.nome_token != 252) {
            cout <<"Na linha "<< linhas << " do era o comando esperado" << endl;
            erro();
        }
        Block();
        token = proximo_token();
        if (token.nome_token != 255) {
            cout <<"Na linha "<< linhas << " end era o comando esperado" << endl;
            erro();
        }
    }
    else if (token.nome_token == 259) {
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
            token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
            token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) {
                Exp();
        }
        else {
            erro();
        }
        if (token.nome_token != 267) {
            cout <<"Na linha "<< linhas << " then era o comando esperado" << endl;
            erro();
        }
        Block();
        token = proximo_token();
        if (token.nome_token == 254) {
            token = proximo_token();
            while (true) {
                if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
                    token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
                    token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) {
                            Exp();
                }
                else {
                            erro();
                }
                token = proximo_token();
                if (token.nome_token != 267) {
                    cout <<"Na linha "<< linhas << " then era o comando esperado" << endl;
                    erro();
                }
                Block();
                token = proximo_token();
                if (token.nome_token != 254) {
                    break;
                }
            }
        }
        if (token.nome_token == 253) {
            Block();
            token = proximo_token();
        }
        if (token.nome_token != 255) {
            cout <<"Na linha "<< linhas << " end era o comando esperado" << endl;
            erro();
        }
    }
    else if (token.nome_token == 266) {
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
            token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
            token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) {
                Exps();
        }
    }
    else if (token.nome_token == 251) {
            return true;
    }
    else if (token.nome_token == 257) {
        token = proximo_token();
        if (token.nome_token == 271) {
            Stmt_1();
        }
        else {
            erro();
        }
    }
    else if (token.nome_token == 261) {
        token = proximo_token();
        if (token.nome_token == 271 || token.nome_token == 258) {
            Stmt_2();
        }
        else {
            erro();
        }
    }
    else {
        erro();
    }
    cout << "Desempilha Stmt"<<endl;
    return true;
}

bool Stmt_1(){
    cout << "Stmt_1"<<endl;
    token = proximo_token();
    if (token.nome_token == 61 || token.nome_token == 260 || token.nome_token == 44){
        Stmt_11();
    }
    else{
        erro();
    }
    cout << "Desempilha Stmt_1"<<endl;
    return true;
}

bool Stmt_11(){
    cout << "Stmt_11"<<endl;
    if ( token.nome_token == 61)
    {
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
                token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
                token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274)
        {
            Exp();
        }
        else
        {
            erro();
        }
        token = proximo_token();
        if ( token.nome_token != 44)
        {
            cout << "Na linha "<< linhas << " ',' era o caractere esperado" << endl;
            erro();
        }
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
                token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
                token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274)
        {
            Exp();
        }
        else
        {
            erro();
        }
        token = proximo_token();
        if (token.nome_token == 44)
        {
            if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
                    token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
                    token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274)
            {
                Exp();
            }
            else
            {
                erro();
            }
        }
        if (token.nome_token != 252)
        {
            cout << "Na linha " << linhas << " do era a palavra esperada"<<endl;
            erro();
        }
        Block();
        token = proximo_token();
        if ( token.nome_token != 255)
        {
            cout << "Na linha " << linhas << " end era a palavra esperada"<<endl;
            erro();
        }
    }
    else if (token.nome_token == 260 || token.nome_token == 44)
    {
        if (token.nome_token == 44 )
        {
            while (true)
            {
                token = proximo_token();
                if (token.nome_token != 271)
                {
                    cout << "Na linha "<< linhas << " era esperado um id"<< endl;
                    erro();
                }
                token = proximo_token();
                if(token.nome_token != 44 ) break;
            }
        }
        else {
            token = proximo_token();
        }
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
                token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
                token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274)
        {
            cout <<"OI"<<endl;
            Exps();
        }
        else
        {
            erro();
        }
        token = proximo_token();
        if (token.nome_token != 252)
        {
            cout << "Na linha " << linhas << " do era a palavra esperada"<<endl;
            erro();
        }
        Block();
        token = proximo_token();
        if ( token.nome_token != 255)
        {
            cout << "Na linha " << linhas << " end era a palavra esperada"<<endl;
            erro();
        }
    }
    else
    {
        cout << "Na linha " << linhas << " '=' ou ',' eram os simbolos esperados ou a palavra reservada in"<<endl;
        erro();
    }
    cout << "Desempilha Stmt_11"<<endl;
    return true;
}

bool Stmt_2(){
    cout << "Stmt_2"<<endl;
    if (token.nome_token == 258) {
            token = proximo_token();
            if (token.nome_token == 271) {
                FunctionBody();
            }
            else {
                cout << "Na linha " << linhas << "era esperado um id" << endl;
                erro();
            }
    }
	else if ( token.nome_token == 271) {
            token = proximo_token();
            if ( token.nome_token != 61) {
                cout << "Na linha " << linhas << "'=' era o caractere esperado" << endl;
                erro();
            }
            token = proximo_token();
            if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
                token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
                token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) { //First(Exps)
                    Exps();
            }
            else {
                erro();
            }
    }
	else {
        cout << "Na linha " << linhas << "era esperado um id ou a palavra reservada 'function'" << endl;
        erro();
    }
    cout << "Desempilha Stmt_2"<<endl;
    return true;
}

bool Exps(){
    cout << "Exps"<<endl;
    Exp();
    while (true) {
        if (token.nome_token == 44 ) {
            token = proximo_token();
            if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
                token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
                token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) { //First(Exp)
                    Exp();
            }
            else{
                erro();
            }
        }
        else{
            break;
        }
    }
    cout << "Desempilha Exps"<<endl;
    return true;
}

bool Exp(){
    cout << "Exp"<<endl;
    if ( token.nome_token == 263) {
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
            token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
            token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) { //First(Exp)
                    Exp();
        }
        else {
            erro();
        }
        token = proximo_token();
        if (token.nome_token  == 264 || token.nome_token  == 250 || token.nome_token  == 60 || token.nome_token  == 62 ||
            token.atributo  == 500 || token.atributo  == 501 || token.atributo  == 502 || token.atributo  == 503 ||
            token.atributo  == 504 || token.nome_token  == 43 || token.nome_token  == 45 || token.nome_token  == 42 ||
            token.nome_token  == 47 || token.nome_token  == 94) { //First(Exp_1)
                Exp_1();
        }
        else {
            return true;
        }
    }
	else if ( token.nome_token == 45) {
            token = proximo_token();
            if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
            token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
            token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) { //First(Exp)
                Exp();
        }
        else {
            erro();
        }
        token = proximo_token();
        if (token.nome_token  == 264 || token.nome_token  == 250 || token.nome_token  == 60 || token.nome_token  == 62 ||
            token.atributo  == 500 || token.atributo  == 501 || token.atributo  == 502 || token.atributo  == 503 ||
            token.atributo  == 504 || token.nome_token  == 43 || token.nome_token  == 45 || token.nome_token  == 42 ||
            token.nome_token  == 47 || token.nome_token  == 94) { //First(Exp_1)
                Exp_1();
        }
        else {
                return true;
        }
    }
	else if (token.nome_token == 271 || token.nome_token == 40) {
          PrefixExp();
          token = proximo_token();
          if (token.nome_token  == 264 || token.nome_token  == 250 || token.nome_token  == 60 || token.nome_token  == 62 ||
              token.atributo  == 500 || token.atributo  == 501 || token.atributo  == 502 || token.atributo  == 503 ||
              token.atributo  == 504 || token.nome_token  == 43 || token.nome_token  == 45 || token.nome_token  == 42 ||
              token.nome_token  == 47 || token.nome_token  == 94) { //First(Exp_1)) {
                    Exp_1();
        }
        else {
            return true;
        }
    }
	else if ( token.nome_token == 258) {
	    Function();
        token = proximo_token();
        if (token.nome_token  == 264 || token.nome_token  == 250 || token.nome_token  == 60 || token.nome_token  == 62 ||
              token.atributo  == 500 || token.atributo  == 501 || token.atributo  == 502 || token.atributo  == 503 ||
              token.atributo  == 504 || token.nome_token  == 43 || token.nome_token  == 45 || token.nome_token  == 42 ||
              token.nome_token  == 47 || token.nome_token  == 94) { //First(Exp_1)) {
                  Exp_1();
        }
        else {
            return true;
        }
    }
	else if ( token.nome_token == 123) {
	    token = proximo_token();
        if ( token.nome_token == 91 || token.nome_token == 271) {
            Field();
            while (true) {
                    token = proximo_token();
                    if ( token.nome_token == 44) {
                            token = proximo_token();
                            if (  token.nome_token == 91 || token.nome_token == 271 ) {
                                    Field();
                            }
                            else {
                                erro();
                            }
                    }
                    else {
                            break;
                    }
            }
        }
        if (token.nome_token != 123) {
            cout <<"Na linha "<<linhas <<"'}' era o caractere esperado"<<endl;
            erro();
        }
        token = proximo_token();
        if (token.nome_token  == 264 || token.nome_token  == 250 || token.nome_token  == 60 || token.nome_token  == 62 ||
            token.atributo  == 500 || token.atributo  == 501 || token.atributo  == 502 || token.atributo  == 503 ||
            token.atributo  == 504 || token.nome_token  == 43 || token.nome_token  == 45 || token.nome_token  == 42 ||
            token.nome_token  == 47 || token.nome_token  == 94) { //First(Exp_1)) {
                Exp_1();
        }
        else {
            return true;
        }
    }
	else if (token.nome_token == 262 || token.nome_token == 268 || token.nome_token == 256 || token.nome_token == 272 || token.nome_token == 274) {
            token = proximo_token();
            if (token.nome_token  == 264 || token.nome_token  == 250 || token.nome_token  == 60 || token.nome_token  == 62 ||
                token.atributo  == 500 || token.atributo  == 501 || token.atributo  == 502 || token.atributo  == 503 ||
                token.atributo  == 504 || token.nome_token  == 43 || token.nome_token  == 45 || token.nome_token  == 42 ||
                token.nome_token  == 47 || token.nome_token  == 94) { //First(Exp_1)) {
                    Exp_1();
            }
            else {
                return true;
            }
    }
	else {
		erro ();
    }
    cout << "Desempilha Exp"<<endl;
    return true;
}

bool Exp_1(){
    cout << "Exp_1"<<endl;
    BinOp();
    token = proximo_token();
    if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
        token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
        token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) {
                Exp();
    }
    else {
        erro();
    }
    cout << "Desempilha Exp_1"<<endl;
    return true;
}

bool PrefixExp(){
    cout << "PrefixExp"<<endl;
    token = proximo_token();
    if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
        token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
        token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274){
            Exp();
            token = proximo_token();
            if (token.nome_token != 40) {
                cout << "Na linha " << linhas << " ')' era o caractere esperado"<<endl;
                erro();
            }
            token = proximo_token();
    }
    else if (token.nome_token == 91) {
        PrefixExp_1();
    }
    cout << "Desempilha PrefixExp"<<endl;
    return true;
}

bool PrefixExp_1(){
    cout << "PrefixExp_1"<<endl;
    token = proximo_token();
	if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
        token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
        token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274){
            Exp();
            token = proximo_token();
            if (token.nome_token != 93) {
                cout<< "Na linha "<< linhas <<"']' era o caractere esperado"<<endl;
                erro();
            }
            token = proximo_token();
            if (token.nome_token == 91) {
                    PrefixExp_1();
            }
            else {
                    erro();
            }
    }
    else {
        erro();
    }
    cout << "Desempilha PrefixExp_1"<<endl;
    return true;
}

bool Field(){
    cout << "Field"<<endl;
    token = proximo_token();
	if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
        token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
        token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274 ) {
            Exp();
            token = proximo_token();
            if (token.nome_token != 93) {
                cout << "Na linha "<< linhas << "']' era o caractere esperado"<<endl;
                erro();
            }
            token = proximo_token();
            if (token.nome_token != 61) {
                cout << "Na linha "<< linhas << "'=' era o caractere esperado"<<endl;
                erro();
            }
            token = proximo_token();
            if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
                token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
                token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274 ) {
                    Exp();
            }
            else {
                erro();
            }
    }
    else if (token.nome_token == 61) {
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
            token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
            token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274 ) {
                Exp();
        }
        else {
            erro();
        }
    }
    else {
        erro();
    }
    cout << "Desempilha Field"<<endl;
	return true;
}

bool BinOp(){
    cout << "Binop"<<endl;
    cout << "Desempilha Binop"<<endl;
    return true;}

bool Vars(){
    cout << "Vars"<<endl;
    Var();
    while (true) {
        token = proximo_token();
		if (token.nome_token == 44) {
			token = proximo_token();
            if (token.nome_token == 271 || token.nome_token == 40) {
                Var();
            }
            else {
                erro();
            }
        }
        else {
            break;
        }
    }
    cout << "Desempilha Vars"<<endl;
	return true;
}

bool Var(){
    cout << "Var"<<endl;
    token = proximo_token();
    if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
        token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
        token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) {
        Exp();
        token = proximo_token();
        if (token.nome_token  != 41) {
            cout << "Na linha "<< linhas <<" ')' era o caractere esperado"<<endl;
            erro();
        }
        token = proximo_token();
        if (token.nome_token == 91) {
            PrefixExp_1();
        }
        else {
            erro();
        }
        token = proximo_token();
        if (token.nome_token  != 91) {
            cout << "Na linha "<< linhas << "'['era o caractere esperado"<<endl;
            erro();
        }
        token = proximo_token();
        if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
            token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
            token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) {
            Exp();
        }
        else {
            erro();
        }
        token = proximo_token();
        if ( token.nome_token  != 93) {
            cout << "Na linha "<< linhas << "']'era o caractere esperado"<<endl;
            erro();
        }
    }
    else if (token.nome_token  == 91) {
        Var_1();
    }
    else {
        erro();
    }
    cout << "Desempilha Var"<<endl;
    return true;
}

bool Var_1(){
    cout << "Var_1"<<endl;
    PrefixExp_1();
    token = proximo_token();
    if (token.nome_token  != 91) {
        cout << "Na linha "<< linhas << "'['era o caractere esperado"<<endl;
        erro();
    }
    token = proximo_token();
    if (token.nome_token  == 263 || token.nome_token  == 45 || token.nome_token  == 271 || token.nome_token  == 40 ||
        token.nome_token  == 258 || token.nome_token  == 123 || token.nome_token  == 262 || token.nome_token  == 268 ||
        token.nome_token  == 256 || token.nome_token  == 272 || token.nome_token  == 274) {
            Exp();
    }
    else {
        erro();
    }
    token = proximo_token();
    if ( token.nome_token  != 93) {
        cout << "Na linha "<< linhas << "']'era o caractere esperado"<<endl;
        erro();
    }
    cout << "Desempilha Var_1"<<endl;
    return true;
}

bool Function(){
    cout << "Function"<<endl;
    token = proximo_token();
	if (token.nome_token == 271) {
        FunctionBody();
    }
    else {
        cout <<"Na linha "<<linhas<<" era esperado um id"<<endl;
        erro();
    }
    cout << "Desempilha Function"<<endl;
    return true;
}

bool FunctionBody(){
    cout << "FunctionBody"<<endl;
    token = proximo_token();
	if (token.nome_token  != 40) {
        cout << "Na linha "<< linhas << "'('era o caractere esperado"<<endl;
        erro();
    }
    token = proximo_token();
    if (token.nome_token == 271) {
        Params();
    }
    if (token.nome_token  != 41) {
        cout << "Na linha "<< linhas << "')'era o caractere esperado"<<endl;
        erro();
    }
    Block();
    token = proximo_token();
    if (token.nome_token != 255) {
        cout <<"Na linha "<< linhas << " end era o comando esperado" << endl;
        erro();
    }
    cout << "Desempilha FunctionBody"<<endl;
    return true;
}

bool Params(){
    cout << "Params"<<endl;
    Names();
    cout << "Desempilha Params"<<endl;
    return true;
}

bool Names(){
    cout << "Names"<<endl;
    while (true) {
        token = proximo_token();
        if (token.nome_token == 44 ) {
            token = proximo_token();
            if (token.nome_token != 271) {
                cout << "Na linha "<< linhas << " era esperado um id"<< endl;
                erro();
            }
        }
        else{
            break;
        }
    }
    cout << "Desempilha Names"<<endl;
    return true;
}

int erro(){ return 0;}

int main ()
{
	tabelaSimbolos.push_back("and");
	tabelaSimbolos.push_back("break");
	tabelaSimbolos.push_back("do");
	tabelaSimbolos.push_back("else");
	tabelaSimbolos.push_back("elseif");
	tabelaSimbolos.push_back("end");
	tabelaSimbolos.push_back("false");
	tabelaSimbolos.push_back("for");
	tabelaSimbolos.push_back("function");
	tabelaSimbolos.push_back("if");
	tabelaSimbolos.push_back("in");
	tabelaSimbolos.push_back("local");
	tabelaSimbolos.push_back("nil");
	tabelaSimbolos.push_back("not");
	tabelaSimbolos.push_back("or");
	tabelaSimbolos.push_back("repeat");
	tabelaSimbolos.push_back("return");
	tabelaSimbolos.push_back("then");
	tabelaSimbolos.push_back("true");
	tabelaSimbolos.push_back("until");
	tabelaSimbolos.push_back("while");

    code = readFile("programa.txt");
    if (code == NULL){
        cout << "Arquivo nao encontrado"<<endl;
    }

    Block();
    /*while(true){
        token = proximo_token();
        if ((token.nome_token == -1) && (token.atributo == -1)){
            break;
        }
    }*/
    return 0;
}
