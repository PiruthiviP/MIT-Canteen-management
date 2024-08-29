/* Pass.h file for the Settings_page*/
#include<unistd.h>
#define CLEAR_COMMAND "clear"
using namespace std;

class User {
private:
    string username = "piruthivi";
    string password = "1234";
    string security = "pasta";

public:
    bool Enterpassword(string pa);
    void changePassword();
    void checkPasswordReqirements();
    void changeusername();
};

bool User::Enterpassword(string pa) {
    if (password == pa)
        return true;
    else
        return false;
}

void User::changeusername() {
    string newusername;
    system(CLEAR_COMMAND);
    cout << "Enter the new username:" << endl;
    cin >> newusername;
    username = newusername;
    cout << "Username changed successfully!!." << endl;
    timer(2);
}

void User::checkPasswordReqirements() {
    system(CLEAR_COMMAND);
    int lcase = 0, ucase = 0, num = 0, symbol = 0;
    for (int i = 0; i < password.length(); i++) {
        if (isupper(password[i]))
            ucase++;
        else if (islower(password[i]))
            lcase++;
        else if (isdigit(password[i]))
            num++;
        else if ((password[i] == 33) || (password[i] == 64) || (password[i] == 35) || (password[i] == 36) || (password[i] == 37) || (password[i] == 94) || (password[i] == 38) || (password[i] == 42) || (password[i] == 40) || (password[i] == 41))
            symbol++;
    }
    if (ucase < 1 || lcase < 1 || num < 1 || symbol < 1) {
        cout << "Password does not meet the requirements"<< endl;
        timer(2);
    } else {
        
        cout << "Password is set successfully"<< endl;
        timer(2);
    }
}

void User::changePassword() {
    system(CLEAR_COMMAND);
    string temp, oldpassword, chsecurity,ssecurity;

    cout << "Enter the  old password:";
    cin >> oldpassword;
    cout << "What is your favourite dish?" << endl;
    cin >> chsecurity;
    if (oldpassword == password && chsecurity == security) {
        cout << "\nYour password should contain :" << endl;
        cout << "\t atleast a uppercase letter \n\t atleast a lowercase letter \n\t atleast a number \n\t atleast a symbol e.g. *, &, %,..." << endl;
        cout << "Enter your new password : ";
        cin >> password;
        cout << "Re-enter your new password : ";
        cin >> temp;
        cout<<"For the new security question"<<endl;
        cout<<"What is your  favourite dish?";
        cin>>ssecurity;
        security=ssecurity;
        if (temp == password) {
            checkPasswordReqirements();
        } else {
            cout << "Password does not match" << endl;
            timer(2);
        }
    } else{
        cout << " Wrong Password or securtiy answer entered .Please try again" << endl;
        timer(2);
    }
}
 User U;//declaring as global for main fiunction
void Settings_page() {
    int passchoice;
    char confirm;
    do {
        system(CLEAR_COMMAND);
        gotoxy(25, 7);
        cout << "1. Change username" << endl;
        gotoxy(25, 8);
        cout << "2. Change password" << endl;
        gotoxy(25, 9);
        cout << "3. About" << endl;
        gotoxy(25, 10);
        cout << "4. Exit" << endl;
        gotoxy(25, 11);
        cout<<"5.Delete everything"<<endl;
        gotoxy(25, 13);
        cout << "Enter your choice: ";
        cin >> passchoice;

        switch (passchoice) {
            case 1:
                U.changeusername();
                
                break;
            case 2:
                U.changePassword();
                
                break;
            case 3:
                // U.About();
                break;
            case 4:
            
                break;
                case 5:
               {
                cout << "Are you sure you want to delete data? (Y/N): ";
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y')
                    exit(0);
                else
                    break;
               }
               
            default:
                cout << "Invalid choice. Please try again." << endl;
		sleep(1);
        }
    } while (passchoice != 4); 
}

