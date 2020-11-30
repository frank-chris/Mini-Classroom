#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "server.hpp"
#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace std;

void instructor(User* usr, string classname){
    int cli_sock = usr -> cli_sock;
    string username = usr -> name;
    string instructor_state = INSTRUCTOR;

    cout<<"\nInstructor state\n";
    
    while(true){
        if((usr -> active) == false){
            break;
        }

        string header;
        string data;
        recv_data(cli_sock, header, data);
        vector<string> strings_list = split_string(header);
        vector<string> data_list = split_string(data);
        if(strings_list[0] == "SEND"){
            int num = stoi(strings_list[1]);
        }
}

