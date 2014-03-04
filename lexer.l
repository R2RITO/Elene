%{
#include <math.h>
#include <unistd.h>
#include "y.tab.h"
 // Arturo #10-10774 Guacara dice que no es necesario
    
    void count();
    int column = 0;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
yylloc.first_column = column; yylloc.last_column = column+yyleng-1;

%}

DIGIT [0-9]
ID    [A-Z][a-zA-Z0-9]*
CARACTER [a-zA-Z0-9]

%option yylineno

%x comment

%%


"/*"         BEGIN(comment);

<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             ;
<comment>"*"+"/"        BEGIN(INITIAL);


\"(\\.|[^\\"])*\"    { printf("%d %d %s\n", yylineno, column, yytext); count(); return STRING;  }




[ \t]                { count(); }// Ignorar Espacios, Tabuladores y Saltos de Linea
[\n]                 { count(); }


"'"+{CARACTER}+"'"   { count(); return CONSTCARACTER; }

"+"                  { count(); return PLUS;       }
"-"                  { count(); return MINUS;      }
"*"                  { count(); return TIMES;      }
"/"                  { count(); return SLASH;      }
"("                  { count(); return LPAREN;     }
")"                  { count(); return RPAREN;     }
";"                  { count(); return SEMICOLON;  }
","                  { count(); return COMMA;      }
"."                  { count(); return PERIOD;     }
"="                  { count(); return BECOMES;    }
"entonces"           { count(); return ENTONCES;   }
"{"                  { count(); return LBRACKET;   }
"}"                  { count(); return RBRACKET;   }
"["                  { count(); return LCORCHET;   }
"]"                  { count(); return RCORCHET;   }
"o"                  { count(); return O;          }
"no"                 { count(); return NO;         }
"si"                 { count(); return SI;         }
"mientras"           { count(); return MIENTRAS;   }
"hacer"              { count(); return HACER;      }
"para"               { count(); return PARA;       }
"tal"                { count(); return TAL;        }
"que"                { count(); return QUE;        }
"con"                { count(); return CON;        }
"cambio"             { count(); return CAMBIO;     }
"leer"               { count(); return LEER;       }
"imprimir"           { count(); return IMPRIMIR;   }
"la"                 { count(); return LA;         }
"funcion"            { count(); return FUNCION;    }
"recibe"             { count(); return RECIBE;     }
"y"                  { count(); return Y;          }
"retorna"            { count(); return RETORNA;    }
"sea"                { count(); return SEA;        }
"estructura"         { count(); return ESTRUCTURA; }
"contiene"           { count(); return CONTIENE;   }
"union"              { count(); return UNION;      }
"vacio"              { count(); return VACIO;      }
"guacara"            { count(); return GUACARA;    }
"entero"             { count(); return ENTERO;     }
"caracter"           { count(); return CARACTER;   }
"flotante"           { count(); return FLOTANTE;   }
"booleano"           { count(); return BOOLEANO;   }
"string"             { count(); return STRING;     }
"retornar"           { count(); return RETORNAR;   }
"valor"              { count(); return VALOR;      }
"verdadero"          { count(); return VERDADERO;  }
"falso"              { count(); return FALSO;      }
"es"                 { count(); return ES;         }
"a"                  { count(); return A;          }
"mayor"              { count(); return MAYOR;      }
"menor"              { count(); return MENOR;      }
"igual"              { count(); return IGUAL;      }
"distinto"           { count(); return DISTINTO;   }
"de"                 { count(); return DE;         }
"tipo"               { count(); return TIPO;       }
"funciones"          { count(); return FUNCIONES;  }
"variables"          { count(); return VARIABLES;  }
"globales"           { count(); return GLOBALES;   }
"arreglo"            { count(); return ARREGLO;    }
{ID}                 { count(); return ID;         }

{DIGIT}+              { count(); sscanf(yytext, "%d" , &yylval); return NUMENTERO  ; }
{DIGIT}+("."{DIGIT}+) { count(); sscanf(yytext, "%lf", &yylval); return NUMFLOTANTE; }

.           { printf("ERROR: %s\n", yytext); }

%%


void count()
{
    int i;

    for (i = 0; yytext[i] != '\0'; i++)
        if (yytext[i] == '\n')
            column = 1;
        else if (yytext[i] == '\t')
            column += 8 - (column % 8);
        else
            column++;
}

yywrap() { }
