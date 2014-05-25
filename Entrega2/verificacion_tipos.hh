# ifndef ELENE_VERIFICACION_TIPOS_HH
# define ELENE_VERIFICACION_TIPOS_HH

# include <string>
# include <iostream>
# include "arbol2.hh"
# include <ostream>

inline bool chequearArgumentos(elene_LISTAEXPR* parametros_actuales, elene_LISTARG* parametros_formales) {

    if ((parametros_actuales == 0) && (parametros_formales == 0)) {
        return true;
    } else if ((parametros_actuales == 0 ) || (parametros_formales == 0)) {      
        return false;
    }

    bool z = chequearArgumentos((*parametros_actuales).resto, (*parametros_formales).resto) 
           && ((*(*parametros_actuales).expr).tipo == (*parametros_formales).tipo);

    return z;

}

inline int alinear(int tam) {

    if ((tam % 4) == 0) {
        return tam;
    } else {
        return (4 - (tam % 4)) + tam;
    }
}


#endif
