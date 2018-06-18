#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <vector>
#include <string>
using namespace std;

#include "../Member.h"

class Dispatcher : public Member
{
    public:
        //ctors, dtors
        Dispatcher();
        virtual ~Dispatcher();

        ///Custom maethods

        void getStarted(int, int, int, int);

        //setters
        void setExp(int);
        void setMoney(int);
        void setLevel(int);
        void setPromBudget(int);
        void setStamina(int);
        void setTaxes(int);

        //getters
        int getExp();
        int getMoney();
        int getLevel();
        int getPromBudget();
        int getStamina();
        int getTaxes();

        //end day operations
        int ChangeDay(int, int, int, int);
        string ChangeDay_Func(string, string, int, vector <string> &, string);

        //patrol's operations
        void PatrolGeneration();

        //call's operations
        int CallTypeValue(string);
        string CallTypeName(string);
        void CallGeneration();
        void RandomCall(const char*, const char*, int, vector <string> &, int *);

        //Dispatcher data check
        void DispLevelUp(string &);
        int DispCurrentLevel();
        int DispCheckRank();
        int DispStamina();

        //other
        int* Generation(string, int, int, int, int, vector<string> &);
        int OperationManage(string, int, bool&, string RespCall = "non", int ResPoints = 0); //Call name, Call type, Call HP, max unit count
        int ShowUnits(const char*);
        void RespondToOperation(vector<string> &, string, bool);

        //virtual realization
        void Stats();
        void StaffManag();
        void Money();
        void MainMenu();

    protected:

    private:
        //Arguments
        int DStamina;
        int currentExp;
        int taxes;
        int promotion;
        int sheriffMoney;
        vector <string> CallSet; //call list
        vector <string> PatrolSet; //patrol list
};

#endif // DISPATCHER_H
