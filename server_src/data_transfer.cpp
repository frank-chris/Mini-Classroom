#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "server.hpp"

using namespace std;

void recv_data(int cli_sock, string *header, string *data){
    int data_recv;
    if((data_recv = recv(cli_sock, header, BUF_SIZE, 0)) < 0){
        perror("recv() failed");
    }
    data = "";
    string buffer;
    vector<string> strings_list = split_string(header);
    int data_to_recv = atoi(strings_list[2]);
    while((data_to_recv > 0) && ((data_recv = recv(cli_sock, buffer, BUF_SIZE, 0)) > 0)){
        data += buffer;
        data_to_recv -= data_recv;
    }
}

void send_data(int cli_sock, bool ok, string msg){
    string code;
    if(ok){
        code = "OK";
    }
    else{
        code = "NOK";
    }
    string len = atoi(msg.length());
    string resp = code + " " + len;
    if(send(cli_sock, resp, BUF_SIZE, 0) < 0){
        perror("send() failed");
    }
    int data_sent;
    if((data_sent = send((usr -> cli_sock), msg, len, 0)) != len){
        perror("send() failed");
        exit(1); // Replace this with fail message
        // fail_msg();
    }
}

void send_file(int cli_sock, string filepath){
    fopen(filepath);
}
