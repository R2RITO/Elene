# ifndef ELENE_CLASES_HH
# define ELENE_CLASES_HH

# include <string>
# include <list>
# include <map>
# include <iostream>

/***************************************************************/
/****** PRINTABLE **********************************************/
/***************************************************************/

class printable { 

public:
	std::string ident;
};

/*****************************************************************/
/******* TIPOS ***************************************************/
/*****************************************************************/

class elene_TIPO : public printable {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    int tam;
    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_TIPO& obj){
        return obj.stream_write(stream); 
    }
};

/***************************************************************/
/****** EXPRESIONES ********************************************/
/***************************************************************/

class elene_EXPR : public printable {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
	elene_TIPO* tipo;
    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_EXPR& obj){
        return obj.stream_write(stream); 
    }

    bool verificar_tipos_case(elene_TIPO* t) {
        return (tipo == t);
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Conjuncion: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Disyuncion: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Adicion: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Sustraccion: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Multiplicacion: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Division: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Mayor que: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Menor que: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Menor o igual: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Mayor o igual: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Distinto: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Igual: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
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

/* Clase para el operador de acceso a estructuras*/
class elene_ACCESO : public elene_EXPRBINARIA { 

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*expr_izq).ident = ident + "    ";
		(*expr_der).ident = ident + "    ";             
        return (os << ident << "Acceso a estructura: {\n" 
                   << ident+"  " << "Expr Izq:\n" << (*expr_izq)
                   << ident+"  " << "Expr Der:\n" << (*expr_der))
				   << ident << "}\n";
    }

public:

    /* Constructor */
    elene_ACCESO(elene_EXPR* izq, elene_EXPR* der): elene_EXPRBINARIA(izq, der) {}

    /* Metodo para copiar */
    elene_ACCESO(const elene_ACCESO &other) {
        expr_izq = other.expr_izq;
        expr_der = other.expr_der;
    }

    /* Metodo destructor */
    virtual ~elene_ACCESO() {
        delete expr_izq;
        delete expr_der;
    }

    elene_ACCESO &operator = (const elene_ACCESO &other) {

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
		(*expr).ident = ident + "    ";         
        return (os << ident << "Menos Unario: {\n" 
                   << ident+"  " << "Expr:\n" << (*expr)
				   << ident << "}\n");
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
		(*expr).ident = ident + "    ";         
        return (os << ident << "Negacion: {\n" 
                   << ident+"  " << "Expr:\n" << (*expr)
				   << ident << "}\n");
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
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
    /* Declaracion de constructor */
    elene_EXPRTERMINAL() {};
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
    std::string nombre;
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << ident << (nombre) << "\n");
    }

public:

    /* Constructor */
    elene_ID(std::string t) : nombre(t) {}

    /* Metodo para copiar */
    elene_ID(const elene_ID &other) {
        nombre = other.nombre;
    }

    /* Metodo destructor */
    virtual ~elene_ID() {
        nombre.clear();
    }

	bool equals(std::string name) {

		return (name.compare(nombre) == 0);
	}

    elene_ID &operator = (const elene_ID &other) {

        if (&other != this) {
            nombre.clear();
            nombre = other.nombre;
        }
    }
};


/*****************************************************************/
/******* LISTA DE EXPRESIONES ************************************/
/*****************************************************************/

/* Argumento al estilo int X, primera regla de gramatica */
class elene_LISTAEXPR : public printable {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {    
		if (resto != 0) {
			(*resto).ident = ident;
            os << (*resto);
        }

		(*expr).ident = ident+"  ";
        os << ident << "Arg: {\n" 
		   << (*expr) << ident << "}\n";
        return os;

    }

public:

    elene_EXPR* expr;
    elene_LISTAEXPR* resto;
	elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_LISTAEXPR() {};
    elene_LISTAEXPR(elene_EXPR* e, elene_LISTAEXPR* r): expr(e), resto(r) {};
    
    /* Declaracion de destructor */
    virtual ~elene_LISTAEXPR() {
        delete expr;        
        delete resto;    
    }

    /* Metodo para copiar */
    elene_LISTAEXPR(const elene_LISTAEXPR &other) {
        expr = other.expr;
        resto = other.resto;
    }

    elene_LISTAEXPR &operator = (const elene_LISTAEXPR &other) {
        if (&other != this) {
            delete expr;        
            delete resto;
            expr = other.expr;
            resto = other.resto;
        }
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTAEXPR& obj) { 
        return obj.stream_write(stream); 
    }
};



/* Clase para manejar la llamada de funciones */
class elene_EXPRFUNC : public elene_EXPRTERMINAL {

protected:

    elene_ID* nombre;
    elene_LISTAEXPR* args; 

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*nombre).ident = ident+"    ";
        os << ident << "Llamada a funcion: {\n" 
           << ident+"  " << "Nombre: \n" << (*nombre);
		if (args) {
			(*args).ident = ident + "    ";
        	os << ident+"  " << "Argumentos:\n" << (*args);
		}
		os << ident << "}\n";
		return os;
    }

public:
    /* Declaracion de constructor */
    elene_EXPRFUNC() {};
    elene_EXPRFUNC(elene_ID* i, elene_LISTAEXPR* a): nombre(i), args(a) {};
    
    /* Declaracion de destructor */
    virtual ~elene_EXPRFUNC () {
        delete nombre;
        delete args;
    }

    /* Metodo para copiar */
    elene_EXPRFUNC(const elene_EXPRFUNC &other) {
        nombre = other.nombre;
        args = other.args;
    }

    elene_EXPRFUNC &operator = (const elene_EXPRFUNC &other) {
        if (&other != this) {
            delete nombre;
            delete args;
            nombre = other.nombre;
            args = other.args;
        }
    }
};


/*-------------------------------------------------------------*/
/*----- EXPRESION PARA ACCEDER A ARREGLOS ---------------------*/
/*-------------------------------------------------------------*/


class elene_ACCARREG : public elene_EXPR {

protected:
    
    elene_ID* arrayID;
    elene_EXPR* expr;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*expr).ident = ident + "    ";
		(*arrayID).ident = ident+"    ";
        return (os << ident << "Acceso a arreglo: {\n"
                   << ident+"  " << "ID del Arreglo:\n" << (*arrayID)
                   << ident+"  " << "Expresion del acceso:\n" << (*expr)) 
				   << ident << "}\n";
    }

public:

    /* Constructor */
    elene_ACCARREG(elene_ID* a, elene_EXPR* e): arrayID(a), expr(e) {}

    /* Metodo para copiar */
    elene_ACCARREG(const elene_ACCARREG &other) {
        arrayID = other.arrayID;
        expr = other.expr;
    }

    /* Metodo destructor */
    virtual ~elene_ACCARREG() {
        delete arrayID;
        delete expr;
    }

    elene_ACCARREG &operator = (const elene_ACCARREG &other) {

        if (&other != this) {

            delete arrayID;
            delete expr;
            arrayID = other.arrayID;
            expr = other.expr;

        }
    }
    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_ACCARREG& obj){
        return obj.stream_write(stream); 
    }
};
/* Clase para los terminales booleanos */
class elene_BOOLEANO : public elene_EXPRTERMINAL { 

protected:

    int valor;
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << ident << "Constante Booleana: {\n" 
                   << ident+"  " << "Valor:" << (valor)
				   << "\n" << ident << "}\n");
    }

public:

    /* Constructor */
    elene_BOOLEANO(int valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_BOOLEANO(const elene_BOOLEANO &other) {
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_BOOLEANO() {}

    elene_BOOLEANO &operator = (const elene_BOOLEANO &other) {

        if (&other != this) {
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
        return (os << ident << "Constante Entero: {\n" 
                   << ident+"  " << "Valor:" << (valor)
				   << "\n" << ident << "}\n");
    }

public:

    /* Constructor */
    elene_ENTERO(int valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_ENTERO(const elene_ENTERO &other) {
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_ENTERO() { }

    elene_ENTERO &operator = (const elene_ENTERO &other) {

        if (&other != this) {
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
        return (os << ident << "Constante Real: {\n" 
                   << ident+"  " << "Valor:" << (valor)
				   << "\n" << ident << "}\n");
    }

public:

    /* Constructor */
    elene_REAL(float valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_REAL(const elene_REAL &other) {
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_REAL() { }

    elene_REAL &operator = (const elene_REAL &other) {

        if (&other != this) {
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
        return (os << ident << "Constante Caracter: {\n" 
                   << ident+"  " << "Valor:" << (valor)
				   << "\n" << ident << "}\n");
    }

public:

    /* Constructor */
    elene_CARACTER(char valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_CARACTER(const elene_CARACTER &other) {
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_CARACTER() { }

    elene_CARACTER &operator = (const elene_CARACTER &other) {

        if (&other != this) {
            valor  = other.valor;
        }
    }
};


/* Clase para los terminales String */
class elene_STRING : public elene_EXPRTERMINAL { 

protected:

    std::string valor;

    /* Metodo para imprimir */
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << ident << "Constante String: {\n" 
                   << ident+"  " << "Valor:" << (valor)
				   << "\n" << ident << "}\n");
    }

public:

    /* Constructor */
    elene_STRING(std::string valor) {
        this -> valor = valor;
    }

    /* Metodo para copiar */
    elene_STRING(const elene_STRING &other) {
        valor  = other.valor;
    }

    /* Metodo destructor */
    virtual ~elene_STRING() {
        valor.clear();
    }

    elene_STRING &operator = (const elene_STRING &other) {

        if (&other != this) {
            valor.clear();
            valor  = other.valor;
        }
    }
};


/*****************************************************************/
/******* INSTRUCCIONES *******************************************/
/*****************************************************************/

class elene_INST : public printable {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
	elene_TIPO* tipo;
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

class elene_LISTAINST : public printable {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    virtual std::ostream& stream_write(std::ostream& os) const = 0; 

public:
	elene_TIPO* tipo;
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
		(*instruccion).ident = ident + "  ";           
        return (os << ident << "Instruccion: {\n" << (*instruccion)
				   << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_LISTAUNIT() {};
    elene_LISTAUNIT(elene_INST* inst): instruccion(inst) {};
    
    /* Declaracion de destructor */
    virtual ~elene_LISTAUNIT () {
        delete instruccion;    
    }

    /* Metodo para copiar */
    elene_LISTAUNIT(const elene_LISTAUNIT &other) {
        instruccion = other.instruccion;
    }

    elene_LISTAUNIT &operator = (const elene_LISTAUNIT &other) {
        if (&other != this) {
            delete instruccion;
            instruccion = other.instruccion;
        }
    }

};


/* Clase para la lista de instrucciones recursiva */
class elene_LISTAMULT : public elene_LISTAINST {

protected:

    elene_INST* instruccion;
    elene_LISTAINST* resto;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*resto).ident = ident;
		(*instruccion).ident = ident+"  ";   
        return (os << (*resto)
                   << ident << "Instruccion: {\n" << (*instruccion)
                   << ident << "}\n");
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

    /* Metodo para copiar */
    elene_LISTAMULT(const elene_LISTAMULT &other) {
        instruccion = other.instruccion;
        resto = other.resto;
    }

    elene_LISTAMULT &operator = (const elene_LISTAMULT &other) {
        if (&other != this) {
            delete instruccion;
            delete resto;
            instruccion = other.instruccion;
            resto = other.resto;
        }
    }
};



/* Clase para manejar tipos de datos simples (Todos menos los arreglos) */
class elene_TIPO_ENTERO : public elene_TIPO {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << ident << "Entero" << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_ENTERO() {
        tam = 4;
    };
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_ENTERO () { }
    
    /* Metodo para copiar */
    elene_TIPO_ENTERO(const elene_TIPO_ENTERO &other) { }

    elene_TIPO_ENTERO &operator = (const elene_TIPO_ENTERO &other) { }

};

/* Clase para manejar tipos de datos simples (Todos menos los arreglos) */
class elene_TIPO_BOOLEANO : public elene_TIPO {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Booleano");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_BOOLEANO() {
        tam = 1;
    };
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_BOOLEANO () { }
    
    /* Metodo para copiar */
    elene_TIPO_BOOLEANO(const elene_TIPO_BOOLEANO &other) { }

    elene_TIPO_BOOLEANO &operator = (const elene_TIPO_BOOLEANO &other) { }

};

/* Clase para manejar tipos de datos simples (Todos menos los arreglos) */
class elene_TIPO_FLOTANTE : public elene_TIPO {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Flotante");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_FLOTANTE() {
        tam = 1;
    };
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_FLOTANTE () { }
    
    /* Metodo para copiar */
    elene_TIPO_FLOTANTE(const elene_TIPO_FLOTANTE &other) { }

    elene_TIPO_FLOTANTE &operator = (const elene_TIPO_FLOTANTE &other) { }

};

/* Clase para manejar tipos de datos simples (Todos menos los arreglos) */
class elene_TIPO_CARACTER : public elene_TIPO {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {          
        return (os << ident << "Caracter" << "\n");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_CARACTER() {
        tam = 1;    
    };
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_CARACTER () { }
    
    /* Metodo para copiar */
    elene_TIPO_CARACTER(const elene_TIPO_CARACTER &other) { }

    elene_TIPO_CARACTER &operator = (const elene_TIPO_CARACTER &other) { }

};

/* Clase para manejar tipos de datos simples (Todos menos los arreglos) */
class elene_TIPO_STRING : public elene_TIPO {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "String");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_STRING() {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_STRING () { }
    
    /* Metodo para copiar */
    elene_TIPO_STRING(const elene_TIPO_STRING &other) { }

    elene_TIPO_STRING &operator = (const elene_TIPO_STRING &other) { }

};

/* Clase para manejar tipos de datos simples (Todos menos los arreglos) */
class elene_TIPO_VACIO : public elene_TIPO {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Vacio");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_VACIO() {
        tam = 0;
    };
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_VACIO () { }
    
    /* Metodo para copiar */
    elene_TIPO_VACIO(const elene_TIPO_VACIO &other) { }

    elene_TIPO_VACIO &operator = (const elene_TIPO_VACIO &other) { }

};

/* Clase para manejar tipos de datos simples (Todos menos los arreglos) */
class elene_TIPO_TYPE_ERROR : public elene_TIPO {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Type Error");
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_TYPE_ERROR() {
        tam = 0;
    };
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_TYPE_ERROR () { }
    
    /* Metodo para copiar */
    elene_TIPO_TYPE_ERROR(const elene_TIPO_TYPE_ERROR &other) { }

    elene_TIPO_TYPE_ERROR &operator = (const elene_TIPO_TYPE_ERROR &other) { }

};



/* Clase para manejar el tipo de datos de arreglos */
class elene_TIPO_ARREGLO : public elene_TIPO {

protected:

    
    int indIzq;
    int indDer;
    

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << ident << "Arreglo\n"); 
                  /* << "  Tipo: " << (*tipo)
                   << "\n"
                   << "  Limite Izquierdo: " << (*indIzq)
                   << "\n"
                   << "  Limite Derecho: " << (*indDer) << "\n");*/
    }

public:
    elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_TIPO_ARREGLO() {};
    elene_TIPO_ARREGLO(elene_TIPO* t, int izq, int der): 
        tipo(t), indIzq(izq), indDer(der) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_ARREGLO () {
        delete tipo;
    }

    /* Metodo para copiar */
    elene_TIPO_ARREGLO(const elene_TIPO_ARREGLO &other) {
        tipo = other.tipo;
        indIzq = other.indIzq;
        indDer = other.indDer;
    }

    elene_TIPO_ARREGLO &operator = (const elene_TIPO_ARREGLO &other) {
        if (&other != this) {
            delete tipo;
            tipo = other.tipo;
            indIzq = other.indIzq;
            indDer = other.indDer;
        }
    }
};

/*****************************************************************/
/******* DECLARACION *********************************************/
/*****************************************************************/

class elene_DECLARACION : public printable {
protected:

    elene_ID* ID; 
    elene_EXPR* expr;
    virtual std::ostream& stream_write(std::ostream& os) const {
        (*ID).ident = ident+"    ";
        (*tipo).ident = ident+"    ";
        os << ident << "Declaracion: {\n" 
           << ident+"  " << "Variable: \n" << *ID
           << ident+"  " << "Tipo: \n" << *tipo;
        if (expr != 0) {
			(*expr).ident = ident+"    ";
            os << ident+"  " << "Expresion:\n " << *expr;
        }
		os << ident << "}\n";
        return os;
    } 

public:
	elene_TIPO* tipo;
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

    /* Metodo para copiar */
    elene_DECLARACION(const elene_DECLARACION &other) {
        ID = other.ID;
        tipo = other.tipo;
        expr = other.expr;
    }

    elene_DECLARACION &operator = (const elene_DECLARACION &other) {
        if (&other != this) {
            delete ID;
            delete tipo;
            delete expr;
            ID = other.ID;
            tipo = other.tipo;
            expr = other.expr;
        }
    }

	elene_TIPO* lookup_attr(std::string name) {
		if ((*ID).equals(name)) {
			return tipo;
		} else {
			return 0;
		}
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

class elene_LISTAVAR : public printable {

protected:
    /* Metodo para imprimir a ser sobreescrito por los hijos */
    elene_DECLARACION* dec;
    elene_LISTAVAR* resto;
    virtual std::ostream& stream_write(std::ostream& os) const {
		if (resto != 0) {
			(*resto).ident = ident;
            os << *resto;
        }
		(*dec).ident = ident+"  ";
        os << *dec;
        return os;
    } 

public:
	elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_LISTAVAR(elene_DECLARACION* dec, elene_LISTAVAR* resto) {
        this -> dec = dec;
        this -> resto = resto;
    }
    
    /* Declaracion de destructor */
    virtual ~elene_LISTAVAR() {
        delete dec;
        delete resto;    
    }

    /* Metodo para copiar */
    elene_LISTAVAR(const elene_LISTAVAR &other) {
        dec = other.dec;
        resto = other.resto;
    }

    elene_LISTAVAR &operator = (const elene_LISTAVAR &other) {
        if (&other != this) {
            delete dec;
            delete resto;
            dec = other.dec;
            resto = other.resto;
        }
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTAVAR& obj) { 
        return obj.stream_write(stream); 
    }

	elene_TIPO* lookup_attr(std::string name) {
		elene_TIPO* res = (*dec).lookup_attr(name);
		if (res != 0) {
			return res;
		} else {
			if (resto == 0) {
				return 0;
			}
			return (*resto).lookup_attr(name);
		}
	}

};


/* Clase para manejar los union */
class elene_TIPO_UNION : public elene_TIPO {

protected:

    elene_LISTAVAR* contenido; 
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << ident << "Union\n");
                   /*<< "Contenido: " << *contenido);*/
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_UNION() {};
    elene_TIPO_UNION(elene_LISTAVAR* c) : contenido(c) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_UNION () {
        delete contenido;
    }
    
    /* Metodo para copiar */
    elene_TIPO_UNION(const elene_TIPO_UNION &other) { 
        contenido = other.contenido;
    }

    elene_TIPO_UNION &operator = (const elene_TIPO_UNION &other) {
        if (&other != this) {
            delete contenido;
            contenido = other.contenido;
        }
    }

};

/* Clase para manejar las estructuras */
class elene_TIPO_ESTRUCTURA : public elene_TIPO {

protected:

    elene_LISTAVAR* contenido; 
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << ident << "Estructura\n");
                   /*<< "Contenido: " << *contenido);*/
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_ESTRUCTURA() {};
    elene_TIPO_ESTRUCTURA(elene_LISTAVAR* c) : contenido(c) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_ESTRUCTURA () {
        delete contenido;
    }
    
    /* Metodo para copiar */
    elene_TIPO_ESTRUCTURA(const elene_TIPO_ESTRUCTURA &other) { 
        contenido = other.contenido;
    }

    elene_TIPO_ESTRUCTURA &operator = (const elene_TIPO_ESTRUCTURA &other) {
        if (&other != this) {
            delete contenido;
            contenido = other.contenido;
        }
    }

	elene_TIPO* lookup_attr(std::string name) {
		return (*contenido).lookup_attr(name);
	}

};

/* Clase para manejar tipos definidos por el usuario*/
class elene_TIPO_DEFINIDO : public elene_TIPO {

protected:

    elene_ID* id;
    elene_TIPO* tipo;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << *id);
    }

public:
    /* Declaracion de constructor */
    elene_TIPO_DEFINIDO() {};
    elene_TIPO_DEFINIDO(elene_ID* t, elene_TIPO* tp): id(t), tipo(tp) {
        tam = (*tipo).tam;
    };
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_DEFINIDO () {
        delete id;
        delete tipo;
    }
    
    /* Metodo para copiar */
    elene_TIPO_DEFINIDO(const elene_TIPO_DEFINIDO &other) { 
        id = other.id;
        tipo = other.tipo;
    }

    elene_TIPO_DEFINIDO &operator = (const elene_TIPO_DEFINIDO &other) {
        if (&other != this) {
            delete id;
            id = other.id;
            delete tipo;
            tipo = other.tipo;
        }
    }

};

/* Clase para la lista de variables con declaraciones */
class elene_BLOQUE : public printable {

protected:

    elene_ID* etiqueta;
    elene_LISTAVAR* listaVariables;
    elene_LISTAINST* listaInstruccion;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		os << ident << "Bloque : {\n";
        if (etiqueta != 0) {
			(*etiqueta).ident = ident+"    ";
            os << ident+"  " << "Etiqueta del bloque: \n" 
			   << (*etiqueta);
        }
        if (listaVariables != 0) {
			(*listaVariables).ident = ident+"    ";			
            os << ident+"  " << "Lista de Declaraciones: {\n" 
			   << (*listaVariables) 
			   << ident+"  " << "}\n" ;   
        }
		(*listaInstruccion).ident = ident+"    ";
        os << ident+"  " << "Lista de Instrucciones: {\n" 
		   << (*listaInstruccion)
		   << ident+"  " << "}\n";
		os << ident << "}\n";
        return os;
    }

public:
	elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_BLOQUE() {};
    elene_BLOQUE(elene_ID* et, elene_LISTAVAR* var, elene_LISTAINST* inst): etiqueta(et), listaVariables(var), listaInstruccion(inst) {};
    
    /* Declaracion de destructor */
    virtual ~elene_BLOQUE () {
        delete etiqueta;
        delete listaVariables;
        delete listaInstruccion;    
    }

    /* Metodo para copiar */
    elene_BLOQUE(const elene_BLOQUE &other) {
        etiqueta = other.etiqueta;
        listaVariables = other.listaVariables;
        listaInstruccion = other.listaInstruccion;
    }

    elene_BLOQUE &operator = (const elene_BLOQUE &other) {
        if (&other != this) {
            delete etiqueta;
            delete listaVariables;
            delete listaInstruccion;
            etiqueta = other.etiqueta;
            listaVariables = other.listaVariables;
            listaInstruccion = other.listaInstruccion;
        }
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
		(*id).ident = ident + "    ";          
        return (os << ident << "Instruccion Leer: { \n" 
                   << ident+"  " << "ID: \n" << (*id)
				   << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_INSTLEER() {};
    elene_INSTLEER(elene_ID* identrada): id(identrada) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTLEER () {
        delete id;    
    }

    /* Metodo para copiar */
    elene_INSTLEER(const elene_INSTLEER &other) {
        id = other.id;
    }

    elene_INSTLEER &operator = (const elene_INSTLEER &other) {
        if (&other != this) {
            delete id;
            id = other.id;
        }
    }
};


/* Clase para la escritura */
class elene_INSTESCR : public elene_INST {

protected:

    elene_EXPR* expr;

	/* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*expr).ident = ident + "    ";          
        return (os << ident << "Instruccion Escribir: { \n" 
                   << ident+"  " << "Expr:\n" << (*expr)
				   << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_INSTESCR() {};
    elene_INSTESCR(elene_EXPR* E): expr(E) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTESCR () {
        delete expr;    
    }

    /* Metodo para copiar */
    elene_INSTESCR(const elene_INSTESCR &other) {
        expr = other.expr;
    }

    elene_INSTESCR &operator = (const elene_INSTESCR &other) {
        if (&other != this) {
            delete expr;
            expr = other.expr;
        }
    }
};

/* Clase para el return */
class elene_INSTRETORNAR : public elene_INST {

protected:

    elene_EXPR* expr;

	/* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*expr).ident = ident + "    ";          
        return (os << ident << "Instruccion Retornar: { \n" 
                   << ident+"  " << "Expr:\n" << (*expr)
				   << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_INSTRETORNAR() {};
    elene_INSTRETORNAR(elene_EXPR* E): expr(E) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTRETORNAR () {
        delete expr;    
    }

    /* Metodo para copiar */
    elene_INSTRETORNAR(const elene_INSTRETORNAR &other) {
        expr = other.expr;
    }

    elene_INSTRETORNAR &operator = (const elene_INSTRETORNAR &other) {
        if (&other != this) {
            delete expr;
            expr = other.expr;
        }
    }
};

/* Clase para el condicional */
class elene_INSTCOND : public elene_INST {

protected:

    elene_EXPR* condicion;
    elene_BLOQUE* bloque;
    elene_INSTCOND* sig;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const { 
		(*condicion).ident = ident+"    ";
		(*bloque).ident = ident+"  ";             
        os << ident << "Instruccion Condicional: {\n" 
           << ident+"  " << "Condicion:\n" << (*condicion)
           << (*bloque);
 
        if (sig != 0) {
			(*sig).ident = ident;
            os << ident+"  " << "Else/Else if:\n" << (*sig);
        }
    	os << ident << "}\n";
        return os;
    }

public:
    /* Declaracion de constructor */
    elene_INSTCOND() {};
    elene_INSTCOND(elene_EXPR* cond, elene_BLOQUE* blq, elene_INSTCOND* s): 
        condicion(cond), bloque(blq), sig(s) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTCOND () {
        delete condicion;
        delete bloque;
        delete sig;    
    }
    
    /* Metodo para copiar */
    elene_INSTCOND(const elene_INSTCOND &other) {
        condicion = other.condicion;
        bloque = other.bloque;
        sig = other.sig;
    }

    elene_INSTCOND &operator = (const elene_INSTCOND &other) {
        if (&other != this) {
            delete condicion;
            delete bloque;
            delete sig;
            condicion = other.condicion;
            bloque = other.bloque;
            sig = other.sig;
        }
    }
};


/* Clase para la asignacion */
class elene_INSTASIG : public elene_INST {

protected:

    elene_ID* id;
    elene_EXPR* ladoDer;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*ladoDer).ident = ident+"    ";
		(*id).ident = ident+"    ";          
        return (os << ident << "Instruccion Asignacion: {\n" 
                   << ident+"  " << "Variable:\n" << (*id)
                   << ident+"  " << "Expresion izquierda:\n" << (*ladoDer)
				   << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_INSTASIG() {};
    elene_INSTASIG(elene_ID* variable, elene_EXPR* rvalue): 
        id(variable), ladoDer(rvalue) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTASIG () {
        delete id;
        delete ladoDer;    
    }

    /* Metodo para copiar */
    elene_INSTASIG(const elene_INSTASIG &other) {
        id = other.id;
        ladoDer = other.ladoDer;
    }

    elene_INSTASIG &operator = (const elene_INSTASIG &other) {
        if (&other != this) {
            delete id;
            delete ladoDer;
            id = other.id;
            ladoDer = other.ladoDer;
        }
    }
};


/* Clase para la asignacion en arreglos */
class elene_INSTASIG_ARREGLO : public elene_INSTASIG {

protected:

    elene_ID* id;
    elene_EXPR* ladoDer;
    elene_EXPR* exprAcceso;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
        (*exprAcceso).ident = ident+"    ";
		(*ladoDer).ident = ident+"    ";
		(*id).ident = ident+"    ";          
        return (os << ident << "Instruccion Asignacion a arreglo: {\n" 
                   << ident+"  " << "Variable:\n" << (*id)
                   << ident+"  " << "Expresion Acceso:\n" << (*exprAcceso)
                   << ident+"  " << "Expresion:\n" << (*ladoDer)
				   << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_INSTASIG_ARREGLO() {};
    elene_INSTASIG_ARREGLO(elene_ID* variable, elene_EXPR* ea, elene_EXPR* rvalue): 
        id(variable), exprAcceso(ea), ladoDer(rvalue) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTASIG_ARREGLO () {
        delete id;
        delete exprAcceso;
        delete ladoDer;    
    }

    /* Metodo para copiar */
    elene_INSTASIG_ARREGLO(const elene_INSTASIG_ARREGLO &other) {
        id = other.id;
        exprAcceso = other.exprAcceso;
        ladoDer = other.ladoDer;
    }

    elene_INSTASIG_ARREGLO &operator = (const elene_INSTASIG_ARREGLO &other) {
        if (&other != this) {
            delete id;
            delete exprAcceso;
            delete ladoDer;
            id = other.id;
            exprAcceso = other.exprAcceso;
            ladoDer = other.ladoDer;
        }
    }
};

/* Clase para la asignacion en estructuras*/
class elene_INSTASIG_ESTRUCTURA : public elene_INSTASIG {

protected:

    elene_ID* id;
    elene_EXPR* ladoDer;
    elene_EXPR* estructura;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
        (*estructura).ident = ident+"    ";
		(*ladoDer).ident = ident+"    ";
		(*id).ident = ident+"    ";          
        return (os << ident << "Instruccion Asignacion a Estructura: {\n" 
                   << ident+"  " << "Estructura:\n" << (*estructura)
                   << ident+"  " << "Campo:\n" << (*id)
                   << ident+"  " << "Expresion:\n" << (*ladoDer)
				   << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_INSTASIG_ESTRUCTURA() {};
    elene_INSTASIG_ESTRUCTURA(elene_ID* variable, elene_EXPR* e, elene_EXPR* rvalue): 
        id(variable), estructura(e), ladoDer(rvalue) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTASIG_ESTRUCTURA () {
        delete id;
        delete estructura;
        delete ladoDer;    
    }

    /* Metodo para copiar */
    elene_INSTASIG_ESTRUCTURA(const elene_INSTASIG_ESTRUCTURA &other) {
        id = other.id;
        estructura = other.estructura;
        ladoDer = other.ladoDer;
    }

    elene_INSTASIG_ESTRUCTURA &operator = (const elene_INSTASIG_ESTRUCTURA &other) {
        if (&other != this) {
            delete id;
            delete estructura;
            delete ladoDer;
            id = other.id;
            estructura = other.estructura;
            ladoDer = other.ladoDer;
        }
    }
};

/* Clase para la iteracion indeterminada */
class elene_INSTMIENTRAS : public elene_INST {

protected:

    elene_EXPR* condicion;
    elene_BLOQUE* bloque; 

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*condicion).ident = ident+"    ";
		(*bloque).ident = ident+"  ";        
        return (os << ident << "Instruccion Mientras: {\n" 
                   << ident+"  " << "Condicion:\n" << (*condicion)
                   << (*bloque) << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_INSTMIENTRAS() {};
    elene_INSTMIENTRAS(elene_EXPR* cond, elene_BLOQUE* blq): 
        condicion(cond), bloque(blq) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTMIENTRAS () {
        delete condicion;
        delete bloque;    
    }

    /* Metodo para copiar */
    elene_INSTMIENTRAS(const elene_INSTMIENTRAS &other) {
        condicion = other.condicion;
        bloque = other.bloque;
    }

    elene_INSTMIENTRAS &operator = (const elene_INSTMIENTRAS &other) {
        if (&other != this) {
            delete condicion;
            delete bloque;
            condicion = other.condicion;
            bloque = other.bloque;
        }
    }
};


/* Clase para la iteracion determinada */
class elene_INSTPARA : public elene_INST {

protected:

    elene_INSTASIG* asignacion;
    elene_EXPR* condicion;
    elene_INSTASIG* cambio;
    elene_BLOQUE* bloque; 

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*asignacion).ident = ident+"    ";      
		(*condicion).ident = ident+"    ";
		(*cambio).ident = ident+"    ";
		(*bloque).ident = ident+"  ";
        return (os << ident << "Instruccion Para: {\n" 
                   << ident+"  " << "Asignacion:\n" << (*asignacion)
                   << ident+"  " << "Condicion:\n" << (*condicion)
                   << ident+"  " << "Cambio:\n" << (*cambio)
                   << (*bloque) << ident << "}\n");
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

    /* Metodo para copiar */
    elene_INSTPARA(const elene_INSTPARA &other) {
        asignacion = other.asignacion;
        condicion = other.condicion;
        cambio = other.cambio;
        bloque = other.bloque;
    }

    elene_INSTPARA &operator = (const elene_INSTPARA &other) {
        if (&other != this) {
            delete asignacion;        
            delete condicion;
            delete cambio;
            delete bloque; 
            asignacion = other.asignacion;
            condicion = other.condicion;
            cambio = other.cambio;
            bloque = other.bloque;
        }
    }

};


/* Clase para la iteracion determinada */
class elene_INSTROMPER: public elene_INST {

    protected:


    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
        return (os << ident << "Instruccion Romper\n");
    }

    public:
    /* Declaracion de constructor */
    elene_INSTROMPER() {};

    /* Declaracion de destructor */
    virtual ~elene_INSTROMPER () {
    }

    /* Metodo para copiar */
    elene_INSTROMPER(const elene_INSTROMPER &other) {

    }

    elene_INSTROMPER &operator = (const elene_INSTROMPER &other) {
        if (&other != this) {
        }
    }

};



/* Clase para la iteracion determinada */
class elene_INSTCONTINUAR: public elene_INST {

    protected:


    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
        return (os << ident << "Instruccion Continuar\n");
    }

    public:
    /* Declaracion de constructor */
    elene_INSTCONTINUAR() {};

    /* Declaracion de destructor */
    virtual ~elene_INSTCONTINUAR () {
    }

    /* Metodo para copiar */
    elene_INSTCONTINUAR(const elene_INSTCONTINUAR &other) {

    }

    elene_INSTCONTINUAR &operator = (const elene_INSTCONTINUAR &other) {
        if (&other != this) {
        }
    }

};

/* Clase para las instrucciones basadas en expresiones */
class elene_INSTEXPR: public elene_INST {

    protected:
        elene_EXPR* expr;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*expr).ident = ident;
        return (os << *expr);
    }

    public:
    /* Declaracion de constructor */
    elene_INSTEXPR() {};
    elene_INSTEXPR(elene_EXPR* e): expr(e) {};

    /* Declaracion de destructor */
    virtual ~elene_INSTEXPR () {
        delete expr;
    }

    /* Metodo para copiar */
    elene_INSTEXPR(const elene_INSTEXPR &other) {
        expr = other.expr;
    }

    elene_INSTEXPR &operator = (const elene_INSTEXPR &other) {
        if (&other != this) {
            delete expr;
            expr = other.expr;
        }
    }

};


/* Clase para manejar un caso de la instruccion case */
class elene_CASO : public printable {

protected:
    elene_EXPR* expr;
    elene_BLOQUE* bloque;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*expr).ident = ident+"    ";
		(*bloque).ident = ident+"  ";
        return (os << ident << "Caso: {\n"
                   << ident+"  " << "Expresion: \n" << (*expr)
                   << (*bloque) << ident << "}\n");
    }

public:
	elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_CASO() {};
    elene_CASO(elene_EXPR* e, elene_BLOQUE* b): expr(e), bloque(b) {};

    /* Declaracion de destructor */
    virtual ~elene_CASO () {
        delete expr;
        delete bloque;
    }

    /* Metodo para copiar */
    elene_CASO(const elene_CASO &other) {
        expr = other.expr; 
        bloque = other.bloque;
    }

    elene_CASO &operator = (const elene_CASO &other) {
        if (&other != this) {
            delete expr;
            delete bloque;
            expr = other.expr;
            bloque = other.bloque;
        }
    }

    bool verificar_tipos(elene_TIPO* tipo) {
        return (*expr).verificar_tipos_case(tipo);
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_CASO& obj) {
        return obj.stream_write(stream);
    }
};

/* Lista de casos para el case */
class elene_LISTACASE : public printable {

protected:

    elene_CASO* caso;
    elene_LISTACASE* resto;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {    
        if (resto != 0) {
			(*resto).ident = ident;
            os << (*resto);
        }
		(*caso).ident = ident;
		os << *caso;
        return os;

    }

public:
	elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_LISTACASE() {};
    elene_LISTACASE(elene_CASO* c, elene_LISTACASE* l): caso(c), resto(l) {};
 
    /* Declaracion de destructor */
    virtual ~elene_LISTACASE() {
        delete caso;
        delete resto;
    }

    /* Metodo para copiar */
    elene_LISTACASE(const elene_LISTACASE &other) {
        caso = other.caso;
        resto = other.resto;
    }

    elene_LISTACASE &operator = (const elene_LISTACASE &other) {
        if (&other != this) {
            delete caso;
            delete resto;
            caso = other.caso;
            resto = other.resto;
        }
    }

    bool verificar_tipos(elene_TIPO* tipo) {
        if ((*caso).verificar_tipos(tipo)) {
            if (resto) {        
                return (*resto).verificar_tipos(tipo);
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTACASE& obj) { 
        return obj.stream_write(stream); 
    }
};



/* Clase para manejar el case */
class elene_INSTCASE : public elene_INST {

protected:

    elene_ID* var;
    elene_LISTACASE* casos;
    elene_BLOQUE* defecto; 

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {
		(*casos).ident = ident+"    ";              
		(*defecto).ident = ident+"    ";
        return (os << ident << "Instruccion Case: {\n" 
                   << ident+"  " << "Variable: " << (*var)
                   << ident+"  " << "Casos: {\n" << (*casos)
				   << ident+"  " << "}\n"
                   << ident+"  " << "Caso por Defecto: \n" << (*defecto)
				   << ident << "}\n");
    }

public:
    /* Declaracion de constructor */
    elene_INSTCASE() {};
    elene_INSTCASE(elene_ID* v, elene_LISTACASE* l, elene_BLOQUE* c): 
        var(v), casos(l), defecto(c) {};
    
    /* Declaracion de destructor */
    virtual ~elene_INSTCASE () {
        delete var;
        delete casos;
        delete defecto;
    }

    /* Metodo para copiar */
    elene_INSTCASE(const elene_INSTCASE &other) {
        var = other.var;
        casos = other.casos;
        defecto = other.defecto;
    }

    elene_INSTCASE &operator = (const elene_INSTCASE &other) {
        if (&other != this) {
            delete var;
            delete casos;
            delete defecto;
            var = other.var;
            casos = other.casos;
            defecto = other.defecto;
        }
    }
};


/*****************************************************************/
/******* LISTA DE ARGUMENTOS *************************************/
/*****************************************************************/

/* Argumento al estilo int X, primera regla de gramatica */
class elene_LISTARG : public printable {

public:

    elene_ID* id;
    elene_LISTARG* resto;
    std::string ref;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {    
		if (resto != 0) {
			(*resto).ident = ident;
            os << *resto;
        }
		(*tipo).ident = ident+"    ";
		(*id).ident = ident+"    ";
        os << ident << "Argumento: {\n" 
           << ident+"  " << "Tipo: \n" << (*tipo)
           << ident+"  " << "ID: \n" << (*id)
           << ident+"  " << "Modo: " << ref
		   << ident << "}\n";

        return os;

    }

public:
	elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_LISTARG() {};
    elene_LISTARG(elene_TIPO* t, elene_ID* i, std::string mod, elene_LISTARG* r): 
        tipo(t), id(i), ref(mod), resto(r) {};
    
    /* Declaracion de destructor */
    virtual ~elene_LISTARG() {
        delete tipo;        
        delete id;
        delete resto;    
    }

    /* Metodo para copiar */
    elene_LISTARG(const elene_LISTARG &other) {
        tipo = other.tipo;
        id = other.id;
        resto = other.resto;
    }

    elene_LISTARG &operator = (const elene_LISTARG &other) {
        if (&other != this) {
            delete tipo;        
            delete id;
            delete resto;
            tipo = other.tipo;
            id = other.id;
            resto = other.resto;
        }
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTARG& obj) { 
        return obj.stream_write(stream); 
    }
};

/*****************************************************************/
/******* DECLARACION FUNCIONES ***********************************/
/*****************************************************************/

class elene_DECFUNCION : public printable {

protected:

    elene_ID* nombre;
    elene_LISTARG* parametros;
    elene_TIPO* retorno;
    elene_BLOQUE* bloque;
 
    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
		(*nombre).ident = ident+"    ";
        os << ident << "Declaracion de Funcion: {\n" 
           << ident+"  " << "Nombre: \n" << (*nombre);
        if (parametros != 0) {
			(*parametros).ident = ident+"    ";
            os << ident+"  " << "Parametros:\n" << (*parametros);
        }
        if (retorno != 0) {
			(*retorno).ident = ident+"    ";
            os << ident+"  " << "Tipo de Retorno: \n" << (*retorno);
        }
		(*bloque).ident = ident+"  ";
        os << (*bloque);
		os << ident << "}\n";
        return os;
    }

public:
	elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_DECFUNCION() {};

    elene_DECFUNCION(elene_ID* nmb, elene_LISTARG* param, elene_TIPO* ret, elene_BLOQUE* blq): 
        nombre(nmb), parametros(param), retorno(ret), bloque(blq) {};

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
class elene_LISTFUN : public printable {

protected:

    elene_DECFUNCION* fun;
    elene_LISTFUN* resto;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {           
		if (resto != 0) {
			(*resto).ident = ident;
            os << (*resto);
        }
		(*fun).ident = ident+"  ";
        os << (*fun);
        return os;
    }

public:
	elene_TIPO* tipo;
    /* Declaracion de constructor */
    elene_LISTFUN() {};
    elene_LISTFUN(elene_DECFUNCION* f, elene_LISTFUN* l): fun(f), resto(l) {};
    
    /* Declaracion de destructor */
    virtual ~elene_LISTFUN() {
        delete fun;
        delete resto;    
    }

    /* Metodo para copiar */
    elene_LISTFUN(const elene_LISTFUN &other) {
        fun = other.fun;
        resto = other.resto;
    }

    elene_LISTFUN &operator = (const elene_LISTFUN &other) {
        if (&other != this) {
            delete fun;
            delete resto;
            fun = other.fun;
            resto = other.resto;
        }
    }

    /*<< Operator overload*/
    friend std::ostream& operator<< (std::ostream& stream,const elene_LISTFUN& obj) { 
        return obj.stream_write(stream); 
    }
};

/*****************************************************************/
/******* FUNCIONES  **********************************************/
/*****************************************************************/

class elene_FUNCIONES : public printable { 

protected:

    elene_LISTFUN* lstfun;
    elene_BLOQUE* programa;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        if ( lstfun != 0 ) {
			(*lstfun).ident = ident+"  ";
            os << ident << "Lista Funciones: {\n" << (*lstfun) 
			   << ident << "}\n";
        }

		(*programa).ident = ident+"  ";
        os << ident << "Programa: { \n" << (*programa)
		   << ident << "}\n";

        return os;
           
    }

public:

	elene_TIPO* tipo;
    /* Constructor */
    elene_FUNCIONES(elene_LISTFUN* lf, elene_BLOQUE* prog): lstfun(lf), programa(prog) {}

    /* Metodo para copiar */
    elene_FUNCIONES(const elene_FUNCIONES &other) {
        lstfun = other.lstfun;
        programa = other.programa;
    }

    /* Metodo destructor */
    virtual ~elene_FUNCIONES() {
        delete lstfun;
        delete programa;
    }

    elene_FUNCIONES &operator = (const elene_FUNCIONES &other) {

        if (&other != this) {

            delete lstfun;
            delete programa;
            lstfun = other.lstfun;
            programa = other.programa;

        }
    }

   /*<< Operator overload*/
   friend std::ostream& operator<< (std::ostream& stream,const elene_FUNCIONES& obj) {
       return obj.stream_write(stream);
   }
};



/*****************************************************************/
/******* VARIABLES GLOBALES  *************************************/
/*****************************************************************/

class elene_VARGLOBAL : public printable { 

protected:

    elene_FUNCIONES* funciones;
    elene_LISTAVAR* listaVar;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              

        if ( listaVar != 0 ) {
			(*listaVar).ident = ident+"  ";
            os << ident << "Variables globales: {\n" << (*listaVar) 
               << ident << "}\n";
        }
		(*funciones).ident = ident;
        os << (*funciones);
           
    }

public:

	elene_TIPO* tipo;
    /* Constructor */
    elene_VARGLOBAL(elene_FUNCIONES* func, elene_LISTAVAR* lv): 
        funciones(func), listaVar(lv) {}

    /* Metodo para copiar */
    elene_VARGLOBAL(const elene_VARGLOBAL &other) {
        funciones = other.funciones;
        listaVar = other.listaVar;
    }

   /*<< Operator overload*/
   friend std::ostream& operator<< (std::ostream& stream,const elene_VARGLOBAL& obj) {
       return obj.stream_write(stream);
   }

    /* Metodo destructor */
    virtual ~elene_VARGLOBAL() {
        delete funciones;
        delete listaVar;
    }

    elene_VARGLOBAL &operator = (const elene_VARGLOBAL &other) {

        if (&other != this) {

            delete funciones;
            delete listaVar;
            funciones = other.funciones;
            listaVar = other.listaVar;

        }
    }


};

/* Clase para manejar tipos de funciones*/
class elene_TIPO_FUNCION : public elene_TIPO {

protected:

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << *id);
    }

public:

    elene_ID* id;
    elene_TIPO* tipo;
    elene_LISTARG* param;

    /* Declaracion de constructor */
    elene_TIPO_FUNCION() {};
    elene_TIPO_FUNCION(elene_ID* t, elene_TIPO* tp, elene_LISTARG* p): id(t), tipo(tp), param(p) {};
    
    /* Declaracion de destructor */
    virtual ~elene_TIPO_FUNCION () {
        delete id;
        delete tipo;
        delete param;
    }
    
    /* Metodo para copiar */
    elene_TIPO_FUNCION(const elene_TIPO_FUNCION &other) { 
        id = other.id;
        tipo = other.tipo;
        param = other.param;
    }

    elene_TIPO_FUNCION &operator = (const elene_TIPO_FUNCION &other) {
        if (&other != this) {
            delete id;
            id = other.id;
            delete tipo;
            tipo = other.tipo;
            delete param;
            param = other.param;
        }
    }

};



# endif
