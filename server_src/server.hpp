#ifndef SERVER_HPP
#define SERVER_HPP

#define SPLITTER '|'
#define BUF_SIZE 1024

// Prompt messages sent for each state. Note that these defines are of const char[] type, so better
// convert them to string first

#define HANDLE_CLI "Welcome to Mini-Classroom\n\
    To log in to an existing account, type: login \n\
    To create a new account account, type: register\n"

#define LOGGED_IN "You are logged in, you can perform the following actions\
    To view the list of courses, type: showall\n\
    To view the list of enrolled courses, type: showmy\n\
    To create class a new class, type: create \n\
    To enroll in an existing class, type: enroll \n\
    To join a class, type: join \n"

#include <bits/stdc++.h>

typedef struct sockets
{
    int cli_sock;
    int serv_sock;
}   sockets;

typedef struct User{
    int cli_sock;
    string name;
    bool active;
}User;

// Filesystem functions
void initFS();
void makedir(string path, string dirname);
void create_file(string path, string filename);

// Server functions
void* new_client_thread(void* arg);
void handle_client(User *usr);
int add_user(string username, string passwd);
int check_credentials(string username, string passwd);

// Data transfer functions
void recv_data(int cli_sock, string &header, string &data);
void send_data(int cli_sock, bool ok, string msg);

// Helper functions
vector<string> split_string(string s);
bool entry_exists(string file, string query);
void create_entry(string directory, string file, string name);
void add_to_file(string filename, string msg);
void add_pair(string username, string passwd);
bool check_pair(string username, string passwd);
string file_contents(string filename); // Only those files that have a single word in every line

#endif /* SERVER_HPP */
