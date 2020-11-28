#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "server.hpp"

using namespace std;


int add_user(string username, string passwd){
    if(entry_exists("Users/users.txt", username)){
        return 0;
    }
    create_entry("Users", username);
    add_pair(username, passwd);
    return 1;
}

int check_credentials(string username, string passwd){
    if(check_pair(username, passwd)){
        return 1;
    }
    return 0;
}



void handle_client(User *usr){
    int cli_sock = usr -> cli_sock;
    string message = "Please enter your Login Credentials\n";
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
        vector<string> parameters = split_string(buffer);
        string username = parameters[0];
        string passwd = parameters[1];
        if(strings_list[0] == "SEND"){
            int num = atoi(strings_list[1]);
            if(num == 0){
                int ret_val = check_credentials(username, passwd);
                if(ret_val == 1){
                    usr -> name = username;
                    send_resp(1, "");
                    logged_in(usr);
                }
                else if(ret_val == 0){
                    send_resp(0, "Password incorrect");
                }
            }
            else if(num == 1){
                int ret_val = add_user(username, passwd);
                if(ret_val == 1){
                    usr -> name = username;
                    send_resp(1, "");
                    logged_in(usr);
                }
                else if(ret_val == 0){
                    send_resp(0, "Username already exists");
                }
            }
        }
    }
}
