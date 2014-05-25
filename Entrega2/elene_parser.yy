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
	#include <sstream>
    #include <string>
    #include <iostream>
    #include <ostream>
    #include <cmath>
    #include "verificacion_tipos.hh"
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
    elene_TIPO* tiposBase [7];
    elene_TIPO_ESTRUCTURA* test;
    elene_TIPO_FUNCION* testFuncion;
    elene_TIPO_ARREGLO* testArreglo;
    elene_TABLA_VALOR* tablaVal;
	elene_TIPO* tipoAux;
    int despGlobal;
    int despStruct;
    int despUnion;
    int despBloque;
    int despl;
    int align;
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


inicio : { 

           tiposBase[0] = new elene_TIPO_BOOLEANO;
           tiposBase[1] = new elene_TIPO_FLOTANTE;
           tiposBase[2] = new elene_TIPO_CARACTER;
           tiposBase[3] = new elene_TIPO_STRING;
           tiposBase[4] = new elene_TIPO_ENTERO;
           tiposBase[5] = new elene_TIPO_VACIO;
           tiposBase[6] = new elene_TIPO_TYPE_ERROR;

           currentLevel = new elene_TABLA(); 
           currentLevel -> insertar("Read",tiposBase[2],1,1,4);
           currentLevel = enterScope(currentLevel);
           tablaGlobal = currentLevel;
         } 
         varglobal 
         { 
           std::cout << "\n\nImprimiendo tabla\n\n"; 
           std::cout << *currentLevel; 
		   //std::cout << *$2;
         }

varglobal : funciones { $$ = new elene_VARGLOBAL($1,0); }
          | VARIABLES GLOBALES LBRACKET 
            { despGlobal = 0;
              despBloque = 0;
              despl = 0;
            }
            listaVariables
            { despGlobal = despBloque;
              despBloque = 0;
            } 
            RBRACKET funciones 
            { $$ = new elene_VARGLOBAL($8,$5); }
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
                      currentLevel -> insertar($2,$5,@2.begin.line,@2.begin.column,despBloque);
                      align = alinear((*$5).tam);
                      despBloque = despBloque + align;
                  } else { 
                      driver.error_redec(@2, $2);
                  }; 
                } 
              | SEA ID DE TIPO tipo CON VALOR expr 
                { $$ = new elene_DECLARACION(new elene_ID($2), $5, $8); 
                  if (!(*currentLevel).local_lookup($2)) { 
                      currentLevel -> insertar($2,$5,@2.begin.line,@2.begin.column,despBloque);
                      align = alinear((*$5).tam);
                      despBloque = despBloque + align;
                  } else { 
                      driver.error_redec(@2, $2);
                  }; 
                }
              ;

bloqueContenido : 
                decContenido { $$ = new elene_LISTAVAR($1, 0); }
                | bloqueContenido SEMICOLON decContenido { $$ = new elene_LISTAVAR($3,$1); }
                ;

decContenido    : ID DE TIPO tipo 
                  { $$ = new elene_DECLARACION(new elene_ID($1),$4,0);
                    if (!(*currentLevel).local_lookup($1)) {
                        currentLevel -> insertar($1,$4,@1.begin.line,@1.begin.column,despl);
                        align = alinear((*$4).tam);
                        despl = despl + align;
                        despStruct = despStruct + align;
                        despUnion = std::max(despUnion,align);
                    } else {
                        driver.error_redec(@1, $1);
                    }; 
                  }
                ;

tipo : BOOLEANO { $$ = tiposBase[0]; }
     | ENTERO   { $$ = tiposBase[4]; }
     | FLOTANTE { $$ = tiposBase[1]; }
     | CARACTER { $$ = tiposBase[2]; }
     | STRING   { $$ = tiposBase[3]; }
     | VACIO    { $$ = tiposBase[5]; }
     | ID       
       { if (!(*currentLevel).lookup($1)) {
            driver.error_tipo_indef(@1,$1);
            $$ = tiposBase[6];
         } else {
            if ( test = dynamic_cast<elene_TIPO_ESTRUCTURA *>((*(*currentLevel).lookup($1)).tipo)) {
                $$ = (*(*currentLevel).lookup($1)).tipo;
                test = 0;
            } else {
                driver.error_tipo_no_estructura(@1,$1);
                $$ = tiposBase[6];
            } 
         }
       }
     | ARREGLO DE tipo DE NUMENTERO A NUMENTERO 
       {
           $$ = new elene_TIPO_ARREGLO($3,$5,$7); 
           align = alinear((*$3).tam);
           if (($7 - $5) < 0) {
               driver.error_indices_incorrectos(@5,$5);
               (*$$).tam = align * ($5 - $7);  
           } else { 
               (*$$).tam = align * ($7 - $5);            
           }           
       }
     | UNION QUE CONTIENE LBRACKET 
       { currentLevel = enterScope(currentLevel);
         despUnion = 0;
         despStruct = 0;
         despl = 0;
       }
       bloqueContenido 
       { currentLevel = exitScope(currentLevel); }
       RBRACKET 
       { $$ = new elene_TIPO_UNION($6);
         (*$$).tam = despUnion;
       }

     | ESTRUCTURA QUE CONTIENE LBRACKET 
       { currentLevel = enterScope(currentLevel);
         despStruct = 0;
         despUnion = 0;
         despl = 0;
       }
       bloqueContenido 
       { currentLevel = exitScope(currentLevel); }
       RBRACKET 
       { $$ = new elene_TIPO_ESTRUCTURA($6);
         (*$$).tam = despStruct;
       }
     | LPAREN tipo RPAREN { $$ = $2; }
     ;

funciones : programa { $$ = new elene_FUNCIONES(0,$1); }
          | FUNCIONES LBRACKET listaFunciones RBRACKET programa { $$ = new elene_FUNCIONES($3,$5); }
          | error END { yyerrok; }
          | FUNCIONES LBRACKET listaFunciones RBRACKET error END { yyerrok; }
          ;
    
listaFunciones : { despl = 0; } decFuncion { $$ = new elene_LISTFUN($2,0); }
               | listaFunciones { despl = 0; } decFuncion { $$ = new elene_LISTFUN($3,$1); }
               | listaFunciones error      { $$ = new elene_LISTFUN(0,$1); yyerrok; yyclearin; }
               ;

decFuncion : SEA LA FUNCION ID QUE RECIBE  
            {  
               currentLevel = enterScope(currentLevel); 
            } 
            listArg
            {
                currentLevel = exitScope(currentLevel);
            }
            Y RETORNA tipo HACER
            {
                if (!(*currentLevel).local_lookup($4)) { 
                   currentLevel -> 
                   insertar($4,new elene_TIPO_FUNCION(new elene_ID($4),$12,$8),@4.begin.line,@4.begin.column,0); 
                } else { 
                   driver.error_fun_redec(@4,$4);
                };
                despl = despBloque;
                despBloque = 0;
            }
            bloque 
            {
                despBloque = despl;
                $$ = new elene_DECFUNCION(new elene_ID($4),$8,$12,$15);                 
            }
           | SEA LA FUNCION ID QUE RETORNA tipo HACER
            {
                if (!(*currentLevel).local_lookup($4)) { 
                   currentLevel -> 
                   insertar($4,new elene_TIPO_FUNCION(new elene_ID($4),$7,0),@4.begin.line,@4.begin.column,0); 
                } else { 
                   driver.error_fun_redec(@4,$4);
                }; 
                despl = despBloque;
                despBloque = 0;
            }
            bloque
            {
                despBloque = despl; 
                $$ = new elene_DECFUNCION(new elene_ID($4),0,$7,$10); 
            }
           ;

listArg : tipo ID  
            { 
                $$ = new elene_LISTARG($1, new elene_ID($2), "Por Valor", 0); 
                if (!(*currentLevel).local_lookup($2)) {
                    currentLevel -> insertar($2,$1,@2.begin.line,@2.begin.column,despl);
                    align = alinear((*$1).tam);
                    despl = despl + align;
                } else { 
                    driver.error_param_redec(@2,$2);
                }; 
            }
        | tipo POR REFERENCIA ID 
            { 
                $$ = new elene_LISTARG($1, new elene_ID($4), "Por Referencia", 0); 
                if (!(*currentLevel).local_lookup($4)) { 
                   currentLevel -> 
                   insertar($4,$1,@4.begin.line,@4.begin.column,despl); 
                   align = alinear((*$1).tam);
                   despl = despl + align;
                } else { 
                   driver.error_param_redec(@4,$4);
                }; 
            }
        | listArg COMMA tipo POR REFERENCIA ID
          { 
              $$ = new elene_LISTARG($3, new elene_ID($6), "Por Referencia", $1); 
              if (!(*currentLevel).local_lookup($6)) {
                  currentLevel -> 
                  insertar($6,$3,@6.begin.line,@6.begin.column,despl); 
                  align = alinear((*$3).tam);
                  despl = despl + align; 
              } else { 
                  driver.error_param_redec(@6,$6);
              }; 
          }
        | listArg COMMA tipo ID
          { 
              $$ = new elene_LISTARG($3, new elene_ID($4), "Por Valor", $1); 
              if (!(*currentLevel).local_lookup($4)) { 
                  currentLevel -> 
                  insertar($4,$3,@4.begin.line,@4.begin.column,despl);
                  align = alinear((*$3).tam);
                  despl = despl + align; 
              } else { 
                  driver.error_param_redec(@4,$4); 
              }; 
          }
        | listArg COMMA error { yyerrok; yyclearin; /* FALTA TIPO !! */ }
        | error COMMA tipo POR REFERENCIA ID { yyerrok; yyclearin; /* FALTA TIPO !! */ }
        | error COMMA tipo ID { yyerrok; yyclearin; /* FALTA TIPO !! */ }
        ;


programa  : GUACARA bloque { $$ = $2; currentLevel = exitScope(currentLevel); (*$$).tipo = (*$2).tipo; /* TIPO */ }
          ;

bloque : LBRACKET listaInstruccion RBRACKET 
       { $$ = new elene_BLOQUE(0,0,$2); 
        /* Inicio Codigo para verificacion de tipos */
        (*$$).tipo = (*$2).tipo; 
        /* Fin Codigo para verificacion de tipos */
       }
       | LBRACKET VARIABLES LBRACKET 
         { currentLevel = enterScope(currentLevel);
         } 
         listaVariables RBRACKET listaInstruccion RBRACKET 
         { $$ = new elene_BLOQUE(0,$5,$7); 
           currentLevel = exitScope(currentLevel);
           /* Inicio Codigo para verificacion de tipos */
           (*$$).tipo = (*$7).tipo;
           /* Fin Codigo para verificacion de tipos */
         }
       | ID COLON LBRACKET listaInstruccion RBRACKET 
         { $$ = new elene_BLOQUE(new elene_ID($1),0,$4); 
           if (!(*tablaGlobal).local_lookup($1)) {
               tablaGlobal ->
               insertar($1,new elene_TIPO_CARACTER(),@1.begin.line,@1.begin.column,0);
           } else {
               driver.error_etiq_redec(@1,$1);
           }
           /* Inicio Codigo para verificacion de tipos */
           (*$$).tipo = (*$4).tipo;
           /* Fin Codigo para verificacion de tipos */
         }
       | ID COLON LBRACKET VARIABLES LBRACKET
         { 
             if (!(*tablaGlobal).local_lookup($1)) {
                 tablaGlobal ->
                 insertar($1,new elene_TIPO_CARACTER(),@1.begin.line,@1.begin.column,0);
             } else {
                 driver.error_etiq_redec(@1,$1);
            }
            currentLevel = enterScope(currentLevel);
         }

         listaVariables RBRACKET listaInstruccion RBRACKET
         
         { $$ = new elene_BLOQUE(new elene_ID($1),$7,$9);  
           currentLevel = exitScope(currentLevel);
           /* Inicio Codigo para verificacion de tipos */ 
           (*$$).tipo = (*$9).tipo;
           /* Fin Codigo para verificacion de tipos */
         }
       | error COLON LBRACKET VARIABLES LBRACKET listaVariables RBRACKET 
         listaInstruccion RBRACKET { yyerrok; /* FALTA TIPO !! */ }
       | error COLON LBRACKET listaInstruccion RBRACKET { yyerrok; /* FALTA TIPO !! */ }
       ;

listaInstruccion : instruccion 
                 { $$ = new elene_LISTAUNIT($1); 
                   /* Inicio Codigo para verificacion de tipos */
                   (*$$).tipo = (*$1).tipo;
                   /* Fin Codigo para verificacion de tipos */
                 }
                 | listaInstruccion SEMICOLON instruccion 
                 { $$ = new elene_LISTAMULT($3,$1);
                   /* Inicio Codigo para verificacion de tipos */
                   if ((*$1).tipo != tiposBase[6] && (*$3).tipo != tiposBase[6]) {
                       (*$$).tipo = tiposBase[5];
                   } else {
                       (*$$).tipo = tiposBase[6];   
                       // IMPRIMIR MENSAJE ??
                   }
                   /* Fin Codigo para verificacion de tipos */
                 }
                 | listaInstruccion SEMICOLON error { yyerrok; /* FALTA TIPO !! */ }
                 | error instruccion { yyerrok; /* FALTA TIPO !! */ }
                 ;

elseif      : else 
            { $$ = $1; 
              /* Inicio Codigo para verificacion de tipos */
              (*$$).tipo = (*$1).tipo; 
              /* Fin Codigo para verificacion de tipos */
            }
            | O SI expr ENTONCES bloque 
            { $$ = new elene_INSTCOND($3,$5,0); 
              /* Inicio Codigo para verificacion de tipos */
              if ((*$3).tipo == tiposBase[0] && (*$5).tipo != tiposBase[6]) {
                (*$$).tipo = tiposBase[5];
              } else {
                (*$$).tipo = tiposBase[6];
                /* Verificacion de expr booleana */
                if ((*$3).tipo != tiposBase[0]) {
                    std::stringstream ss;
				    ss << "Se esperaba una expresion booleana, pero se encontro: " 
                       << (*(*$3).tipo);
                    driver.error(@3, ss.str());
                }
              }
              /* Fin Codigo para verificacion de tipos */
            }
            | O SI expr ENTONCES bloque elseif 
            { $$ = new elene_INSTCOND($3,$5,$6); 
              /* Inicio Codigo para verificacion de tipos */
              if ((*$3).tipo == tiposBase[0] && (*$5).tipo != tiposBase[6]
                 && (*$6).tipo != tiposBase[6] ) {
                (*$$).tipo = tiposBase[5];
              } else {
                (*$$).tipo = tiposBase[6];
                /* Verificacion de expr booleana */
                if ((*$3).tipo != tiposBase[0]) {
                    std::stringstream ss;
				    ss << "Se esperaba una expresion booleana, pero se encontro: " 
                       << (*(*$3).tipo);
                    driver.error(@3, ss.str());
                }
              }
              /* Fin Codigo para verificacion de tipos */
            }
            ;

else        : SI NO ENTONCES bloque 
            { $$ = new elene_INSTCOND(new elene_BOOLEANO(1),$4,0); 
              /* Inicio Codigo para verificacion de tipos */
              (*$$).tipo = (*$4).tipo;
              /* Fin Codigo para verificacion de tipos */
            }
            ;

asignacion  : ID BECOMES expr 
            { $$ = new elene_INSTASIG(new elene_ID($1), $3); 
              /* Inicio Codigo para verificacion de tipos */
              tablaVal = (*currentLevel).lookup($1);
              if (tablaVal) {
                // Esta en la tabla de simbolos
                if ((*tablaVal).tipo == (*$3).tipo && (*$3).tipo != tiposBase[6]) {
                    // Los tipos concuerdan
                    (*$$).tipo = tiposBase[5];
                } else {
                    // Los tipos no concuerdan, error.
                    (*$$).tipo = tiposBase[6];
                    std::stringstream ss;
				    ss << "Se esperaba: " << (*(*tablaVal).tipo) 
                       << ", pero se encontro: " << (*(*$3).tipo);
                    driver.error_tipo_asignacion(@3, ss.str());
                }
              } else { 
                 // No estaba declarada
                 (*$$).tipo = tiposBase[6];
                 driver.error_indef(@1,$1);
              };  
              /* Fin Codigo para verificacion de tipos */
            }
            | ID LCORCHET expr RCORCHET BECOMES expr 
            { 
               $$ = new elene_INSTASIG_ARREGLO(new elene_ID($1), $3, $6);
               /* Inicio Codigo para verificacion de tipos */
               tablaVal = (*currentLevel).lookup($1);
               if (tablaVal) {
                    testArreglo = dynamic_cast<elene_TIPO_ARREGLO *> ((*tablaVal).tipo);
                    if (testArreglo) {
                        if ((*$3).tipo != tiposBase[6] && (*$6).tipo != tiposBase[6]) {
                            // Es una asignacion correcta!
                            (*$$).tipo = tiposBase[5];
                        } else {
                            // Las expresiones tienen errores
                            (*$$).tipo = tiposBase[6];
                        } 
                    } else {
                        // No es un arreglo
		                (*$$).tipo = tiposBase[6];
                        driver.error_tipo_no_es_array(@1,$1);
                    }
                    testArreglo = 0;
               } else { 
                 // No estaba declarada
                 (*$$).tipo = tiposBase[6];
                 driver.error_indef(@1,$1);
               };  
               /* Fin Codigo para verificacion de tipos */
            }
            | expr PERIOD ID BECOMES expr
            {
              $$ = new elene_INSTASIG_ESTRUCTURA(new elene_ID($3), $1, $5);
              /* Inicio Codigo para verificacion de tipos */
			  test = dynamic_cast<elene_TIPO_ESTRUCTURA *> ((*$1).tipo);
				if (test) {
					tipoAux = (*test).lookup_attr($3);
					if (tipoAux) {
                        if (tipoAux == (*$5).tipo) {
                            (*$$).tipo = tiposBase[5];
                        } else {
                            std::stringstream ss;
				            ss << "Se esperaba: " << (*tipoAux) 
                            << " pero se encontro: " << (*(*$5).tipo);
                            (*$$).tipo = tiposBase[6];
                            driver.error(@4,ss.str());
                        }
					} else {
						(*$$).tipo = tiposBase[6];
						driver.error_tipo_attr_no_dec(@3,$3);
					}
				} else {
					(*$$).tipo = tiposBase[6];
					driver.error_tipo_no_estr(@1,"");
				}
                test = 0;
              /* Fin Codigo para verificacion de tipos */
            }
            ;

instruccion : LEER ID 
            { $$ = new elene_INSTLEER(new elene_ID($2)); 
            /* Inicio Codigo para verificacion de tipos */
              if (!(*currentLevel).lookup($2)) { 
                  driver.error_indef(@2,$2);
                  (*$$).tipo = tiposBase[6];
              } else {
                  (*$$).tipo = tiposBase[5];
              }
            /* Fin Codigo para verificacion de tipos */
            } 
            | IMPRIMIR expr 
            { $$ = new elene_INSTESCR($2);
              /* Inicio Codigo para verificacion de tipos */
              if ((*$2).tipo != tiposBase[6]) {
                (*$$).tipo = tiposBase[5];
              } else {
                (*$$).tipo = tiposBase[6];
              }
              /* Fin Codigo para verificacion de tipos */
            }
            | RETORNAR expr 
            { $$ = new elene_INSTRETORNAR($2); 
              /* Inicio Codigo para verificacion de tipos */
              if ((*$2).tipo != tiposBase[6]) {
                (*$$).tipo = tiposBase[5];
              } else {
                (*$$).tipo = tiposBase[6];
              }
              /* Fin Codigo para verificacion de tipos */
            }
            | SI expr ENTONCES bloque 
            { $$ = new elene_INSTCOND($2, $4, 0);  
              /* Inicio Codigo para verificacion de tipos */
              if ((*$2).tipo == tiposBase[0] && (*$4).tipo == tiposBase[5]) {
                (*$$).tipo = tiposBase[5];
              } else {
                (*$$).tipo = tiposBase[6];
                /* Verificacion de expr booleana */
                if ((*$2).tipo != tiposBase[0]) {
                    std::stringstream ss;
				    ss << "Se esperaba una expresion booleana, pero se encontro: " 
                       << (*(*$2).tipo);
                    driver.error(@2, ss.str());
                }
              }
              /* Fin Codigo para verificacion de tipos */
            }
            | SI expr ENTONCES bloque elseif 
            { $$ = new elene_INSTCOND($2,$4,$5); 
              /* Inicio Codigo para verificacion de tipos */
              if ((*$2).tipo == tiposBase[0] && (*$4).tipo == tiposBase[5] && 
                  (*$5).tipo == tiposBase[5] ) {
                (*$$).tipo = tiposBase[5];
              } else {
                (*$$).tipo = tiposBase[6];
                /* Verificacion de expr booleana */
                if ((*$2).tipo != tiposBase[0]) {
                    std::stringstream ss;
				    ss << "Se esperaba una expresion booleana, pero se encontro: " 
                       << (*(*$2).tipo);
                    driver.error(@2, ss.str());
                }
              }
              /* Fin Codigo para verificacion de tipos */
            }
            | asignacion 
            { $$ = $1; (*$$).tipo = (*$1).tipo; }
            | MIENTRAS expr HACER bloque 
            { $$ = new elene_INSTMIENTRAS($2,$4); 
              /* Inicio Codigo para verificacion de tipos */
              if ((*$2).tipo == tiposBase[0] && (*$4).tipo == tiposBase[5]) {
                (*$$).tipo = tiposBase[5];
              } else {
                (*$$).tipo = tiposBase[6];
                /* Verificacion de expr booleana */
                if ((*$2).tipo != tiposBase[0]) {
                    std::stringstream ss;
				    ss << "Se esperaba una expresion booleana, pero se encontro: " 
                       << (*(*$2).tipo);
                    driver.error(@2, ss.str());
                }
                // IMPRIMIR MENSAJE ??
              }
              /* Fin Codigo para verificacion de tipos */
            }
            | PARA asignacion TAL QUE expr CON CAMBIO asignacion HACER bloque 
            { $$ = new elene_INSTPARA($2,$5,$8,$10); 
              /* Inicio Codigo para verificacion de tipos */
              if ((*$2).tipo == tiposBase[5] && (*$5).tipo == tiposBase[0] &&
                  (*$8).tipo == tiposBase[5] && (*$10).tipo == tiposBase[5] ) {
                  (*$$).tipo = tiposBase[5];
              } else {
                  (*$$).tipo = tiposBase[6];
                  /* Verificacion de expr booleana */
                  if ((*$5).tipo != tiposBase[0]) {
                    std::stringstream ss;
				    ss << "Se esperaba una expresion booleana, pero se encontro: " 
                       << (*(*$5).tipo);
                    driver.error(@5, ss.str());
                  }
                  // IMPRIMIR MENSAJE ??
              }
              /* Fin Codigo para verificacion de tipos */
            } 
            | expr 
            { $$ = new elene_INSTEXPR($1);
              /* Inicio Codigo para verificacion de tipos */
              if ((*$1).tipo != tiposBase[6]) {
                (*$$).tipo = tiposBase[5];
              } else {
                (*$$).tipo = tiposBase[6];
              }
              /* Fin Codigo para verificacion de tipos */
            }
            | ROMPER ITERACION { $$ = new elene_INSTROMPER(); (*$$).tipo = tiposBase[5]; }
            | CONTINUAR ITERACION { $$ = new elene_INSTCONTINUAR(); (*$$).tipo = tiposBase[5]; }
            | instruccionCase { $$ = $1; (*$$).tipo = (*$1).tipo; }
            ;

instruccionCase : SEA ID IGUAL A LBRACKET casosCase POR DEFECTO HACER bloque RBRACKET
                  { $$ = new elene_INSTCASE(new elene_ID($2),$6,$10);
                    /* Inicio Codigo para verificacion de tipos */
                    tablaVal = (*currentLevel).lookup($2);
                    if (tablaVal) {
                        // Verificamos que el tipo de ID concuerde con los casos
                        if ((*$6).verificar_tipos((*tablaVal).tipo)) {
                            if ((*$6).tipo == tiposBase[5] && (*$10).tipo == tiposBase[5]) {
                                (*$$).tipo = tiposBase[5];
                            } else {
                                (*$$).tipo = tiposBase[6];
                                // IMPRIMIR MENSAJE ??
                            }
                        } else {
                            (*$$).tipo = tiposBase[6];
                            driver.error_tipo_case_var_expr(@2,$2);
                        }
                    } else {
                        (*$$).tipo = tiposBase[6];
                        driver.error_tipo_case_var_undec(@2,$2);
                    }
                    /* Fin Codigo para verificacion de tipos */
                  }
                | SEA error IGUAL A LBRACKET casosCase POR DEFECTO HACER bloque RBRACKET
                  { yyerrok;  /* FALTA TIPOS Asignamos error y ya?*/ }
                | SEA ID IGUAL A LBRACKET error POR DEFECTO HACER bloque RBRACKET
                  { yyerrok;  /* FALTA TIPOS */ }
                | SEA error IGUAL A LBRACKET error POR DEFECTO HACER bloque RBRACKET
                  { yyerrok;  /* FALTA TIPOS */}
                ;

casosCase : caso 
          {  $$ = new elene_LISTACASE($1,0); 
             /* Inicio Codigo para verificacion de tipos */
             (*$$).tipo = (*$1).tipo;
             /* Fin Codigo para verificacion de tipos */
          }
          | casosCase caso 
          { $$ = new elene_LISTACASE($2,$1); 
            /* Inicio Codigo para verificacion de tipos */
            if ((*$1).tipo == tiposBase[5] && (*$2).tipo == tiposBase[5]) {
                (*$$).tipo = tiposBase[5];
            } else {
                (*$$).tipo = tiposBase[6];
                // IMPRIMIR MENSAJE ??
            }
            /* Fin Codigo para verificacion de tipos */
          }
          ;

caso : expr ENTONCES HACER bloque 
       { $$ = new elene_CASO($1,$4); 
         /* Inicio Codigo para verificacion de tipos */
         if ((*$1).tipo != tiposBase[6] && (*$4).tipo != tiposBase[6]) {
            (*$$).tipo = tiposBase[5];
         } else {
            (*$$).tipo = tiposBase[6];
            // IMPRIMIR MENSAJE ?? 
         }
         /* Fin Codigo para verificacion de tipos */
       }

listaExpr: listaExpr COMMA expr 
         { $$ = new elene_LISTAEXPR($3,$1);
           /* Inicio Codigo para verificacion de tipos */
           if ((*$1).tipo != tiposBase[6] && (*$3).tipo != tiposBase[6]) {
               // Si no hay problema es vacio
               (*$$).tipo = tiposBase[5];   
           } else {
               // Si uno es error, es error.
               (*$$).tipo = tiposBase[6];   
               if ((*$3).tipo == tiposBase[6]) {
                   driver.error_tipo_listaexpr_expr(@3,"");
               }
           }
           /* Fin Codigo para verificacion de tipos */
         }
         | expr 
         { $$ = new elene_LISTAEXPR($1, 0);
           /* Inicio Codigo para verificacion de tipos */ 
           if ((*$1).tipo != tiposBase[6]) {
               // Si no tiene errores, es vacio
               (*$$).tipo = tiposBase[5]; 
           } else {
               // Si si tiene, es error
               (*$$).tipo = tiposBase[6]; 
               driver.error_tipo_listaexpr_expr(@1,"");
           }
           /* Fin Codigo para verificacion de tipos */
         }
         | 
         { $$ = new elene_LISTAEXPR(0,0); 
           // El tipo es vacio
           (*$$).tipo = tiposBase[5]; 
         } 
         | listaExpr COMMA error 
         { // El tipo es el mismo que el de la lista
           (*$$).tipo = (*$1).tipo; 
           yyerrok; yyclearin; 
         } 
         | error expr            
         { yyerrok; yyclearin; 
           /* Inicio Codigo para verificacion de tipos */
           if ((*$2).tipo != tiposBase[6]) {
               // Si la expr no tiene error, es vacio
               (*$$).tipo = tiposBase[5];
           } else {
               // En caso contrario, error.
               (*$$).tipo = tiposBase[6]; 
           }
           /* Fin Codigo para verificacion de tipos */
         }
         ;         


expr : LPAREN expr RPAREN  { $$ = $2; (*$$).tipo = (*$2).tipo; }
     | ID LCORCHET expr RCORCHET 
	 { $$ = new elene_ACCARREG(new elene_ID($1),$3);
       /* Inicio Codigo para verificacion de tipos */
       tablaVal = (*currentLevel).lookup($1);
	   if (tablaVal) {
            testArreglo = dynamic_cast<elene_TIPO_ARREGLO *> ((*tablaVal).tipo);
            if (testArreglo) {
                (*$$).tipo = (*testArreglo).tipo;
            } else {
		        (*$$).tipo = tiposBase[6];
                driver.error_tipo_no_es_array(@1,$1);
            }
            testArreglo = 0;
	   } else {
			(*$$).tipo = tiposBase[6];
			driver.error_tipo_array_undec(@1,$1);
	   }
       /* Fin Codigo para verificacion de tipos */
	 }
     | exprBinaria         { $$ = $1; (*$$).tipo = (*$1).tipo; }
     | exprUnaria          { $$ = $1; (*$$).tipo = (*$1).tipo; }
     | terminal            { $$ = $1; (*$$).tipo = (*$1).tipo; }
     ;

exprBinaria : expr Y expr 
			{ $$ = new elene_CONJUNCION($1,$3);
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$3).tipo) && ((*$1).tipo == tiposBase[0])) {
				(*$$).tipo = tiposBase[0];
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Conjuncion de " << (*(*$1).tipo) << " con " << (*(*$3).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr O expr 
			{ $$ = new elene_DISYUNCION($1,$3); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$3).tipo) && ((*$1).tipo == tiposBase[0])) {
				(*$$).tipo = tiposBase[0];
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Disyuncion de " << (*(*$1).tipo)<< " con " << (*(*$3).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr PLUS expr 
			{ $$ = new elene_ADICION($1,$3); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$3).tipo) && ( ((*$1).tipo == tiposBase[1]) || (*$1).tipo == tiposBase[4])) {
				(*$$).tipo = (*$1).tipo;
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Adicion de " << (*(*$1).tipo) << " con " << (*(*$3).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr MINUS expr 
			{ $$ = new elene_SUSTRACCION($1,$3);
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$3).tipo) && ( ((*$1).tipo == tiposBase[1]) || (*$1).tipo == tiposBase[4])) {
				(*$$).tipo = (*$1).tipo;
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Sustraccion de " << (*(*$1).tipo) << " con " << (*(*$3).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */ 
			}
            | expr TIMES expr 
			{ $$ = new elene_MULTIPLICACION($1,$3); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$3).tipo) && ( ((*$1).tipo == tiposBase[1]) || (*$1).tipo == tiposBase[4])) {
				(*$$).tipo = (*$1).tipo;
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Multiplicacion de " << (*(*$1).tipo) << " con " << (*(*$3).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr SLASH expr 
			{ $$ = new elene_DIVISION($1,$3); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$3).tipo) && ( ((*$1).tipo == tiposBase[1]) || (*$1).tipo == tiposBase[4])) {
				(*$$).tipo = (*$1).tipo;
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Division de " << (*(*$1).tipo) << " con " << (*(*$3).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr MAYOR QUE expr 
			{ $$ = new elene_MAYOR($1,$4); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$4).tipo) && ( ((*$1).tipo == tiposBase[1]) || (*$1).tipo == tiposBase[4])) {
				(*$$).tipo = tiposBase[0]; // Es booleano
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Relacion 'mayor que' de " << (*(*$1).tipo) << " con " << (*(*$4).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			} 
            | expr MENOR QUE expr 
			{ $$ = new elene_MENOR($1,$4); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$4).tipo) && ( ((*$1).tipo == tiposBase[1]) || (*$1).tipo == tiposBase[4])) {
				(*$$).tipo = tiposBase[0]; // Es booleano
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Relacion 'menor que' de " << (*(*$1).tipo) << " con " << (*(*$4).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr MAYOR O IGUAL QUE expr 
			{ $$ = new elene_MAYORIGUAL($1,$6); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$6).tipo) && ( ((*$1).tipo == tiposBase[1]) || (*$1).tipo == tiposBase[4])) {
				(*$$).tipo = tiposBase[0]; // Es booleano
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Relacion 'mayor o igual' de " << (*(*$1).tipo) << " con " << (*(*$6).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr MENOR O IGUAL QUE expr 
			{ $$ = new elene_MENORIGUAL($1,$6); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$6).tipo) && ( ((*$1).tipo == tiposBase[1]) || (*$1).tipo == tiposBase[4])) {
				(*$$).tipo = tiposBase[0]; // Es booleano
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Relacion 'menor o igual' de " << (*(*$1).tipo) << " con " << (*(*$6).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr DISTINTO A expr        
			{ $$ = new elene_DISTINTO($1,$4); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$4).tipo) && ( ((*$1).tipo != tiposBase[5]) && (*$1).tipo != tiposBase[6])) { /*OJO!! ESOS DISTINTOS (Estr)*/
				(*$$).tipo = tiposBase[0]; // Es booleano
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Relacion 'distinto' compara " << (*(*$1).tipo) << " con " << (*(*$4).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr IGUAL A expr           
			{ $$ = new elene_IGUAL($1,$4); 
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$1).tipo == (*$4).tipo) && ( ((*$1).tipo != tiposBase[5]) && (*$1).tipo != tiposBase[6])) { /*OJO!! ESOS DISTINTOS (Estr)*/
				(*$$).tipo = tiposBase[0]; // Es booleano
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Relacion 'igual' compara " << (*(*$1).tipo)<< " con " << (*(*$4).tipo);
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
			}
            | expr PERIOD ID            
			{ $$ = new elene_ACCESO($1, new elene_ID($3));
              /* Inicio Codigo para verificacion de tipos */
			  test = dynamic_cast<elene_TIPO_ESTRUCTURA *> ((*$1).tipo);
				if (test) {
					tipoAux = (*test).lookup_attr($3);
					if (tipoAux) {
						(*$$).tipo = tipoAux;
					} else {
						(*$$).tipo = tiposBase[6];
						driver.error_tipo_attr_no_dec(@3,$3);
					}
				} else {
					(*$$).tipo = tiposBase[6];
					driver.error_tipo_no_estr(@1,"");
				}
                test = 0;
              /* Fin Codigo para verificacion de tipos */
			}
            ;

exprUnaria : MINUS expr %prec NEG  
		   { $$ = new elene_MENOSUNARIO($2);
			  /* Inicio Codigo para verificacion de tipos */
			  if ( ((*$2).tipo == tiposBase[1]) || ((*$2).tipo == tiposBase[4]) ) {
				(*$$).tipo = (*$2).tipo;
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Menos unario aplicado sobre " << (*(*$2).tipo) ;
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */
		   }
           | NO expr %prec NEGBOOL 
		   { $$ = new elene_NEGACION($2);
			  /* Inicio Codigo para verificacion de tipos */
			  if ( (*$2).tipo == tiposBase[0]) {
				(*$$).tipo = (*$2).tipo;
			  } else {
			  	(*$$).tipo = tiposBase[6];
				std::stringstream ss;
				ss << "Negacion aplicada sobre " << (*(*$2).tipo) ;
				driver.error_tipo_expr(@2,ss.str());
			  }
			  /* Fin codigo para verificacion de tipos */  
		   }
           ;

terminal : VERDADERO        { $$ = new elene_BOOLEANO($1); (*$$).tipo = tiposBase[0];  }     
         | FALSO            { $$ = new elene_BOOLEANO($1); (*$$).tipo = tiposBase[0]; }
         | NUMENTERO        { $$ = new elene_ENTERO($1); (*$$).tipo = tiposBase[4];}
         | NUMFLOTANTE      { $$ = new elene_REAL($1); (*$$).tipo = tiposBase[1];}
         | CONSTCARACTER    { $$ = new elene_CARACTER($1); (*$$).tipo = tiposBase[2];}
         | ID               { $$ = new elene_ID($1); 
                                if (!(*currentLevel).lookup($1)) { 
                                    driver.error_indef(@1,$1);
                                    (*$$).tipo = tiposBase[6];
                                } else {
                                    (*$$).tipo = (*(*currentLevel).lookup($1)).tipo;
                                }                           
                            }
         | ID LPAREN listaExpr RPAREN 
           { $$ = new elene_EXPRFUNC(new elene_ID($1),$3); 
                if (!(*currentLevel).lookup($1)) { 
                    (*$$).tipo = tiposBase[6];
                    driver.error_indef(@1,$1);
                } else if (testFuncion = dynamic_cast<elene_TIPO_FUNCION *>((*(*currentLevel).lookup($1)).tipo)) {
                                                      
                    if (chequearArgumentos($3,(*testFuncion).param) ) {
                        (*$$).tipo = (*(*currentLevel).lookup($1)).tipo;
                    } else {
                        (*$$).tipo = tiposBase[6];
                        driver.error_parametros(@1,$1);
                    }
                    
                    testFuncion = 0;

                } else {
                    driver.error_no_funcion(@1,$1);
                    (*$$).tipo = tiposBase[6];
                }; 
           }
         | STRING           { $$ = new elene_STRING($1); (*$$).tipo = tiposBase[3]; }
         ;
%%

void yy::elene_parser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
