#ifndef JSON_LIB_H
#define JSON_LIB_H

#include <any>
#include <stdexcept>
#include <string>
#include <vector>

class JSON {
  public:
    std::string name;
    std::string value;

    JSON(std::string name, std::string value);
    static std::string getValuesFromName(std::string name, std::vector<JSON> atrs);
};

std::vector<JSON> analyseJSON(std::string fileName);
std::vector<std::vector<std::string>> parse(std::string contentOfJSON);

#endif
