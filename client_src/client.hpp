#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <unistd.h>
#define BUFSIZE 1024

using namespace std;

char delim = '|'; 
string delim_s = "|";

struct user
{
    int sock;
};

//handle
void handle_user(user);
char * join_str_int(char *, int);
vector <string> split_string(string);
int get_response(user);

//logging
void login_user (user);
void register_user (user);

#endif /* CLIENT_HPP */