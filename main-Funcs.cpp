#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

void commit(std::string message, std::string url, std::string branch, std::string remote) {
    //std::cout << message << std::endl;

    if (url != "NO-INPUT") {
        if (!(std::filesystem::exists(".git") || std::filesystem::is_directory(".git"))) {
            system("git init");
        }

        //git remote add $config.defaultRemote "$gitURL.git"
        std::string cmd = "git remote add ";
        cmd.append(remote);
        cmd.append(" ");
        cmd.append(url);
        system(cmd.c_str());

        cmd = "git pull ";
        cmd.append(remote);
        cmd.append(" ");
        cmd.append(branch);
        cmd.append(" --allow-unrelated-histories");
        system(cmd.c_str());

        system("git add .");

        cmd = "git commit -m \"";
        cmd.append(message);
        cmd.append("\"");
        system(cmd.c_str());

        cmd = "git push --set-upstream ";
        cmd.append(remote);
        cmd.append(" ");
        cmd.append(branch);
        system(cmd.c_str());
    }
    else {
        system("git pull --no-edit");

        system("git add .");

        std::string command = "git commit -m \"";
        command.append(message);
        command.append("\"");

        //std::cout << command;

        system(command.c_str());

        system("git push");
    }
}

void log(int num) {
    //std::cout << num;
    std::string command = "git log --oneline -n ";
    command.append(std::to_string(num));
    system(command.c_str());
}

void changeGITName(std::string name, std::string email, std::string global) {

    if (name == "NOT-SET" || email == "NOT-SET") {
        throw std::invalid_argument("not valid name or email, change it from 'NOT-SET' to your Git username and emil");
    }

    if (global == "true") {
        std::string cmd = "git config --global user.name ";
        cmd.append(name);
        system(cmd.c_str());

        cmd = "git config --global user.email ";
        cmd.append(email);
        system(cmd.c_str());

        std::cout << "----------------------------" << std::endl;
        std::cout << "Your global git name / email" << std::endl;
        std::cout << name << " / " << email << std::endl;
        std::cout << "----------------------------" << std::endl;
    }
    else {
        std::string cmd = "git config user.name ";
        cmd.append(name);
        system(cmd.c_str());

        cmd = "git config user.email ";
        cmd.append(email);
        system(cmd.c_str());

        std::cout << "----------------------------" << std::endl;
        std::cout << "Your local git name / email " << std::endl;
        std::cout << name << " / " << email << std::endl;
        std::cout << "----------------------------" << std::endl;
    }
}

void branchCreateSwitch(std::string branch){
    std::string cmd = "git branch ";
    cmd.append(branch);
    system(cmd.c_str());
    
    cmd = "git checkout ";
    cmd.append(branch);
    system(cmd.c_str());

    system("git branch");
}