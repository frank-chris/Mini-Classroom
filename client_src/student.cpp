#include "client.hpp"

void view_submission(user usr)
{
    string category, assignment_name;
    cout << "Category:    " << flush;
    cin >> category;
    cout << "Assignment Name:    " << flush;
    cin >> assignment_name;

    string to_send = category + delim + assignment_name;
    int len = to_send.length();

    char sub_header[1024] = "ASK|2|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);
}

void make_submission(user usr)
{
    string category, assignment_name, file_name;
    cout << "Category:    " << flush;
    cin >> category;
    cout << "Assignment Name:    " << flush;
    cin >> assignment_name;
    cout << "File Name:    " << flush;
    cin >> file_name;

    string to_send = category + delim + assignment_name + delim + file_name;
    int len = to_send.length();

    char sub_header[1024] = "SEND|0|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);
    get_response(usr);
    upload_file(usr);
}

void join_chat_session(user usr)
{
    string code;
    cout << "Enter code:   " << flush;
    cin >> code;
    int p_code = stoi(code);
    string to_send = code;
    int len = to_send.length();

    char sub_header[1024] = "ASK|8|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);

    pthread_t chat_thread;
    if (pthread_create(&chat_thread, NULL, chat_client, &p_code) != 0)
    {
        perror("thread creation error");
        return;
    }

    pthread_join(chat_thread, NULL);

    strcpy(sub_header, "ASK|9|");
    header = join_str_int(sub_header, len);
    send_request(usr, header, to_send, len);
}

void download_attachment(user usr)
{
    string type, category, assignment_name, filename;
    cout << "Type:    " << flush;
    cin >> type;
    cout << "Category:    " << flush;
    cin >> category;
    cout << "Assignment Name:    " << flush;
    cin >> assignment_name;
    cout << "File Name:    " << flush;
    cin >> filename;

    string to_send = type + delim + category + delim + assignment_name + delim + filename;
    int len = to_send.length();

    char sub_header[1024] = "ASK|3|";
    char *header = join_str_int(sub_header, len);

    send_request(usr, header, to_send, len);
    string filepath;
    get_response_file(usr, filename);
}
