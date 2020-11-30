#include <stdio.h>
#include "client.hpp"

int get_response(user usr){
    char buffer[BUFSIZE + 1];
    int num_bytes = read(usr.sock, buffer, BUFSIZE);
    if (num_bytes < 0)  perror ("send error");
    buffer[num_bytes] = '\0';

    vector <string> keys = split_string(buffer);
    int len = atoi(keys[1].c_str());

    int rec_bytes = 0;
    while (rec_bytes < len)
    {
        num_bytes = read (usr.sock, buffer, min(BUFSIZE, len - rec_bytes));
        buffer[num_bytes] = '\0';
        if (num_bytes < 0)  perror ("send error");
        rec_bytes += num_bytes;
    }
}


void handle_command(user usr){

    login_user(usr);
    ;
}


void handle_user(user usr){
    char buffer [BUFSIZE + 1]; memset (buffer, '\0', sizeof(buffer));
    int num_bytes = 0;
    while (1){
        get_response(usr);
        handle_command(usr);
        get_response(usr);
    }
}