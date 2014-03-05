#ifndef ELENE_DRIVER_HH
# define ELENE_DRIVER_HH
# include <string>
# include <map>
# include "elene_parser.hh"

# define YY_DECL \
yy::elene_parser::symbol_type yylex (elene_driver& driver)
YY_DECL;

class elene_driver {

    public:

        /*Funcion para el manejador */
        elene_driver();

        /* Ni Idea */
        virtual ~elene_driver();
        
        /* Posiblemente tabla de simbolos 
        std::map<std::string, int> variables;
        int result;
        */

        // Encapsulamiento de la coordinacion con el escaner de Flex
        // Podemos con esto abrir y cerrar la fase de escaneo
        void scan_begin ();
        void scan_end ();
        bool trace_scanning;

        // Realizamos algo similar para el parser
        // Run the parser on file F.
        // Return 0 on success.
        int parse (const std::string& f);
        // The name of the file being parsed.
        // Used later to pass the file name to the location tracker.
        std::string file;
        // Whether parser traces should be generated.
        bool trace_parsing;

        // Error handling.
        void error (const yy::location& l, const std::string& m);
        void error (const std::string& m);
};
#endif // ! ELENE_DRIVER_HH
