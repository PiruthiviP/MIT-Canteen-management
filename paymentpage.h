
#include <string>
#include <qrencode.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "customer_details.h"
using namespace std;
Data D;
string generateRandomString(int length) {
    const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   string result;
    for (int i = 0; i < length; ++i) {
        result += charset[rand() % charset.length()];
    }
    return result;
}
int Paymentpage(double totalAmount) {
    
    srand(time(nullptr));

    // Payment information
    const string upiId = "abccd@oksbi--example "; //   UPI ID must 
    const double amount = totalAmount; // Payment amount

    // Generate transaction reference ID
    string transactionRef = generateRandomString(10); // Change to generateRandomString(10) for random or generateSequentialReferenceID(counter) for sequential

    D.refdata(transactionRef);
    // Format payment data
    string paymentData = "upi://pay?pa=" + upiId + "&am=" + std::to_string(amount) + "&tr=" + transactionRef;

    // Generate QR code
    QRcode *qr = QRcode_encodeString(paymentData.c_str(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);

    if (qr) {
        
        for (int y = 0; y < qr->width; y++) {
            for (int x = 0; x < qr->width; x++) {
                cout << (qr->data[y * qr->width + x] & 1 ? "██" : "  ");
            }
            cout << std::endl;
        }
        QRcode_free(qr);
        
        
    } else {
        std::cerr << "Failed to generate QR code" << std::endl;
        return 1;
    }
    return 0;

    
}

