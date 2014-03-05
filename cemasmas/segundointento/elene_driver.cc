#include "elene_driver.hh"
#include "elene_parser.hh"
     
elene_driver::elene_driver () : trace_scanning (false), trace_parsing (false) {
        /*variables["one"] = 1;
        variables["two"] = 2;*/ 
}
 
elene_driver::~elene_driver () { }
     
int elene_driver::parse (const std::string &f) {
    file = f;
    scan_begin ();
    yy::calcxx_parser parser (*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end ();
    return res;
}
     
void calcxx_driver::error (const yy::location& l, const std::string& m) {
    std::cerr << l << ": " << m << std::endl;
}
     
void calcxx_driver::error (const std::string& m) {
    std::cerr << m << std::endl;
}
