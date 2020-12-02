#include "client.hpp"
#include <sstream>
#include <sys/stat.h>
#include <termios.h>

char *join_str_int(char *req, int len)
{
    string clen_ = to_string(len);
    char *clen = new char[clen_.length() + 1];
    strcpy(clen, clen_.c_str());
    strcat(req, clen);
    return req;
}

//function to break string by a delimeter
vector<string> split_string(string s)
{
    stringstream ss(s);
    vector<string> all;
    string v;
    while (getline(ss, v, delim))
    {
        all.push_back(v);
    }
    return all;
}

/*
Returns the file size of the file present on the path.
It returns -1 in case of an error
*/
int get_file_size(string path)
{
    struct stat st;
    if (stat(path.c_str(), &st) == -1)
    {
        perror("Path error");
        return -1;
    }
    return st.st_size;
}

/*
(Diasable echoing) Hides the password typed by the user 
*/
char getch_pwd()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}