//customer_details.h file for referce id and oder no
#include<iostream>
#define CLEAR_COMMAND "clear"
#include<unistd.h>
//#include"class.h"
using namespace std;
void tim(int sec)
{
   sleep(sec);
}

class Data
{
    string referenceId[1000];
    int orderNumber[1000];
    int j = 0,s=0; // Initialize j,s to 0
    int Amount[1000];
public:
    void oderdata(int ON) 
    {   
        orderNumber[j++] = ON; // Use j as index and then increment j
    }   

    void refdata(string ref)
    {   
        referenceId[s++] = ref; // Use j as index and then increment j
    }   
    void amount(int amount)
    {
	    int a=0;
	    Amount[a++]=amount;
    }

    void showdata() {
    cout << "UPI Transaction Id:" << "\t\t Order No" <<"\t\t"<<"Amount"<< endl;
    for (int i = 0; i < j; i++) {
        cout << setw(20) << left << referenceId[i] << "\t\t" << orderNumber[i] <<"\t\t\t"<<Amount[i]<< endl;
    }   
}

};

extern Data D;

void Customer_details_page()
{
    while (true)
    {   
        system(CLEAR_COMMAND);
        D.showdata();
        tim(5);
        cout << "Press any key to exit";
        getchar();
        break; // Exiting the loop after one iteration
    }   
}
