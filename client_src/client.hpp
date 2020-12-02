#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#define BUFSIZE 1024
#define delim '|'
// Chat defines
#define LENGTH 2048
#define CHAT_PORT 9000

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
void logout_user(user);

//chat
void str_overwrite_stdout();
void str_trim_lf(char*, int);
void* send_msg_handler(void*);
void* recv_msg_handler(void*);
void* chat_client(void*);

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
void chat_session(user);
void join_chat_session(user);

//student
void view_submission(user);
void make_submission(user);

#endif /* CLIENT_HPP */