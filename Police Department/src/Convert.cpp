#include "../include/Convert.h"
#include <sstream>
int stringToInt(string in){
    stringstream prom;
    prom << in;
    int out;
    prom >> out;
    return out;
}

string intToString(int in){
    stringstream prom;
    prom << in;
    string out;
    prom >> out;
    return out;
}
