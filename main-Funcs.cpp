#include <cstdlib>
#include <format>
#include <iostream>
#include <string>

void commit(std::string message){
    //std::cout << message << std::endl;

    system("git add .");

    std::string command = "git commit -m '";
    command.append(message);
    command.append("'");

    std::cout << command;

    system(command.c_str());

    system("git push");
}