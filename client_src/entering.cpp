#include "client.hpp"

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

void get_all_courses(user usr)
{
    int len = 0;
    char sub_header[1024] = "ASK|0|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}

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

void get_joined_courses(user usr)
{
    int len = 0;
    char sub_header[1024] = "ASK|2|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}

void logout_user (user usr)
{
    int len = 0;
    char sub_header[1024] = "ASK|3|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}