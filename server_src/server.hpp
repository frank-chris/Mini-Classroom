#ifndef SERVER_HPP
#define SERVER_HPP

using namespace std;

#include <string>
#include <vector>
#include <netinet/in.h>

#define SPLITTER '|'
#define BUF_SIZE 1024

// Chat defines
#define LENGTH 2048
#define CHAT_PORT 9000
#define MAX_CLIENTS 100
#define BUFFER_SZ 2048

// Prompt messages sent for each state. Note that these defines are of const char[] type, so better
// convert them to string first

#define HANDLE_CLI "\n\nWelcome to Mini-Classroom-\n\
    To log in to an existing account, type: login \n\
    To create a new account account, type: register\n"

#define LOGGED_IN "\n\nYou are logged in, you can perform the following actions-\n\
    To view the list of courses, type: showall\n\
    To view the list of enrolled courses, type: showmy\n\
    To create class a new class, type: create \n\
    To enroll in an existing class, type: enroll \n\
    To join a class, type: join \n"

#define STUDENT "\n\nYou have entered the classroom, you can perform the following actions-\n\
    To see the Classwork section, type: classwork \n\
    To see the People section, type: people \n\
    To view your submission for a work, type viewsub \n\
    To make a submission for a work, type makesub \n\
    To view a classroom post, type viewpost \n\
    To download an attachment, type downloadattachment \n\
    To logout of the class,  type exitclass \n\
    To join a chat session, type joinsession\n\
    Once logged in, press exit to exit the chat\n"


#define INSTRUCTOR "\n\nYou have entered the classroom, you can perform the following actions-\n\
    To see the Classwork section, type: classwork \n\
    To see the People section, type: people \n\
    To add a new post, type createpost \n\
    To view all submissions of a work, type viewallsubs \n\
    To view a particular student’s submission, type viewparticularsubs \n\
    To view a classroom post, type viewpost \n\
    To download a student’s submission, type downloadsub \n\
    To logout of the class, type exitclass \n\
    To create a chat session, type createsession\n\
    Once logged in, press exit to exit the chat\n"


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

typedef struct chat_arg{
    int cli_sock;
    string name;
    bool active;
    int p_code;
}chat_arg;

/* Chat client structure */
typedef struct{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char name[32];
    int cli_sock;
} client_t;

// Filesystem functions
void initFS();
void makedir(string path, string dirname);
void create_file(string path, string filename);

// Chat functions
void queue_add(client_t *cl);
void queue_remove(int uid);
void send_message(char *s, int uid);
void* handle_chat_client(void *arg);
void* chat_server(void* arg);
void* send_msg_handler(void* arg);
void* recv_msg_handler(void* arg);
void* chat_client(void* arg);


// Server functions
void *new_client_thread(void* arg);
void handle_client(User *usr);
int add_user(string username, string passwd);
int check_credentials(string username, string passwd);
void logged_in(User *usr);
void student(User* usr, string classname);
void instructor(User* usr, string classname);
void show_people_list(int cli_sock, string classname, bool instructor);
void show_classwork(int cli_sock, string classname, bool instructor);
void view_classroom_update(int cli_sock, int type, string category, string update_name, string classname, bool instructor);
void download_attachment(int cli_sock, int type, string category, string update_name, string classname, string filename);


// Data transfer functions
void recv_data(int cli_sock, string &header, string &data);
void send_data(int cli_sock, bool ok, string msg);
void send_file(int cli_sock, bool ok, string filepath);

// Helper functions
vector<string> split_string(string s);
bool entry_exists(string file, string query);
void create_entry(string directory, string file, string name);
void add_to_file(string filename, string msg);
void add_pair(string username, string passwd);
bool check_pair(string username, string passwd);
string read_file(string filename);
string file_contents(string filename); // Only those files that have a single word in every line
vector<string> list_of_entries(string filename);
string view_submission(string student, string course, string category, string update);

#endif /* SERVER_HPP */
