#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "server.hpp"
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <fstream.h>

using namespace std;

vector<string> split_string(string s){
    stringstream ss(s);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> v(begin, end);
    return v;
}

bool entry_exists(string file, string query){
    ifstream infile(file);
    string entry;
    while(infile >> entry){
        if(entry == query){
            return true;
        }
    }
    return false;
}

// Creates a new directory with name, also adds an entry name to file.
void create_entry(string directory, string file, string name){
    makedir(directory, name);
    
    ofstream outfile;
    outfile.open(file, ios_base::app);
    outfile << name << endl;
}

void add_pair(string username, string passwd){
    ofstream outfile;
    string file = "Users/pairs.txt";
    outfile.open(file, ios_base::app);
    outfile << username << " "<< passwd << endl;
}

bool check_pair(string username, string passwd){
    string file = "Users/pairs.txt";
    ifstream infile(file);
    string u, p;
    while(infile >> u >> p){
        if((u == username) and (p == passwd)){
            return true;
        }
    }
    return false;
}

void add_to_class(string classname, string username, bool instructor){
    if(instructor){
        string path = "Classrooms/" + classname;
        ofstream outfile;
        string file = path + "/" + "instructors.txt";
    }
    else{
        string path = "Classrooms/" + classname;
        ofstream outfile;
        string file = path + "/" + "students.txt";
        path = "Users/" + username;
        makedir()
    }
}

string file_contents(string filename){
    ifstream infile(filename);
    string res = "";
    string buf;
    while(infile >> buf){
        res += buf;
    }
    return res;
}

