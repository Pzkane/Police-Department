#include "Dispatcher.h"
#include "../../include/Convert.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

Dispatcher::Dispatcher()
{
    this->CallGeneration();
    this->PatrolGeneration();
}

Dispatcher::~Dispatcher()
{
    //dtor
}

void Dispatcher::getStarted(int prom, int money, int taxes, int exp)
{
    this->setExp(exp);
    this->sheriffMoney = money;
    this->setPromBudget(prom);
    this->MainMenu();

    ofstream Money("PD/Money.txt");
    Money << this->sheriffMoney << " " << this->getPromBudget() << " " << taxes;
    Money.close();
    //ctor
}

void Dispatcher::setMoney(int cash){
    this->sheriffMoney = cash;
}

int Dispatcher::getMoney(){
    return this->sheriffMoney;
}

string Dispatcher::ChangeDay_Func(string checkType, string checkID, int sum, vector <string> &UnitSet, string buffer){ //Continuing ChangeDay method if needed
    int random = 0, randomValue = 0;
    string fileBuff, junk, lineF, bufferF, tuks;
    int valueF, valueDisp = this->DispStamina();
    fstream AllUnits;
    fstream UnitRewrite;

    if(checkType == "|Wh")
        random = rand() % 70;
    else if (checkType == "|Yl")
            random = rand() % 100;
        else if (checkType == "|Rd")
                random = rand() % 120;
            else
                random = rand() % 170;

    for(int i = 0; i < UnitSet.size(); i++){
        fileBuff = "PD/Staff/";
        fileBuff += UnitSet.at(i);
        fileBuff += ".txt";
        UnitRewrite.open(fileBuff.c_str(), ios_base::in);
        UnitRewrite >> junk >> valueF;;
        UnitRewrite.close();

        if(checkType == "|Wh"){
                valueF -= 8;
                valueDisp -= 5;
            }else if (checkType == "|Yl"){
                    valueF -= 16;
                    valueDisp -= 10;
                }else if (checkType == "|Rd"){
                        valueF -= 20;
                        valueDisp -= 15;
                    }else{
                        valueF -= 28;
                        valueDisp -= 20;
                    }

        this->setStamina(valueDisp);

        if(sum < random){
            if(checkType == "|Wh")
                valueF -= 3;
            else if (checkType == "|Yl")
                    valueF -= 4;
                else if (checkType == "|Rd")
                        valueF -= 5;
                    else
                        valueF -= 6;
        }
        if (valueF <= 0){
            AllUnits.open("PD/Staff/StaffFile/StaffList.txt", ios_base::in);
            while(getline(AllUnits, lineF)){
                if (lineF.find(UnitSet.at(i)) == string::npos){
                    bufferF += lineF;
                    bufferF += '\n';
                }
            }
            AllUnits.close();

            remove(fileBuff.c_str());

            AllUnits.open("PD/Staff/StaffFile/StaffList.txt", ios_base::out);
            AllUnits << bufferF;
            AllUnits.close();
            bufferF.clear();
        }else{
            UnitRewrite.open(fileBuff.c_str(), ios_base::out);
            UnitRewrite << junk << " " << valueF;
            UnitRewrite.close();

            UnitRewrite.open("PD/Staff/StaffFile/FreeUnits.txt", ios_base::out | ios_base::app);
            UnitRewrite << UnitSet.at(i) << '\n';
            UnitRewrite.close();
        }
        junk.clear(); valueF = NULL;
    }

    if(sum >= random){
        randomValue = this->CallTypeValue(checkType);
        this->setMoney(this->getMoney() + randomValue);
        buffer += "Chance: "; buffer += intToString(random); buffer += "/"; buffer += intToString(sum); buffer += " "; buffer += "Call["; buffer += checkID; buffer += "] with rating "; buffer += CallTypeName(checkType); buffer += " was SUCCESSFUL. +"; buffer += intToString(randomValue); buffer += "$"; buffer += " +"; randomValue = this->CallTypeValue(checkType); buffer += intToString(randomValue); buffer += "EXP";
        this->setExp(this->getExp() + randomValue);
    }else{
        randomValue = this->CallTypeValue(checkType);
        this->setTaxes(this->getTaxes() + randomValue);
        buffer += "Chance: "; buffer += intToString(random); buffer += "/"; buffer += intToString(sum); buffer += " "; buffer += "Call["; buffer += checkID; buffer += "] with rating "; buffer += CallTypeName(checkType); buffer += " FAILED. Taxes increased by "; buffer += intToString(randomValue); buffer += "$";
    }buffer += '\n';

    return buffer;
}

int Dispatcher::ChangeDay(int money, int prom, int taxes, int exp){
    srand(time(NULL));
    this->setMoney(money);
    this->setPromBudget(prom);
    this->setTaxes(taxes);
    this->setExp(exp);
    this->setStamina(this->DispStamina());

    srand(time(NULL));
    vector <string> UnitSet;
    string line, unit, checkType, type, buffer = "", id, value, checkID = "non"; ///calls
    int izv, random, Char = 0, sum = 0; ///calls
    int randomMoney = 5; ///patrols
    srand(time(NULL));
    cout<<"Would you really like to end this day?[1/0]"<<endl;
    cin>>izv;

    if(izv == 1){
        buffer += "=========== DAY LOG ==========="; buffer += '\n'; buffer += '\n';
        buffer += "Old cash amount: "; buffer += intToString(this->getMoney()); buffer += "$"; buffer += '\n'; buffer += "Old taxes amount: "; buffer += intToString(this->getTaxes()); buffer += "$"; buffer += '\n'; buffer += "Old EXP amount: "; buffer += intToString(this->getExp()); buffer += '\n'; buffer += '\n';
        ///DO ALL FILE JOB
        ifstream Responded("PD/Staff/StaffFile/BusyUnits.txt");
        while(getline(Responded, line)){
            if(line.find("|Wh") != string::npos || line.find("|Yl") != string::npos || line.find("|Rd") != string::npos || line.find("|TH") != string::npos){
                ///THIS IS CALLS
                for (int i = 0; i < line.size(); i++){ ///Finding out unit name(type)
                    if(line[i] != 32){
                        unit += line[i];
                        Char++;
                    }else{
                        Char++;
                        break;
                    }
                }

                UnitSet.push_back(unit);

                for (int i = Char; i < line.size(); i++){ ///Finding out ID
                    if(line[i] != 32){
                        id += line[i];
                        Char++;
                    }else{
                        Char++;
                        break;
                    }
                }
                for (int i = Char; i < line.size(); i++){ ///Finding out call type
                    if(line[i] != 32){
                        type += line[i];
                        Char++;
                    }else{
                        Char++;
                        break;
                    }
                }

                for (int i = Char; i < line.size(); i++){ ///Finding out unit's value
                    if(line[i] != 32){
                        value += line[i];
                        Char++;
                    }else{
                        Char++;
                        break;
                    }
                }

                    ///CALLS : STATEMENT PART

                if(checkID == "non")
                    checkID = id;

                if(id == checkID){
                    sum += stringToInt(value);
                    checkType = type;
                }else{
                    buffer = this->ChangeDay_Func(checkType, checkID, sum, UnitSet, buffer);
                    UnitSet.clear();

                    checkID = id;
                    checkType = type;
                }

                Char = 0;
                unit.clear(); id.clear(); type.clear(); value.clear();
            }else{
                if(checkID == id){
                    buffer = this->ChangeDay_Func(checkType, checkID, sum, UnitSet, buffer);

                    UnitSet.clear();

                    checkID = id;
                    checkType = type;
                }
                Char = 0;

                ///THIS IS PATROLS

                for (int i = 0; i < line.size(); i++){ ///Finding out unit name(type)
                    if(line[i] != 32){
                        unit += line[i];
                        Char++;
                    }else{
                        Char++;
                        break;
                    }
                }
                //Patrol below
                buffer += "Money to 1 unit for patrolling +";
                switch(this->DispCheckRank()){
                    case 1:
                        {
                            randomMoney = rand () % 100 + 10;
                        }
                    case 2:
                        {
                            randomMoney = rand () % 150 + 10;
                        }
                    case 3:
                        {
                            randomMoney = rand () % 200 + 10;
                        }
                    case 4:
                        {
                            randomMoney = rand () % 250 + 10;
                        }
                    case 5:
                        {
                            randomMoney = rand () % 300 + 10;
                        }
                }

                string fileBuff = "PD/Staff/", junk;
                int valueF;
                fileBuff += unit;
                fileBuff += ".txt";
                fstream UnitRewrite;
                UnitRewrite.open(fileBuff.c_str(), ios_base::in);
                UnitRewrite >> junk >> valueF;
                UnitRewrite.close();

                valueF -= 10;
                string lineF, bufferF;
                if (valueF < 0){    //If unit's value < 0, then delete unit
                    fstream DelUnits;
                    DelUnits.open("PD/Staff/StaffFile/StaffList.txt", ios_base::in);
                    while(getline(DelUnits, lineF)){
                        if (lineF.find(unit) == string::npos){
                            bufferF += lineF;
                            bufferF += '\n';
                        }
                    }
                    DelUnits.close();

                    remove(fileBuff.c_str());

                    DelUnits.open("PD/Staff/StaffFile/StaffList.txt", ios_base::out);
                    DelUnits << bufferF << '\n';
                    DelUnits.close();
                    bufferF.clear();
                }else{  //else minus stamina points
                    UnitRewrite.open(fileBuff.c_str(), ios_base::out);
                    UnitRewrite << junk << " " << valueF;
                    UnitRewrite.close();

                    UnitRewrite.open("PD/Staff/StaffFile/FreeUnits.txt", ios_base::out | ios_base::app);
                    UnitRewrite << unit << '\n';
                    UnitRewrite.close();
                }
                junk.clear(); valueF = NULL;

                this->setMoney(this->getMoney() + randomMoney);
                this->setExp(this->getExp() + randomMoney);
                buffer += intToString(randomMoney); buffer += "$ and EXP"; buffer += '\n';
            }
            unit.clear(); Char = 0;
        }

        if(checkID != "non"){
            buffer = this->ChangeDay_Func(checkType, checkID, sum, UnitSet, buffer);

            UnitSet.clear();

            checkID = id;
            checkType = type;
        }
        Responded.close();

        buffer += '\n'; buffer += "New cash amount: "; buffer += intToString(this->getMoney()); buffer += "$"; buffer += '\n'; buffer += "Total taxes amount: "; buffer += intToString(this->getTaxes()); buffer += "$"; buffer += '\n'; buffer += "EXP amount: "; buffer += intToString(this->getExp()); buffer += '\n'; buffer += '\n';
        this->DispLevelUp(buffer);
        buffer += "========= END OF LOG =========="; buffer += '\n'; buffer += '\n';

        ofstream LogFile("PD/log.txt", ios_base::app);
        LogFile << buffer;
        LogFile.close();

        cout<<buffer<<endl;
        line.clear(); buffer.clear();

        buffer += "Dispatcher "; buffer += intToString(this->getStamina()); buffer += '\n';

        fstream ExpNew;
        ExpNew.open("PD/Dispatcher/DispatcherData.txt", ios_base::in);
        int counter = 0;
        while(getline(ExpNew, line)){
            if (counter != 0 && counter != 2){
                buffer += line;
                buffer += '\n';
            }
            counter++;
        }
        ExpNew.close();
        buffer += intToString(this->getExp());

        ExpNew.open("PD/Dispatcher/DispatcherData.txt", ios_base::out);
        ExpNew << buffer;
        ExpNew.close();

        ofstream Money("PD/Money.txt");
        Money << this->getMoney() << " " << this->getPromBudget() << " " << this->taxes;
        Money.close();

        ofstream NotBusyAnymore("PD/Staff/StaffFile/BusyUnits.txt", ios_base::out | ios_base::trunc); //clearing busy units (that responding on call/patrol)
        NotBusyAnymore.close();

        return 101;
    }else{
        return 4;
    }
}

string Dispatcher::CallTypeName(string type){ //string call_type
    if(type == "|Wh")   ///Returns call's rating
        return "WHITE";
    else if (type == "|Yl")
            return "YELLOW";
        else if (type == "|Rd")
                return "RED";
            else
                return "~THREAT~";
}

int Dispatcher::CallTypeValue(string type){ //string call_type
    if(type == "|Wh")   ///Returns call's value (probability for success)
        return rand () % 100 + 250;
    else if (type == "|Yl")
            return rand () % 100 + 450;
        else if (type == "|Rd")
                return rand () % 100 + 650;
            else
                return rand () % 100 + 950;
}

void Dispatcher::Stats(){
    int izv;
    do{
        cout<<"Choose operation"<<endl;
        cout<< "1. Show log" <<endl; //
        cout<< "2. Show units" <<endl; //
        cout<< "3. Show money" <<endl; //
        cout<< "4. Show dispatcher's stats"<<endl;//
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
                    this->ShowUnits("PD/Staff/StaffFile/StaffList.txt");
                    break;
                }
            case 3:
                {
                    system("CLS");
                    cout<<"Total amount of money: "<<this->getMoney()<<"$"<<endl;
                    cout<<"Your promotion budget: "<<this->getPromBudget()<<"$"<<endl;
                    system("pause");
                    system("CLS");
                    break;
                }
            case 4:
                {
                    system("CLS");
                    cout<<"\t Dispatcher:"<<endl;
                    cout<<"\t \t Stamina: "<<this->DispStamina()<<"/150"<<endl;
                    cout<<"\t \t Level: "<<this->DispCurrentLevel()<<endl;
                    cout<<"\t \t XP: "<<this->getExp()<<" EXP"<<endl;
                    system("pause");
                    system("CLS");
                    break;
                }
            case 0:
                {
                    break;
                }
            default:
                {
                    cout<<"Choose 1 - 4 or exit!"<<endl;
                }
        }
    }while(izv != 0);
}

void Dispatcher::StaffManag(){
    int izv;
    do{
        cout<<"Choose operation:"<<endl;
        cout<< "1. Calls" <<endl;
        cout<< "2. Patrols" <<endl;
        cout<<"--------------------"<<endl;
        cout<< "0. Exit" <<endl;
        cin>>izv;

        switch(izv){
            case 1:
                {
                    system("CLS");
                    if(this->DispStamina() > 0)
                        this->RespondToOperation(CallSet, "call", 1);
                    else
                        cout<<"Your Dispatcher is exhausted. Restore his energy or hire a new one."<<endl;
                    break;
                }
            case 2:
                {
                    system("CLS");
                    if(this->DispStamina() > 0)
                        this->RespondToOperation(PatrolSet, "patrol", 0);
                    else
                        cout<<"Your Dispatcher is exhausted. Restore his energy or hire a new one."<<endl;
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
    }while(izv != 0);
}

int Dispatcher::DispCurrentLevel(){
    string line;
    int counter = 0;
    ifstream LevelCurr("PD/Dispatcher/DispatcherData.txt");
    while(getline(LevelCurr, line)){
        if (counter == 1){
            return stringToInt(line);
        }
        counter++;
    }
}

void Dispatcher::DispLevelUp(string &buffer){
    string line;
    int level, counter = 0;
    bool Up = false;

    switch(this->DispCurrentLevel()){ //level up Dispatcher's rank if EXP > [statement]
        case 1:
            {
                if(this->getExp() > 7000){
                    level = this->DispCurrentLevel() + 1;
                    Up = true;
                }
                break;
            }
        case 2:
            {
                if(this->getExp() > 15000){
                    level = this->DispCurrentLevel() + 1;
                    cout<<"LEVEL AFTRE 2nd: "<<level<<endl;
                    Up = true;
                }
                break;
            }
        case 3:
            {
                if(this->getExp() > 21000){
                    level = this->DispCurrentLevel() + 1;
                    Up = true;
                }
                break;
            }
        case 4:
            {
                if(this->getExp() > 30000){
                    level = this->DispCurrentLevel() + 1;
                    Up = true;
                }
                break;
            }
        case 5:
            {
                Up = true;
                break;
            }
    }
    if (Up){
        if (Up && this->DispCurrentLevel() == 5)
            buffer += "Level is maxed out.\n\n";
        else{   //If LEVEL UP, then re-write values in data file
            buffer += "LEVEL UP! From LVL "; buffer += intToString(this->DispCurrentLevel()); buffer += " to LVL "; buffer += intToString(level); buffer += '\n\n'; buffer += '\n';
            fstream ChangeLevel;
            string bufferF;
            ChangeLevel.open("PD/Dispatcher/DispatcherData.txt", ios_base::in);
            while(getline(ChangeLevel, line)){
                if(counter == 1){
                    bufferF += intToString(level);
                    bufferF += '\n';
                }else{
                    bufferF += line;
                    bufferF += '\n';
                }
                counter++;
            }
            ChangeLevel.close();
            cout<<bufferF<<endl;

            ChangeLevel.open("PD/Dispatcher/DispatcherData.txt", ios_base::out);
            ChangeLevel << bufferF;
            ChangeLevel.close();
        }
    }else{
        buffer += "Current LVL: "; buffer += intToString(this->DispCurrentLevel()); buffer += '\n'; buffer += '\n';
    }
}

int Dispatcher::DispStamina(){ //returns dispatcher's stamina
    string junk;
    int stamina;
    ifstream Stamina("PD/Dispatcher/DispatcherData.txt");
    Stamina >> junk >> stamina;
    Stamina.close();

    return stamina;
}

int Dispatcher::DispCheckRank(){ //returns dispatcher's rank/level
    string line;
    int level;
    ifstream DispatcherData("PD/Dispatcher/DispatcherData.txt", ios_base::in);
    int counter = 0;
    while(getline(DispatcherData,line)){
        if(counter == 1){
            level = stringToInt(line);
        }
        counter++;
    }
    DispatcherData.close();
    return level;
}

int* Dispatcher::Generation(string filename, int ArrSize, int randA, int randB, int opCount, vector<string> &Vector){ // ... , vector <string> & Vector_with_call_or_patrol_list
    int randLine, counter = 0;              //generates random file lines for patrols/calls without repeats
    string line;
    int * a = new int[ArrSize];
    srand(time(NULL));
    int iArr = 0;
    ifstream Operation;
    for(int i = 0; i < opCount; i++){
        randLine = rand() %randA;
        Operation.open(filename.c_str());
        while(getline(Operation, line)){
            for(int j = 0; j < opCount; j++){
                while(randLine == a[j]){
                    randLine = rand () %randB;
                }
            }

            if (counter == randLine){
                Vector.push_back(line);
                a[iArr] = randLine;
                break;
            }
            counter++;
        }
        counter = 0;
        iArr++;
        line.clear();
        Operation.close();
    }
    return a;
}

void Dispatcher::PatrolGeneration(){
    int lineCount = 0;      //according to Dispatcher's rank generates certain amount of calls
    string line;
    int PatrolLines = this->DispCheckRank();

    ifstream PatrolsF("PD/Patrols/PatrolList.txt");
    while(getline(PatrolsF, line)){
        lineCount++;
    }
    PatrolsF.close();

    this->Generation("PD/Patrols/PatrolList.txt", PatrolLines, lineCount, lineCount, PatrolLines, this->PatrolSet); //string filename, int ArrSize, int randA, int randB, int opCount, vector<string> Vector
}

void Dispatcher::CallGeneration(){
    string line;

    srand(time(NULL));
    ifstream CallsF("PD/Calls/White.txt");
    CallsF.close();
    int * a = new int[3];

    a = this->Generation("PD/Calls/White.txt", 3, 6, 3, 2, CallSet);
    int CallLines = this->DispCheckRank();

    int rankContinue = 2;
    if(CallLines > 1){
        srand(time(NULL));
        switch(rankContinue){   //according to Dispatcher's rank generates certain amount of patrols
            case 2:
                {
                    this->RandomCall("PD/Calls/Yellow.txt", "PD/Calls/White.txt", 4, this->CallSet, a);        //Primary path, reserve path, chance of call, vector, array
                    if (rankContinue == CallLines){
                        break;
                    }
                }
            case 3:
                {
                    this->RandomCall("PD/Calls/Yellow.txt", "PD/Calls/White.txt", 2, this->CallSet, a);
                    if (rankContinue == CallLines){
                        break;
                    }
                }
            case 4:
                {
                    this->RandomCall("PD/Calls/Red.txt", "PD/Calls/Yellow.txt", 2, this->CallSet, a);
                    if (rankContinue == CallLines){
                        break;
                    }
                }
            case 5:
                {
                    this->RandomCall("PD/Calls/THREAT.txt", "PD/Calls/Red.txt", 5, this->CallSet, a);
                    break;
                }
        }
    }
    cout<<endl;
}

void Dispatcher::RespondToOperation(vector<string> &Vector, string pronounce, bool calls){
    int num, VecCount = 0;  //menu for call/patrol respond
    bool check;
    string line;
    do{
        for(int i = 0; i < Vector.size(); i++){
            if (Vector[i] != " - - - ")
                VecCount++;
        }
        cout<<"You have "<<VecCount<<" unresolved "<<pronounce<<"(s):"<<endl;
        for(int i = 0; i < Vector.size(); i++){
            cout<<i+1<<") "<<Vector[i]<<endl;
        }

        cout<<"Type "<<pronounce<<"'s number or '0' to quit: "<<endl;
        srand(time(NULL));
        cin>>num;
        num = abs(num);

        if(num == 0){
            system("CLS");
            break;
        }

        if (num > Vector.size()){
            cout<<"Choose one of the numbers!"<<endl;
        }else{
            if (Vector.at(num-1) == " - - - "){
                cout<<"This "<<pronounce<<" is empty! Choose another one."<<endl;
            }else{
                line = Vector[num-1];
                if(calls){
                    system("CLS");
                    if (Vector.at(num-1).find("|Wh") != string::npos){
                        check = OperationManage(line, 4, calls, "|Wh", 70);
                    }
                    if (Vector.at(num-1).find("|Yl") != string::npos){
                        check = OperationManage(line, 4, calls, "|Yl", 100);
                    }
                    if (Vector.at(num-1).find("|Rd") != string::npos){
                        check = OperationManage(line, 5, calls, "|Rd", 120);
                    }
                    if (Vector.at(num-1).find("|TH") != string::npos){
                        check = OperationManage(line, 6, calls, "|TH", 170);
                    }
                }else{
                    check = OperationManage(line, 2, calls);
                }

                if (check)
                    Vector[num-1] = " - - - ";
            }
        }
        VecCount = 0;
    }while(num > Vector.size() || Vector.at(num-1) == " - - - ");
}

int Dispatcher::OperationManage(string name, int Units, bool &calls, string RespCall, int ResPoints){
    int izv, counter = 0, unitCount = 0, id = 0, value = 1, sum = 0;    //adding units to patrol/call
    string staff, line;
    int UnitSize = 0;

    id = rand () % 200 + 100;

    do{
        cout<<calls<<endl;
        cout<<"Call \""<<name<<"\""<<endl;
        if(calls)
            cout<<"Incident's rating is "<<ResPoints<<" points."<<endl;
        else
            cout<<"You can add only 2 units to patrol."<<endl;
        cout<<"Choose "<<Units-unitCount<<" or less of your units to response, or type '0' to stop preparation."<<endl;
        UnitSize = ShowUnits("PD/Staff/StaffFile/FreeUnits.txt");

        cin>>izv;
        izv = abs(izv);

        if(izv == 0)
            break;

        if(izv > UnitSize){
            cout<<"Choose one of the staff members or type '0' to quit from menu!"<<endl;
        }else{
            ifstream StaffFile("PD/Staff/StaffFile/FreeUnits.txt");
            string UnitName;
            while(getline(StaffFile,line)){
                if (counter == izv-1){
                    staff = "PD/Staff/";
                    staff += line;
                    staff += ".txt";
                    ifstream MemberFile(staff.c_str());
                    MemberFile >> UnitName >> value;
                    MemberFile.close();
                }
                counter++;
            }
            StaffFile.close();

            if (value == 0){
                cout<<"This unit is exhausted. Choose another unit."<<endl;
            }else{
                counter = 0;
                if(izv != 0)
                    cout<<StaffTypeName(UnitName)<<" has entered on duty!"<<endl<<endl;
                string buffer;

                ifstream ReadDel("PD/Staff/StaffFile/FreeUnits.txt");
                while (getline(ReadDel,line)){
                    if (counter == izv-1){
                        if (line.find("Officer") != string::npos){
                            value = 15;
                        }
                        if (line.find("SAS") != string::npos){
                            value = 30;
                        }
                        if (line.find("K9") != string::npos){
                            value = 25;
                        }

                        ofstream WriteIn("PD/Staff/StaffFile/BusyUnits.txt", ios::app);
                        if(calls)
                            WriteIn << line <<" "<< intToString(id)<<" "<< RespCall <<" "<< value << '\n';
                        else
                            WriteIn << line <<" "<< intToString(id) << '\n';
                        WriteIn.close();

                        sum += value;

                    }else{
                        buffer += line;
                        buffer += '\n';
                    }
                    counter++;
                }
                ReadDel.close();

                ofstream WriteStaff("PD/Staff/StaffFile/FreeUnits.txt");
                WriteStaff << buffer;
                WriteStaff.close();

                unitCount++;
            }
        }
        if(unitCount == Units){
            break;
        }
        if (ResPoints != 0)
            cout<<"Current call point count: "<<sum<<"/"<<ResPoints<<endl;
        cout<<"Do you want to stop adding units? You cannot edit this call after confirmation.[1/0]"<<endl;
        cin>>izv;
        counter = 0;
        system("CLS");

    }while(izv != 1 || izv > UnitSize || value == 0);

    if (unitCount > 0){
        if (calls)
            cout<<"Call responded."<<endl;
        else
            cout<<"Patrol has been dispatched"<<endl;
        system("pause");
        system("CLS");
        return 1;
    }else{
        if (calls)
            cout<<"Call was not responded."<<endl;
        else
            cout<<"Patrol has not been dispatched"<<endl;
        system("pause");
        system("CLS");
        return 0;
    }
}

void Dispatcher::RandomCall(const char* Primary, const char* Reserve, int chance, vector <string> &Vector, int *Array){ //Primary path, reserve path, chance of call, vector, array
    int randLine, counter = 0;
    string line;
    ifstream CallsType(Primary);
    CallsType.close();

    int localChance = rand () %chance + 1;
    if (localChance == chance){
        CallsType.open(Primary);
        randLine = rand () %3;
        while (getline(CallsType,line)){
            if(counter == randLine){
                Vector.push_back(line);
                //cout<<Vector.size()<<") "<<line<<endl;
            }
            counter++;
        }
        CallsType.close();
    }else{
        CallsType.open(Reserve);
        while(getline(CallsType, line)){
            for(int j = 0; j < 2; j++){
                while(Array[j] == chance){
                    chance = rand () %3;
                    j = 0;
                }
            }

            if(chance == counter){
                Vector.push_back(line);
                //cout<<Vector.size()<<") "<<line<<endl;
            }
            counter++;
        }
        CallsType.close();
    }
}

int Dispatcher::ShowUnits(const char* filename){
    string staff, line, staffMem, stam;
    cout<<"Your staff members. Choose one:"<<endl;
    int counter = 0;
    ifstream StaffFile(filename);
    while(getline(StaffFile,line)){
        staff = "PD/Staff/";    //Officer320
        staff += line;
        staff += ".txt";
        ifstream MemberFile(staff.c_str());
        MemberFile >> staffMem >> stam;
        cout<<counter+1<<") "<<this->StaffTypeName(staffMem)<<" "<<stam<<"/"<<this->StaffTypeVal(staffMem)<<endl; //1. Officer
        MemberFile.close();
        counter++;
    }
    StaffFile.close();
    cout<<"... or type '0' to quit."<<endl;
    return counter;
    system("CLS");
}

void Dispatcher::Money(){
    string line, staff; //recharge unit's stamina for money
    int counter = this->ShowUnits("PD/Staff/StaffFile/StaffList.txt"), izv;
    do{
        cin>>izv;
        izv = abs(izv);
        if(izv == 0){
            break;
        }else{
            if(izv > counter){
                cout<<"Choose one of the staff members or type '0' to quit from menu!"<<endl;
            }else{
                ifstream StaffFile("PD/Staff/StaffFile/StaffList.txt");
                counter = 0;
                string buffer;
                while(getline(StaffFile,line)){
                    if (counter == izv-1){
                        cout<<"TEST 'buffer': "<<line<<endl;
                        staff = "PD/Staff/";
                        staff += line;
                        staff += ".txt";
                        ifstream MemberFile(staff.c_str());
                        MemberFile >> buffer;
                        MemberFile.close();
                        this->setPromBudget(Restore(buffer, staff, Member::getStamina(staff), this->getPromBudget())); //Member
                    }
                    counter++;
                }
                StaffFile.close();
                break;
            }
        }
    }while(izv != 0);
    system("CLS");
}

void Dispatcher::setStamina(int energ){
    this->DStamina = energ;
}

int Dispatcher::getStamina(){
    return this->DStamina;
}

void Dispatcher::setTaxes(int bills){
    this->taxes = bills;
}

int Dispatcher::getTaxes(){
    return this->taxes;
}

void Dispatcher::setPromBudget(int cash){
    this->promotion = cash;
}

int Dispatcher::getPromBudget(){
    return this->promotion;
}

void Dispatcher::setExp(int experience){
    this->currentExp = experience;
}

int Dispatcher::getExp(){
    return this->currentExp;
}

void Dispatcher::MainMenu(){
    int izv;
    do{
        cout<<"Choose operation"<<endl;
        cout<< "1. Staff menu" <<endl;
        cout<< "2. Promotion" <<endl;
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
