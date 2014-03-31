#include "elene_driver.hh"
#include "elene_parser.tab.hh"

/* Implementacion de los metodos definidos en elene_driver.hh */

/* Implementacion del constructor */
elene_driver::elene_driver (): 
    trace_scanning (false), trace_parsing (false) { }

/* Implementacion del destructor */
elene_driver::~elene_driver () { }

/* Implementacion de la funcion parse */
int elene_driver::parse(const std::string &f) {
    file = f;
    scan_begin();
    yy::elene_parser parser(*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end();
    return res;
}

/* Implementacion de las funciones para reporte de errores */
void elene_driver::error (const yy::location& l, const std::string& m) {
    std::cerr 
        << "Error de sintaxis en: "
        << "Linea: " << l.begin.line
        << " y Columna: " << l.begin.column << ".\n " 
        << "Bison dice que : " << m 
        << std::endl;
}
void elene_driver::error (const std::string& m) {
    std::cerr << m << std::endl;
}


