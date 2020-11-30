#include "client.hpp"

void login_user(user usr)
{
    string username, password;
    cout << "Username:    ";
    cin >> username;
    cout << "Password:    ";
    password = "";

    char ch = '\0';
    cin.ignore();
    while (1)
    {

        ch = getch_pwd();
        if (ch == '\n')
            break;
        password = password + ch;
        cout << "*" << flush;
    }
    cout << endl;

    int len = username.length() + password.length() + 1;
    char sub_header[1024] = "SEND|0|";
    char *header = join_str_int(sub_header, len);
    string cred = username + delim + password;

    send_request(usr, header, cred, len);
}

void register_user(user usr)
{
    string username, password, password_temp;
    cout << "Username:    ";
    cin >> username;
    bool valid = false;
    char ch = '\0';

    while (valid)
    {
        cout << "Password:    ";
        password = "";

        ch = '\0';
        cin.ignore();
        while (1)
        {
            ch = getch_pwd();
            if (ch == '\n')
                break;
            password = password + ch;
            cout << "*" << flush;
        }
        cout << endl;

        cout << "Retype Password:    ";
        password_temp = "";

        ch = '\0';
        while (1)
        {
            ch = getch_pwd();
            if (ch == '\n')
                break;
            password_temp = password_temp + ch;
            cout << "*" << flush;
        }
        cout << endl;

        if (password_temp != password)
            cout << "Passwords don't match" << endl;

        else
            valid = true;
    }

    int len = username.length() + password.length() + 1;
    char sub_header[1024] = "SEND|1|";
    char *header = join_str_int(sub_header, len);
    string cred = username + delim + password;

    send_request(usr, header, cred, len);
}
