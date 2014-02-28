%{
#include <math.h>
#include <unistd.h>
 // #include "y.tab.h"
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

"+"                  { printf("PLUS");       }
"-"                  { printf("MINUS");      }
"*"                  { printf("TIMES");      }
"/"                  { printf("SLASH");      }
"("                  { printf("LPAREN");     }
")"                  { printf("RPAREN");     }
";"                  { printf("SEMICOLON");  }
","                  { printf("COMMA");      }
"."                  { printf("PERIOD");     }
"="                  { printf("BECOMES");    }
"{"                  { printf("LBRACKET");   }
"}"                  { printf("RBRACKET");   }
"["                  { printf("LCORCHET");   }
"]"                  { printf("RCORCHET");   }
"entonces"           { printf("ENTONCES");   }
"o"                  { printf("O");          }
"no"                 { printf("NO");         }
"si"                 { printf("SI");         }
"mientras"           { printf("MIENTRAS");   }
"hacer"              { printf("HACER");      }
"para"               { printf("PARA");       }
"tal"                { printf("TAL");        }
"que"                { printf("QUE");        }
"con"                { printf("CON");        }
"cambio"             { printf("CAMBIO");     }
"leer"               { printf("LEER");       }
"imprimir"           { printf("IMPRIMIR");   }
"la"                 { printf("LA");         }
"funcion"            { printf("FUNCION");    }
"recibe"             { printf("RECIBE");     }
"y"                  { printf("Y");          }
"retorna"            { printf("RETORNA");    }
"sea"                { printf("SEA");        }
"estructura"         { printf("ESTRUCTURA"); }
"contiene"           { printf("CONTIENE");   }
"union"              { printf("UNION");      }
"vacio"              { printf("VACIO");      }
"guacara"            { printf("GUACARA");    }
"entero"             { printf("ENTERO");     }
"caracter"           { printf("CARACTER");   }
"flotante"           { printf("FLOTANTE");   }
"booleano"           { printf("BOOLEANO");   }
"string"             { printf("STRING");     }
"retornar"           { printf("RETORNAR");   }
"valor"              { printf("VALOR");      }
"verdadero"          { printf("VERDADERO");  }
"falso"              { printf("FALSO");      }
"es"                 { printf("ES");         }
"a"                  { printf("A");          }
"mayor"              { printf("MAYOR");      }
"menor"              { printf("MENOR");      }
"igual"              { printf("IGUAL");      }
"distinto"           { printf("DISTINTO");   }
"de"                 { printf("DE");         }
"tipo"               { printf("TIPO");       }
"funciones"          { printf("FUNCIONES");  }
"variables"          { printf("VARIABLES");  }
"globales"           { printf("GLOBALES");   }
"arreglo"            { printf("ARREGLO");    }

ID                   { printf("ID");         }

{DIGIT}+              { printf("NUMENTERO")  ; }
{DIGIT}+("."{DIGIT}+) { printf("NUMFLOTANTE"); }

%%


main() {
    yylex();
}
