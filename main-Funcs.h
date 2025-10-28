#ifndef main_Funcs_h
#define main_Funcs_h

#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

void commit(std::string message, std::string url, std::string branch, std::string remote);
void log(int num);
void changeGITName(std::string name, std::string email, std::string global);
void branchCreateSwitch(std::string branch);
void branchSwitch(std::string branch);

#endif
