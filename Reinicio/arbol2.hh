# ifndef ELENE_CLASES_HH
# define ELENE_CLASES_HH

# include <string>
# include <map>
# include <iostream>


/***************************************************************/
/****** EXPRESIONES ********************************************/
/***************************************************************/

class elene_EXPR /* : public printable */ {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_EXPR& obj){
        return obj.stream_write(stream); 
    }
};


/***************************************************************/
/****** EXPRESIONES BINARIAS ***********************************/
/***************************************************************/

class elene_EXPRBINARIA : public elene_EXPR {

protected:
    elene_EXPR* expr_izq;
    elene_EXPR* expr_der;
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    /* Declaracion de constructor */
    elene_EXPRBINARIA() {};
    elene_EXPRBINARIA(elene_EXPR* izq, elene_EXPR* der):expr_izq(izq), expr_der(der) {};
    /* Declaracion de destructor */
    virtual ~elene_EXPRBINARIA () {}

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_EXPRBINARIA& obj) { 
        return obj.stream_write(stream); 
    }
};



class elene_CONJUNCION : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Conjuncion:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_CONJUNCION(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_CONJUNCION(const elene_CONJUNCION &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_CONJUNCION() {
        delete expr_izq;
        delete expr_der;
    }

    elene_CONJUNCION &operator = (const elene_CONJUNCION &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};


/* Clase para la disyuncion */
class elene_DISYUNCION : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Disyuncion:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_DISYUNCION(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_DISYUNCION(const elene_DISYUNCION &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_DISYUNCION() {
        delete expr_izq;
        delete expr_der;
    }

    elene_DISYUNCION &operator = (const elene_DISYUNCION &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};

/* Clase para la suma */
class elene_ADICION : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Adicion:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_ADICION(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_ADICION(const elene_ADICION &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_ADICION() {
        delete expr_izq;
        delete expr_der;
    }

    elene_ADICION &operator = (const elene_ADICION &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};

/* Clase para la resta */
class elene_SUSTRACCION : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Sustraccion:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_SUSTRACCION(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_SUSTRACCION(const elene_SUSTRACCION &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_SUSTRACCION() {
        delete expr_izq;
        delete expr_der;
    }

    elene_SUSTRACCION &operator = (const elene_SUSTRACCION &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};


/* Clase para la multiplicacion */
class elene_MULTIPLICACION : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Multiplicacion:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_MULTIPLICACION(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_MULTIPLICACION(const elene_MULTIPLICACION &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_MULTIPLICACION() {
        delete expr_izq;
        delete expr_der;
    }

    elene_MULTIPLICACION &operator = (const elene_MULTIPLICACION &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};


/* Clase para la division */
class elene_DIVISION : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Division:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_DIVISION(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_DIVISION(const elene_DIVISION &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_DIVISION() {
        delete expr_izq;
        delete expr_der;
    }

    elene_DIVISION &operator = (const elene_DIVISION &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};

/* Clase para el mayor que */
class elene_MAYOR : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Mayor Que:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_MAYOR(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_MAYOR(const elene_MAYOR &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_MAYOR() {
        delete expr_izq;
        delete expr_der;
    }

    elene_MAYOR &operator = (const elene_MAYOR &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};


/* Clase para el menor que */
class elene_MENOR : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Menor Que:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_MENOR(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_MENOR(const elene_MENOR &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_MENOR() {
        delete expr_izq;
        delete expr_der;
    }

    elene_MENOR &operator = (const elene_MENOR &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};

/* Clase para el menor o igual que */
class elene_MENORIGUAL : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Menor O Igual Que:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_MENORIGUAL(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_MENORIGUAL(const elene_MENORIGUAL &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_MENORIGUAL() {
        delete expr_izq;
        delete expr_der;
    }

    elene_MENORIGUAL &operator = (const elene_MENORIGUAL &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};


/* Clase para el mayor o igual que */
class elene_MAYORIGUAL : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Mayor O Igual Que:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_MAYORIGUAL(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_MAYORIGUAL(const elene_MAYORIGUAL &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_MAYORIGUAL() {
        delete expr_izq;
        delete expr_der;
    }

    elene_MAYORIGUAL &operator = (const elene_MAYORIGUAL &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};


/* Clase para el distinto a */
class elene_DISTINTO : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Distinto:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_DISTINTO(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_DISTINTO(const elene_DISTINTO &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_DISTINTO() {
        delete expr_izq;
        delete expr_der;
    }

    elene_DISTINTO &operator = (const elene_DISTINTO &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};

/* Clase para el igual a */
class elene_IGUAL : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Distinto:\n" 
                   << "  Expr Izq:\n" << (*expr_izq)
                   << "  Expr Der:\n" << (*expr_der));
    }

public:

    /* Constructor */
    elene_IGUAL(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_IGUAL(const elene_IGUAL &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_IGUAL() {
        delete expr_izq;
        delete expr_der;
    }

    elene_IGUAL &operator = (const elene_IGUAL &other) {

        if (&other != this) {

            delete expr_izq;
            delete expr_der;
            expr_izq = other.expr_izq;
            expr_der = other.expr_der;

        }
    }
};

/**********************************************************/
/***** EXPRESIONES UNARIAS ********************************/
/**********************************************************/

class elene_EXPRUNARIA : public elene_EXPR {

protected:
    elene_EXPR* expr;
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    /* Declaracion de constructor */
    elene_EXPRUNARIA() {};
    elene_EXPRUNARIA(elene_EXPR* E):expr(E) {};
    /* Declaracion de destructor */
    virtual ~elene_EXPRUNARIA () {}

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_EXPRUNARIA& obj) { 
        return obj.stream_write(stream); 
    }
};


/* Clase para el menos unario */
class elene_MENOSUNARIO : public elene_EXPRUNARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Menos Unario:\n" 
                   << "  Expr:\n" << (*expr));
    }

public:

    /* Constructor */
    elene_MENOSUNARIO(elene_EXPR* E): elene_EXPRUNARIA(E) {}

    /* Metodo para copiar */
    elene_MENOSUNARIO(const elene_MENOSUNARIO &other) {
        expr = other.expr;
    }

    /* Metodo destructor */
    virtual ~elene_MENOSUNARIO() {
        delete expr;
    }

    elene_MENOSUNARIO &operator = (const elene_MENOSUNARIO &other) {

        if (&other != this) {

            delete expr;
            expr = other.expr;

        }
    }
};


/* Clase para la negacion booleana */
class elene_NEGACION : public elene_EXPRUNARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Menos Unario:\n" 
                   << "  Expr:\n" << (*expr));
    }

public:

    /* Constructor */
    elene_NEGACION(elene_EXPR* E): elene_EXPRUNARIA(E) {}

    /* Metodo para copiar */
    elene_NEGACION(const elene_NEGACION &other) {
        expr = other.expr;
    }

    /* Metodo destructor */
    virtual ~elene_NEGACION() {
        delete expr;
    }

    elene_NEGACION &operator = (const elene_NEGACION &other) {

        if (&other != this) {

            delete expr;
            expr = other.expr;

        }
    }
};


/*****************************************************************/
/******* TERMINALES **********************************************/
/*****************************************************************/

/* Clase para el terminal */
class elene_EXPRTERMINAL : public elene_EXPR {

protected:
    std::string* nombre;
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    /* Declaracion de constructor */
    elene_EXPRTERMINAL() {};
    elene_EXPRTERMINAL(std::string* nomb) {};
    /* Declaracion de destructor */
    virtual ~elene_EXPRTERMINAL () {}

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_EXPRTERMINAL& obj) { 
        return obj.stream_write(stream); 
    }
};

/* Clase para el id */
class elene_ID : public elene_EXPRTERMINAL { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Id:\n" 
                   << "  Nombre:\n" << (nombre));
    }

public:

    /* Constructor */
    elene_ID(std::string* nomb) {}

    /* Metodo para copiar */
    elene_ID(const elene_ID &other) {
        nombre = other.nombre;
    }

    /* Metodo destructor */
    virtual ~elene_ID() {
        delete nombre;
    }

    elene_ID &operator = (const elene_ID &other) {

        if (&other != this) {

            delete nombre;
            nombre = other.nombre;

        }
    }
};

/*****************************************************************/
/******* INSTRUCCIONES *******************************************/
/*****************************************************************/

class elene_INST /* : public printable */ {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_INST& obj){
        return obj.stream_write(stream); 
    }
};


/* Clase para la lectura */
class elene_INSTLEER : public elene_INST {

protected:

    elene_ID* id;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Instruccion Leer:\n" 
                   << "  ID:\n" << (*id));
    }

public:
    /* Declaracion de constructor */
    elene_INSTLEER() {};
    elene_INSTLEER(elene_ID* identrada): id(identrada) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTLEER () {
        delete id;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_INSTLEER& obj) { 
        return obj.stream_write(stream); 
    }
};


/* Clase para la escritura */
class elene_INSTESCR : public elene_INST {

protected:

    elene_ID* id;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Instruccion Escribir:\n" 
                   << "  ID:\n" << (*id));
    }

public:
    /* Declaracion de constructor */
    elene_INSTESCR() {};
    elene_INSTESCR(elene_ID* identrada): id(identrada) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTESCR () {
        delete id;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_INSTESCR& obj) { 
        return obj.stream_write(stream); 
    }
};

/* Clase para el condicional */
/* Falta la parte del else y sus relativos */
class elene_INSTCOND : public elene_INST {

protected:

    elene_EXPR* condicion;
    elene_EXPR* bloque;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Instruccion Condicional:\n" 
                   << "  Condicion:\n" << (*condicion)
                   << "  Bloque:\n" << (*bloque));
    }

public:
    /* Declaracion de constructor */
    elene_INSTCOND() {};
    elene_INSTCOND(elene_EXPR* cond, elene_EXPR* blq): condicion(cond), bloque(blq) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTCOND () {
        delete condicion;
        delete bloque;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_INSTCOND& obj) { 
        return obj.stream_write(stream); 
    }
};


/* Clase para el condicional */
class elene_INSTASIG : public elene_INST {

protected:

    elene_ID* id;
    elene_EXPR* ladoDer;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Instruccion Asignacion:\n" 
                   << "  Variable:\n" << (*id)
                   << "  Expresion izquierda:\n" << (*ladoDer));
    }

public:
    /* Declaracion de constructor */
    elene_INSTASIG() {};
    elene_INSTASIG(elene_ID* variable, elene_EXPR* rvalue): id(variable), ladoDer(rvalue) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTASIG () {
        delete id;
        delete ladoDer;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_INSTASIG& obj) { 
        return obj.stream_write(stream); 
    }
};


# endif
