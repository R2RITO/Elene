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
/* Pendiente con ese string*, fue para que no chillara g++
   ademas de que no es seguro que solo un string con el nombre sea el miembro */
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
    std::string texto;
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Id:\n" 
                   << "  Texto:\n" << (texto));
    }

public:

    /* Constructor */
    elene_ID(std::string texto) {}

    /* Metodo para copiar */
    elene_ID(const elene_ID &other) {
        texto = other.texto;
        nombre = other.nombre;
    }

    /* Metodo destructor */
    virtual ~elene_ID() {
        delete nombre;
        texto.clear();
    }

    elene_ID &operator = (const elene_ID &other) {

        if (&other != this) {

            delete nombre;
            texto.clear();
            nombre = other.nombre;
            texto = other.texto;
        }
    }
};

/* Clase para los terminales booleanos */
class elene_BOOLEANO : public elene_EXPRTERMINAL { 

protected:

    int valor;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Constante Booleana:\n" 
                   << "  Valor:\n" << (valor));
    }

public:

    /* Constructor */
    elene_BOOLEANO(int valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_BOOLEANO(const elene_BOOLEANO &other) {
        nombre = other.nombre;
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_BOOLEANO() {
        delete nombre;
    }

    elene_BOOLEANO &operator = (const elene_BOOLEANO &other) {

        if (&other != this) {

            delete nombre;
            nombre = other.nombre;
            valor  = other.valor;
        }
    }
};

/* Clase para los terminales enteros */
class elene_ENTERO : public elene_EXPRTERMINAL { 

protected:

    int valor;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Constante Entera:\n" 
                   << "  Valor:\n" << (valor));
    }

public:

    /* Constructor */
    elene_ENTERO(int valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_ENTERO(const elene_ENTERO &other) {
        nombre = other.nombre;
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_ENTERO() {
        delete nombre;
    }

    elene_ENTERO &operator = (const elene_ENTERO &other) {

        if (&other != this) {

            delete nombre;
            nombre = other.nombre;
            valor  = other.valor;
        }
    }
};


/* Clase para los terminales reales */
class elene_REAL : public elene_EXPRTERMINAL { 

protected:

    float valor;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Constante Real:\n" 
                   << "  Valor:\n" << (valor));
    }

public:

    /* Constructor */
    elene_REAL(float valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_REAL(const elene_REAL &other) {
        nombre = other.nombre;
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_REAL() {
        delete nombre;
    }

    elene_REAL &operator = (const elene_REAL &other) {

        if (&other != this) {

            delete nombre;
            nombre = other.nombre;
            valor  = other.valor;
        }
    }
};


/* Clase para los terminales caracteres */
class elene_CARACTER : public elene_EXPRTERMINAL { 

protected:

    char valor;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Constante Caracter:\n" 
                   << "  Valor:\n" << (valor));
    }

public:

    /* Constructor */
    elene_CARACTER(char valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_CARACTER(const elene_CARACTER &other) {
        nombre = other.nombre;
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_CARACTER() {
        delete nombre;
    }

    elene_CARACTER &operator = (const elene_CARACTER &other) {

        if (&other != this) {

            delete nombre;
            nombre = other.nombre;
            valor  = other.valor;
        }
    }
};


/* Clase para los terminales String */
class elene_STRING : public elene_EXPRTERMINAL { 

protected:

    std::string valor;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Cadena de caracteres:\n" 
                   << "  Valor:\n" << (valor));
    }

public:

    /* Constructor */
    elene_STRING(std::string valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_STRING(const elene_STRING &other) {
        nombre = other.nombre;
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_STRING() {
        delete nombre;
        valor.clear();
    }

    elene_STRING &operator = (const elene_STRING &other) {

        if (&other != this) {

            delete nombre;
            valor.clear();
            nombre = other.nombre;
            valor  = other.valor;
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




/*****************************************************************/
/******* LISTA DE INSTRUCCIONES **********************************/
/*****************************************************************/

/* Notar que tal vez no sea necesaria la clase abstracta y las dos implementaciones
   ya que se puede hacer solo una concreta que tenga los dos casos */

/* Clase abstracta para la lista de instrucciones */

class elene_LISTAINST /* : public printable */ {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTAINST& obj){
        return obj.stream_write(stream); 
    }
};


/* Clase para la lista de instrucciones con una instruccion */
class elene_LISTAUNIT : public elene_LISTAINST {

protected:

    elene_INST* instruccion;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Lista de Instrucciones:\n" 
                   << "  Instruccion:\n" << (*instruccion));
    }

public:
    /* Declaracion de constructor */
    elene_LISTAUNIT() {};
    elene_LISTAUNIT(elene_INST* inst): instruccion(inst) {};
    
    /* Declaracion de destructor */
    virtual ~elene_LISTAUNIT () {
        delete instruccion;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTAUNIT& obj) { 
        return obj.stream_write(stream); 
    }
};


/* Clase para la lista de instrucciones recursiva */
class elene_LISTAMULT : public elene_LISTAINST {

protected:

    elene_INST* instruccion;
    elene_LISTAINST* resto;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Lista de Instrucciones:\n" 
                   << "  Instruccion:\n" << (*instruccion)
                   << "  Resto:\n" << (*resto));
    }

public:
    /* Declaracion de constructor */
    elene_LISTAMULT() {};
    elene_LISTAMULT(elene_INST* inst, elene_LISTAINST* rst): instruccion(inst), resto(rst) {};
    
    /* Declaracion de destructor */
    virtual ~elene_LISTAMULT () {
        delete instruccion;
        delete resto;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTAMULT& obj) { 
        return obj.stream_write(stream); 
    }
};

/*****************************************************************/
/******* TIPOS ***************************************************/
/*****************************************************************/
/*
tipo : BOOLEANO { $$ = "Bool"; }
     | ENTERO   { $$ = "Entero"; }
     | FLOTANTE { $$ = "Real"; }
     | CARACTER { $$ = "Char"; }
     | STRING   { $$ = "String";}
     | VACIO    { $$ = "Vacio"; }
     | ARREGLO DE tipo DE expr A expr { $$ = "Arreglo"; }
     | LPAREN tipo RPAREN { $$ = $2; }
     ;*/

class elene_TIPO /* : public printable */ {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO& obj){
        return obj.stream_write(stream); 
    }
};

class elene_TIPO_BOOLEANO : public elene_TIPO {

protected:

    std::string nombre;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Tipo:\n" 
                   << "  Nombre:" << (nombre)
                   << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_BOOLEANO() {};
    elene_TIPO_BOOLEANO(std::string nmb) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_BOOLEANO () {
        nombre.clear();
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO_BOOLEANO& obj) { 
        return obj.stream_write(stream); 
    }
};


class elene_TIPO_ENTERO : public elene_TIPO {

protected:

    std::string nombre;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Tipo:\n" 
                   << "  Nombre:" << (nombre)
                   << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_ENTERO() {};
    elene_TIPO_ENTERO(std::string nmb) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_ENTERO () {
        nombre.clear();
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO_ENTERO& obj) { 
        return obj.stream_write(stream); 
    }
};


class elene_TIPO_FLOTANTE : public elene_TIPO {

protected:

    std::string nombre;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Tipo:\n" 
                   << "  Nombre:" << (nombre)
                   << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_FLOTANTE() {};
    elene_TIPO_FLOTANTE(std::string nmb) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_FLOTANTE () {
        nombre.clear();
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO_FLOTANTE& obj) { 
        return obj.stream_write(stream); 
    }
};


class elene_TIPO_CARACTER : public elene_TIPO {

protected:

    std::string nombre;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Tipo:\n" 
                   << "  Nombre:" << (nombre)
                   << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_CARACTER() {};
    elene_TIPO_CARACTER(std::string nmb) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_CARACTER () {
        nombre.clear();
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO_CARACTER& obj) { 
        return obj.stream_write(stream); 
    }
};


class elene_TIPO_STRING : public elene_TIPO {

protected:

    std::string nombre;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Tipo:\n" 
                   << "  Nombre:" << (nombre)
                   << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_STRING() {};
    elene_TIPO_STRING(std::string nmb) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_STRING () {
        nombre.clear();
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO_STRING& obj) { 
        return obj.stream_write(stream); 
    }
};


class elene_TIPO_VACIO : public elene_TIPO {

protected:

    std::string nombre;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Tipo:\n" 
                   << "  Nombre:" << (nombre)
                   << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_VACIO() {};
    elene_TIPO_VACIO(std::string nmb) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_VACIO () {
        nombre.clear();
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO_VACIO& obj) { 
        return obj.stream_write(stream); 
    }
};


class elene_TIPO_ARREGLO : public elene_TIPO {

protected:

    elene_TIPO* tipo;
    elene_EXPR* indIzq;
    elene_EXPR* indDer;
    

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Arreglo:\n" 
                   << "  Tipo: " << (tipo)
                   << "\n"
                   << "  Limite Izquierdo: " << (indIzq)
                   << "\n"
                   << "  Limite Derecho: " << (indDer) << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_ARREGLO() {};
    elene_TIPO_ARREGLO(elene_TIPO* t, elene_EXPR* izq, elene_EXPR* der): tipo(t), indIzq(izq), indDer(der) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_ARREGLO () {
        delete tipo;
        delete indIzq;
        delete indDer;
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO_ARREGLO& obj) { 
        return obj.stream_write(stream); 
    }
};


/*****************************************************************/
/******* DECLARACION *********************************************/
/*****************************************************************/

class elene_DECLARACION {
protected:

    elene_ID* ID; 
    elene_TIPO* tipo;
    elene_EXPR* expr;
    virtual std::ostream& stream_write(std::ostream& os) const {
        if (expr != 0) {
            return (os << "Declaracion:\n" 
                       << " Variable:\n" << *ID
                       << " Tipo:\n" << tipo
                       << " Expresion:\n " << *expr);
        }
        return (os << "Declaracion:\n" 
                   << " Variable:\n" << *ID
                   << " Tipo:\n" << tipo);
    } 

public:
    /* Declaracion de constructor */
    elene_DECLARACION(elene_ID* ID, elene_TIPO* tipo, elene_EXPR* expr) {
        this -> ID = ID;
        this -> tipo = tipo;
        this -> expr = expr;
    }
    
    /* Declaracion de destructor */
    virtual ~elene_DECLARACION () {
        delete ID;
        delete tipo;
        delete expr;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_DECLARACION& obj) { 
        return obj.stream_write(stream); 
    }
};


/*****************************************************************/
/******* LISTA DE VARIABLES **************************************/
/*****************************************************************/

/* Notar que tal vez no sea necesaria la clase abstracta y las dos implementaciones
   ya que se puede hacer solo una concreta que tenga los dos casos */

/* Clase abstracta para la lista de variables */

class elene_LISTAVAR /* : public printable */ {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    elene_DECLARACION* dec;
    elene_LISTAVAR* resto;
    virtual std::ostream& stream_write(std::ostream& os) const {
        if (resto != 0) {
            return (os << "Lista Variables:\n" 
                       << " Declaracion:\n" << *dec
                       << " Resto:\n " << *resto);
        }
        return (os << "Lista Variables:\n" 
                   << " Declaracion:\n" << *dec);
    } 

public:
    /* Declaracion de constructor */
    elene_LISTAVAR(elene_DECLARACION* dec, elene_LISTAVAR* resto) {
        this -> dec = dec;
    }
    
    /* Declaracion de destructor */
    virtual ~elene_LISTAVAR() {
        delete dec;
        delete resto;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTAVAR& obj) { 
        return obj.stream_write(stream); 
    }

};



/* Clase para la lista de variables con declaraciones */
/* Ese elene_EXPR es elene_listaVariables o como se vaya a llamar */
class elene_BLOQUE {

protected:

    elene_LISTAVAR* listaVariables;
    elene_LISTAINST* listaInstruccion;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
        if (listaVariables != 0) { 
            return (os << "Bloque:\n"
                   << " Lista de Declaraciones:\n" << (*listaVariables) 
                   << " Lista de Instrucciones:\n" << (*listaInstruccion));    
        }              
        return (os << "Bloque:\n"
                   << " Lista de Instrucciones:\n" << (*listaInstruccion));
    }

public:
    /* Declaracion de constructor */
    elene_BLOQUE() {};
    elene_BLOQUE(elene_LISTAVAR* var, elene_LISTAINST* inst): listaVariables(var), listaInstruccion(inst) {};
    
    /* Declaracion de destructor */
    virtual ~elene_BLOQUE () {
        delete listaVariables;
        delete listaInstruccion;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_BLOQUE& obj) { 
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

    elene_EXPR* expr;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Instruccion Escribir:\n" 
                   << "  Expr:\n" << (*expr));
    }

public:
    /* Declaracion de constructor */
    elene_INSTESCR() {};
    elene_INSTESCR(elene_EXPR* E): expr(E) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTESCR () {
        delete expr;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_INSTESCR& obj) { 
        return obj.stream_write(stream); 
    }
};

/* Clase para el condicional */
/* Falta la parte del else y sus relativos */
/* Ese bloque es un elene_BLOQUE que no existe aun */
class elene_INSTCOND : public elene_INST {

protected:

    elene_EXPR* condicion;
    elene_BLOQUE* bloque;
    elene_INSTCOND* sig;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        os << "Instruccion Condicional:\n" 
           << "  Condicion:\n" << (*condicion)
           << "  Bloque:\n" << (*bloque);
 
        if (sig != 0) {
            os << "  Else/Else if:\n" << (*sig);
        }
    
        return os;
    }

public:
    /* Declaracion de constructor */
    elene_INSTCOND() {};
    elene_INSTCOND(elene_EXPR* cond, elene_BLOQUE* blq, elene_INSTCOND* s): condicion(cond), bloque(blq), sig(s) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTCOND () {
        delete condicion;
        delete bloque;
        delete sig;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_INSTCOND& obj) { 
        return obj.stream_write(stream); 
    }
};


/* Clase para la asignacion */
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


/* Clase para la iteracion indeterminada */
/* Ese bloque es elene_BLOQUE */
/* ALERTA: Lo que le sigue al guail es un bloque a juro? no puede ser inst directo? pensar esto <---- */
class elene_INSTMIENTRAS : public elene_INST {

protected:

    elene_EXPR* condicion;
    elene_BLOQUE* bloque; 

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Instruccion Mientras:\n" 
                   << "  Condicion:\n" << (*condicion)
                   << "  Bloque:\n" << (*bloque));
    }

public:
    /* Declaracion de constructor */
    elene_INSTMIENTRAS() {};
    elene_INSTMIENTRAS(elene_EXPR* cond, elene_BLOQUE* blq): condicion(cond), bloque(blq) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTMIENTRAS () {
        delete condicion;
        delete bloque;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_INSTMIENTRAS& obj) { 
        return obj.stream_write(stream); 
    }
};


/* Clase para la iteracion determinada */
/* Ese bloque es elene_BLOQUE */
class elene_INSTPARA : public elene_INST {

protected:

    elene_INSTASIG* asignacion;
    elene_EXPR* condicion;
    elene_INSTASIG* cambio;
    elene_BLOQUE* bloque; 

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Instruccion Para:\n" 
                   << "  Asignacion:\n" << (*asignacion)
                   << "  Condicion:\n" << (*condicion)
                   << "  Cambio:\n" << (*cambio)
                   << "  Bloque:\n" << (*bloque));
    }

public:
    /* Declaracion de constructor */
    elene_INSTPARA() {};
    elene_INSTPARA(elene_INSTASIG* asig, elene_EXPR* cond, elene_INSTASIG* cmb, elene_BLOQUE* blq): 
                asignacion(asig), condicion(cond), cambio(cmb), bloque(blq) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTPARA () {
        delete asignacion;        
        delete condicion;
        delete cambio;
        delete bloque;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_INSTPARA& obj) { 
        return obj.stream_write(stream); 
    }
};
/*****************************************************************/
/******* LISTA DE ARGUMENTOS *************************************/
/*****************************************************************/

/*listArg : tipo ID
        | tipo POR REFERENCIA ID
        | tipo POR REFERENCIA ID COMMA listArg
        | tipo ID COMMA listArg
        ;*/

/* Argumento al estilo int X, primera regla de gramatica */
class elene_LISTARG {

protected:

    elene_TIPO* tipo;
    elene_ID* id;
    elene_LISTARG* resto;
    std::string ref;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {    
        if (resto == 0) {
            return (os << "Lista de Argumentos:\n" 
                   << "  Tipo:" << (*tipo)
                   << "  ID:" << (*id)
                   << "  Modo: " << ref
                   << "\n");
        }          
        return (os << "Lista de Argumentos:\n" 
                   << "  Tipo:" << (*tipo)
                   << "  ID:" << (*id)
                   << "  Modo: " << ref
                   << "  " << (*resto)
                   << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_LISTARG() {};
    elene_LISTARG(elene_TIPO* t, elene_ID* i, std::string mod, elene_LISTARG* r): tipo(t), id(i), ref(mod), resto(r) {};
    
    /* Declaracion de destructor */
    virtual ~elene_LISTARG() {
        delete tipo;        
        delete id;
        delete resto;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTARG& obj) { 
        return obj.stream_write(stream); 
    }
};

/*****************************************************************/
/******* DECLARACION FUNCIONES ***********************************/
/*****************************************************************/

class elene_DECFUNCION {

protected:

    elene_ID* nombre;
    elene_LISTARG* parametros;
    elene_TIPO* retorno;
    elene_BLOQUE* bloque;
 
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        os << "Declaracion de Funcion:\n" 
           << "  Nombre:\n" << (*nombre);

        if (parametros != 0) {
            os << "  Parametros:\n" << (*parametros);
        }

        if (retorno != 0) {
            os << "  Tipo de Retorno:\n" << (*retorno);
        }

        os << "  Bloque:\n" << (*bloque);
        return os;
    }

public:

    /* Declaracion de constructor */
    elene_DECFUNCION() {};

    elene_DECFUNCION(elene_ID* nmb, elene_LISTARG* param, elene_TIPO* ret, elene_BLOQUE* blq): nombre(nmb), parametros(param), retorno(ret), bloque(blq) {};

    /* Declaracion de destructor */
    virtual ~elene_DECFUNCION () {

        delete nombre;
        delete parametros;
        delete retorno;
        delete bloque;
    }

    /* Metodo para copiar*/ 
    elene_DECFUNCION(const elene_DECFUNCION &other) {

        nombre = other.nombre;
        parametros = other.parametros;
        retorno = other.retorno;
        bloque = other.bloque;
    }

    elene_DECFUNCION &operator = (const elene_DECFUNCION &other) {

        if (&other != this) {
            delete nombre;
            delete parametros;
            delete retorno;
            delete bloque;
            nombre = other.nombre;
            parametros = other.parametros;
            retorno = other.retorno;
            bloque = other.bloque;
        }
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_DECFUNCION& obj) { 
        return obj.stream_write(stream); 
    }
};



/*****************************************************************/
/******* LISTA DE FUNCIONES  *************************************/
/*****************************************************************/


/* Argumento al estilo int X, primera regla de gramatica */
class elene_LISTFUN {

protected:

    elene_DECFUNCION* fun;
    elene_LISTFUN* resto;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {    
        if (resto == 0) {
            return (os << "Lista de Funciones:\n" 
                   << "  Funcion:" << (*fun)
                   << "\n");
        }          
        return (os << "Lista de Argumentos:\n" 
                   << "  Funcion:" << (*fun)
                   << "  " << (*resto)
                   << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_LISTFUN() {};
    elene_LISTFUN(elene_DECFUNCION* f, elene_LISTFUN* l): fun(f), resto(l) {};
    
    /* Declaracion de destructor */
    virtual ~elene_LISTFUN() {
        delete fun;
        delete resto;    
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTFUN& obj) { 
        return obj.stream_write(stream); 
    }
};




# endif
