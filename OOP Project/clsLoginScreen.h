#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "Global.h"
#include "clsMainScreen.h"

class clsLoginScreen :protected clsScreen
{

private :

  static  bool _Login(short trials = 3)
    {
        bool LoginFaild = false;
        short LoginFaildCount = 0;

        string Username, Password;
        do
        {
     
            if (LoginFaild)
            {
                LoginFaildCount++;
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "\nYou have "<<(trials - LoginFaildCount)
                    <<" trials to login!\n\n";
            }

            if(LoginFaildCount == trials){
                cout << "\nYou are bolked after " << trials << " faild trials!\n\n";
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();

        return true;
  }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }

};

