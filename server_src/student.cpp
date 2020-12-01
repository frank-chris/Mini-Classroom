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

void show_classwork(int cli_sock, string classname, bool instructor){

    string type_1 = "Classrooms/" + classname + "/type_1/";
    string type_2 = "Classrooms/" + classname + "/type_2/";
    
    string res = "Classwork-\n";
    res += "--------------\n";

    res += "Type 1\n-------\n";

    vector<string> categories = list_of_entries(type_1 + "categories.txt");

    for(string cat : categories){
        res += cat + "-\n";
        vector<string> updates = list_of_entries(type_1 + cat +"/updates.txt");
        for(string upd : updates){
            res += upd + "\n";
        }
        res += "---------------\n\n";
    }

    res += "Type 2\n-------\n";

    categories = list_of_entries(type_2 + "categories.txt");

    for(string cat : categories){
        res += cat + "-\n";
        vector<string> updates = list_of_entries(type_2 + cat +"/updates.txt");
        for(string upd : updates){
            res += upd + "\n";
        }
        res += "---------------\n\n";
    }
    if(instructor){
        res += INSTRUCTOR;
    }
    else{
        res += STUDENT;
    }
    send_data(cli_sock, true, res);
}

void show_people_list(int cli_sock, string classname, bool instructor){
    string student_path = "Classrooms/" + classname + "/students.txt";
    string instructor_path = "Classrooms/" + classname + "/instructors.txt";

    string res = "People-\n";
    res += "--------------\n";
    res += "Instructors-\n";
    res += file_contents(instructor_path);
    res += "--------------\n";
    res += "Students-\n";
    res += file_contents(student_path);
    res += "--------------\n";
    res += STUDENT;
    if(instructor){
        res += INSTRUCTOR;
    }
    else{
        res += STUDENT;
    }
    send_data(cli_sock, true, res);
}

void view_classroom_update(int cli_sock, int type, string category, string update_name, string classname, bool instructor){
    string path;
    if(type == 1){
        path = "Classrooms/" + classname + "/type_1/" + category + "/" + update_name;
    }
    else if(type == 2){
        path = "Classrooms/" + classname + "/type_2/" + category + "/" + update_name;
    }
    if(access((path + "/display_text.txt").c_str(), F_OK) != 0){
        cout<<"Path does not exist"<<endl;
        string res = "";
        if(instructor){
            res += INSTRUCTOR;
        }
        else{
            res += STUDENT;
        }
        send_data(cli_sock, false, res);
    }
    else{
        string res = file_contents(path + "/display_text.txt");
        res += "\n--------------\nThese are the attachments present here-\n";
        res += file_contents(path + "/attachments.txt");
        res += "\n--------------\n";
        if(instructor){
            res += INSTRUCTOR;
        }
        else{
            res += STUDENT;
        }
        send_data(cli_sock, true, res);
    }
}

void download_attachment(int cli_sock, int type, string category, string update_name, string classname, string filename){
    string path;
    if(type == 1){
        path = "Classrooms/" + classname + "/type_1/" + category + "/" + update_name + "/" + filename;
    }
    else if(type == 2){
        path = "Classrooms/" + classname + "/type_2/" + category + "/" + update_name + "/" + filename;
    }

    if(access(path.c_str(), F_OK) == 0){
        send_file(cli_sock, true, path);
        send_data(cli_sock, true, INSTRUCTOR);
    }
    else{
        send_file(cli_sock, false, "");
        send_data(cli_sock, false, INSTRUCTOR);
    }
    

}

void student(User* usr, string classname){
    int cli_sock = usr -> cli_sock;
    string username = usr -> name;
    string student_state = STUDENT;

    cout<<"\nStudent state\n";
    
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
            if(num == 0){
                string category = data_list[0];
                string updatename = data_list[1];
                string filename = data_list[2];
                string subm_dir = "Users/" + username + "/" + classname + "/" + category + "/" + updatename;

                send_data(cli_sock, true, "Uploading...");
                create_file(subm_dir, filename);
                header = "";
                data = "";
                recv_data(cli_sock, header, data);
                add_to_file(subm_dir + "/" + filename, data);
                add_to_file(subm_dir + "/submissions.txt", filename);
                send_data(cli_sock, true, student_state);
            }
        }
        else if(strings_list[0] == "ASK"){
            int num = stoi(strings_list[1]);
            if(num == 0){
                int type = stoi(data_list[0]);
                string category = data_list[1];
                string update_name = data_list[2];
                view_classroom_update(cli_sock, type, category, update_name, classname, false);
            }
            else if(num == 2){
                string category = data_list[0];
                string update_name = data_list[1];
                string res = "Your submissions for " + update_name + " -\n";
                res += view_submission(username, classname, category, update_name);
                send_data(cli_sock, true, res);
            }
            else if(num == 3){
                int type = stoi(data_list[0]);
                string category = data_list[1];
                string update_name = data_list[2];
                string filename = data_list[3];
                download_attachment(cli_sock, type, category, update_name, classname, filename);
            }
            else if(num == 4){
                show_people_list(cli_sock, classname, false);
            }
            else if(num == 5){
                show_classwork(cli_sock, classname, false);
            }
            else if(num == 6){
                
            }
            else if(num == 7){
                string log_in = LOGGED_IN;
                send_data(cli_sock, true, log_in);
                logged_in(usr);
            }
        }
    }
}
