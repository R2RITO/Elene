%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name {elene_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert


%code requires {
    #include <string>
    #include <iostream>
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
%left O
%left Y
%left EQ NE
%nonassoc LT GT LE GE
%left PLUS MINUS
%left TIMES SLASH
%left NEG NEGBOOL
%printer { yyoutput << $$; } <*>;

%%

%start inicio;


inicio : expr


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

instruccion : LEER ID
            | IMPRIMIR expr
            | SI expr ENTONCES bloque
            | SI expr ENTONCES bloque elseif
            | asignacion 
            | MIENTRAS expr HACER bloque
            | PARA asignacion TAL QUE expr CON CAMBIO asignacion HACER bloque 
            ;


expr : LPAREN expr RPAREN 
     | exprBinaria       
     | exprUnaria     
     | terminal           
     ;

exprBinaria : expr operador expr { std::cout << "Expresion \n"; }
            ;

operador : MAYOR QUE %prec GT  { std::cout << "mayor\n"; }
         | MENOR QUE %prec LT  { std::cout << "menor\n"; }
         | MAYOR O IGUAL QUE %prec GE { std::cout << "mayorigual\n"; }
         | MENOR O IGUAL QUE %prec LE { std::cout << "menorigual\n"; }
         | IGUAL A %prec EQ { std::cout << "igual\n"; }
         | DISTINTO A %prec NE { std::cout << "distinto\n"; }
         | Y { std::cout << "y\n"; }
         | O { std::cout << "o\n"; }
         | PLUS { std::cout << "mas\n"; }
         | MINUS { std::cout << "menps\n"; }
         | TIMES { std::cout << "por\n"; }
         | SLASH { std::cout << "entre\n"; }
         ; 

exprUnaria : MINUS expr %prec NEG { std::cout << "menos unario \n"; }
           | NO expr %prec NEGBOOL {std::cout << "negacion \n"; }
           ;

terminal : VERDADERO        
         | FALSO           
         | NUMENTERO      
         | NUMFLOTANTE   
         | CONSTCARACTER
         | ID           
         | STRING      


%%

void yy::elene_parser::error (const location_type& l, const std::string& m) {
    driver.error (l, m);
}
