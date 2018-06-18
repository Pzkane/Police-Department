#ifndef MEMBER_H
#define MEMBER_H

#include <string>
using namespace std;

class Member{
    public:
        Member();
        virtual ~Member();

        //setters
        void setPromBudget(double);
        void setCash(double);

        //getters
        int getStamina(string);

        //Class' methods
        int StaffTypeVal(string);
        int Restore(string, string, int, int);
        string StaffTypeName(string);
        void YouDontHaveEnoughMoney();

        //virtual for Dispatcher
        virtual int ChangeDay(int, int, int, int);
        virtual void getStarted(int, int, int, int);

        //virtual for Sheriff/Dispatcher
        virtual void Stats();
        virtual void StaffManag();
        virtual void Money();
        virtual void MainMenu();

    protected:

    private:
};

#endif // MEMBER_H
