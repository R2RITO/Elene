/* LENGUAJES DE PROGRAMACION II
 * 
 * Implementacion del parser de Elene
 * Autores:
 *      Arturo Voltattorni 10-10774
 *      Fernando Dagostino 10-10812
 */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {elene_parser}
%define api.token.constructor
%define api.value.type variant
/*%define parse.assert*/


%code requires {
    #include <string>
    #include <iostream>
    #include <ostream>
    #include "arbol2.hh"
    #include <cmath>
    class elene_driver;
}




// The parsing context.
%param { elene_driver& driver }

%locations
%initial-action {
    // Initialize the initial location.
    @$.begin.filename = @$.end.filename = &driver.file;
};

%define parse.trace
%define parse.error verbose

%code
{
    #include "elene_driver.hh"
    #include "tabla.hh"
    elene_TABLA* currentLevel;
    elene_TABLA* tablaGlobal;
    double col;
    double linea;
    elene_LISTFUN* lstf;
}

%define api.token.prefix {TOK_}



%token END  0  "end of file"
%token <std::string> STRING "Cadena de caracteres"
%token <std::string> ID "Identificador"
%token <int> NUMENTERO "Numero entero"
%token <float> NUMFLOTANTE "Numero flotante"
%token <char>  CONSTCARACTER "Caracter"
%token <int> VERDADERO "Verdadero"
%token <int> FALSO "Falso"

/* Bison declarations.  */
%token PLUS
%token MINUS
%token TIMES
%token SLASH
%token LPAREN
%token RPAREN
%token SEMICOLON
%token COLON
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
%token RETORNAR
%token VALOR
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
%token FUNCION
%token ARREGLO
%token LA
%token POR
%token REFERENCIA
%token ROMPER
%token CONTINUAR
%token ITERACION
%token DEFECTO

%type <elene_TIPO*> tipo
%type <elene_BLOQUE*> bloque
%type <elene_LISTAVAR*> listaVariables
%type <elene_DECLARACION*> decVariable
%type <elene_LISTAINST*> listaInstruccion
%type <elene_INST*> instruccion
%type <elene_INSTASIG*> asignacion
%type <elene_INSTCOND*> elseif
%type <elene_INSTCOND*> else
%type <elene_EXPR*> expr
%type <elene_EXPRBINARIA*> exprBinaria
%type <elene_EXPRUNARIA*>  exprUnaria 
%type <elene_EXPRTERMINAL*> terminal
%type <elene_LISTARG*> listArg
%type <elene_LISTFUN*> listaFunciones
%type <elene_DECFUNCION*> decFuncion
%type <elene_VARGLOBAL*> varglobal
%type <elene_FUNCIONES*> funciones
%type <elene_BLOQUE*> programa
%type <elene_LISTAEXPR*> listaExpr
%type <elene_LISTAVAR*> bloqueContenido
%type <elene_DECLARACION*> decContenido
%type <elene_INSTCASE*> instruccionCase
%type <elene_LISTACASE*> casosCase
%type <elene_CASO*> caso


%left O
%left Y
%left IGUAL DISTINTO A
%nonassoc MAYOR MENOR QUE
%left PLUS MINUS
%left TIMES SLASH
%left NEG NEGBOOL
%left PERIOD
%printer { yyoutput << $$; } <*>;

%%

%start inicio;


inicio : { currentLevel = new elene_TABLA(); 
           currentLevel -> insertar("Read",new elene_TIPO_SIMPLE("Funcion"),1,1,4);
           currentLevel = enterScope(currentLevel);
           tablaGlobal = currentLevel;
         } 
         varglobal 
         { 
           std::cout << "\n\nImprimiendo tabla\n\n"; 
           std::cout << *currentLevel; 
         }

varglobal : funciones { $$ = new elene_VARGLOBAL($1,0); }
          | VARIABLES GLOBALES LBRACKET listaVariables RBRACKET funciones 
            { $$ = new elene_VARGLOBAL($6,$4); }
          ;

listaVariables : decVariable { $$ = new elene_LISTAVAR($1,0); }
               | listaVariables SEMICOLON decVariable { $$ = new elene_LISTAVAR($3, $1); }
               | listaVariables SEMICOLON error { yyerrok; }
               | error SEMICOLON decVariable    { yyerrok; }
               | error decVariable              { yyerrok; }
               ;

decVariable   : SEA ID DE TIPO tipo 
                { $$ = new elene_DECLARACION(new elene_ID($2),$5,0); 
                  if (!(*currentLevel).local_lookup($2)) { 
                      currentLevel -> insertar($2,$5,@2.begin.line,@2.begin.column,0);
                  } else { 
                      std::cout << "Error variable: " 
                                << $2 << " ya esta declarada en Linea: "
                                << @2.begin.line << " Columna: " 
                                << @2.begin.column << "\n"; 
                  }; 
                } 
              | SEA ID DE TIPO tipo CON VALOR expr 
                { $$ = new elene_DECLARACION(new elene_ID($2), $5, $8); 
                  if (!(*currentLevel).local_lookup($2)) { 
                      currentLevel -> insertar($2,$5,@2.begin.line,@2.begin.column,0); 
                  } else { 
                      std::cout << "Error variable: " << $2 
                                << " ya esta declarada en Linea: "
                                << @2.begin.line << " Columna: " 
                                << @2.begin.column << "\n";
                  }; 
                }
              ;

bloqueContenido : decContenido { $$ = new elene_LISTAVAR($1, 0); }
                | bloqueContenido SEMICOLON decContenido { $$ = new elene_LISTAVAR($3,$1); }
                ;

decContenido    : ID DE TIPO tipo 
                  { $$ = new elene_DECLARACION(new elene_ID($1),$4,0);
                    if (!(*currentLevel).local_lookup($1)) {
                        currentLevel -> insertar($1,$4,@1.begin.line,@1.begin.column,0);
                    } else {
                        std::cout << "Error variable: " << $1
                                  << " ya esta declarada en Linea: "
                                  << @1.begin.line << " Columna: "
                                  << @1.begin.column << "\n";
                    }; 
                  }
                ;

tipo : BOOLEANO { $$ = new elene_TIPO_SIMPLE("Booleano"); }
     | ENTERO   { $$ = new elene_TIPO_SIMPLE("Entero"); }
     | FLOTANTE { $$ = new elene_TIPO_SIMPLE("Flotante"); }
     | CARACTER { $$ = new elene_TIPO_SIMPLE("Caracter"); }
     | STRING   { $$ = new elene_TIPO_SIMPLE("String");}
     | VACIO    { $$ = new elene_TIPO_SIMPLE("Vacio");}
     | ID       
       { if (!(*currentLevel).local_lookup($1)) {
            std::cout << "Error - Declaracion con tipo '" << $1
                      <<"' no definido en Linea: "
                      << @1.begin.line << " Columna: " << @1.begin.column << "\n";
            $$ = new elene_TIPO_SIMPLE("Indefinido");
         } else {
            $$ = new elene_TIPO_DEFINIDO(new elene_ID($1)); 
         }
       }
     | ARREGLO DE tipo DE expr A expr { $$ = new elene_TIPO_ARREGLO($3,$5,$7); }
     | UNION QUE CONTIENE LBRACKET 
       { currentLevel = enterScope(currentLevel); }
       bloqueContenido 
       { currentLevel = exitScope(currentLevel); }
       RBRACKET 
       { $$ = new elene_TIPO_UNION($6); }

     | ESTRUCTURA QUE CONTIENE LBRACKET 
       { currentLevel = enterScope(currentLevel); }
       bloqueContenido 
       { currentLevel = exitScope(currentLevel); }
       RBRACKET { $$ = new elene_TIPO_ESTRUCTURA($6); }
     | LPAREN tipo RPAREN { $$ = $2; }
     ;

funciones : programa { $$ = new elene_FUNCIONES(0,$1); }
          | FUNCIONES LBRACKET listaFunciones RBRACKET programa { $$ = new elene_FUNCIONES($3,$5); }
          | error END { yyerrok; }
          | FUNCIONES LBRACKET listaFunciones RBRACKET error END { yyerrok; }
          ;
    
listaFunciones : decFuncion { $$ = new elene_LISTFUN($1,0); }
               | listaFunciones decFuncion { $$ = new elene_LISTFUN($2,$1); }
               | listaFunciones error      { $$ = new elene_LISTFUN(0,$1); yyerrok; yyclearin; }
               ;

decFuncion : SEA LA FUNCION ID QUE RECIBE  
             { if (!(*currentLevel).local_lookup($4)) { 
                   currentLevel -> 
                   insertar($4,new elene_TIPO_SIMPLE("Funcion"),@4.begin.line,@4.begin.column,0); 
               } else { 
                   std::cout << "Error, funcion : " << $4 
                             << " ya esta declarada en Linea: "<< @4.begin.line 
                             << " Columna: " << @4.begin.column << "\n"; 
               }; 
               currentLevel = enterScope(currentLevel); 
            } 
            listArg Y RETORNA tipo HACER bloque 
            { 
                $$ = new elene_DECFUNCION(new elene_ID($4),$8,$11,$13); 
                currentLevel = exitScope(currentLevel);     
            }
           | SEA LA FUNCION ID QUE RETORNA
             { if (!(*currentLevel).local_lookup($4)) { 
                   currentLevel -> 
                   insertar($4,new elene_TIPO_SIMPLE("Funcion"),@4.begin.line,@4.begin.column,0); 
               } else { 
                   std::cout << "Error, funcion: " << $4 
                             << " ya esta declarada en Linea: "<< @4.begin.line 
                             << " Columna: " << @4.begin.column << "\n"; 
               }; 
             }
             tipo HACER bloque
             { $$ = new elene_DECFUNCION(new elene_ID($4),0,$8,$10); }
           ;

listArg : tipo ID  
            { 
                $$ = new elene_LISTARG($1, new elene_ID($2), "Por Valor", 0); 
                if (!(*currentLevel).local_lookup($2)) { 
                    currentLevel -> insertar($2,$1,@2.begin.line,@2.begin.column,0);
                } else { 
                    std::cout 
                    << "Error, parametro: " << $2 
                    << " ya esta declarado en Linea: "<< @2.begin.line 
                    << " Columna: " << @2.begin.column << "\n"; 
                }; 
            }
        | tipo POR REFERENCIA ID 
            { 
                $$ = new elene_LISTARG($1, new elene_ID($4), "Por Referencia", 0); 
                if (!(*currentLevel).local_lookup($4)) { 
                   currentLevel -> 
                   insertar($4,$1,@4.begin.line,@4.begin.column,0); 
                } else { 
                   std::cout 
                   << "Error, parametro: " << $4 
                   << " ya esta declarado en Linea: "
                   << @4.begin.line << " Columna: " 
                   << @4.begin.column << "\n"; 
                }; 
            }
        | listArg COMMA tipo POR REFERENCIA ID
          { 
              $$ = new elene_LISTARG($3, new elene_ID($6), "Por Referencia", $1); 
              if (!(*currentLevel).local_lookup($6)) { 
                  currentLevel 
                  -> insertar($6,$3,@6.begin.line,@6.begin.column,0); 
              } else { 
                  std::cout << "Error, parametro: " << $6 
                  << " ya esta declarado en Linea: "<< @6.begin.line 
                  << " Columna: " << @6.begin.column << "\n"; 
              }; 
          }
        | listArg COMMA tipo ID
          { 
              $$ = new elene_LISTARG($3, new elene_ID($4), "Por Valor", $1); 
              if (!(*currentLevel).local_lookup($4)) { 
                  currentLevel -> 
                  insertar($4,$3,@4.begin.line,@4.begin.column,0); 
              } else { 
                  std::cout << "Error, parametro: " << $4 
                  << " ya esta declarado en Linea: "<< @4.begin.line 
                  << " Columna: " << @4.begin.column << "\n"; 
              }; 
          }
        | listArg COMMA error { yyerrok; yyclearin; }
        | error COMMA tipo POR REFERENCIA ID { yyerrok; yyclearin; }
        | error COMMA tipo ID { yyerrok; yyclearin; }
        ;


programa  : GUACARA bloque { $$ = $2; currentLevel = exitScope(currentLevel); }
          ;

bloque : LBRACKET listaInstruccion RBRACKET { $$ = new elene_BLOQUE(0,0,$2); }
       | LBRACKET VARIABLES LBRACKET 
         { currentLevel = enterScope(currentLevel); } 
         listaVariables RBRACKET listaInstruccion RBRACKET 
         { $$ = new elene_BLOQUE(0,$5,$7); 
           currentLevel = exitScope(currentLevel); }
       | ID COLON LBRACKET listaInstruccion RBRACKET 
         { $$ = new elene_BLOQUE(new elene_ID($1),0,$4); 
           if (!(*tablaGlobal).local_lookup($1)) {
               tablaGlobal ->
               insertar($1,new elene_TIPO_SIMPLE("Etiqueta"),@1.begin.line,@1.begin.column,0);
           } else {
               std::cout << "Error, etiqueta: " << $1
               << " ya esta declarada en Linea: "<< @1.begin.line
               << " Columna: " << @1.begin.column << "\n";
           }
         }
       | ID COLON LBRACKET VARIABLES LBRACKET
         { 
             if (!(*tablaGlobal).local_lookup($1)) {
                 tablaGlobal ->
                 insertar($1,new elene_TIPO_SIMPLE("Etiqueta"),@1.begin.line,@1.begin.column,0);
             } else {
                 std::cout << "Error, etiqueta: " << $1
                 << " ya esta declarada en Linea: "<< @1.begin.line
                 << " Columna: " << @1.begin.column << "\n";
            }

            currentLevel = enterScope(currentLevel);
         }

         listaVariables RBRACKET listaInstruccion RBRACKET
         
         { $$ = new elene_BLOQUE(new elene_ID($1),$7,$9);  
           currentLevel = exitScope(currentLevel); }
       | error COLON LBRACKET VARIABLES LBRACKET listaVariables RBRACKET 
         listaInstruccion RBRACKET { yyerrok; }
       | error COLON LBRACKET listaInstruccion RBRACKET { yyerrok; }
       ;

listaInstruccion : instruccion { $$ = new elene_LISTAUNIT($1); }
                 | listaInstruccion SEMICOLON instruccion 
                   { $$ = new elene_LISTAMULT($3,$1); }
                 | listaInstruccion SEMICOLON error { yyerrok; }
                 | error instruccion { yyerrok; }
                 ;

elseif      : else { $$ = $1; }
            | O SI expr ENTONCES bloque { $$ = new elene_INSTCOND($3,$5,0); }
            | O SI expr ENTONCES bloque elseif { $$ = new elene_INSTCOND($3,$5,$6); }
            ;

else        : SI NO ENTONCES bloque { $$ = new elene_INSTCOND(new elene_BOOLEANO(1),$4,0); }
            ;

asignacion  : ID BECOMES expr { $$ = new elene_INSTASIG(new elene_ID($1), $3); 
                                if (!(*currentLevel).lookup($1)) { 
                                    std::cout 
                                    << "Error no encuentro " << $1 
                                    << " utilizada en la linea: " 
                                    << @1.begin.line << " y columna: " 
                                    << @1.begin.column << "\n"; 
                                };  
                              }
            ;

instruccion : LEER ID { $$ = new elene_INSTLEER(new elene_ID($2)); 
                        if (!(*currentLevel).lookup($2)) { 
                            std::cout 
                            << "Error no encuentro " << $2 
                            << " utilizada en la linea: " << @2.begin.line 
                            << " y columna: " << @2.begin.column << "\n"; 
                        };  
                      } 
            | IMPRIMIR expr { $$ = new elene_INSTESCR($2); }
            | RETORNAR expr { $$ = new elene_INSTRETORNAR($2); }
            | SI expr ENTONCES bloque { $$ = new elene_INSTCOND($2, $4, 0);  }
            | SI expr ENTONCES bloque elseif { $$ = new elene_INSTCOND($2,$4,$5); }
            | asignacion { $$ = $1; }
            | MIENTRAS expr HACER bloque { $$ = new elene_INSTMIENTRAS($2,$4); }
            | PARA asignacion TAL QUE expr CON CAMBIO asignacion HACER bloque 
              { $$ = new elene_INSTPARA($2,$5,$8,$10); } 
            | expr { $$ = new elene_INSTEXPR($1); }
            | ROMPER ITERACION { $$ = new elene_INSTROMPER(); }
            | CONTINUAR ITERACION { $$ = new elene_INSTCONTINUAR(); }
            | instruccionCase { $$ = new elene_INSTROMPER(); }
            ;

instruccionCase : SEA ID IGUAL A LBRACKET casosCase POR DEFECTO HACER bloque RBRACKET
                  { $$ = new elene_INSTCASE(new elene_ID($2),$6,$10); }
                | SEA error IGUAL A LBRACKET casosCase POR DEFECTO HACER bloque RBRACKET
                  { yyerrok; }
                | SEA ID IGUAL A LBRACKET error POR DEFECTO HACER bloque RBRACKET
                  { yyerrok; }
                | SEA error IGUAL A LBRACKET error POR DEFECTO HACER bloque RBRACKET
                  { yyerrok; }
                ;

casosCase : caso {  $$ = new elene_LISTACASE($1,0); }
          | casosCase caso { $$ = new elene_LISTACASE($2,0); }
          ;

caso : expr ENTONCES HACER bloque { $$ = new elene_CASO($1,$4); }

listaExpr: listaExpr COMMA expr { $$ = new elene_LISTAEXPR($3,$1);}
         | expr { $$ = new elene_LISTAEXPR($1, 0); }
         | { $$ = new elene_LISTAEXPR(0,0); }
         | listaExpr COMMA error { yyerrok; yyclearin; }
         | error expr            { yyerrok; yyclearin; }
         ;         


expr : LPAREN expr RPAREN  { $$ = $2; }
     | ID LCORCHET expr RCORCHET { $$ = new elene_ACCARREG(new elene_ID($1),$3); }
     | exprBinaria         { $$ = $1; }
     | exprUnaria          { $$ = $1; }
     | terminal            { $$ = $1; }
     ;

exprBinaria : expr Y expr { $$ = new elene_CONJUNCION($1,$3); }
            | expr O expr { $$ = new elene_DISYUNCION($1,$3); }
            | expr PLUS expr { $$ = new elene_ADICION($1,$3); }
            | expr MINUS expr { $$ = new elene_SUSTRACCION($1,$3); }
            | expr TIMES expr { $$ = new elene_MULTIPLICACION($1,$3); }
            | expr SLASH expr { $$ = new elene_DIVISION($1,$3); }
            | expr MAYOR QUE expr { $$ = new elene_MAYOR($1,$4); } 
            | expr MENOR QUE expr { $$ = new elene_MENOR($1,$4); }
            | expr MAYOR O IGUAL QUE expr { $$ = new elene_MAYORIGUAL($1,$6); }
            | expr MENOR O IGUAL QUE expr { $$ = new elene_MENORIGUAL($1,$6); }
            | expr DISTINTO A expr        { $$ = new elene_DISTINTO($1,$4); }
            | expr IGUAL A expr           { $$ = new elene_IGUAL($1,$4); }
            | expr PERIOD expr            { $$ = new elene_ACCESO($1,$3); }
            ;

exprUnaria : MINUS expr %prec NEG  { $$ = new elene_MENOSUNARIO($2); }
           | NO expr %prec NEGBOOL { $$ = new elene_NEGACION($2);  }
           ;

terminal : VERDADERO        { $$ = new elene_BOOLEANO($1);  }     
         | FALSO            { $$ = new elene_BOOLEANO($1); }
         | NUMENTERO        { $$ = new elene_ENTERO($1); }
         | NUMFLOTANTE      { $$ = new elene_REAL($1); }
         | CONSTCARACTER    { $$ = new elene_CARACTER($1); }
         | ID               { $$ = new elene_ID($1); 
                              if (!(*currentLevel).lookup($1)) { 
                                  std::cout 
                                  << "Error no encuentro " << $1 
                                  << " utilizada en la linea: " << @1.begin.line 
                                  << " y columna: " << @1.begin.column << "\n"; 
                              };   
                            }
         | ID LPAREN listaExpr RPAREN 
           { $$ = new elene_EXPRFUNC(new elene_ID($1),$3); 
             if (!(*currentLevel).lookup($1)) { 
                 std::cout 
                 << "Error no encuentro " 
                 << $1 << " utilizada en la linea: " 
                 << @1.begin.line << " y columna: " 
                 << @1.begin.column << "\n";
             }; 
           }
         | STRING           { $$ = new elene_STRING($1); }
         ;

%%

void yy::elene_parser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
