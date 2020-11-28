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

using namespace std;


int create_class(string classname){
    if(entry_exists("Classrooms/classrooms.txt", classname)){
        return 0;
    }
    create_entry("Classrooms", classname);
    add_to_class(classname, (usr -> name), true); // 0 for instructor, 1 for student
    return 1;
}

int enroll(string classname){
    if(entry_exists("Classrooms/classrooms.txt", classname)){

        return 1;
    }
    return 0;
}

void logged_in(User *usr){
    int cli_sock = usr -> cli_sock;
    string message = "Welcome user " + (usr -> name) + "!\n";
    int data_sent;
    if((data_sent = send((usr -> cli_sock), message, message.size(), 0)) != message.size()){
        perror("send() failed");
        exit(1); // Replace this with fail message
        // fail_msg();
    }
    string header;
    while(true){
        if((usr -> active) == false){
            break;
        }
        
        int data_recv;
        if((data_recv = recv(cli_sock, header, BUF_SIZE, 0)) < 0){
            perror("recv() failed");
            exit(1); //Replace
        }

        string data = "";
        string buffer;
        int data_to_recv = atoi(strings_list[2]);
        while((data_to_recv > 0) && ((data_recv = recv(cli_sock, buffer, BUF_SIZE, 0)) > 0)){
            data += buffer;
            data_to_recv -= data_recv;
        }
        vector<string> strings_list = split_string(header);
        if(strings_list[0] == "SEND"){
            int num = atoi(strings_list[1]);
            if(num == 0){
                int ret_val = create_class(data);
                if(ret_val == 0){
                    send_resp(0, "Classroom already exists");
                }
                else{
                    send_resp(1, "Classroom created!");
                }
            }
            else if(num == 1){
                int ret_val = enroll(data);
                if(ret_val == 0){
                    send_resp(0, "Classroom does not exist");
                }
                else{
                    string resp = "Enrolled in Class " + data;
                    send_resp(1, resp);
                }
            }
        }
        else if(strings_list[0] == "ASK"){
            int num = atoi(strings_list[1]);
            if(num == 0){
                // Get the full list of courses
            }
            else if(num == 1){
                // Enter a classroom
            }
            else if(num == 2){
                // Get a list of courses joined
            }
        }
    }
}
