# ifndef ELENE_CLASES_HH
# define ELENE_CLASES_HH

# include <string>
# include <map>





class elene_ID {

    public:
        elene_ID(<std::string> nombre, <std::string> tipo, void valor);
        <std::string> nombre;
        <std::string> tipo;
        void valor;
}

elene_ID::elene_ID(<std::string> nombre, <std::string> tipo, void valor) {

    this -> nombre = nombre;
    this -> tipo   = tipo;
    this -> valor  = valor;
}






class elene_EXPR {

    public:
        elene_EXPR(<std::string> tipo, void expr);
        <std::string> tipo;
        void expr;
}

elene_EXPR::elene_EXPR(<std::string> tipo, void expr) {

    this -> tipo = tipo;
    this -> expr = expr;
}






class elene_EXPRBOOLEANA {
    
    public:
        elene_EXPRBOOLEANA(<std::string> operador, elene_EXPR exprIzq, elene_EXPR exprDer);
        <std::string> operador;
        elene_EXPR exprIzq;
        elene_EXPR exprDer;
}

elene_EXPRBOOLEANA::elene_EXPRBOOLEANA(<std::string> operador, elene_EXPR exprIzq, elene_EXPR exprDer) {

    this -> operador = operador;
    this -> exprIzq  = exprIzq;
    this -> exprDer  = exprDer;
}






class elene_EXPRARITMETICA {

    public:
        elene_EXPRARITMETICA(<std::string> operador, elene_EXPR exprIzq, elene_EXPR exprDer);
        <std::string> operador;
        elene_EXPR exprIzq;
        elene_EXPR exprDer;
}

elene_EXPRARITMETICA::elene_EXPRARITMETICA(<std::string> operador, elene_EXPR exprIzq, elene_EXPR exprDer) {

    this -> operador = operador;
    this -> exprIzq  = exprIzq;
    this -> exprDer  = exprDer;
}






class elene_LEER {

    public:
        elene_LEER(elene_ID ID);
        elene_ID ID;
}

elene_LEER::elene_LEER(elene_ID ID) {

    this -> ID = ID;
}






class elene_IMPRIMIR {

    public:
        elene_IMPRIMIR(elene_EXPR valor);
        elene_EXPR valor;
}

elene_IMPRIMIR::elene_IMPRIMIR(elene_EXPR valor) {

    this -> valor = valor;
}





class elene_DECVAR {

    public:
        <
}





/* Falta considerar aun la tabla de simbolos, no sirve aun*/
class elene_BLOQUE {

    public:
        elene_BLOQUE(void vars, <std::list<elene_INST>> insts);
        void vars;
        <std::list<elene_INST>> insts;
}


elene_BLOQUE::elene_BLOQUE(void vars , <std::list<elene_INST>> insts) {
    this -> vars = vars;
    this -> insts = insts;
}








/* REVISAR EL IF, FALTAN COSAS COMO ELSIF Y ELSE*/ 
class elene_CONDICIONALSI {

    public:
        elene_CONDICIONALSI(elene_EXPR exprCond, elene_BLOQUE bloque);
        elene_EXPR exprCond;
        elene_BLOQUE bloque;
}


elene_CONDICIONALSI::elene_CONDICIONALSI(elene_EXPR exprCond, elene_BLOQUE bloque) {

    this -> exprCond = exprCond;
    this -> bloque = bloque;
}







class elene_ASIGNACION {

    public:
        elene_ASIGNACION(elene_ID ID, elene_EXPR EXPR);
        elene_ID ID;
        elene_EXPR EXPR;
}


elene_ASIGNACION::elene_ASIGNACION(elene_ID ID, elene_EXPR EXPR) {

    this -> ID = ID;
    this -> EXPR = EXPR;
}







class elene_MIENTRAS {

    public:
        elene_MIENTRAS(elene_EXPR exprCond, elene_BLOQUE bloque);
        elene_EXPR exprCond;
        elene_BLOQUE bloque;
}

elene_MIENTRAS::elene_MIENTRAS(elene_EXPR exprCond, elene_BLOQUE bloque) {

    this -> exprCond = exprCond;
    this -> bloque   = bloque;
}







class elene_FOR {

    public:
        elene_FOR(elene_ASIGNACION asig, elene_EXPR expr, elene_ASIGNACION cambio, elene_BLOQUE bloque);
        elene_ASIGNACION asig;
        elene_EXPR expr;
        elene_ASIGNACION cambio;
        elene_BLOQUE bloque;

}

elene_PARA::elene_PARA(elene_ASIGNACION asig, elene_EXPR expr, elene_ASIGNACION cambio, elene_BLOQUE bloque) {

    this -> asig = asig;
    this -> expr = expr;
    this -> cambio = cambio;
    this -> bloque = bloque;
}






# endif
