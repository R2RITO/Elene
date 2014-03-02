%{

#define YYSTYPE double
#include <math.h>
#include <stdio.h>

int yylex (void);
void yyerror (char const *);

%}
     
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

%token NUMENTERO
%token NUMFLOTANTE

%token FUNCIONES
%token VARIABLES
%token GLOBALES

%token FUNCION
%token ARREGLO
%token ID
%token LA
%token POR
%token READ
%token REFERENCIA


%left O
%left Y
%left EQ NE
%nonassoc LT GT LE GE
%left PLUS MINUS
%left TIMES SLASH
%left NEG
     
%% /* The grammar follows.  */

inicio : varglobal


varglobal : funciones 
          | VARIABLES GLOBALES LBRACKET listaVariables RBRACKET funciones
          ;

listaVariables : decVariable
               | decVariable SEMICOLON listaVariables
               ;

decVariable   : SEA ID DE TIPO tipo
              | SEA ID DE TIPO tipo CON VALOR expr
              ;

tipo : BOOLEANO
     | ENTERO
     | FLOTANTE
     | CARACTER
     | STRING
     | VACIO
     | ARREGLO DE tipo DE expr A expr
     | LPAREN tipo RPAREN 
     ;

funciones : programa
          | FUNCIONES LBRACKET listaFunciones RBRACKET programa
          ;
    
listaFunciones : decFuncion
               | decFuncion listaFunciones
               ;

decFuncion : SEA LA FUNCION ID QUE RECIBE listArg Y RETORNA tipo HACER bloque 
           | SEA LA FUNCION ID QUE RETORNA tipo HACER bloque
           | SEA LA FUNCION ID QUE RECIBE listArg HACER bloque
           ;

listArg : tipo ID
        | tipo POR REFERENCIA ID
        | tipo POR REFERENCIA ID COMMA listArg
        | tipo ID COMMA listArg
        ;

programa  : GUACARA bloque
          ;

bloque : LBRACKET variables RBRACKET
       ;

variables : listaInstruccion
          | VARIABLES LBRACKET listaVariables RBRACKET listaInstruccion
          ;

listaInstruccion : instruccion
                 | instruccion SEMICOLON listaInstruccion 
                 ;

elseif      : else
            | O SI expr ENTONCES bloque
            | O SI expr ENTONCES bloque elseif
            ;

else        : SI NO ENTONCES bloque
            ;
asignacion  : ID BECOMES expr
            ;

instruccion : READ ID
            | IMPRIMIR ID
            | SI expr ENTONCES bloque
            | SI expr ENTONCES bloque elseif
            | asignacion 
            | MIENTRAS expr HACER bloque
            | PARA asignacion TAL QUE expr CON CAMBIO expr HACER bloque 
            ;


expr : LPAREN expr RPAREN { $$ = $2; } 
     | exprBooleana       { $$ = $1; }
     | exprAritmetica     { $$ = $1; }
     | terminal           { $$ = $1; }
     ;


exprBooleana : expr MAYOR QUE expr %prec LT         { $$ = $1 > $4; }
             | expr MENOR QUE expr %prec GT         { $$ = $1 < $4; }
             | expr MAYOR O IGUAL QUE expr %prec GE { $$ = ($1 >= $4); }
             | expr MENOR O IGUAL QUE expr %prec LE { $$ = ($1 <= $4); }
             | expr IGUAL A expr %prec EQ           { $$ = ($1 == $4); }
             | expr DISTINTO A expr %prec NE        { $$ = ($1 != $4); }
             | expr Y expr                          { $$ = ($1 && $3); }
             | expr O expr                          { $$ = ($1 || $3); }
             ;

exprAritmetica : expr PLUS expr  { $$ = $1 + $3; }
               | expr MINUS expr { $$ = $1 - $3; }
               | expr TIMES expr { $$ = $1 * $3; }
               | expr SLASH expr { $$ = $1 / $3; }
               ;


terminal : VERDADERO   { $$ = 1; }
         | FALSO       { $$ = 0; }
         | NUMENTERO   { $$ = $1; }
         | NUMFLOTANTE { $$ = $1; }
         | CARACTER    { $$ = $1; }
         | ID          { $$ = $1; }
         ;


/*
expr : LPAREN expr RPAREN
     | exprBooleana
     | exprAritmetica
     | terminal
     ;


exprBooleana : expr MAYOR QUE expr %prec LT
             | expr MENOR QUE expr %prec GT
             | expr MAYOR O IGUAL QUE expr %prec GE
             | expr MENOR O IGUAL QUE expr %prec LE
             | expr IGUAL A expr %prec EQ
             | expr DISTINTO A expr %prec NE
             | expr Y expr
             | expr O expr
             ;

exprAritmetica : expr PLUS expr
               | expr MINUS expr
               | expr TIMES expr
               | expr SLASH expr
               ;


terminal : VERDADERO
         | FALSO
         | NUMENTERO
         | NUMFLOTANTE
         | CARACTER
         | ID
         ;
*/

%%

void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

void main (int argc,char **argv)
{
  yyparse ();
}
