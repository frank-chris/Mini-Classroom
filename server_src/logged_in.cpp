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
    /*
     * Add instructor to "Classrooms/classname/instructors.txt" 
     * No personal entry will be made, however, the instructor can access the course related data
     * of all students enrolled in the course
     * Create directories named Type 1 and Type 2
     */
    if(entry_exists("Classrooms/classrooms.txt", classname)){
        return 0;
    }
    create_entry("Classrooms", classname);
    add_to_class(classname, (usr -> name), true); // 0 for instructor, 1 for student
    string classpath = "Classrooms/" + classname;
    makedir(classpath, "Type 1");
    makedir(classpath, "Type 2");
    return 1;
}

int enroll(string classname){
    /*
     * Add student to "Classrooms/classname/students.txt" 
     * In "Users/username", create an entry for this course
     *
     * To be added:
     * Copy the contents of all assignments, projects, etc that have been created in the class
     */
    if(entry_exists("Classrooms/classrooms.txt", classname)){
        string username = usr -> name;
        add_to_class(classname, username, false);
        string personal_path = "Users/" + username;
        create_entry(personal_path, classname);
        return 1;
    }
    return 0;
}

void logged_in(User *usr){
    int cli_sock = usr -> cli_sock;
    string login = LOGGED_IN;
    while(true){
        if((usr -> active) == false){
            break;
        }

        string header;
        string data;
        recv_data(cli_sock, &header, &data);
        vector<string> strings_list = split_string(header);
        vector<string> parameters = split_string(data);
 
        if(strings_list[0] == "SEND"){
            int num = atoi(strings_list[1]);
            if(num == 0){
                int ret_val = create_class(data);
                if(ret_val == 0){
                    send_data(cli_sock, 0, login);
                    continue;
                }
                else{
                    send_data(cli_sock, 1, login);
                    continue;
                }
            }
            else if(num == 1){
                int ret_val = enroll(data);
                if(ret_val == 0){
                    send_data(cli_sock, 0, login);
                    continue;
                }
                else{
                    send_data(cli_sock, 1, login);
                    continue;
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
