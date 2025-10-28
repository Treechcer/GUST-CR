#include "JSON-lib.h"
#include "main-Funcs.h"
#include <iostream>
#include <regex>
#include <stdexcept>

std::string changeMode(std::string mode);

int main(int argc, char *argv[]) {
    std::string ver = "0.0.12";
    std::vector<JSON> config = analyseJSON("config.json");

    std::string message;
    std::string mode;
    std::string url = "NO-INPUT";
    std::string branch = JSON::getValuesFromName("defaultBranch", config);
    std::string remote = JSON::getValuesFromName("defaultRemote", config);
    int num = -1;

    std::string workspace = argv[0];
    //std::cout << config.size();

    //std::cout << argc << std::endl;

    for (int i = 1; i < argc; i += 2) {
        if (std::regex_search(argv[i], std::regex("c(o(m(m(m(i(t)?)?)?)?)?)?")) || mode == "c") {
            message = argv[i + 1];
            //std::cout << argv[i] << " " << argv[i + 1] << std::endl;
        }
        else if (std::string(argv[i]) == "-m") {
            mode = argv[i + 1];
            //std::cout << argv[i] << " " << argv[i + 1] << std::endl;
        }
        else if (std::regex_search(argv[i], std::regex("n(u(m)?)?")) || mode == "n") {
            try {
                num = std::stoi(argv[i + 1]);
            } catch (...) {
                throw std::invalid_argument("-n must be integer number");
            }
        }
        else if (std::regex_search(argv[i], std::regex("u(r(l)?)?")) || mode == "url") {
            url = argv[i + 1];
        }
        else if (std::regex_search(argv[i], std::regex("b(r(a(n(c(h)?)?)?)?)?")) || mode == "b") {
            branch = argv[i + 1];
        }
    }

    if (JSON::getValuesFromName("setupName", config) == "true") {
        changeGITName(JSON::getValuesFromName("name", config), JSON::getValuesFromName("email", config), JSON::getValuesFromName("setNameEmailGlobal", config));
    }

    if (mode.empty() && JSON::getValuesFromName("useDefaultMode", config) == "true") {
        mode = JSON::getValuesFromName("defaultMode", config);
    }

    if (num == -1) {
        num = stoi(JSON::getValuesFromName("defaultNum", config));
    }

    mode = changeMode(mode);

    if (mode == "commit") {
        commit(message, url, branch, remote);
    }
    else if (mode == "log") {
        log(num);
    }

    //for (int i = 0; i < config.size(); i++) {
    //    std::cout << config[i].name << " : " << config[i].value << std::endl;
    //}

    return 0;
}

std::string changeMode(std::string mode) {
    if (std::regex_search(mode, std::regex("c(o(m(m(m(i(t)?)?)?)?)?)?"))) {
        return "commit";
    }
    else if (std::regex_search(mode, std::regex("l(o(g)?)?"))) {
        return "log";
    }
    else {
        return mode;
    }
}