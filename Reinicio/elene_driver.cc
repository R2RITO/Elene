#include "elene_driver.hh"
#include "elene_parser.tab.hh"

elene_driver::elene_driver (): trace_scanning (false), trace_parsing (false) {

}

elene_driver::~elene_driver () { }

int elene_driver::parse(const std::string &f) {
    file = f;
    scan_begin();
    yy::elene_parser parser(*this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end();
    return res;
}

void elene_driver::error (const yy::location& l, const std::string& m) {
    std::cerr << l << ": " << m << std::endl;
}

void elene_driver::error (const std::string& m) {
    std::cerr << m << std::endl;
}


