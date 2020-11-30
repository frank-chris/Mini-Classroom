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


int create_class(string classname, string username){
    /*
     * Create the entry for classname in "Classrooms"
     * Add instructor to "Classrooms/classname/instructors.txt" 
     * An empty personal directory for the course will be made, however, the instructor can access the course related data
     * of all students enrolled in the course
     * Create directories named Type 1 and Type 2
     */
    if(entry_exists("Classrooms/classrooms.txt", classname)){
        return 0;
    }
    create_entry("Classrooms", "Classrooms/classrooms.txt", classname);
    string classpath = "Classrooms/" + classname;
    create_file(classpath, "/instructors.txt");
    create_file(classpath, "/students.txt");
    add_to_file(classpath + "/instructors.txt", username);
    makedir(classpath, "Type 1");
    makedir(classpath, "Type 2");
    string personal_path = "Users/" + username;
    string courses_file = personal_path + "/courses.txt";
    create_entry(personal_path, courses_file, classname);
    return 1;
}

int enroll(string classname, string username){
    /*
     * Add student to "Classrooms/classname/students.txt" 
     * In "Users/username", create an entry for this course
     *
     * To be added:
     * Copy the contents of all assignments, projects, etc that have been created in the class
     */
    if(entry_exists("Classrooms/classrooms.txt", classname)){
        string classpath = "Classrooms/" + classname;
        add_to_file(classpath + "/students.txt", username);
        string personal_path = "Users/" + username;
        string courses_file = personal_path + "/courses.txt";
        create_entry(personal_path, courses_file, classname);
        return 1;
    }
    return 0;
}

void logged_in(User *usr){
    int cli_sock = usr -> cli_sock;
    string username = usr -> name;
    string login = LOGGED_IN;
    while(true){
        if((usr -> active) == false){
            break;
        }

        string header;
        string data;
        recv_data(cli_sock, header, data);
        vector<string> strings_list = split_string(header);
 
        if(strings_list[0] == "SEND"){
            int num = atoi(strings_list[1].c_str());
            if(num == 0){
                int ret_val = create_class(data, username);
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
                int ret_val = enroll(data, username);
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
            int num = atoi(strings_list[1].c_str());
            if(num == 0){
                // Read classrooms.txt, append login to it
                string res = "List of all courses available-\n";
                res += file_contents("Classrooms/classrooms.txt");
                res += "--------------\n";
                res += LOGGED_IN;
                send_data(cli_sock, true, res);
            }
            else if(num == 1){
                // Enter a classroom
                string classname = data;
                string user_courses = "Users/" + username + "/courses.txt";
                if(entry_exists(user_courses, classname)){
                    string instructor_path = "Classrooms/" + classname + "instructors.txt";
                    if(entry_exists(instructor_path, username)){
                        send_data(cli_sock, true, STUDENT);
                        instructor(usr, classname);
                    }
                    string student_path = "Classrooms/" + classname + "students.txt";
                    if(entry_exists(student_path, username)){
                        send_data(cli_sock, true, INSTRUCTOR);
                        student(usr, classname);
                    }
                }
            }
            else if(num == 2){
                // Get a list of courses joined
                string res = "List of joined courses-\n";
                string filename = "Users/" + username + "/courses.txt";
                res += file_contents(filename);
                res += "--------------\n";
                res += LOGGED_IN;
                send_data(cli_sock, true, res);
                
            }
        }
    }
}
