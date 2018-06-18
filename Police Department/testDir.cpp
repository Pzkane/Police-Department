#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    string line;
    ifstream testDir("PD/Dispatcher/DispatcherData.txt");
    while(getline(testDir,line)){
        cout<<line<<endl;
    }

    return 0;
}
