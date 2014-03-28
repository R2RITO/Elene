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

%left O
%left Y
%left IGUAL DISTINTO A
%nonassoc MAYOR MENOR QUE
%left PLUS MINUS
%left TIMES SLASH
%left NEG NEGBOOL
%printer { yyoutput << $$; } <*>;

%%

%start inicio;


inicio : { currentLevel = new elene_TABLA(); currentLevel -> insertar("Read",new elene_TIPO_SIMPLE("FuncionPredef"),1,1,4); } varglobal { std::cout << *$2; std::cout << "\n\nImprimiendo tabla\n\n"; std::cout << *currentLevel; }

varglobal : funciones { $$ = new elene_VARGLOBAL($1,0); }
          | VARIABLES GLOBALES LBRACKET { currentLevel = enterScope(currentLevel); } listaVariables { currentLevel = exitScope(currentLevel); }  RBRACKET funciones { $$ = new elene_VARGLOBAL($8,$5); }
          ;

listaVariables : decVariable { $$ = new elene_LISTAVAR($1,0); }
               | decVariable SEMICOLON listaVariables { $$ = new elene_LISTAVAR($1, $3); }
               ;

decVariable   : SEA ID DE TIPO tipo { $$ = new elene_DECLARACION(new elene_ID($2),$5,0); currentLevel -> insertar($2,$5,@2.begin.line,@2.begin.column,0); } 
              | SEA ID DE TIPO tipo CON VALOR expr { $$ = new elene_DECLARACION(new elene_ID($2), $5, $8); currentLevel -> insertar($2,$5,@2.begin.line,@2.begin.column,0) /* Falta el valor */; }
              ;

tipo : BOOLEANO { $$ = new elene_TIPO_SIMPLE("Booleano"); }
     | ENTERO   { $$ = new elene_TIPO_SIMPLE("Entero"); }
     | FLOTANTE { $$ = new elene_TIPO_SIMPLE("Flotante"); }
     | CARACTER { $$ = new elene_TIPO_SIMPLE("Caracter"); }
     | STRING   { $$ = new elene_TIPO_SIMPLE("String");}
     | VACIO    { $$ = new elene_TIPO_SIMPLE("Vacio");}
     | ARREGLO DE tipo DE expr A expr { $$ = new elene_TIPO_ARREGLO($3,$5,$7); }
     | LPAREN tipo RPAREN { $$ = $2; }
     ;

funciones : programa { $$ = new elene_FUNCIONES(0,$1); }
          | FUNCIONES LBRACKET listaFunciones RBRACKET programa { $$ = new elene_FUNCIONES($3,$5); }
          ;
    
listaFunciones : decFuncion { $$ = new elene_LISTFUN($1,0); }
               | decFuncion listaFunciones { $$ = new elene_LISTFUN($1,$2); }
               ;

decFuncion : SEA LA FUNCION ID QUE RECIBE listArg Y RETORNA tipo HACER bloque { $$ = new elene_DECFUNCION(new elene_ID($4),$7,$10,$12); }
           | SEA LA FUNCION ID QUE RETORNA tipo HACER bloque { $$ = new elene_DECFUNCION(new elene_ID($4),0,$7,$9); }
           | SEA LA FUNCION ID QUE RECIBE listArg HACER bloque { $$ = new elene_DECFUNCION(new elene_ID($4),$7,0,$9); }
           ;

listArg : tipo ID  { $$ = new elene_LISTARG($1, new elene_ID($2), "Por Valor", 0); }
        | tipo POR REFERENCIA ID { $$ = new elene_LISTARG($1, new elene_ID($4), "Por Referencia", 0); }
        | tipo POR REFERENCIA ID COMMA listArg { $$ = new elene_LISTARG($1, new elene_ID($4), "Por Referencia", $6); }
        | tipo ID COMMA listArg { $$ = new elene_LISTARG($1, new elene_ID($2), "Por Valor", $4); }
        ;


programa  : GUACARA bloque { $$ = $2; }
          ;

bloque : LBRACKET listaInstruccion RBRACKET { $$ = new elene_BLOQUE(0,$2); }
       | LBRACKET VARIABLES LBRACKET { currentLevel = enterScope(currentLevel); } listaVariables RBRACKET listaInstruccion RBRACKET { $$ = new elene_BLOQUE($5, $7); currentLevel = exitScope(currentLevel); }
       ;

listaInstruccion : instruccion { $$ = new elene_LISTAUNIT($1); }
                 | instruccion SEMICOLON listaInstruccion { $$ = new elene_LISTAMULT($1,$3); }
                 ;

elseif      : else { $$ = $1; }
            | O SI expr ENTONCES bloque { $$ = new elene_INSTCOND($3,$5,0); }
            | O SI expr ENTONCES bloque elseif { $$ = new elene_INSTCOND($3,$5,$6); }
            ;

else        : SI NO ENTONCES bloque { $$ = new elene_INSTCOND(new elene_BOOLEANO(1),$4,0); }
            ;
asignacion  : ID BECOMES expr { $$ = new elene_INSTASIG(new elene_ID($1), $3); }
            ;

instruccion : LEER ID { $$ = new elene_INSTLEER(new elene_ID($2)); } 
            | IMPRIMIR expr { $$ = new elene_INSTESCR($2); }
            | SI expr ENTONCES bloque { $$ = new elene_INSTCOND($2, $4, 0);  }
            | SI expr ENTONCES bloque elseif { $$ = new elene_INSTCOND($2,$4,$5); }
            | asignacion { $$ = $1; }
            | MIENTRAS expr HACER bloque { $$ = new elene_INSTMIENTRAS($2,$4); }
            | PARA asignacion TAL QUE expr CON CAMBIO asignacion HACER bloque { $$ = new elene_INSTPARA($2,$5,$8,$10); } 
            ;


expr : LPAREN expr RPAREN  { $$ = $2; }
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
            ;

exprUnaria : MINUS expr %prec NEG  { $$ = new elene_MENOSUNARIO($2); }
           | NO expr %prec NEGBOOL { $$ = new elene_NEGACION($2);  }
           ;

terminal : VERDADERO        { $$ = new elene_BOOLEANO($1);  }     
         | FALSO            { $$ = new elene_BOOLEANO($1); }
         | NUMENTERO        { $$ = new elene_ENTERO($1); }
         | NUMFLOTANTE      { $$ = new elene_REAL($1); }
         | CONSTCARACTER    { $$ = new elene_CARACTER($1); }
         | ID               { $$ = new elene_ID($1); if (!(*currentLevel).lookup($1)) { std::cout << "Error no encuentro " << $1 << "\n"; /*yy::elene_parser::error(@1,"Var no declarada\n");*/ };   }
         | STRING           { $$ = new elene_STRING($1); }
         ;

%%

void yy::elene_parser::error (const location_type& l, const std::string& m) {
    std::cout << "La";
    driver.error (l, m);
}
