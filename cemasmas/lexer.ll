%{
/* Librerias */
#include <string>  /* Librerias para el manejo de Strings */
#include <climits> /* Librerias para detecter overflows */
#include <cstdlib>
#include "y.tab.h"

/* Definiciones */
#undef yywrap      /* Desactivamos interaccion por consola */
#define yywrap() 1 /* Decimos a flex que yywrap esta definido */

static yy::location posicion; /* Posicion del token actual */

/* Accion ejecutada cada vez que se obtiene un Token */
/* Se escribe el numero de columna del token */
#define YY_USER_ACTION posicion.columns (yyleng);

%}

%option noyywrap
%option noinput
%option nounput
%option batch
%option debug

%x comment

DIGIT [0-9]
ID    [A-Z][a-zA-Z0-9]*
CARACTER [a-zA-Z0-9]

%%

%{
    /* Codigo ejecutado cada vez que yylex es llamado */
    /* Tiene que ver con lo que se hace cada vez que se toma un token */
    /* Lineas y columnas y eso... */
    posicion.step();
%}

[ \t]+               { posicion.step(); } //Ignorar espacios, tabuladores y saltos de linea.
[\n]+                { posicion.lines (yyleng); posicion.step (); }   

"/*"                    BEGIN(comment);  // Reglas para los comentarios
<comment>[^*\n]*                         // Ignorar todo lo que no sea *
<comment>"*"+[^*/\n]*                    // Saltos de linea
<comment>\n                              // Saltos de linea
<comment>"*"+"/"        BEGIN(INITIAL);  // Fin de comentario


\"(\\.|[^\\"])*\"    { return (yy::LN_parser::make_STRING("HOLA", posicion));  }
"'"+{CARACTER}+"'"   { return (yy::LN_parser::make_CONSTCARACTER('H',posicion)); }







{ID}                  { return (yy::LN_parser::make_ID("Hola", posicion)); }

"verdadero"           { return (yy::LN_parser::make_VERDADERO(1,posicion));  }

"falso"               { return (yy::LN_parser::make_FALSO(1, posicion));      }

{DIGIT}+              {   // Regla para los enteros
                          long num = strtol(yytext, NULL, 10); 
                          if (!(INT_MIN <= num) && (num <= INT_MAX) && (errno != ERANGE)) {
                              //AQUI HAY QUE DAR ERROR
                          }
                          return (yy::LN_parser::make_NUMENTERO(1, posicion));
                      }

{DIGIT}+("."{DIGIT}+) {   // Regla para los numeros reales
                          //Falta esto. Como pasar de yytext a real y chequear overflow
                          return (yy::LN_parser::make_NUMFLOTANTE(0.0, posicion));
                      }

.                     { /* Driver de error FALTA*/ } 

<<EOF>>               { return (yy::LN_parser::make_ENDFILE(posicion)); }


%%
//Aqui no va nada mas
