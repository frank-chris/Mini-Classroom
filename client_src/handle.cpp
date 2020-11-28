#include <iostream>
#include <stdio.h>
#include "client.hpp"
#define BUFSIZ 1024
using namespace std;


void login (user usr){
    string username, password; 
    cout<<"Username:\t";    cin>>username;
    cout<<"Password:\t";    cin>>password;

    int len = username.length() + password.length() + 1;
    char sub_header [1024] = "SEND 0 ";
    char * header = join_str_int(sub_header, len);

    int num_bytes = send(usr.sock, sub_header, 1024, 0);
    if (num_bytes<0) perror("send error");

    num_bytes = send (usr.sock, (username + password).c_str(), len+1, 0);
}

void handle_command(user usr, char *buffer){
    login(usr);
    ;
}


void handle_user(user usr){
    char buffer [BUFSIZ + 1];
    int num_bytes = 0;
    while (1){
        num_bytes = read(usr.sock, buffer, 1024);
        handle_command(usr, buffer);
    }
}