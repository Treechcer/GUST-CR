#include "JSON-lib.h"
#include "main-Funcs.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::string ver = "0.0.3";
    std::vector<JSON> config = analyseJSON("test.json");

    std::string message;
    std::string mode;

    //std::cout << config.size();

    //std::cout << argc << std::endl;

    for (int i = 1; i < argc; i += 2){
        if(std::string(argv[i]) == "-c"){
            message = argv[i + 1];
            //std::cout << argv[i] << " " << argv[i + 1] << std::endl;
        }
        else if (std::string(argv[i]) == "-m") {
            mode = argv[i + 1];
            //std::cout << argv[i] << " " << argv[i + 1] << std::endl;
        }
    }

    if (mode == "commit"){
        commit(message);
    }

    return 0;
}