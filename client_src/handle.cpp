#include "client.hpp"
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int get_response(user usr)
{
    char buffer[BUFSIZE + 1];
    int num_bytes = read(usr.sock, buffer, BUFSIZE);
    if (num_bytes < 0)
        perror("send error");
    buffer[num_bytes] = '\0';

    vector<string> keys = split_string(buffer);

    if (keys[0] == "OK")
    {
        cout << "Successful" << endl;
    }
    else
    {
        cout << "Failed" << endl;
    }
    cout << "--------------------------\n\n"
         << endl;

    int len = atoi(keys[1].c_str());

    int rec_bytes = 0;
    while (rec_bytes < len)
    {
        num_bytes = read(usr.sock, buffer, min(BUFSIZE, len - rec_bytes));
        buffer[num_bytes] = '\0';
        if (num_bytes < 0)
            perror("send error");
        rec_bytes += num_bytes;
        cout << buffer << flush;
    }
    cout << endl;
}

int send_request(user usr, char *header, string data, int len)
{

    int num_bytes = send(usr.sock, header, 1024, 0);
    if (num_bytes < 0)
    {
        perror("send error");
        return -1;
    }

    if (len)
    {
        num_bytes = send(usr.sock, data.c_str(), len, 0);
        if (num_bytes < 0)
        {
            perror("send error");
            return -1;
        }
    }

    return 0;
}

int send_file(user usr, string path, int len)
{
    int read_fd = open(path.c_str(), O_RDONLY);
    int num_bytes = sendfile(usr.sock, read_fd, NULL, BUFSIZE);
    cout << "Total Bytes Sent: " << num_bytes << endl;
    cout << "Total Bytes Expected to be sent: " << len << endl;
}

void handle_command(user usr)
{
    string command;
    cout << "Enter a command:    " << flush;
    getline(cin, command);

    bool valid = true;

    do
    {
        valid = true;
        //Logging
        if (command == "login")
            login_user(usr);
        else if (command == "register")
            register_user(usr);

        //Entering
        else if (command == "create")
            create_classroom(usr);
        else if (command == "showall")
            get_all_courses(usr);
        else if (command == "enroll")
            enrol_classroom(usr);
        else if (command == "join")
            enter_classroom(usr);
        else if (command == "showmy")
            get_joined_courses(usr);

        //Instructor
        else if (command == "classwork")
            get_classwork(usr);
        else if (command == "people")
            get_people(usr);
        else if (command == "showmy")
            get_joined_courses(usr);
        //else if (command == "showmy") get_joined_courses(usr);
        //else if (command == "showmy") get_joined_courses(usr);
        //else if (command == "showmy") get_joined_courses(usr);
        //else if (command == "showmy") get_joined_courses(usr);
        //else if (command == "showmy") get_joined_courses(usr);
        //create_post(usr);
        //view_all_submissions(usr);
        //view_particular_submission(usr);
        //view_post(usr);
        // download_file(usr);
        //get_people(usr);
        // get_classwork(usr);
        // exit_class(usr);

        else
        {
            valid = false;
            cout << "Invalid command" << endl;
        }
    } while (valid == false);
}

void handle_user(user usr)
{
    char buffer[BUFSIZE + 1];
    memset(buffer, '\0', sizeof(buffer));
    int num_bytes = 0;
    cout << "\nConnecting..." << endl;
    cout << "==========>  " << flush;
    get_response(usr);

    while (1)
    {
        handle_command(usr);
        cout << "==========>  " << flush;
        get_response(usr);
    }
}