# ifndef ELENE_CLASES_HH
# define ELENE_CLASES_HH

# include <string>
# include <map>
# include <iostream>


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



# endif
