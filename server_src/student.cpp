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

void show_classwork(int cli_sock, string classname){

    string type_1 = "Classrooms/" + classname + "/type_1/";
    string type_2 = "Classrooms/" + classname + "/type_2/";
    
    string res = "Classwork-\n";
    res += "--------------\n";

    // open type_1 directory
    DIR * dp = opendir(type_1.c_str());
    
    // check if directory was opened
    if(dp == NULL){
        perror("opendir error");
    }

    // loop through the entries of the type_1 directory
    struct dirent *d;
    while ((d = readdir(dp)) != NULL) {
        // ignore if entry is . or ..
        if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, "..")){
            continue;
        }
        res += string(d->d_name);
        res += "\n--------------\n";

        DIR * dp_2 = opendir((type_1 + string(d->d_name)).c_str());
        // check if directory was opened
        if(dp_2 == NULL){
            perror("opendir error");
        }

        struct dirent *d_2;
        while ((d_2 = readdir(dp_2)) != NULL)
        {
            // ignore if entry is . or ..
            if (!strcmp(d_2->d_name, ".") || !strcmp(d_2->d_name, "..")){
                continue;
            }
            res += string(d_2->d_name);
            res += "\n";
        }
        closedir(dp_2);
    }
    // close directory
    closedir(dp);


    res += "--------------\n";

    // open type_2 directory
    dp = opendir(type_2.c_str());
    
    // check if directory was opened
    if(dp == NULL){
        perror("opendir error");
    }

    // loop through the entries of the type_2 directory

    while ((d = readdir(dp)) != NULL) {
        // ignore if entry is . or ..
        if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, "..")){
            continue;
        }
        res += string(d->d_name);
        res += "\n--------------\n";

        DIR * dp_2 = opendir((type_2 + string(d->d_name)).c_str());
        // check if directory was opened
        if(dp_2 == NULL){
            perror("opendir error");
        }

        struct dirent *d_2;
        while ((d_2 = readdir(dp_2)) != NULL)
        {
            // ignore if entry is . or ..
            if (!strcmp(d_2->d_name, ".") || !strcmp(d_2->d_name, "..")){
                continue;
            }
            res += string(d_2->d_name);
            res += "\n";
        }
        closedir(dp_2);
    }
    // close directory
    closedir(dp);

    res += "--------------\n";
    res += STUDENT;
    send_data(cli_sock, true, res);
}

void show_people_list(int cli_sock, string classname){
    string student_path = "Classrooms/" + classname + "/students.txt";
    string instructor_path = "Classrooms/" + classname + "/instructors.txt";

    string res = "People-\n";
    res += "--------------\n";
    res += "Instructors-\n\n";
    res += file_contents(instructor_path);
    res += "--------------\n";
    res += "Students-\n\n";
    res += file_contents(student_path);
    res += "--------------\n";
    res += STUDENT;
    send_data(cli_sock, true, res);
}

void view_classroom_update(int cli_sock, int type, string category, string update_name, string classname){
    string path;
    if(type == 1){
        path = "Classrooms/" + classname + "/type_1/" + category + "/" + update_name;
    }
    else if(type == 2){
        path = "Classrooms/" + classname + "/type_2/" + category + "/" + update_name;
    }
    if(access((path + "/display_text.txt").c_str(), F_OK) != 0){
        cout<<"Path does not exist"<<endl;
        string res = STUDENT;
        send_data(cli_sock, false, res);
    }
    else{
        string res = file_contents(path + "/display_text.txt");
        res += "\n--------------\n";
        res += STUDENT;
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
                string taskname = data_list[1];
                string filename = data_list[2];
                string filedir = "Classrooms/" + classname +"/type_1/" + category + "/" + taskname;
                string filepath = "Classrooms/" + classname +"/type_1/" + category + "/" + taskname + "/" + filename;
                if(access(filepath.c_str(), F_OK) == 0){
                    send_data(cli_sock, false, student_state);
                    // File already exists
                }
                else{
                    send_data(cli_sock, true, "Uploading...");
                    create_file(filedir, filename);
                    header = "";
                    data = "";
                    recv_data(cli_sock, header, data);
                    add_to_file(filepath, data);
                    send_data(cli_sock, true, student_state);
                }
            }
        }
        else if(strings_list[0] == "ASK"){
            int num = stoi(strings_list[1]);
            if(num == 0){
                int type = stoi(data_list[0]);
                string category = data_list[1];
                string update_name = data_list[2];
                view_classroom_update(cli_sock, type, category, update_name, classname);
            }
            else if(num == 2){
                string category = data_list[0];
                string update_name = data_list[1];
                string path = "Classrooms/" + classname + "/type_1/" + category + "/" + update_name + "/" + "updates.txt";
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
                show_people_list(cli_sock, classname);
            }
            else if(num == 5){
                show_classwork(cli_sock, classname);
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
