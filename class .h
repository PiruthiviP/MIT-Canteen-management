#include <iomanip>
#include <string>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include "paymentpage.h"

#define CLEAR_COMMAND "clear"
using namespace std;

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x); // Move cursor to position (x, y)
}

void timer(int sec) {
    sleep(sec);
}

class Add_Item {
    string name;
    float price;
    int stock;
    int quantityInput;
    int quantities[50]; // Array to store quantities
    int iniStock; // to store initial stock for each item

public:
    void displayItems();
    void add_foodlist();
    void remove_foodlist();
    void change_price();
    void change_stock();
    void Billing_page();
    void printReceipt();
    double calculateTotalAmount();
    void saveItemsToFile();
    void loadItemsFromFile();
    void sales_page();
};

Add_Item items[50];
int numItems = 0;
Add_Item I; // Making it a global object

// File name to store items data
string Itemsfile = "items.txt";

void Add_Item::saveItemsToFile() {
    ofstream file(Itemsfile);
    if (file.is_open()) {
        for (int i = 0; i < numItems; ++i) {
            file << items[i].name << " " << items[i].price << " " << items[i].stock << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file..." << endl;
    }
}

void Add_Item::loadItemsFromFile() {
    ifstream file(Itemsfile);
    if (file.is_open()) {
        while (!file.eof()) {
            file >> name >> price >> stock;
            if (!file.fail()) {
                items[numItems].name = name;
                items[numItems].price = price;
                items[numItems].stock = stock;
                items[numItems].iniStock = stock;
                numItems++;
            }
        }
        file.close();
    } else {
        cout << "Unable to open file for reading: " << endl;
    }
}

void Add_Item::Billing_page() {
    char user_opt;
    int opt, j = 0;

    memset(quantities, 0, sizeof(quantities)); // Reset quantities to zero to starting a new billing session
    system(CLEAR_COMMAND);

    cout << "Choose an item:" << endl;
    for (int i = 0; i < numItems; i++) {
        cout << i + 1 << ". " << items[i].name << endl;
        j++;
    }
    while (true) {
        cout << "Enter your choice: ";
        cin >> opt;

        if (opt < 0 || opt > j) {
            cout << "Invalid choice. Please enter a number between 1 and " << j << "." << endl;
            continue;
        }

        cout << "Enter the quantity: ";
        cin >> items[opt - 1].quantityInput;

        if (items[opt - 1].quantityInput > items[opt - 1].stock) {
            cout << "Out of stock." << endl;
            continue;
        }

        // Update quantities array
        quantities[opt - 1] = items[opt - 1].quantityInput;
        items[opt - 1].stock -= items[opt - 1].quantityInput; // Reduce stock

        cout << "Do you want to add more items? (Y/N): ";
        cin >> user_opt;
        if (user_opt != 'Y' && user_opt != 'y') {
            break;
        }
    }
    I.printReceipt();
}

void Add_Item::displayItems() {
    if (numItems == 0) {
        cout << "No items added yet." << endl;
    } else {
        cout << "Current items:" << endl;
        for (int i = 0; i < numItems; ++i) {
            cout << i + 1 << ". " << items[i].name << " - Price: " << items[i].price << " - Stock: " << items[i].stock << endl;
        }
    }
}

void Add_Item::add_foodlist() {
    system(CLEAR_COMMAND);

    cout << "Enter the food name: ";
    cin >> name;

    for (int i = 0; i < numItems; ++i) {
        if (items[i].name == name) {
            cout << "The item already exists." << endl;
            timer(1);
            return;
        }
    }

    cout << "Enter the price of the food: ";
    cin >> price;

    cout << "Enter the stock of this food: ";
    cin >> stock;

    ofstream file(Itemsfile, ios::app); // Saving the item to the file
    if (file.is_open()) {
        file << name << " " << price << " " << stock << endl;
        file.close();
    } else {
        cout << "Unable to open file..." << endl;
        timer(1);
        return;
    }

    items[numItems].name = name;
    items[numItems].price = price;
    items[numItems].stock = stock;
    items[numItems].iniStock = stock; // Initialize iniStock for the current item
    numItems++;
    cout << "Item added successfully." << endl;
    timer(1);
}

void Add_Item::change_price() {
    system(CLEAR_COMMAND);
    displayItems();
    int itemNumber;
    cout << "Enter the number of the item to change price: ";
    cin >> itemNumber;

    if (itemNumber > 0 && itemNumber <= numItems) {
        cout << "Enter the new price: ";
        cin >> items[itemNumber - 1].price;
        cout << "Price updated successfully." << endl;
        timer(1);
    } else {
        cout << "Invalid item number." << endl;
        timer(1);
    }
}

void Add_Item::remove_foodlist() {
    system(CLEAR_COMMAND);
    displayItems();
    int itemNumber;
    cout << "Enter the number of the item to remove: ";
    cin >> itemNumber;
    if (itemNumber > 0 && itemNumber <= numItems) {
        for (int i = itemNumber - 1; i < numItems - 1; i++) {
            items[i] = items[i + 1];
        }
        numItems--;
        cout << "Item removed successfully." << endl;
        timer(1);
    } else {
        cout << "Invalid item number." << endl;
        timer(1);
    }
}

void Add_Item::change_stock() {
    system(CLEAR_COMMAND);
    displayItems();
    int itemNumber;
    cout << "Enter the number of the item to change stock: ";
    cin >> itemNumber;

    if (itemNumber > 0 && itemNumber <= numItems) {
        cout << "Enter the new stock: ";
        cin >> items[itemNumber - 1].stock;
        cout << "Stock updated successfully." << endl;
        timer(1);
    } else {
        cout << "Invalid item number." << endl;
        timer(1);
    }
}

void printCentered(const string &text, int width) {
    int padding = (width - text.length()) / 2;
    cout << setw(padding + text.length()) << right << text << endl;
}

void printSeparator(int width) {
    cout << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
}

double Add_Item::calculateTotalAmount() {
    double totalAmount = 0.0;

    // Calculate total amount based on items ordered 
    for (int i = 0; i < numItems; i++) {
        if (quantities[i] > 0) {
            totalAmount += items[i].price * quantities[i];
        }
    }
    D.amount(totalAmount);
    return totalAmount;
}

void Add_Item::printReceipt() {
    system(CLEAR_COMMAND);
    cout << "TOTAL AMOUNT" << "₹" << calculateTotalAmount() << endl;
    getchar();
    cout << "Redirecting to payment page............" << endl;
    timer(2);
    system(CLEAR_COMMAND);
    // Calling Paymentpage function 
    Paymentpage(calculateTotalAmount());

    timer(16);
    system(CLEAR_COMMAND);

    const string restaurantName = "MIT RESTAURANT";
    const string address = "MITCAMPUS CHROMPET CHENNAI-44";

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    string dateTime = ctime(&time);

    static int orderNo = 1000;
    D.oderdata(orderNo);
    // D.(calculateTotalAmount());
    const int lineWidth = 40;

    printCentered(restaurantName, lineWidth);
    printCentered(address, lineWidth);
    cout << left << setw(7) << "DATE: " << dateTime;
    cout << right << setw(2) << "ORDER NO:" << orderNo++ << endl;
    printSeparator(lineWidth);

    for (int i = 0; i < numItems; i++) {
        if (quantities[i] > 0) {
            double itemTotal = items[i].price * quantities[i];
            cout << setw(30) << left << items[i].name << "₹" << fixed << setprecision(2) << itemTotal << endl;
            cout << "QTY: " << quantities[i] << " @ " << items[i].price << " each" << endl;
        }
    }

    printSeparator(lineWidth);
    cout << setw(30) << left << "TOTAL AMOUNT" << "₹" << calculateTotalAmount() << endl;
    printSeparator(lineWidth);
    cout << "\tHAVE A NICE DAY.\n   THANK YOU. VISIT AGAIN." << endl;
}

void Add_Item::sales_page() {
    system(CLEAR_COMMAND);
    cout << "Item Name\tTotal Stock\tQuantity Sold" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < numItems; i++) {
        int quantitySold = items[i].iniStock - items[i].stock;
        cout << setw(20) << left << items[i].name << setw(15) << left << items[i].iniStock << setw(15) << left << quantitySold << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
    timer(5);
}

void Add_items_page() {
    int choice;
    do {
        system(CLEAR_COMMAND);
        gotoxy(25, 7);
        cout << "1. Add items" << endl;
        gotoxy(25, 8);
        cout << "2. Remove items" << endl;
        gotoxy(25, 9);
        cout << "3. Change price" << endl;
        gotoxy(25, 10);
        cout << "4. Change stock" << endl;
        gotoxy(25, 11);
        cout << "5. Exit" << endl;
        gotoxy(25, 13);
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                I.add_foodlist();
                break;
            case 2:
                I.remove_foodlist();
                break;
            case 3:
                I.change_price();
                break;
            case 4:
                I.change_stock();
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                timer(1);
        }
    } while (choice != 5);
}

