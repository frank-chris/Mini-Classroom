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

//utils
vector<string> split_string(string);
char *join_str_int(char *, int);
int get_file_size(string);
char getch_pwd();
int get_response_file(user, string);

//handle
void handle_user(user);
int get_response(user);
int send_request(user, char *, string, int);
int send_file(user, string, int);

//logging
void login_user(user);
void register_user(user);

//entering
void create_classroom(user);
void get_all_courses(user);
void enrol_classroom(user);
void enter_classroom(user);
void get_joined_courses(user);

//instructor
void create_post(user);
void upload_file(user);
void view_all_submissions(user);
void view_particular_submission(user);
void view_post(user);
void download_file(user);
void get_people(user);
void get_classwork(user);
void exit_class(user);

//student
void view_submission(user);
void make_submission(user);

#endif /* CLIENT_HPP */