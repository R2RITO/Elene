%{

#define YYSTYPE double
#include <math.h>
#include <stdio.h>

int yylex (void);
void yyerror (char const *);

%}

/*
    Gramatica :)


inicio : varglobal


varglobal : funciones 
          | VARIABLES GLOBALES LBRACKET listaVariables RBRACKET funciones

listaVariables : decVariable
               | decVariable SEMICOLON listaVariables

decVariables   : SEA ID DE TIPO tipo
               | SEA ID DE TIPO tipo CON VALOR expr

tipo : BOOLEANO
     | ENTERO
     | FLOTANTE
     | CARACTER
     | STRING
     | VACIO
     // FALTA ARREGLO


funciones : programa
          | FUNCIONES LBRACKET listaFunciones RBRACKET programa

listaFunciones : decFuncion
               | decFuncion listaFunciones

decFuncion : SEA LA FUNCION ID QUE RECIBE listArg Y RETORNA retorno HACER bloque 
           | SEA LA FUNCION ID QUE RETORNA retorno HACER bloque
           | SEA LA FUNCION ID QUE RECIBE listArg HACER bloque

listArg : // FALTA


retorno : // FALTA

programa  : GUACARA bloque


bloque : LBRACKET variables RBRACKET

variables : listaInstruccion
          | VARIABLES LBRACKET listaVariables RBRACKET listaInstruccion

listaInstruccion : instruccion
                 | instruccion SEMICOLON listaInstruccion 


instruccion : READ ID

instruccion : IMPRIMIR ID

instruccion : SI expr ENTONCES bloque
            | SI expr ENTONCES bloque elseif

elseif      : else
            | O SI expr ENTONCES bloque
            | O SI expr ENTONCES bloque elseif

else        : SI NO ENTONCES bloque

asignacion  : ID BECOMES expr

instruccion : asignacion 

instruccion : MIENTRAS expr HACER bloque

instruccion : PARA asignacion TAL QUE expr CON CAMBIO expr HACER bloque 





input :
      | input line
      ;
     
line  :     '\n'
      | exp '\n'  { printf ("\t%.10g\n", $1); }
      ;
     
exp   : NUM                { $$ = $1;         }
      | exp '+' exp        { $$ = $1 + $3;    }
      | exp '-' exp        { $$ = $1 - $3;    }
      | exp '*' exp        { $$ = $1 * $3;    }
      | exp '/' exp        { $$ = $1 / $3;    }
      | '-' exp  %prec NEG { $$ = -$2;        }
      | exp '^' exp        { $$ = pow ($1, $3); }
      | '(' exp ')'        { $$ = $2;         }
      ;






*/


     
/* Bison declarations.  */

%token PLUS
%token MINUS
%token TIMES
%token SLASH
%token LPAREN
%token RPAREN
%token SEMICOLON
%token COMMA
%token PERIOD
%token BECOMES
%token LBRACKET
%token RBRACKET
%token LCORCHET
%token RCORCHET

%token ENTONCES
%token O
%token NO
%token SI
%token MIENTRAS
%token HACER
%token PARA
%token TAL
%token QUE
%token CON
%token CAMBIO
%token LEER
%token IMPRIMIR
%token RECIBE
%token Y
%token RETORNA
%token SEA
%token ESTRUCTURA
%token CONTIENE
%token UNION
%token VACIO
%token GUACARA
%token ENTERO
%token CARACTER
%token FLOTANTE
%token BOOLEANO
%token STRING
%token RETORNAR
%token VALOR
%token VERDADERO
%token FALSO
%token ES
%token A
%token MAYOR
%token MENOR
%token IGUAL
%token DISTINTO
%token DE
%token TIPO

%token FUNCIONES
%token VARIABLES
%token GLOBALES

%left '-' '+'
%left '*' '/'
%left NEG     /* negation--unary minus */
%right '^'    /* exponentiation */
     
%% /* The grammar follows.  */
input :    /* empty */
      | input line
      ;
     
line  :     '\n'
      | exp '\n'  { printf ("\t%.10g\n", $1); }
      ;
     
exp   : NUM                { $$ = $1;         }
      | exp '+' exp        { $$ = $1 + $3;    }
      | exp '-' exp        { $$ = $1 - $3;    }
      | exp '*' exp        { $$ = $1 * $3;    }
      | exp '/' exp        { $$ = $1 / $3;    }
      | '-' exp  %prec NEG { $$ = -$2;        }
      | exp '^' exp        { $$ = pow ($1, $3); }
      | '(' exp ')'        { $$ = $2;         }
      ;
%%

void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

void main (int argc,char **argv)
{
  yyparse ();
}
