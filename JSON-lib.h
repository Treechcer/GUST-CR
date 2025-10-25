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

    static std::any getValuesFromName(const std::string name, const std::vector<JSON> atrs);
};

std::vector<JSON> analyseJSON(const std::string fileName);
std::vector<std::vector<std::string>> parse(const std::string contentOfJSON);

#endif
