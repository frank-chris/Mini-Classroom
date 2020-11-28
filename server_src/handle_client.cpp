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
    string message = HANDLE_CLI;
    send_data(cli_sock, true, message);
    while(true){
        if((usr -> active) == false){
            break;
        }

        string header;
        string data;
        int data_recv;
        recv_data(cli_sock, &header, &data);
        vector<string> strings_list = split_string(header);
        vector<string> parameters = split_string(data);
        string username = parameters[0];
        string passwd = parameters[1];
        if(strings_list[0] == "SEND"){
            int num = atoi(strings_list[1]);
            if(num == 0){
                int ret_val = check_credentials(username, passwd);
                if(ret_val == 1){
                    usr -> name = username;
                    string new_message = LOGGED_IN;
                    send_data(cli_sock, true, new_message);
                    logged_in(usr);
                }
                else if(ret_val == 0){
                    send_data(cli_sock, false, message); // Not sending a good response
                }
            }
            else if(num == 1){
                int ret_val = add_user(username, passwd);
                if(ret_val == 1){
                    usr -> name = username;
                    string new_message = LOGGED_IN;
                    send_data(cli_sock, true, new_message);
                    logged_in(usr);
                }
                else if(ret_val == 0){
                    send_data(cli_sock, false, message);
                }
            }
        }
    }
}
