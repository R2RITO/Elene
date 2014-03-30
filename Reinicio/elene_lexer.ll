%{
 
/* LENGUAJES DE PROGRAMACION II
 * 
 * Implementacion para el Lexer del lenguaje Elene
 * Autores:
 *     Arturo Voltattorni 10-10774
 *     Fernando Dagostino 10-10812
 *
 */

# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include <cfloat>
# include <stdlib.h>
# include "elene_driver.hh"
# include "elene_parser.tab.hh"

# undef yywrap
# define yywrap() 1

// Para detectar la posicion de cada token declarado.
static yy::location loc;
%}

%option noyywrap nounput batch debug noinput

DIGIT [0-9]
ID    [a-zA-Z][a-zA-Z0-9]*
CARACTER [a-zA-Z0-9]

%{
    // Codigo a ejecutar cada vez que un token hace match.
    #define YY_USER_ACTION  loc.columns (yyleng);
%}

%x comment

%%

%{
    // Code run each time yylex is called.
    loc.step ();
%}


[ \t]+               loc.step(); //Ignorar espacios, tabuladores y saltos de linea.
[\n]+                loc.lines (yyleng); loc.step ();

"/*"                    BEGIN(comment);  // Reglas para los comentarios
<comment>[^*\n]*                         // Ignorar todo lo que no sea *
<comment>"*"+[^*/\n]*                    // Saltos de linea
<comment>\n                              // Saltos de linea
<comment>"*"+"/"        BEGIN(INITIAL);  // Fin de comentario 


\"(\\.|[^\\"])*\"    { return (yy::elene_parser::make_STRING(yytext, loc));  }
"'"+{CARACTER}+"'"   { return (yy::elene_parser::make_CONSTCARACTER(yytext[0],loc)); }
"+"                  {  return (yy::elene_parser::make_PLUS(loc));       }
"-"                  {  return (yy::elene_parser::make_MINUS(loc));      }
"*"                  {  return (yy::elene_parser::make_TIMES(loc));      }
"/"                  {  return (yy::elene_parser::make_SLASH(loc));      }
"("                  {  return (yy::elene_parser::make_LPAREN(loc));     }
")"                  {  return (yy::elene_parser::make_RPAREN(loc));     }
";"                  {  return (yy::elene_parser::make_SEMICOLON(loc));  }
":"                  {  return (yy::elene_parser::make_COLON(loc));      }
","                  {  return (yy::elene_parser::make_COMMA(loc));      }
"."                  {  return (yy::elene_parser::make_PERIOD(loc));     }
"="                  {  return (yy::elene_parser::make_BECOMES(loc));    }
"entonces"           {  return (yy::elene_parser::make_ENTONCES(loc));   }
"{"                  {  return (yy::elene_parser::make_LBRACKET(loc));   }
"}"                  {  return (yy::elene_parser::make_RBRACKET(loc));   }
"["                  {  return (yy::elene_parser::make_LCORCHET(loc));   }
"]"                  {  return (yy::elene_parser::make_RCORCHET(loc));   }
"o"                  {  return (yy::elene_parser::make_O(loc));          }
"no"                 {  return (yy::elene_parser::make_NO(loc));         }
"si"                 {  return (yy::elene_parser::make_SI(loc));         }
"mientras"           {  return (yy::elene_parser::make_MIENTRAS(loc));   }
"hacer"              {  return (yy::elene_parser::make_HACER(loc));      }
"para"               {  return (yy::elene_parser::make_PARA(loc));       }
"tal"                {  return (yy::elene_parser::make_TAL(loc));        }
"que"                {  return (yy::elene_parser::make_QUE(loc));        }
"con"                {  return (yy::elene_parser::make_CON(loc));        }
"cambio"             {  return (yy::elene_parser::make_CAMBIO(loc));     }
"leer"               {  return (yy::elene_parser::make_LEER(loc));       }
"imprimir"           {  return (yy::elene_parser::make_IMPRIMIR(loc));   }
"la"                 {  return (yy::elene_parser::make_LA(loc));         }
"funcion"            {  return (yy::elene_parser::make_FUNCION(loc));    }
"recibe"             {  return (yy::elene_parser::make_RECIBE(loc));     }
"y"                  {  return (yy::elene_parser::make_Y(loc));          }
"retorna"            {  return (yy::elene_parser::make_RETORNA(loc));    }
"sea"                {  return (yy::elene_parser::make_SEA(loc));        }
"estructura"         {  return (yy::elene_parser::make_ESTRUCTURA(loc)); }
"contiene"           {  return (yy::elene_parser::make_CONTIENE(loc));   }
"union"              {  return (yy::elene_parser::make_UNION(loc));      }
"vacio"              {  return (yy::elene_parser::make_VACIO(loc));      }
"guacara"            {  return (yy::elene_parser::make_GUACARA(loc));    }
"entero"             {  return (yy::elene_parser::make_ENTERO(loc));     }
"caracter"           {  return (yy::elene_parser::make_CARACTER(loc));   }
"flotante"           {  return (yy::elene_parser::make_FLOTANTE(loc));   }
"booleano"           {  return (yy::elene_parser::make_BOOLEANO(loc));   }
"retornar"           {  return (yy::elene_parser::make_RETORNAR(loc));   }
"valor"              {  return (yy::elene_parser::make_VALOR(loc));      }
"es"                 {  return (yy::elene_parser::make_ES(loc));         }
"a"                  {  return (yy::elene_parser::make_A(loc));          }
"mayor"              {  return (yy::elene_parser::make_MAYOR(loc));      }
"menor"              {  return (yy::elene_parser::make_MENOR(loc));      }
"igual"              {  return (yy::elene_parser::make_IGUAL(loc));      }
"distinto"           {  return (yy::elene_parser::make_DISTINTO(loc));   }
"de"                 {  return (yy::elene_parser::make_DE(loc));         }
"tipo"               {  return (yy::elene_parser::make_TIPO(loc));       }
"funciones"          {  return (yy::elene_parser::make_FUNCIONES(loc));  }
"variables"          {  return (yy::elene_parser::make_VARIABLES(loc));  }
"globales"           {  return (yy::elene_parser::make_GLOBALES(loc));   }
"arreglo"            {  return (yy::elene_parser::make_ARREGLO(loc));    }
"verdadero"          {  return (yy::elene_parser::make_VERDADERO(1,loc));}
"falso"              {  return (yy::elene_parser::make_FALSO(0, loc));   }
"romper"             {  return (yy::elene_parser::make_ROMPER(loc));     }
"continuar"          {  return (yy::elene_parser::make_CONTINUAR(loc));  }
"iteracion"          {  return (yy::elene_parser::make_ITERACION(loc));  }
"por"                {  return (yy::elene_parser::make_POR(loc));        }
"referencia"         {  return (yy::elene_parser::make_REFERENCIA(loc)); }
"defecto"            {  return (yy::elene_parser::make_DEFECTO(loc));    }

{DIGIT}+             {   // Regla para los enteros
                         long num = strtol(yytext, NULL, 10);
                         if (!(INT_MIN <= num) && (num <= INT_MAX) && (errno != ERANGE)) {
                             std::cout << loc << "Error - Overflow para los enteros";
                             return (yy::elene_parser::make_NUMENTERO(0, loc));
                         }
                         return (yy::elene_parser::make_NUMENTERO(num, loc));
                     }


{ID}                 { return (yy::elene_parser::make_ID(yytext,loc)); }


{DIGIT}+("."{DIGIT}+) {   // Regla para los numeros reales

                          float num = atof(yytext);
                          if (!(FLT_MIN <= num) && (num <= FLT_MAX) && (errno != ERANGE)) {
                              std::cout << loc << "Error - Overflow para los reales";
                              return (yy::elene_parser::make_NUMFLOTANTE(0.0, loc));
                          }
                          return (yy::elene_parser::make_NUMFLOTANTE(num, loc));
                      }

.                     { std::cout << loc << " Error lexicografico - Caracter \""
                                  << yytext[0]<<"\" inesperado.\n";
                      } 

<<EOF>>               { return (yy::elene_parser::make_END(loc)); }

%%

// Funciones del driver implementadas aca por simplicidad
void elene_driver::scan_begin() {

    yy_flex_debug = trace_scanning;

    if (file.empty() || file == "-")
        yyin = stdin;
    else if (!(yyin = fopen (file.c_str (), "r"))) {
        error ("cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
}

void elene_driver::scan_end() {
    fclose (yyin);
}


