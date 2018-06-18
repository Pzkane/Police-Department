#include "../include/Member.h"
#include "../include/Convert.h"
#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;

Member::Member(){
    //ctor
}

Member::~Member(){
    //dtor
}

void Member::Stats(){
    cout<<"Error?//Stats//"<<endl;
}

void Member::StaffManag(){
    cout<<"Error?"<<endl;
}

void Member::Money(){
    cout<<"Error?"<<endl;
}

void Member::MainMenu(){
    cout<<"Error?"<<endl;
}

void Member::YouDontHaveEnoughMoney(){
    cout<<"You don't have enough money!"<<endl;
}

void Member::getStarted(int a, int b, int c, int d){
    cout<<"Error?"<<endl;
}

int Member::ChangeDay(int a, int b, int c, int d){
    cout<<"Error?"<<endl;
}

int Member::getStamina(string path){
    string junk;
    int stamina;
    ifstream MemberFile(path.c_str());
    MemberFile >> junk >> stamina;
    MemberFile.close();
    return stamina;
}

string Member::StaffTypeName(string type){ //string unit_type
    if(type == "Dispatcher"){           ///Return unit's clean type
        return type;
    }
    if(type == "Officer"){
        return type;
    }
    if(type == "K9_Unit"){
        return "K9 Unit";
    }
    if(type == "SAS_Trooper"){
        return "SAS Trooper";
    }
}

int Member::StaffTypeVal(string type){ //string unit_type
    if(type == "Dispatcher"){          ///Return unit's value
        return 150;
    }
    if(type == "Officer"){
        return 50;
    }
    if(type == "K9_Unit"){
        return 40;
    }
    if(type == "SAS_Trooper"){
        return 100;
    }
}

int Member::Restore(string Type, string path, int CurrentStamina, int money){ //string unit's_type, string unit_filePath, int unit_stamina, int Sheriff/Dispatcher_money
    int cash, value, counter = 0;
    int TypeSStam = this->StaffTypeVal(Type);
    string line, buffer;
    bool atb = false, maxAccess = false;
    ifstream MemberValue(path.c_str());
    MemberValue.close();

    int koef;
    if (Type == "Dispatcher"){  //Making coefficient
        koef = 50;
    }
    else
        koef = 30;

    do{
        cout<<"Your current budget: "<<money<<"$"<<endl;
        cout<<this->StaffTypeName(Type)<<"'s stamina is ";
        cout<<CurrentStamina<<"/"<<TypeSStam<<endl;
        cout<<"1 point of stamina equals to "<<koef<<"$. How much do you want to restore?"<<endl;
        cin>>value;
        value == abs(value);
        if (value == 0){
            cout<<"Quiting..."<<endl;
            break;
        }else{
            if (value > TypeSStam || value > TypeSStam - CurrentStamina){ //Logical operations
                cout<<"Max restore value is "<< TypeSStam - CurrentStamina << ". Do you want to restore to the MAX?[1/0]"<<endl; /** On MAX **/
                cin>>atb;
                if (atb == 1){
                    if ((TypeSStam - CurrentStamina)*koef > money){
                        this->YouDontHaveEnoughMoney();
                        atb = false;
                    }else
                        maxAccess = true;
                }else{
                    atb = false;
                }
            }else{
                if (value * koef > money)
                    this->YouDontHaveEnoughMoney();
                else
                    atb = true;
            }
        }
    }while (atb == false);

    MemberValue.open(path.c_str());
    MemberValue >> line;
    buffer += line;
    buffer += " ";
    if(maxAccess){
        cash = money - (TypeSStam - CurrentStamina)*koef;    //for max value [Dispatcher]
        buffer += intToString(TypeSStam);
    }else{
        cash = money - value*koef;
        //for written value [Dispatcher]
        int sum = CurrentStamina + value;
        buffer += intToString(sum);
    }
    buffer += '\n';
    line.clear();
    while (Type == "Dispatcher" && getline(MemberValue,line)){
        if (counter >= 0){
            MemberValue >> line;        //dedicated process for dispatcher
            buffer += line;
            buffer += '\n';
        }
        counter++;
    }
    MemberValue.close();

    ofstream WriteValue(path.c_str());
    WriteValue << buffer;
    WriteValue.close();

    if (value > 0){
        if (maxAccess)
            cout<<Type<<" has been restored to maximum "<<TypeSStam<<"/"<<TypeSStam<<" points of stamina for "<< (TypeSStam - CurrentStamina)*koef <<"$."<<endl;
        else if (atb)
                cout<<Type<<" has been restored to "<<value<<" points of stamina for "<< value*koef <<"$. Total point count " << CurrentStamina + value <<"/"<< TypeSStam <<endl;
    }
    return cash;
}





