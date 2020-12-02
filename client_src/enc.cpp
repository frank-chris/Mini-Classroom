#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/*
This encryption uses a substitution cypher.
*/
vector <int> rd = {
    124, 83, 43, 101, 56, 67, 49, 68, 58, 82, 99, 71, 115, 34, 107, 88, 91, 50, 64, 72, 123, 118,
    89, 44, 46, 74, 59, 94, 95, 90, 62, 110, 45, 100, 35, 119, 103, 96, 41, 54, 98, 112, 52, 111,
    121, 113, 105, 32, 126, 73, 120, 60, 84, 75, 48, 92, 81, 39, 116, 104, 61, 93, 38, 77, 85, 108,
    40, 65, 69, 47, 57, 87, 102, 63, 114, 79, 80, 42, 122, 66, 55, 106, 109, 51, 117, 76, 125, 86,
    97, 33, 70, 37, 36, 53, 78
};

map <int, int> enc, decr;

void init_enc_decr(){
        for (int i=32; i<127; i++){
            enc[i] = rd[i-32];
            decr[rd[i-32]] = i;
        }
}

/*
converts the input string to its encrypted form
*/
string encrypt(string inp){
    if (enc.size()==0){
        init_enc_decr();
    }
    string out = "";
    for (int i=0; i<inp.length(); i++){
        if ((int)inp[i]<127 && (int)inp[i]>=32)
            out = out + (char)enc[inp[i]];
        else out = out + inp[i];
    }
    return out;
}
/*
converts the decoded string to the originial string
*/
string decrypt (string out){
    if (enc.size()==0){
        init_enc_decr();
    }

    string inp = "";
    for (int i=0; i<out.length(); i++){
        if ((int)out[i]<127 && (int)out[i]>=32)
            inp = inp + (char)decr[out[i]];
        else inp = inp + out[i];
    }
    return inp;
}

