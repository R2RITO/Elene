%skeleton "lalr1.cc"
%require "3.0.2"

%{
//#include <ARBOLSINTACTICO.hh> 
%}

%defines
%define parser_class_name {LN_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires 
{ 
#include <string>
}

%locations /* Activamos el seguimiento de posiciones */

/* Aqui falta un pedazo de codigo para el initial action
   Es decir, Setear el comienzo en el archivo */

/* Para expresar mejor los errores de sintaxis */
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOK_}
%token
    ENDFILE 0 "Fin de archivo"
    SEMICOLON ";"
    /* Todos los tokens que no tengan tipo ... PARA...SI...*/
;

%token <std::string> STRING "Cadena de caracteres"
%token <std::string> ID "Identificador"
%token <int> NUMENTERO "Numero entero"
%token <float> NUMFLOTANTE "Numero flotante"
%token <char>  CONSTCARACTER "Caracter"
%token <int> VERDADERO "Verdadero"
%token <int> FALSO "Falso"

%start inicio

%%

inicio : terminal { };

terminal : VERDADERO        {  }
         | FALSO            {  }
         | NUMENTERO        {  }
         | NUMFLOTANTE      {  }
         | CONSTCARACTER    {  }
         | ID               {  }
         | STRING           {  };


%%
