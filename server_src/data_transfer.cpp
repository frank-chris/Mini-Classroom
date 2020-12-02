#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include "server.hpp"

using namespace std;

void recv_data(int cli_sock, string &header, string &data){
    int data_recv;
    string temp;
    char temp_header[BUF_SIZE + 1];
    data_recv = recv(cli_sock, temp_header, BUF_SIZE, 0);
    if(data_recv < 0){
        perror("recv() failed");
    }
    temp_header[data_recv] = '\0';
    temp = decrypt (temp_header);
    strcpy (temp_header, temp.c_str());


    header = temp_header;
    data = "";

    char temp_buffer[BUF_SIZE + 1];
    
    vector<string> strings_list = split_string(header);
    string buffer;
    int data_to_recv = atoi(strings_list[2].c_str());
    while((data_to_recv > 0) && ((data_recv = recv(cli_sock, temp_buffer, BUF_SIZE, 0)) > 0)){
        if(data_recv < 0){
            perror("recv() failed");
        }
        temp_buffer[data_recv] = '\0';
        temp = decrypt (temp_buffer);
        strcpy (temp_buffer , temp.c_str());
        buffer = temp_buffer;
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
    string len = to_string(msg.length());
    string resp = code + SPLITTER + len;
    resp = encrypt(resp);
    // cout<<resp<<endl;
    if(send(cli_sock, resp.c_str(), BUF_SIZE, 0) < 0){
        perror("send() failed");
    }
    int data_sent;
    // cout<<msg<<endl;
    msg = encrypt(msg);
    // cout<<msg<<endl;
    if((data_sent = send((cli_sock), msg.c_str(), stoi(len), 0)) != stoi(len)){
        perror("send() failed");
        exit(1); // Replace this with fail message
        // fail_msg();
    }
}

void send_file(int cli_sock, bool ok, string filepath){
    string code;
    if(ok){
        code = "OK";
    }
    else{
        code = "NOK";
        string len = 0;
        string resp = code + SPLITTER + len;
        resp = encrypt (resp);
        if(send(cli_sock, resp.c_str(), BUF_SIZE, 0) < 0){
            perror("send() failed");
        }
        return;
    }
    FILE * fptr = fopen(filepath.c_str(), "r");
    if(fptr == NULL){
        printf("Filepath %s does not exists.\n", filepath.c_str());
        // But this has probably already been handled at an upper level
    }
    fseek(fptr, 0L, SEEK_END);
    long int filesize = ftell(fptr);
    rewind(fptr);
    if(fclose(fptr) != 0){
        perror("fclose() failed");
    }
    string len = to_string(filesize);
    string resp = code + SPLITTER + len;
    resp = encrypt (resp);
    if(send(cli_sock, resp.c_str(), BUF_SIZE, 0) < 0){
        perror("send() failed");
    }
    int fd = open(filepath.c_str(), O_RDONLY);
    int trials = 3; // 3 chances to send the file
    while(sendfile(cli_sock, fd, NULL, filesize) != filesize){
        perror("sendfile() failed");
        if(trials-- <= 0){
            break;
        }
    }
    close(fd);
}
