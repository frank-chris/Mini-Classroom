#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <unistd.h>

typedef struct user
{
    int sock;
} user;

void handle_user(user);
void login (user);
void handle_command (user);

char * join_str_int(char *req, int len){
    string clen_ = to_string(len);
    char * clen = new char [clen_.length() + 1];
    strcpy (clen, clen_.c_str());
    return clen;
}

#endif /* CLIENT_HPP */