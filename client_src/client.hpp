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
#define delim '|'

using namespace std;


struct user
{
    int sock;
};

//handle
void handle_user(user);
char * join_str_int(char *, int);
vector <string> split_string(string);
int get_response(user);
int send_request(user, char *, string, int );

//logging
void login_user (user);
void register_user (user);

//Entering
void create_classroom(user);
void get_all_courses(user);
void enrol_classroom(user);
void enter_classroom(user);
void get_joined_courses(user);

#endif /* CLIENT_HPP */