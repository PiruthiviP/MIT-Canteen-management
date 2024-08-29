#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include"class.h"
#include"pass.h"



using namespace std;
#define CLEAR_COMMAND "clear"
unsigned int choice = 0;

string temppas;//checking the tmeporary password

void displayMenu() {
    gotoxy(25, 7);
    cout << "1. Billing";

    gotoxy(25, 8);
    cout << "2. Add or remove items";

    gotoxy(25, 9);
    cout << "3. Customer details";

    gotoxy(25, 10);
    cout << "4. View Sales";

    gotoxy(25, 11);
    cout << "5. Settings";
    gotoxy(25, 15);
    cout << "Enter your choice: ";
}
int getChoice() {
    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        if (choice >= 1 && choice <= 6) {
            break;
        } else {
            cout << "Wrong number entered. Please try again." << endl;
            cin.clear();
        }
    }
    return choice;
}
 


int main() {
	
    Data D;
    I.loadItemsFromFile();
    system(CLEAR_COMMAND); 
    gotoxy(22, 10);
    cout << "Welcome to MIT Canteen";

    gotoxy(27, 17);
    cout << "Press Any Key to continue";

    getchar();
   system(CLEAR_COMMAND); 
    cout << "Select Any option from below";

    choice = getChoice();

     
    while (true) {
        switch (choice) {
           case 1: {
                
                    system(CLEAR_COMMAND); 
                    I.Billing_page();
                    char ch;
                    cout << "Press any key to continue." << endl;
                    ch = getchar();
                    if (ch == 27) { // Check if the pressed key is the escape key
                    system(CLEAR_COMMAND);
                    cout << "Select Any option from below";
                    choice = getChoice();
                        }
                     else {
                            continue;
                            }
                break;
            }
    
            case 2: {
                bool passwordEntered = false;
                while (!passwordEntered) {
                    system(CLEAR_COMMAND);
                    
                    cout << "Enter the Password.";
                    cin >> temppas;
                    if (U.Enterpassword(temppas)) {
                        Add_items_page();
                        system(CLEAR_COMMAND);
                        cout << "Select Any option from below";
                        choice = getChoice();
                        passwordEntered = true; 
                    } else {
                        cout << "Wrong Password entered. Try again." << endl;
                    }
                }
                break;
            }
            case 3:
            {
                string s;
                bool passwordEntered = false;
                while (!passwordEntered) {
                    system(CLEAR_COMMAND);
                    cout << "Enter the Password.";
                    cin >> temppas;
                    cout<<"What is your  favourite dish?";
                     cin>>s;     
                    if (U.Enterpassword(temppas)) {
                        Customer_details_page();
                        system(CLEAR_COMMAND);
                        cout << "Select Any option from below";
                        choice = getChoice();
                        passwordEntered = true; 
                    } else {
                        cout << "Wrong Password entered. Try again." << endl;
                    }
		    
                }
                break;
            }
                
                break;
            case 4:
                 {
			 bool passwordEntered = false;
                while (!passwordEntered) {
                    system(CLEAR_COMMAND);

                    cout << "Enter the Password.";
                    cin >> temppas;
                    if (U.Enterpassword(temppas)) {
                        I.sales_page();
                        system(CLEAR_COMMAND);
                        cout << "Select Any option from below";
                        choice = getChoice();
                        passwordEntered = true;
                    } else {
                        cout << "Wrong Password entered. Try again." << endl;
                    }
                }
                break;

		 }

                break;
            case 5: {
                bool passwordEntered = false;
                while (!passwordEntered) {
                    cout << "Enter the Password: ";
                    cin >> temppas;
                    if (U.Enterpassword(temppas)) {
                        Settings_page();
                        system(CLEAR_COMMAND);
                        cout << "Select Any option from below" << endl;
                        choice = getChoice();
                        passwordEntered = true;
                    } else {
                        cout << "Wrong Password entered. Try again." << endl;
                    }
                }
                break;
            }
            default:
                cout << "Oops, an error occurred. Please try again.";
                break;
        }
    }
    return 0;
}
