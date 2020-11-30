#include "client.hpp"

void login_user(user usr){
    string username, password; 
    cout<<"Username:    ";    cin>>username;
    system ("stty -echo");
    cout<<"Password:    ";    cin>>password;
    system ("stty echo");   cout<<endl;

    int len = username.length() + password.length() + 1;
    char sub_header [1024] = "SEND|0|";
    char * header = join_str_int(sub_header, len);

    int num_bytes = send(usr.sock, header, 1024, 0);
    if (num_bytes<0) perror("send error");

    string cred = username + delim + password;
    num_bytes = send (usr.sock, cred.c_str(), len, 0);
    if (num_bytes<0) perror ("send error");
    cout<<cred<<endl;
}

void register_user (user usr){
    string username, password, password_temp;
    cout<<"Username:    ";    cin>>username;
    bool valid = false;
    while (valid) 
    {
        system ("stty -echo");
        cout<<"Password:    ";    cin>>password;
        cout<<"Retype Password:    "; cin>>password_temp;
        system ("stty echo");   cout<<endl;
        if (password_temp != password)
            cout<<"Passwords don't match"<<endl;
        else valid = true;
    }

    int len = username.length() + password.length() + 1;
    char sub_header [1024] = "SEND|1|";
    char * header = join_str_int(sub_header, len);

    int num_bytes = send(usr.sock, header, 1024, 0);
    if (num_bytes<0) perror("send error");

    num_bytes = send (usr.sock, (username + string (1, delim) + password).c_str(), len, 0);
}
