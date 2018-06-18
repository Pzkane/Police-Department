#ifndef SHERIFF_H
#define SHERIFF_H

#include "../Member.h"

class Sheriff : public Member
{
    public:
        //ctors, dtors
        Sheriff();
        Sheriff(int, int, int);
        virtual ~Sheriff();

        ///Custom maethods

        //setters
        void setTaxes(int);
        void setCash(int);

        //getters
        int getTaxes();
        double getCash();

        //Class' methods
        void AddMember(int, string);
        void DispatcherFunc(int*); //Interaction with Dispatcher's data

        //virtual realization
        void Stats();
        void Money();
        void MainMenu();
        void StaffManag();

    protected:

    private:
        //Arguments
        int taxes;
        int money;
        int dispMoney;
};

#endif // SHERIFF_H
