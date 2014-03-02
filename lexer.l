%{
#include <math.h>
#include <unistd.h>
#include "y.tab.h"
 // Arturo #10-10774 Guacara dice que no es necesario

%}

DIGIT [0-9]
ID    [A-Z][a-zA-Z0-9]*

%option lex-compat

%x comment
%%
        int line_num = 1;

"/*"         BEGIN(comment);

<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             ++line_num;
<comment>"*"+"/"        BEGIN(INITIAL);


\"(\\.|[^\\"])*\"    { printf("%d STRING\n", &yylineno);   }


[ \t\n] // Ignorar Espacios, Tabuladores y Saltos de Linea

"+"                  { return PLUS;       }
"-"                  { return MINUS;      }
"*"                  { return TIMES;      }
"/"                  { return SLASH;      }
"("                  { return LPAREN;     }
")"                  { return RPAREN;     }
";"                  { return SEMICOLON;  }
","                  { return COMMA;      }
"."                  { return PERIOD;     }
"="                  { return BECOMES;    }
"entonces"           { return ENTONCES;   }
"{"                  { return LBRACKET;   }
"}"                  { return RBRACKET;   }
"["                  { return LCORCHET;   }
"]"                  { return RCORCHET;   }
"o"                  { return O;          }
"no"                 { return NO;         }
"si"                 { return SI;         }
"mientras"           { return MIENTRAS;   }
"hacer"              { return HACER;      }
"para"               { return PARA;       }
"tal"                { return TAL;        }
"que"                { return QUE;        }
"con"                { return CON;        }
"cambio"             { return CAMBIO;     }
"leer"               { return LEER;       }
"imprimir"           { return IMPRIMIR;   }
"la"                 { return LA;         }
"funcion"            { return FUNCION;    }
"recibe"             { return RECIBE;     }
"y"                  { return Y;          }
"retorna"            { return RETORNA;    }
"sea"                { return SEA;        }
"estructura"         { return ESTRUCTURA; }
"contiene"           { return CONTIENE;   }
"union"              { return UNION;      }
"vacio"              { return VACIO;      }
"guacara"            { return GUACARA;    }
"entero"             { return ENTERO;     }
"caracter"           { return CARACTER;   }
"flotante"           { return FLOTANTE;   }
"booleano"           { return BOOLEANO;   }
"string"             { return STRING;     }
"retornar"           { return RETORNAR;   }
"valor"              { return VALOR;      }
"verdadero"          { return VERDADERO;  }
"falso"              { return FALSO;      }
"es"                 { return ES;         }
"a"                  { return A;          }
"mayor"              { return MAYOR;      }
"menor"              { return MENOR;      }
"igual"              { return IGUAL;      }
"distinto"           { return DISTINTO;   }
"de"                 { return DE;         }
"tipo"               { return TIPO;       }
"funciones"          { return FUNCIONES;  }
"variables"          { return VARIABLES;  }
"globales"           { return GLOBALES;   }
"arreglo"            { return ARREGLO;    }

{ID}                 { return ID;         }

{DIGIT}+              { sscanf(yytext, "%d" , &yylval); return NUMENTERO  ; }
{DIGIT}+("."{DIGIT}+) { sscanf(yytext, "%lf", &yylval); return NUMFLOTANTE; }

%%

yywrap() { }
