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
        << "- ERROR - "
        << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column << ". " 
        << m 
        << std::endl;
}

void elene_driver::error_redec (const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - " << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column
		<< ". Variable '" << m << "' ya habia sido declarada."
        << std::endl;
}

void elene_driver::error_tipo_indef (const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - "
        << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column 
		<< ". Tipo '" << m << "' no ha sido definido. " 
        << std::endl;
}

void elene_driver::error_fun_redec(const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - " << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column
		<< ". Funcion '" << m << "' ya habia sido declarada."
        << std::endl;
}

void elene_driver::error_param_redec(const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - " << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column
		<< ". Parametro '" << m << "' ya habia sido declarado."
        << std::endl;
}

void elene_driver::error_etiq_redec(const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - " << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column
		<< ". Etiqueta '" << m << "' ya habia sido declarada."
        << std::endl;
}

void elene_driver::error_indef(const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - " << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column
		<< ". '" << m << "' no ha sido declarada."
        << std::endl;
}

void elene_driver::error_tipo_no_estructura(const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - " << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column
		<< ". '" << m << "' no tiene un tipo que corresponda a una estructura."
        << std::endl;
}

void elene_driver::error_parametros(const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - " << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column
		<< ". '" << m << "' fue llamada con parametros incorrectos."
        << std::endl;
}

void elene_driver::error_no_funcion(const yy::location& l, const std::string& m) {
    std::cerr 
        << "- ERROR - " << "Linea: " << l.begin.line
        << ", Columna: " << l.begin.column
		<< ". '" << m << "' no tiene un tipo que corresponda a una funcion."
        << std::endl;
}

void elene_driver::error_tipo_expr(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". Error de tipo: " << m << std::endl;
}

void elene_driver::error_tipo_attr_no_dec(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". Atributo '" << m << "' no declarado en la estructura" << std::endl;
}

void elene_driver::error_tipo_no_estr(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". Se intento acceder a un elemento que no es una estructura" << std::endl;
}

void elene_driver::error_tipo_array_undec(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". Arreglo " << m << " no ha sido declarado. " << std::endl;
}

void elene_driver::error_tipo_no_es_array(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". Variable " << m << " no es de tipo arreglo. " << std::endl;
}

void elene_driver::error_tipo_listaexpr_expr(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". Expresion con error de tipos. " << std::endl;
}

void elene_driver::error_tipo_case_var_undec(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". Variable " << m << " no ha sido declarada. " << std::endl;
}

void elene_driver::error_tipo_case_var_expr(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". Tipo de la variable " << m << " no concuerda con el tipo de la expresion de uno de los casos. " << std::endl;
}

void elene_driver::error_tipo_asignacion(const yy::location& l, const std::string& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". " << m << std::endl;
}

void elene_driver::error_indices_incorrectos(const yy::location& l, const int& m) {
	std::cerr
		<< "- ERROR - " << "Linea: " << l.begin.line
		<< ", Columna: " << l.begin.column
		<< ". " << "El limite izquierdo debe ser menor al derecho" << std::endl;
}


void elene_driver::error (const std::string& m) {
    std::cerr << m << std::endl;
}


