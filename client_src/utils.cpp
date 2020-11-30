#include "client.hpp"
#include <sstream>

char * join_str_int(char *req, int len){
    string clen_ = to_string(len);
    char * clen = new char [clen_.length() + 1];
    strcpy (clen, clen_.c_str());
    strcat (req, clen);
    return req;
}

vector<string> split_string(string s){
    stringstream ss(s);
    vector<string> all;
    string v;
    while (getline(ss, v, delim ))
    {
        all.push_back(v);
    }
    return all;
}
