#include "JSON-lib.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

/*class JSON {
    public:
        std::string name;
        std::string value;

    JSON(std::string name, std::string value) {
        this->name = name;
        this->value = value;
    }

    static std::string getValuesFromName(std::string name, std::vector<JSON> atrs){
        for (int i = 0; i < atrs.size(); i++){
            if (atrs[i].name == name){
                return atrs[i].value;
            }
        }

        throw std::invalid_argument("name doesn't exist in JSON");
    }
};*/

JSON::JSON(std::string name, std::string value) {
    this->name = name;
    this->value = value;
}

std::string JSON::getValuesFromName(std::string name, std::vector<JSON> atrs) {
    for (int i = 0; i < atrs.size(); i++) {
        if (atrs[i].name == name) {
            return atrs[i].value;
        }
    }

    throw std::invalid_argument("name doesn't exist in JSON");
}

std::vector<std::vector<std::string>> parse(std::string contentOfJSON);

std::vector<JSON> analyseJSON(std::string fileName) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    if (!std::regex_search(fileName, std::regex("\\.(JSON)*(json)*$"))) {
        throw std::invalid_argument("not valid JSON file");
    }

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::ofstream outfile(fileName);
        outfile << getDefaultConfig() << std::endl;
        outfile.close();
        file.open(fileName);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    //std::cout << content << std::endl;

    std::vector<std::vector<std::string>> parsed = parse(content);
    std::vector<JSON> atrs;
    for (int index = 0; index < parsed[0].size(); index++) {
        atrs.push_back(JSON(parsed[0][index], parsed[1][index]));
    }

    //for (int i = 0; i < atrs.size(); i++) {
    //std::cout << atrs[i].name << " " << atrs[i].value << std::endl;
    //}

    return atrs;
}

std::string getDefaultConfig(){
    return R"({
    "defaultMode": "c",
    "useDefaultMode": true,
    "defaultBranch": "main",
    "defaultRemote": "origin",

    "setupName": false,
    "setNameEmailGlobal": false,
    "email": "treechcer@gmail.com",
    "name": "Treechcer"
})";
}

    std::vector<std::vector<std::string>> parse(std::string contentOfJSON) {
        std::vector<std::string> names;
        std::vector<std::string> values;
        bool wasColon = false;

        while (contentOfJSON.length() > 0) {
            char c = contentOfJSON[0];
            if (c == ' ' || c == '{' || c == '}' || c == '\n') {
                contentOfJSON.erase(0, 1);
                continue;
            }

            if (c == ':') {
                contentOfJSON.erase(0, 1);
                wasColon = true;
                continue;
            }
            if (c == ',') {
                contentOfJSON.erase(0, 1);
                wasColon = false;
                continue;
            }

            if (c == '"') {
                std::string varName = "";
                while (true) {
                    contentOfJSON.erase(0, 1);
                    char ch = contentOfJSON[0];
                    if (ch == '"')
                        break;

                    varName.push_back(ch);
                }
                if (wasColon)
                    values.push_back(varName);
                else
                    names.push_back(varName);
            }
            else if ((c >= '0' && c <= '9') || c == '-') {
                std::string value = "";
                while (true) {
                    char ch = contentOfJSON[0];
                    if (ch == ',' || ch == '\n')
                        break;

                    value.push_back(ch);
                    contentOfJSON.erase(0, 1);
                }
                values.push_back(value);
                continue;
            }
            else {
                if (contentOfJSON[0] == 't' && contentOfJSON[1] == 'r' &&
                    contentOfJSON[2] == 'u' && contentOfJSON[3] == 'e') {
                    if (!wasColon)
                        throw std::invalid_argument("not valid JSON");
                    values.push_back("true");
                    contentOfJSON.erase(0, 4);
                }
                else if (contentOfJSON[0] == 'f' && contentOfJSON[1] == 'a' &&
                         contentOfJSON[2] == 'l' && contentOfJSON[3] == 's' &&
                         contentOfJSON[4] == 'e') {
                    if (!wasColon)
                        throw std::invalid_argument("not valid JSON");
                    values.push_back("false");
                    contentOfJSON.erase(0, 5);
                }
                else {
                    throw std::invalid_argument("not valid JSON");
                }
                continue;
            }

            contentOfJSON.erase(0, 1);
        }

        std::vector<std::vector<std::string>> returningVec;
        returningVec.push_back(names);
        returningVec.push_back(values);

        return returningVec;
}