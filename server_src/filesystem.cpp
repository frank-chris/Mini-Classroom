#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include "server.hpp"

using namespace std;

void initFS(){
    makedir(".", "Users");
    makedir(".", "Classrooms");
    create_file("Users", "users.txt");
    create_file("Users", "pairs.txt");
    create_file("Classrooms", "classrooms.txt");
    cout<<"\nInitialized filesystem\n";
}

void makedir(string path, string dirname){
    string command = "mkdir " + path + "/" + dirname;
    system(command.c_str());
    command = "chmod 777 " + path + "/" + dirname;
    system(command.c_str());
}

void create_file(string path, string filename){
    string command = "touch " + path + "/" + filename;
    system(command.c_str());
    command = "chmod 777 " + path + "/" + filename;
    system(command.c_str());
}

