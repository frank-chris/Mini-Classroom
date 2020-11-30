#include "client.hpp"

void create_post(user usr)
{
    //Modify this in accordance with types
    string type, category, deadline, assignment_name, desc;
    vector<string> file_names;
    int num_files;
    cout << "Type:    " << flush;
    cin >> type;
    cout << "Category:    " << flush;
    cin >> category;
    cout << "Number of Files:    " << flush;
    cin >> num_files;

    for (int i = 0; i < num_files; i++)
    {
        cout << "Enter File ";
        cout << i + 1;
        cout << ":    ";
        cout << flush;

        string temp;
        cin >> temp;
        file_names.push_back(temp);
    }

    cout << "Deadline:    " << flush;
    cin >> deadline;
    cout << "Assignment Name:    " << flush;
    cin >> assignment_name;
    cin.ignore();
    cout << "Description:    " << flush;
    getline(cin, desc);

    string to_send = type + delim + category + delim + to_string(num_files) + delim;
    for (int i = 0; i < num_files; i++)
    {
        to_send = to_send + file_names[i] + delim;
    }
    to_send = to_send + deadline + delim + assignment_name + delim + desc;

    int len = to_send.length();

    char sub_header[1024] = "SEND|0|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);
    get_response(usr);

    for (int i = 0; i < num_files; i++)
    {
        upload_file(usr);
    }
}

void upload_file(user usr)
{
    string path;
    cout << "File Path:   " << flush;
    cin >> path;
    int len = get_file_size(path);
    if (len == -1)
        return;

    char sub_header[1024] = "SEND|0|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
    send_file(usr, path, len);
}

void view_all_submissions(user usr)
{
    string category, assignment_name;
    cout << "Category:    " << flush;
    cin >> category;
    cout << "Assignment Name:    " << flush;
    cin >> assignment_name;

    string to_send = category + delim + assignment_name;
    int len = to_send.length();

    char sub_header[1024] = "ASK|1|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);
}

void view_particular_submission(user usr)
{
    string category, assignment_name, student;
    cout << "Category:    " << flush;
    cin >> category;
    cout << "Assignment Name:    " << flush;
    cin >> assignment_name;
    cout << "Student Name:    " << flush;
    cin >> student;

    string to_send = category + delim + assignment_name + delim + student;
    int len = to_send.length();

    char sub_header[1024] = "ASK|2|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);
}

void view_post(user usr)
{
    string type, category, assignment_name;
    cout << "Type:    " << flush;
    cin >> type;
    cout << "Category:    " << flush;
    cin >> category;
    cout << "Assignment Name:    " << flush;
    cin >> assignment_name;

    string to_send = type + delim + category + delim + assignment_name;
    int len = to_send.length();

    char sub_header[1024] = "ASK|0|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);
}

void download_file(user usr)
{
    string category, assignment_name, student;
    cout << "Category:    " << flush;
    cin >> category;
    cout << "Assignment Name:    " << flush;
    cin >> assignment_name;
    cout << "Student Name:    " << flush;
    cin >> student;

    string to_send = category + delim + assignment_name + delim + student;
    int len = to_send.length();

    char sub_header[1024] = "ASK|3|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);
    string file_name = category + "_" + assignment_name + "_" + student;
    get_response_file(usr, file_name);
}

void get_people(user usr)
{
    int len = 0;

    char sub_header[1024] = "ASK|4|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}

void get_classwork(user usr)
{
    int len = 0;

    char sub_header[1024] = "ASK|5|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}

void exit_class(user usr)
{
    int len = 0;

    char sub_header[1024] = "ASK|7|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, "", len);
}