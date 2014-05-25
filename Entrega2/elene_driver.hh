# ifndef ELENE_DRIVER_HH
# define ELENE_DRIVER_HH
# include <string>
# include <map>
# include "elene_parser.tab.hh"

// Tell Flex the lexer's prototype ...
# define YY_DECL \
yy::elene_parser::symbol_type yylex (elene_driver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of Elene.
class elene_driver {
    public:
        elene_driver();
        virtual ~elene_driver();

    int result;

    // Handling the scanner.
    void scan_begin ();
    void scan_end ();
    bool trace_scanning;

    // Run the parser on file F.
    // Return 0 on success.
    int parse(const std::string& f);

    // The name of the file being parsed.
    // Used later to pass the file name to the location tracker.
    std::string file;

    // Whether parser traces should be generated.
    bool trace_parsing;


    // Error handling.
    void error(const yy::location& l, const std::string& m);
    void error(const std::string& m);
	void error_redec(const yy::location& l, const std::string& m);
	void error_tipo_indef (const yy::location& l, const std::string& m);
	void error_fun_redec(const yy::location& l, const std::string& m);
	void error_param_redec(const yy::location& l, const std::string& m);
	void error_etiq_redec(const yy::location& l, const std::string& m);
	void error_indef(const yy::location& l, const std::string& m);
    void error_tipo_no_estructura(const yy::location& l, const std::string& m);
    void error_parametros(const yy::location& l, const std::string& m);
    void error_no_funcion(const yy::location& l, const std::string& m);
	void error_tipo_expr(const yy::location& l, const std::string& m);
	void error_tipo_attr_no_dec(const yy::location& l, const std::string& m);
	void error_tipo_no_estr(const yy::location& l, const std::string& m);
	void error_tipo_array_undec(const yy::location& l, const std::string& m);
    void error_tipo_no_es_array(const yy::location& l, const std::string& m);
    void error_tipo_listaexpr_expr(const yy::location& l, const std::string& m);
    void error_tipo_case_var_undec(const yy::location& l, const std::string& m);
    void error_tipo_case_var_expr(const yy::location& l, const std::string& m);
    void error_tipo_asignacion(const yy::location& l, const std::string& m);
    void error_indices_incorrectos(const yy::location& l, const int& m);
};

#endif // ! ELENE_DRIVER_HH
