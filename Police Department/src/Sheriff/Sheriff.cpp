#include "../../include/Sheriff/Sheriff.h"
#include "Dispatcher.h"
#include "../../include/Convert.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;

Sheriff::Sheriff()
{

}

Sheriff::Sheriff(int money, int prom, int taxes)
{
    this->dispMoney = prom;
    this->setTaxes(taxes);
    this->setCash(money);
    this->MainMenu();

    ofstream Money("PD/Money.txt");
    Money << this->getCash() << " " << this->dispMoney << " " << this->getTaxes();
    Money.close();
    //ctor
}

Sheriff::~Sheriff()
{
    //dtor
}

void Sheriff::MainMenu(){
    int izv;
    do{
        cout<<"Choose operation:"<<endl;
        cout<< "1. Add staff" <<endl;
        cout<< "2. Money operations" <<endl;
        cout<< "3. Stats" <<endl;
        cout<<"--------------------"<<endl;
        cout<< "0. Exit" <<endl;

        cin>>izv;
        switch(izv){
            case 1:
                {
                    system("CLS");
                    this->StaffManag();
                    break;
                }
            case 2:
                {
                    system("CLS");
                    this->Money();
                    break;
                }
            case 3:
                {
                    system("CLS");
                    this->Stats();
                    break;
                }
            case 0:
                {
                    system("CLS");
                    break;
                }
            default:
                {
                    cout<<"Choose 1 - 3 or exit!"<<endl;
                }
        }
    }while(izv != 0);
}

void Sheriff::DispatcherFunc(int *value){
    int disIev;
    int atb;
    do{
        cout<<"Choose operation:"<<endl;
        cout<< "1. Change dispatcher" <<endl;
        cout<< "2. Regenerate dispatcher" <<endl;
        cout<<"--------------------"<<endl;
        cout<< "0. Exit" <<endl;
        cin>>disIev;

        switch(disIev){
            case 1:
                {
                    do{
                        system("CLS");
                        string buffer;
                        cout<<"Your current budget: "<<this->getCash()<<"$"<<endl;
                        cout<<"It will cost you 1000$ and all dispatcher's data will be lost! Proceed? [1/0]"<<endl;
                        cin>>atb;
                        if (atb == 1 && this->getCash() >= 1000){
                            buffer = "Dispatcher 150";
                            buffer += '\n';
                            buffer += '1';
                            buffer += '\n';
                            buffer += '0';
                            buffer += '\n';
                            ofstream DispatcherWrite("PD/Dispatcher/DispatcherData.txt");
                            DispatcherWrite << buffer;
                            DispatcherWrite.close();
                            buffer.clear();

                            double cash = this->getCash() - 1000;
                            this->setCash(cash);
                            cout<<"Your dispatcher's stamina, level and EXP was reset to defaults."<<endl;
                        }else{
                            this->YouDontHaveEnoughMoney();
                        }
                        if (atb != 1 && atb != 0){
                            cout<<"Type 1 or 0."<<endl;
                        }
                    }while(atb != 1 && atb != 0);
                    break;
                }
            case 2:
                {
                    do{
                        system("CLS");
                        this->setCash(Restore("Dispatcher", "PD/Dispatcher/DispatcherData.txt", Member::getStamina("PD/Dispatcher/DispatcherData.txt"), this->getCash())); //Method 'Restore'
                    }while(atb == false && value == 0);
                    break;
                }
            case 0:
                {
                    system("CLS");
                    break;
                }
            default:
                {
                    cout<<"Choose 1 - 2 or exit!"<<endl;
                }
        }
    }while(disIev != 0);
}

void Sheriff::Money(){
    int izv;
    do{
        int value = 0;
        cout<<"Choose operation:"<<endl;
        cout<< "1. Dispatcher's money" <<endl;
        cout<< "2. Promotion Budget" <<endl;
        cout<< "3. Taxes" <<endl;
        cout<<"--------------------"<<endl;
        cout<< "0. Exit" <<endl;

        cin>>izv;
        switch(izv){
            case 1:
                {
                    system("CLS");
                    this->DispatcherFunc(&value);
                    break;
                }
            case 2:
                {
                    do{
                        system("CLS");
                        cout<<"Current amount of cash: "<<this->getCash()<<endl;
                        cout<<"How much do you want to transfer on promotion budget?"<<endl;
                        cin>>value;
                        value = abs(value);
                        if (value > this->getCash()){
                            this->YouDontHaveEnoughMoney();
                        }else{
                            double cash = this->getCash() - value;
                            this->setCash(cash);
                            this->dispMoney += value;
                            cout<<value<<"$ has been transfered to promotion budget."<<endl;
                        }
                    }while(value > this->getCash());
                    break;
                }
            case 3:
                {
                    do{
                        system("CLS");
                        cout<<"Current amount of cash: "<<this->getCash()<<"$"<<endl;
                        cout<<"Taxes for unsuccessful calls: "<<this->getTaxes()<<"$"<<endl;
                        cout<<"How much do you want to pay?"<<endl;
                        cin>>value;
                        value = abs(value);
                        if (value > this->getCash()){
                            this->YouDontHaveEnoughMoney();
                        }else{
                            this->setCash(this->getCash() - value);
                            if (value > this->getTaxes())
                                value = this->getTaxes();
                            cout<<value<<"$ has been transfered to to pay taxes."<<endl;
                            this->setTaxes(this->getTaxes() - value);
                        }
                    }while(value > this->money);
                    break;

                }
            case 0:
                {
                    system("CLS");
                    break;
                }
            default:
                {
                    cout<<"Choose 1 - 3 or exit!"<<endl;
                }
        }
    }while(izv != 0);
}

void Sheriff::AddMember(int cost, string type){ //int unit_cost, string unit_type
    int counts;
    cout<<"Your current budget: "<<this->getCash()<<"$"<<endl;
    cout<<"1 "<<type<<" cost "<<cost<<"$."<<endl;
    cout<<"How many "<<type<<"s do you want to hire? (Type '0' to quit)"<<endl;
    do{
        cin>>counts;
        counts = abs(counts);
        if(counts == 0){
            cout<<"Quitting..."<<endl;
        }else{
            if(counts * cost > this->getCash()){
                this->YouDontHaveEnoughMoney();
            }else{

                for(int i = 1; i <= counts; i++){ //Making new unit with unique label
                    string buffer;
                    srand (time(NULL));
                    int randVal = rand() % 999 + 1;
                    string line, test, typeName = type + intToString(randVal);

                    ifstream StaffListRead("PD/Staff/StaffFile/StaffList.txt");
                    while(getline(StaffListRead,line)){
                        srand (time(NULL));
                        while(typeName == line){
                            randVal = rand() % 999 + 1;
                            typeName = type + intToString(randVal); //Unit's name + unique numbers = unit's filename
                        }
                    }
                    StaffListRead.close();

                    string filename = "PD/Staff/";
                    filename += typeName;
                    filename += ".txt";
                    ofstream StaffWrite(filename.c_str());
                    StaffWrite << type << " " << this->StaffTypeVal(type);
                    StaffWrite.close();

                    buffer += typeName;
                    buffer += '\n';

                    ofstream StaffListWrite("PD/Staff/StaffFile/StaffList.txt", ios::app);
                    StaffListWrite << buffer;
                    StaffListWrite.close();

                    StaffListWrite.open("PD/Staff/StaffFile/FreeUnits.txt", ios::app);
                    StaffListWrite << buffer;
                    StaffListWrite.close();

                    buffer.clear();
                }


                int cash = this->getCash() - counts * cost;
                this->setCash(cash);
                cout<<counts<<" "<<this->StaffTypeName(type)<<"(s) has been hired for "<<counts*cost<<"$."<<endl;
                counts=0;
            }
        }
    }while(counts != 0);
}

void Sheriff::StaffManag(){
    int izv;
    do{
        cout<<"Choose unit's type:"<<endl;
        cout<<"1. Officer"<<endl;
        cout<<"2. K9 Unit"<<endl;
        cout<<"3. SAS Trooper"<<endl;
        cout<<"--------------------"<<endl;
        cout<<"0. Exit"<<endl;

        cin>>izv;
        switch(izv){
            case 1:
                {
                    system("CLS");
                    this->AddMember(500,"Officer");
                    break;
                }
            case 2:
                {
                    system("CLS");
                    this->AddMember(700,"K9_Unit");
                    break;
                }
            case 3:
                {
                    system("CLS");
                    this->AddMember(1500,"SAS_Trooper");
                    break;
                }
            case 0:
                {
                    system("CLS");
                    break;
                }
            default:
                {
                    cout<<"Choose 1 - 3 or exit!"<<endl;
                }
        }
    }while(izv != 0);
}


void Sheriff::setCash(int cash){
    this->money = cash;
}

double Sheriff::getCash(){
    return this->money;
}

void Sheriff::setTaxes(int bills){
    this->taxes = bills;
}

int Sheriff::getTaxes(){
    return this->taxes;
}

void Sheriff::Stats(){
    int izv;
    do{
        cout<<"Choose operation"<<endl;
        cout<< "1. Show log" <<endl; //
        cout<< "2. Show money" <<endl; //
        cout<< "3. Show taxes" <<endl;
        cout<<"--------------------"<<endl;
        cout<< "0. Exit" <<endl;

        cin>>izv;
        switch(izv){
            case 1:
                {
                    system("CLS");
                    string line;
                    ifstream LogFile("PD/log.txt");
                    while(getline(LogFile, line)){
                        cout<< '\t' << line <<endl;
                    }
                    cout<<"Use scroll to see a whole log."<<endl;
                    system("pause");
                    system("CLS");
                    break;
                }
            case 2:
                {
                    system("CLS");
                    cout<<"Total amount of money: "<<this->getCash()<<"$"<<endl;
                    cout<<"Your promotion budget: "<<this->dispMoney<<"$"<<endl;
                    system("pause");
                    system("CLS");
                    break;
                }
            case 3:
                {
                    system("CLS");
                    cout<<"Current taxes: "<<this->getTaxes()<< "$" <<endl;
                    if (this->getTaxes() >= 5000)
                        cout<<"You have reached taxes amount. You need to pay some."<<this->getTaxes()<<"/5000 $"<<endl;
                    else
                        cout<<"Max taxes amount is 5000$. Next payment limit will appear after " << 5000 - this->getTaxes() << "$" <<endl;
                    system("pause");
                    system("CLS");
                }
            case 0:
                {
                    system("CLS");
                    break;
                }
            default:
                {
                    cout<<"Choose 1 - 3 or exit!"<<endl;
                }
        }
    }while(izv != 0);
}
