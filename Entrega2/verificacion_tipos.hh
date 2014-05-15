# ifndef ELENE_VERIFICACION_TIPOS_HH
# define ELENE_VERIFICACION_TIPOS_HH

# include <string>
# include <iostream>
# include "arbol2.hh"

inline bool chequearArgumentos(elene_LISTAEXPR* parametros_actuales, elene_LISTARG* parametros_formales) {

    if ((parametros_actuales == 0) && (parametros_formales == 0)) {
        return true;
    } else if ((parametros_actuales == 0 ) || (parametros_formales == 0)) {
        return false;
    }

    return chequearArgumentos((*parametros_actuales).resto, (*parametros_formales).resto) 
           && ((*parametros_actuales).tipo == (*parametros_formales).tipo);

}

#endif
