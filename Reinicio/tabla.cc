# include <string>
# include <map>
# include <iostream>
# include <list>

class elene_TABLA_VALOR {

protected:

    std::string tipo;
    int lin;
    int col;
    int size;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        return (os << "Linea: " << lin
                   << " Columna: " << col
                   << " Tipo: " << tipo 
                   << " Tam: " << size);
    }

public:

    elene_TABLA_VALOR() {};
    elene_TABLA_VALOR(std::string S, int L, int C, int T) {
        this -> tipo = S;
        this -> lin  = L;
        this -> col  = C;
        this -> size = T;
    }

    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_TABLA_VALOR& obj){
        return obj.stream_write(stream); 
    }
};



class elene_TABLA {

protected:
    elene_TABLA* padre;
    std::map <std::string, elene_TABLA_VALOR*> tabla;
    std::list <elene_TABLA*> hijos;

    /* Metodo para imprimir */
    virtual std::ostream& stream_write(std::ostream& os) const {              
        std::map<std::string, elene_TABLA_VALOR*>::const_iterator iter;

        for (iter = tabla.begin(); iter!=tabla.end(); iter++) {
            std::cout << "Nombre: " << iter -> first << " "
                      << *(iter -> second) << "\n";
        }

        std::list<elene_TABLA*>::const_iterator t_iter;

        for (t_iter = hijos.begin(); t_iter!=hijos.end(); ++t_iter) {
            std::cout << **t_iter ; /* Revisar ese ** */
        }
        
    }

public:

    elene_TABLA() : padre(0) {};
    elene_TABLA(elene_TABLA* T) : padre(T) {
        if (T != 0) {
            T -> nuevoHijo(this);
        }
    };
    
    void insertar(std::string nom, std::string tip, int lin, int col, int size) {
        elene_TABLA_VALOR* entrada = new elene_TABLA_VALOR(tip,lin,col,size);
        tabla[nom] = entrada;
    }

    elene_TABLA_VALOR* lookup(std::string nom) {

        if (tabla[nom] != 0) {
            return tabla[nom];
        } else {
            if (padre != 0) {
                return (*padre).lookup(nom);
            } else {
                return 0;
            }
        }    
    }

    void nuevoHijo(elene_TABLA* hijo) {
        (this -> hijos).push_back(hijo);
    }
    /* Sobrecarga del operador << */
    friend std::ostream& operator<< (std::ostream& stream,const elene_TABLA& obj){
        return obj.stream_write(stream); 
    }
};


int main() {
  std::cout << "Hello World!\n";

    elene_TABLA* tablita = new elene_TABLA();
    /*elene_TABLA* tablaHijo = new elene_TABLA(tablita); */
    elene_TABLA* tablon  = new elene_TABLA(tablita);

    tablon -> insertar("Hola","Entero",1,1,4);
    tablon -> insertar("Chais", "Char", 2,7,1);
    /*tablaHijo -> insertar("SoyHijo", "Bool", 2,7,1); */
    tablita -> insertar("Pruebita", "Bool", 1,2,3); 

    std::cout << *tablita;

  return 1; 
}
