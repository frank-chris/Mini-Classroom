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
#include <signal.h>

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
        string curpath = "Classrooms/" + classname;
        if(strings_list[0] == "SEND"){
            int num = stoi(strings_list[1]);
            if(num == 0){
                int type = stoi(data_list[0]);
                string category = data_list[1];
                string update_name = data_list[2];
                send_data(cli_sock, true, "Uploading to Classroom...");
                if(type == 1){
                    curpath += "/type_1";
                    if(entry_exists(curpath + "/categories.txt", category) == false){
                        create_entry(curpath, curpath + "/categories.txt", category);
                    }
                    curpath += "/" + category;
                    if(entry_exists(curpath + "/updates.txt", update_name) == false){
                        create_entry(curpath, curpath + "/updates.txt", update_name);
                    }
                    curpath += "/" + update_name;
                    string deadline = data_list[3];
                    string text = data_list[4];
                    string update_info = deadline + "\n" + text; // First line of the info file contains deadline
                    create_file(curpath, "display_text.txt");
                    add_to_file(curpath + "/display_text.txt", update_info);
                    create_file(curpath, "attachments.txt");
                    int num_files = stoi(data_list[5]);
                    for(int i = 0; i < num_files; i++){
                        string filename = data_list[6 + i];
                        header = "";
                        data = "";
                        recv_data(cli_sock, header, data);
                        create_file(curpath, filename);
                        add_to_file(curpath + "/" + filename, data);
                        add_to_file(curpath + "/attachments.txt", filename);
                        send_data(cli_sock, true, instructor_state);
                    }
                }
                else{
                    curpath += "/type_2";
                    if(entry_exists(curpath + "/categories.txt", category) == false){
                        create_entry(curpath, curpath + "/categories.txt", category);
                    }
                    curpath += "/" + category;
                    if(entry_exists(curpath + "/updates.txt", update_name) == false){
                        create_entry(curpath, curpath + "/updates.txt", update_name);
                    }
                    curpath += "/" + update_name;
                    string text = data_list[3];
                    string update_info = text; 
                    create_file(curpath, "display_text.txt");
                    add_to_file(curpath + "/display_text.txt", update_info);
                    int num_files = stoi(data_list[4]);
                    for(int i = 0; i < num_files; i++){
                        string filename = data_list[5 + i];
                        header = "";
                        data = "";
                        recv_data(cli_sock, header, data);
                        create_file(curpath, filename);
                        add_to_file(curpath + "/" + filename, data);
                        send_data(cli_sock, true, instructor_state);
                    }
                }
            }
        }
        else if(strings_list[0] == "ASK"){
            pthread_t chat_server_thread;
            int num = stoi(strings_list[1]);
            if(num == 0){
                int type = stoi(data_list[0]);
                string category = data_list[1];
                string update_name = data_list[2];
                view_classroom_update(cli_sock, type, category, update_name, classname, true);
            }
            else if(num == 1){
                string category = data_list[0];
                string update_name = data_list[1];
                curpath += "/type_1";
                if(entry_exists(curpath + "/categories.txt", category) == false){
                    send_data(cli_sock, false, INSTRUCTOR);
                    continue;
                }
                curpath += "/" + category;
                if(entry_exists(curpath + "/updates.txt", update_name) == false){
                    send_data(cli_sock, false, INSTRUCTOR);
                    continue;
                }
                string res = "Submissions for " + update_name + " -\n--------------\n";
                vector<string> students = list_of_entries(curpath + "/students.txt");
                for(string student : students){
                    res += view_submission(student, classname, category, update_name);
                }
                send_data(cli_sock, true, res);
            }
            else if(num == 2){
                string category = data_list[0];
                string update_name = data_list[1];
                string student_name = data_list[2];
                curpath += "/type_1";
                if(entry_exists(curpath + "/categories.txt", category) == false){
                    send_data(cli_sock, false, INSTRUCTOR);
                    continue;
                }
                curpath += "/" + category;
                if(entry_exists(curpath + "/updates.txt", update_name) == false){
                    send_data(cli_sock, false, INSTRUCTOR);
                    continue;
                }
                string res = "Submissions for " + update_name + " -\n--------------\n";
                res += view_submission(student_name, classname, category, update_name);
                send_data(cli_sock, true, res);
            }
            else if(num == 3){
                int type = 1;
                string category = data_list[0];
                string update_name = data_list[1];
                string student_name = data_list[2];
                string filename = data_list[3];
                string path = "Users/" + student_name +"/" + classname + "/" + category + "/" + update_name + "/" + filename;
                if(access(path.c_str(), F_OK) != 0){
                    send_file(cli_sock, false, "");
                    send_data(cli_sock, false, INSTRUCTOR);
                }
                else{
                    send_file(cli_sock, true, path);
                    send_data(cli_sock, true, INSTRUCTOR);
                }
            }
            else if(num == 4){
                show_people_list(cli_sock, classname, true);
            }
            else if(num == 5){
                show_classwork(cli_sock, classname, true);
            }
            else if(num == 7){
                string log_in = LOGGED_IN;
                send_data(cli_sock, true, log_in);
                logged_in(usr);
            }
            else if(num == 8){
                pthread_create(&chat_server_thread, NULL, chat_server, usr);
            }
            else if(num == 9){
                kill(getpid(), SIGHUP);
                sleep(1);
                pthread_cancel(chat_server_thread);
                cout<<"\nChat server closed\n";
                send_data(cli_sock, true, INSTRUCTOR);
            }
        }
    }
}

