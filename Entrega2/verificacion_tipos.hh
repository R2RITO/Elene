# ifndef ELENE_VERIFICACION_TIPOS_HH
# define ELENE_VERIFICACION_TIPOS_HH

# include <string>
# include <iostream>
# include "arbol2.hh"
# include <ostream>

inline bool chequearArgumentos(elene_LISTAEXPR* parametros_actuales, elene_LISTARG* parametros_formales) {

    if ((parametros_actuales == 0) && (parametros_formales == 0)) {
        std::cout << "Retorno true\n";
        return true;
    } else if ((parametros_actuales == 0 ) || (parametros_formales == 0)) {
                std::cout << "Retorno false\n";        
        return false;
    }

    bool z = chequearArgumentos((*parametros_actuales).resto, (*parametros_formales).resto) 
           && ((*(*parametros_actuales).expr).tipo == (*parametros_formales).tipo);

    std::cout << z << "\n";

    std::cout << "Actuales: " << (*(*(*parametros_actuales).expr).tipo);
    std::cout << "Formales: " << (*(*parametros_formales).tipo) << "\n\n\n";

    return z;

}


#endif
