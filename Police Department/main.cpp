#include "include/Member.h"
#include "include/Dispatcher/Dispatcher.h"
#include "include/Sheriff/Sheriff.h"
#include "include/Convert.h"
#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

int main(){
    string line;
    int moneyLine, promLine, taxesLine, exp, counter;
    int izv;
    ifstream Cash;
    ifstream GetLevel;

    do{
        GetLevel.open("PD/Dispatcher/DispatcherData.txt", ios_base::in);
        counter = 0;
        while(getline(GetLevel, line)){
            if (counter == 2){
                exp = stringToInt(line);
            }
            counter++;
        }
        GetLevel.close();


        Member * personDisp;
        Member * personSher;
        personDisp = new Dispatcher();
        do{
                ///Foremost Main menu
            Cash.open("PD/Money.txt", ios_base::in);
            Cash >> moneyLine >> promLine >> taxesLine;
            Cash.close();

            cout<<"Select variant: "<<endl;
            cout<<"1. Dispatcher    2. Sheriff  |   3. End day"<<endl<<endl;
            cout<<"                 0. Exit"<<endl;
            cin>>izv;

            switch(izv){
                case 1:
                    {
                        ///To Dispatcher
                        system("CLS");
                        if(taxesLine > 5000)
                            cout<<"Go pay taxes."<<endl;
                        else{
                            personDisp->getStarted(promLine, moneyLine, taxesLine, exp);
                            izv = 4;
                        }
                        break;
                    }
                case 2:
                    {
                        ///To Sheriff
                        system("CLS");
                        personSher = new Sheriff(moneyLine, promLine, taxesLine);
                        break;
                    }
                case 3:
                    {
                        ///End your day and make a log
                        system("CLS");
                        izv = personDisp->ChangeDay(moneyLine, promLine, taxesLine, exp);
                        break;
                    }
                case 0:
                    {
                        cout<<"Exit? [1/0]"<<endl;
                        cin>>izv;
                        system("CLS");
                        break;
                    }
                default:
                    {
                        cout<<"Choose one of the variants!"<<endl;
                    }
            }
        }while(izv != 1 && izv != 101);
        delete &personDisp;
        delete &personSher;
        moneyLine = NULL; promLine = NULL; taxesLine = NULL; exp = NULL;
    }while(izv != 1);
    return 0;
}
