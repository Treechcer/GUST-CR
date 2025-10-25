#include "JSON-lib.h"
#include "main-Funcs.h"
#include <iostream>
#include <regex>
#include <stdexcept>

int main(int argc, char *argv[]) {
    std::string ver = "0.0.6";
    std::vector<JSON> config = analyseJSON("config.json");

    std::string message;
    std::string mode;
    std::string url = "NO-INPUT";
    std::string branch = JSON::getValuesFromName("defaultBranch", config);
    std::string remote = JSON::getValuesFromName("defaultRemote", config);
    int num;

    std::string workspace = argv[0];
    //std::cout << config.size();

    //std::cout << argc << std::endl;

    for (int i = 1; i < argc; i += 2){
        if (std::regex_search(argv[i], std::regex("c(o?m?m?i?t?)?")) || mode == "c") {
            message = argv[i + 1];
            //std::cout << argv[i] << " " << argv[i + 1] << std::endl;
        } else if (std::string(argv[i]) == "-m") {
            mode = argv[i + 1];
            //std::cout << argv[i] << " " << argv[i + 1] << std::endl;
        } else if (std::regex_search(argv[i], std::regex("n(u(m)?)?")) || mode == "n") {
            try{
                num = std::stoi(argv[i + 1]);
            } catch(...){
                throw std::invalid_argument("-n must be integer number");
            }
        } else if (std::regex_search(argv[i], std::regex("u(r(l)?)?")) || mode == "url"){
            url = argv[i + 1];
        } else if (std::regex_search(argv[i], std::regex("b(r(a(n(c(h)?)?)?)?)?")) || mode == "b"){
            branch = argv[i + 1];
        }
    }

    if (mode.empty() && JSON::getValuesFromName("useDefaultMode", config) == "true") {
        mode = JSON::getValuesFromName("defaultMode", config);
    }

    //std::cout << mode;

    if (mode == "commit"){
        commit(message, url, branch, remote);
    }
    else if (mode == "log"){
        log(num);
    }

    return 0;
}