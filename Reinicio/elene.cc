#include <iostream>
#include "elene_driver.hh"

int main (int argc, char *argv[]) {
    int res = 0;
    elene_driver driver;

    for (int i = 1; i < argc; ++i)
        if (argv[i] == std::string("-p"))
            driver.trace_parsing = true;
        else if (argv[i] == std::string("-s"))
            driver.trace_scanning = true;
        else if (!driver.parse(argv[i])) {
            std::cout << "\n\n Result: ";
            std::cout << driver.result << std::endl;
        }
        else
            res = 1;

    return res;

}

