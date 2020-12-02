#include "client.hpp"

//Handles create classroom user command
void create_classroom(user usr)
{
    string cl_name;
    cout << "Name of the classroom:   " << flush;
    cin >> cl_name;

    int len = cl_name.length();

    char sub_header[1024] = "SEND|0|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, cl_name, len);
}

//Handles get all courses user command
void get_all_courses(user usr)
{
    int len = 0;
    char sub_header[1024] = "ASK|0|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}

//Handles enrollment in a course
void enrol_classroom(user usr)
{
    string cl_name;
    cout << "Enrol in the classroom:    " << flush;
    cin >> cl_name;

    int len = cl_name.length();

    char sub_header[1024] = "SEND|1|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, cl_name, len);
}

//Handles the viewing of classroom by a user
void enter_classroom(user usr)
{
    string cl_name;
    cout << "Enter the classroom:    " << flush;
    cin >> cl_name;

    int len = cl_name.length();

    char sub_header[1024] = "ASK|1|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, cl_name, len);
}

//Displays a list of the courses that the user has joined
void get_joined_courses(user usr)
{
    int len = 0;
    char sub_header[1024] = "ASK|2|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}

//Logs the user out 
void logout_user (user usr)
{
    int len = 0;
    char sub_header[1024] = "ASK|3|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}