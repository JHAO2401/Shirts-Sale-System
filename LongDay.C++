#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>  // toupper fuction
#include <cstdlib>
#include <windows.h> // sleep fuction
using namespace std;

// variables
int customerCount = 0;
int orderCount = 0;
int totalItems = 0;
int totalUnits = 0;
double companyTotalRevenue = 0;
int companyTotalSold = 0;
int Step = 1;
string CardNumber, ExpMonth, ExpYear, SecurityCode;
char Confirm;
double Cash;
string digit;

// Structures for payment result
struct PaymentResult {
    string method;
    double paid = 0;
    double change = 0;
    PaymentResult() : method(""), paid(0), change(0) {} //Make sure the system has a clean initialization of every new PaymentResult object
};

// Structures for customer record
struct CustomerRecord {
    string name = "";
    string items[100];
    string sizes[100];
    int qty[100];
    double prices[100];
    string deliveryType = "";
    string paymentMethod = "";
    double totalPaid = 0.0;
    int itemCount = 0;
};

// Structures for order summary
struct OrderSummary {
    string customerName = "";
    string items[100];
    string sizes[100];
    int qty[100];
    double total = 0.0;
    int itemCount = 0;
};

// collect data from CustomerRecord to allCustomers
CustomerRecord allCustomers[100];
// collect data from OrderSummary to allOrders
OrderSummary allOrders[100];

// all Function declarations
void displayLogo();
void displayMenu();
bool isAllDigits(const string digit);
bool isPhoneDigits(const string PhoneDigit);
void loadingScreen();
void customerName(string& customer);
void printInvoice(string customer, string cartItems[], string cartSize[], int cartQty[],
    double cartPrice[], int cartCount, int invoiceNo, double total, double discountAmount,
    double discountRate, double serviceCharge, double tax, double fee, double finalTotal,
    string deliveryType, string address, string phone, int totalItems);
void printReceipt(string customer, string cartItems[], string cartSize[], int cartQty[],
    double cartPrice[], int cartCount, int invoiceNo, string paymentMethod,
    double paymentAmount, double change, double discountAmount, double discountRate,
    double serviceCharge, double tax, double fee, double finalTotal, string selectedName,
    string deliveryType, string address, string phone, double subtotal, int totalItems);
PaymentResult processPayment(double finalTotal);
void getDeliveryDetails(string& address, string& phone);
void displayDeliveryDetails(const string& address, const string& phone);
void printReport();

// Function display logo
void displayLogo() {
    cout << R"(                                                | |         _     _                       ___       
                                  )|(          _|_|_      o' \,=./ `o      ,,,,,         <_*_>     
                                 (o o)         (o o)         (o o)       //(o o)\\       (o o)      
                             ooO--(_)--Ooo-ooO--(_)--Ooo-ooO--(_)--Ooo-ooO--(_)--Ooo------(_)--Ooo- 
  
                                      ______                      ________                
                                        ___  / ___________________ ___  __ \_____ ____  __
                                        __  /  _  __ \_  __ \  __ `/_  / / /  __ `/  / / /
                                        _  /___/ /_/ /  / / / /_/ /_  /_/ // /_/ /  /_/ / 
                                        /_____/\____//_/ /_/\__, / /_____/ \__,_/ \__, /
                                                           /____/                /____/
   
        --------------------------------------------------------------------------------------------------------
   )" << endl;
}

// fuction display menu
void displayMenu() {
    cout << "                                                      Welcome to LongDay" << endl;
    cout << "\t--------------------------------------------------------------------------------------------------------" << endl;
}

// check customer enter is digit or not
bool isAllDigits(const string digit) {
    for (char d : digit) {
        if (!isdigit(d)) return false;
    }
    return true;
}

// check customer enter is phone digit or not
bool isPhoneDigits(const string PhoneDigit) {
    for (char p : PhoneDigit) {
        if (!isdigit(p)) return false;
    }
    return true;
}
// loding screen
void loadingScreen() {
    cout << "\nLoading...";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        Sleep(500);
    }
    system("cls");
}

// check customer have enter name or not
void customerName(string& customer) {
    do {
        cout << "Enter your name: ";
        getline(cin, customer);
        if (customer.empty()) {
            cout << "Name cannot be empty. Please enter again." << endl;
        }
    } while (customer.empty());
}

// fuction invoice
void printInvoice(string customer, string cartItems[], string cartSize[], int cartQty[],
    double cartPrice[], int cartCount, int invoiceNo, double total, double discountAmount,
    double discountRate, double serviceCharge, double tax, double fee, double finalTotal,
    string deliveryType, string address, string phone, int totalItems) {

    cout << "\n=========================================\n";
    cout << "             LONGDAY STORE INVOICE\n";
    cout << "=========================================\n";
    cout << "Invoice No: " << invoiceNo << endl;
    cout << "Customer: " << customer << endl;
    cout << "Method: " << deliveryType << "\n";
    if (deliveryType == "Delivery") {
        cout << "Address: " << address << "\n";
        cout << "Phone:   " << phone << "\n";
    }
    cout << "\n";
    cout << "-----------------------------------------\n";
    cout << left << setw(5) << "No" << setw(15) << "Item" << setw(8) << "Size"
        << setw(8) << "Qty" << setw(10) << "Price(RM)" << endl;
    cout << "-----------------------------------------\n";

    //disply all customer detail
    for (int i = 0; i < cartCount; i++) {
        double itemTotal = cartQty[i] * cartPrice[i];
        cout << left << setw(5) << i + 1 << setw(15) << cartItems[i]
            << setw(8) << cartSize[i] << setw(8) << cartQty[i]
            << setw(10) << fixed << setprecision(2) << itemTotal << endl;
    }

    cout << "-----------------------------------------\n";
    cout << setw(28) << "Subtotal: RM " << fixed << setprecision(2) << total << endl;
    cout << "Discount (" << discountRate * 100 << "%):" << setw(10) << "RM " << discountAmount << endl;
    cout << setw(28) << "Service (4%): " << serviceCharge << endl;
    cout << setw(28) << "Tax (3%): " << tax << endl;
    if (deliveryType == "Delivery") {
        cout << setw(28) << "Delivery Fee:" << fee << endl;
    }
    cout << setw(28) << "Total (RM): " << finalTotal << endl;
    cout << setw(28) << "Total Items: " << totalItems << endl;
    cout << "=========================================\n";
    cout << "   Please confirm and select payment\n";
    cout << "=========================================\n";
}

// fuction receipt
void printReceipt(string customer, string cartItems[], string cartSize[], int cartQty[],
    double cartPrice[], int cartCount, int invoiceNo, string paymentMethod,
    double paymentAmount, double change, double discountAmount, double discountRate,
    double serviceCharge, double tax, double fee, double finalTotal, string selectedName,
    string deliveryType, string address, string phone, double total, int totalItems) {

    cout << "\n=========================================\n";
    cout << "             LONGDAY STORE RECEIPT\n";
    cout << "=========================================\n";
    cout << "             Tel:012-3456789             \n";
    cout << "Receipt No: " << invoiceNo << endl;
    cout << "Customer: " << customer << endl;
    cout << "Payment Method: " << paymentMethod << endl;
    cout << "Method: " << deliveryType << endl;
    if (deliveryType == "Delivery") {
        cout << "Address: " << address << endl;
        cout << "Phone:   " << phone << endl;
    }
    cout << "\n-----------------------------------------\n";
    cout << left << setw(5) << "No" << setw(15) << "Item" << setw(8) << "Size"
        << setw(8) << "Qty" << setw(10) << "Price(RM)" << endl;
    cout << "-----------------------------------------\n";

    //disply all customer detail
    for (int i = 0; i < cartCount; i++) {
        double itemTotal = cartQty[i] * cartPrice[i];
        cout << left << setw(5) << i + 1 << setw(15) << cartItems[i]
            << setw(8) << cartSize[i] << setw(8) << cartQty[i]
            << setw(10) << fixed << setprecision(2) << itemTotal << endl;
    }

    cout << "-----------------------------------------\n";
    cout << setw(28) << "Subtotal (RM): " << fixed << setprecision(2) << total << endl;
    cout << "Discount (" << discountRate * 100 << "%):" << setw(10) << "RM " << discountAmount << endl;
    cout << setw(28) << "Service (4%): " << serviceCharge << endl;
    cout << setw(28) << "Tax (3%): " << tax << endl;
    if (deliveryType == "Delivery") {
        cout << setw(28) << "Delivery Fee:" << fee << endl;
    }
    cout << setw(28) << "Total (RM): " << finalTotal << endl;
    cout << setw(28) << "Total Items: " << totalItems << endl;
    cout << "-----------------------------------------\n";
    cout << "Payment Method: " << selectedName << endl;
    cout << "Payment Amount: RM " << fixed << setprecision(2) << paymentAmount << endl;
    cout << "Change: RM " << fixed << setprecision(2) << change << endl;
    cout << "=========================================\n";
    cout << "   Thank you for shopping with us!       \n";
    cout << "=========================================\n";
}

// check payment result and payment process
PaymentResult processPayment(double finalTotal) {
    string codes[] = { "EW", "ew", "CC", "cc", "DC", "dc", "C", "c" };
    string names[] = { "e-Wallet", "Credit Card", "Debit Card", "Cash" };
    string paymentMethod, selectedName = "";

    do {
        cout << "\nSelect payment method (EW=e-Wallet, CC=Credit Card, DC=Debit Card, C=Cash): ";
        cin >> paymentMethod;

        // display payment method name that the customer selected
        for (int i = 0; i < 8; i++) {
            if (paymentMethod == codes[i]) {
                selectedName = names[i / 2]; //The element in names array at the index of i divided by 2.
                break;
            }
        }

        if (selectedName == "") {
            cout << "Invalid payment method. Please try again.\n";
        }
    } while (selectedName == "");

    // check all result 
    PaymentResult result;
    result.method = selectedName;
    result.paid = finalTotal;
    result.change = 0;

    cout << "\n==== Payment with " << selectedName << " ====\n";

    // e-Wallet payment process
    if (selectedName == "e-Wallet") {
        loadingScreen();
        cout << R"(  
                      ######################################################################################
                      ######################################################################################
                      ######################################################################################
                      #######               ###### ##  ##  ##            ####    ####               ########
                      #######  ###########  ##  ## ###   ##    ##   ##     #####  ###  ###########  ########
                      #######  ##       ##  ############  #########  #####    #######  ##       ##  ########
                      #######  ##       ##  ###    ###       ##  ###        #########  ##       ##  ########
                      #######  ##       ##  ###### #####  #####  #### ##### #########  ##       ##  ########
                      #######  ###########  ##   ##   ####   #####   ###   #####  ###  ###########  ########
                      #######               ##     ###  #####  ##  ###  ##  ###  ####               ########
                      ############################     ############     ######    ##########################
                      #######             ###    ############   ################       ## ###  #### ########
                      #########   ###########      #######        ##################   ########     ########
                      ######     ########     #######################        #################   ###########
                      ###########    ####    ####     ###            #####    #################     ########
                      #######          ##########       ##########      #######   ###   ######    ##########
                      ######## ####  ########    ###############      #########      #####          ########
                      #########    #####    ####    #######    #####   ######    ###   ####    #### ########
                      #########   ###############################################################   ########
                      #################         #######    ##########     ###########     #######   ########
                      ########  ############################     ##################   ######################
                      #########       ##############       ##############    ######      ########   ########
                      ###########   #############           #########   ###############     ################
                      #########          ####################      ###############         ######   ########
                      ######################################################################################
                      ######               ###          #######          #############             #########
                      ######  ###########  ##########             #######              #####       #########
                      ######  ##       ##  #################################################################
                      ######  ##       ##    ###            #####          ###          #########  #########
                      ######  ##       ##  ##       ###      ####        #####     #####     ####  #########
                      ######  ###########  ###   ##      ###      #################                #########
                      ######               ########    #####       ###########         #######    ##########
                      ######################################################################################
                      ######################################################################################
                      ######################################################################################)" << endl;
        Sleep(2000);
        cout << "Payment Successful " << selectedName << "!\n";
    }
    // Credit Card and Debit Card payment process
    else if (selectedName == "Credit Card" || selectedName == "Debit Card") {
        loadingScreen();


        while (true) {
            switch (Step) {
            case 1:
                cout << "Enter Card Number (16 digits): ";
                cin >> CardNumber;
                if (CardNumber.size() == 16 && isAllDigits(CardNumber)) { //Check if the number has 16 or not
                    Step = 2;
                }
                else {
                    cout << "Invalid Card Number. Please enter exactly 16 digits.\n";
                }
                break;

            case 2:
                cout << "Enter Expiration Month (MM): ";
                cin >> ExpMonth;
                if (ExpMonth.size() == 2 && isAllDigits(ExpMonth)) { //Check if the number has 2 or not
                    int month = stoi(ExpMonth);
                    if (month >= 1 && month <= 12) {
                        Step = 3;
                    }
                    else {
                        cout << "Invalid Month. Please enter 01 - 12.\n";
                    }
                }
                else {
                    cout << "Invalid Month Format.\n";
                }
                break;

            case 3:
                cout << "Enter Expiration Year (YY): ";
                cin >> ExpYear;
                if (ExpYear.size() == 2 && isAllDigits(ExpYear)) {  //Check if the number has 2 or not
                    int year = stoi(ExpYear);
                    if (year >= 1 && year <= 99) {
                        Step = 4;
                    }
                    else {
                        cout << "Invalid Year. Please enter 01 - 99.\n";
                    }
                }
                else {
                    cout << "Invalid Year Format.\n";
                }
                break;

            case 4:
                cout << "Enter Security Code (4 digits): ";
                cin >> SecurityCode;
                if (SecurityCode.size() == 4 && isAllDigits(SecurityCode)) { //Check if the number has 4 or not
                    Step = 5;
                }
                else {
                    cout << "Invalid CVV. Must be 4 digits.\n";
                }
                break;

            case 5:
                cout << "\nConfirm Payment with " << selectedName << "? (Y/N): "; // Confirm the payment process from credit card and debit card
                cin >> Confirm;

                Confirm = toupper(Confirm);
                if (Confirm != 'Y' && Confirm != 'N') {
                    cout << "\nInvalid input. Please enter a valid alphabet.\n";
                    continue;
                }
                if (Confirm == 'Y') {
                    cout << "Payment Successful via " << selectedName << "!\n";
                    return result;
                }
                else if (Confirm == 'N') {
                    cout << "Payment Cancelled. Please enter your details again.\n";
                    Step = 1;
                }

                break;
            }
        }
    }
    // Cash payment process
    else if (selectedName == "Cash") {

        do {
            cout << "Enter your cash amount: RM ";
            cin >> Cash;
            if (Cash < finalTotal) {
                cout << "Invalid amount. Please enter your amount again.\n";
            }

            if (cin.fail()) {
                cin.clear();  // clear the error 
                cin.ignore(1000, '\n'); // discard invalid input
                cout << "Invalid input. Please enter a valid amount.\n";
                continue;
            }
        } while (Cash < finalTotal || cin.fail());

        //Calculate whether the cash has less than the total amount or not 
        result.paid = Cash;
        result.change = Cash - finalTotal;
        cout << "Payment Successful! Change: RM " << fixed << setprecision(2) << result.change << endl;
    }

    return result;
}

// check delivery detail is correct or not
void getDeliveryDetails(string& address, string& phone) {
    cout << "Enter your delivery address: ";
    cin.ignore();
    getline(cin, address);

    while (true) {
        cout << "Enter your phone number (10 digits): ";
        getline(cin, phone);
        if (phone.length() == 10 && isPhoneDigits(phone)) { //Check if the phone number has 10 or not
            break;
        }
        else {
            cout << "Invalid phone number. Please enter exactly 10 digits.\n";
        }
    }
}

//store delivery detail from customer
void displayDeliveryDetails(const string& address, const string& phone) {
    cout << "\n--- Delivery Details ---" << endl;
    cout << "Address: " << address << endl;
    cout << "Phone: " << phone << endl;
    cout << "-------------------------" << endl;
}

// check total sold and total revenue from company report
void printReport() {
    system("cls");
    cout << "================================= COMPANY REPORT =================================" << endl;
    cout << "Total Revenue Collected : RM " << fixed << setprecision(2) << companyTotalRevenue << endl;
    cout << "Total Items Sold        : " << companyTotalSold << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "Summary List:\n" << endl;

    if (orderCount == 0) {
        cout << "No orders have been made yet." << endl;
    }
    else {
        cout << left << setw(5) << "No"
            << setw(15) << "Customer"
            << setw(30) << "Items"
            << setw(12) << "Total Units"
            << right << setw(15) << "Total (RM)" << endl;
        cout << "----------------------------------------------------------------------------------\n";

        // display customer name and order
        for (int i = 0; i < orderCount; i++) {
            cout << left << setw(5) << i + 1;
            cout << setw(15) << allOrders[i].customerName;

            string itemList = "";

            //display all order summary
            for (int j = 0; j < allOrders[i].itemCount; j++) {
                itemList += allOrders[i].items[j] + " (" + allOrders[i].sizes[j] + ")";
                totalUnits += allOrders[i].qty[j];
                if (j < allOrders[i].itemCount - 1) {
                    itemList += ", ";
                }
            }

            cout << setw(30) << itemList;
            cout << setw(12) << totalUnits;
            cout << right << setw(15) << fixed << setprecision(2) << allOrders[i].total << endl;
        }

        cout << "==================================================================================\n";
    }
}

int main() {

    string customer;
    string items[6] = { "Skirt", "Dress", "T-shirt", "Pants", "Outwear", "Jeans" };
    double prices[6] = { 20, 40, 30, 70, 50, 100 };
    int category, qty;
    string size;

    string cartItems[100];
    string cartSize[100];
    int cartQty[100];
    double cartPrice[100];

    int cartCount = 0;
    int unitCount = 0;
    int orderSumQty = 0;

    int choice;
    char cont;
    char ans;
    int delChoice;
    int delQty;
    char next;

    char deliveryChoice;
    char confirmChoice;
    string deliveryType;
    string address;
    string phone;

    double total = 0;
    double fee = 0.0;
    double discountRate = 0.0;
    int customerNum = 0;
    double change = 0.0;

    bool running = true; // for customer entering loop
    bool shopping = true;  // for shopping loop
    bool stopDelete = false; // for delete loop
    bool continueShopping = false; // for continue loop
    bool backToMainMenu = false;  // back to main menu loop

    int invoiceNo = 1;

    // customer entering loop
    while (running) {
        system("cls");
        displayLogo();
        displayMenu();
        cout << "\t\t\t\t\t\t==== Welcome to LongDay Menu ====\n" << endl;
        cout << "Customer No: " << customerNum + 1 << endl;
        cout << "\t\t\t\t\t\t----------------------------\n";
        cout << "\t\t\t\t\t\t|1. Order entry            |\n";
        cout << "\t\t\t\t\t\t|2. Reporting              |\n";
        cout << "\t\t\t\t\t\t|3. Exit                   |\n";
        cout << "\t\t\t\t\t\t----------------------------\n" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        // check number is from 1 to 3 
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
            Sleep(2000);
            continue;

        }

        cin.ignore(1000, '\n');

        if (choice == 1) {
            customerName(customer);
            shopping = true;
            stopDelete = false;
            continueShopping = false;
            backToMainMenu = false;
            cartCount = 0;
            total = 0;

            // customer entering shop
            while (shopping) {
                loadingScreen();

                cout << R"(You selected: LongDay Menu
                      + ------------ + --------------- + ------ +
                      |   Category   |       Size      | Price  |
                      + ------------ + --------------- + ------ +
                      | 1) Skirt     |  S / M / L / XL | RM 20  |
                      | 2) Dress     |  S / M / L / XL | RM 40  |
                      | 3) T-shirt   |  S / M / L / XL | RM 30  |
                      | 4) Pants     |  S / M / L / XL | RM 70  |
                      | 5) Outwear   |  S / M / L / XL | RM 50  |
                      | 6) Jeans     |  S / M / L / XL | RM 100 |
                      + ------------ + --------------- + ------ +
                  )" << endl;

                do {
                    cout << "Enter Category number(1-6): ";
                    cin >> category;
                    if (cin.fail() || category < 1 || category > 6) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid category. Please enter 1-6.\n";
                    }
                    else {
                        break;
                    }
                } while (true);

                do {
                    cout << "Enter Size (S/M/L/XL): ";
                    cin >> size;
                } while (size != "S" && size != "s" && size != "M" && size != "m" &&
                    size != "L" && size != "l" && size != "XL" && size != "xl");

                do {
                    cout << "Quantity: ";
                    cin >> qty;
                    if (cin.fail() || qty <= 0) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "\nInvalid quantity. Please enter again\n";
                    }
                    else {
                        break;
                    }
                } while (true);

                // check what the customer buys
                int index = category - 1;
                cartItems[cartCount] = items[index];
                cartSize[cartCount] = size;
                cartQty[cartCount] = qty;
                cartPrice[cartCount] = prices[index];
                cartCount++;

                totalItems += qty;
                cout << "Added to cart!\n";

                // check customer view cart and calculate total amount from each item they buy
                total = 0;
                cout << "\n---------------- YOUR CART ----------------" << endl;
                for (int i = 0; i < cartCount; i++) {
                    double itemTotal = cartQty[i] * cartPrice[i];
                    cout << i + 1 << ". " << cartItems[i] << " | Size: "
                        << cartSize[i] << " | Qty: " << cartQty[i]
                        << " | RM" << fixed << setprecision(2) << itemTotal << endl;
                    total += itemTotal;
                }
                cout << "-------------------------------------------" << endl;
                cout << "TOTAL = RM" << fixed << setprecision(2) << total << endl;

                // Asking the customer if they want to continue or not
                do {
                    cout << "\nDo you want to continue shopping? (y/n):";
                    cin >> cont;
                    cont = toupper(cont);
                    if (cont == 'Y' || cont == 'N') { // if y continue shopping 
                        break;
                    }
                    else {
                        cout << "\nInvalid input. Please type only 'y' or 'n'.\n";
                    }
                } while (true);

                // if n stop shopping and go to delete item fuction
                if (cont == 'N') {

                    while (!stopDelete && cartCount > 0) {

                        // let customer choose delete item or stop delete
                        cout << "\nEnter item number to delete ( [0 = delete ALL] [-1 = stop delete] [Enter Number In View Cart]):";
                        cin >> delChoice;

                        //Check if the entered number is correct or not
                        if (cin.fail()) {
                            cin.clear();// clear the error 
                            cin.ignore(1000, '\n');// discard invalid input
                            cout << "\nInvalid input. Please enter a number.\n";
                            continue;
                        }

                        // check if the customer entered choice is correct or not
                        if (delChoice != -1 && delChoice != 0 && (delChoice < 1 || delChoice > cartCount)) {
                            cout << "\nInvalid choice. Please enter again.\n";
                            continue;
                        }

                        // all items are removed
                        if (delChoice == 0) {
                            cartCount = 0;
                            totalItems = 0;
                            total = 0;
                            cout << "All items removed from cart.\n";
                            break;
                        }
                        // stop deleting items and go to delivery function
                        else if (delChoice == -1) {
                            cout << "Stop deleting.\n";
                            stopDelete = true; // go to delivery
                            break;
                        }
                        //count how many items got deleted by the customer
                        else if (delChoice > 0 && delChoice <= cartCount) {
                            cout << "How many items to delete (max " << cartQty[delChoice - 1] << "): ";
                            cin >> delQty;

                            //Check if the entered number is correct or not
                            if (cin.fail() || delQty < 1 || delQty > cartQty[delChoice - 1]) {
                                cin.clear(); // clear the error 
                                cin.ignore(1000, '\n'); // discard invalid input
                                cout << "\nInvalid input. Please enter a number between 1 and "
                                    << cartQty[delChoice - 1] << ".\n";
                                continue;
                            }

                            // check what the customer item was deleted
                            if (delQty >= cartQty[delChoice - 1]) {

                                //all items removed
                                totalItems -= cartQty[delChoice - 1];
                                for (int j = delChoice - 1; j < cartCount - 1; j++) {
                                    cartItems[j] = cartItems[j + 1];
                                    cartSize[j] = cartSize[j + 1];
                                    cartQty[j] = cartQty[j + 1];
                                    cartPrice[j] = cartPrice[j + 1];
                                }
                                cartCount--;
                                cout << "Item removed.\n";
                            }
                            //Calculate the total items removed
                            else {
                                totalItems -= delQty;
                                cartQty[delChoice - 1] -= delQty;
                                cout << delQty << " item(s) removed.\n";
                            }
                        }
                        // check again customer view cart and calculate total amount from each item they buy
                        total = 0;
                        cout << "\n---------------- YOUR CART ----------------" << endl;
                        if (cartCount > 0) {
                            for (int i = 0; i < cartCount; i++) {
                                double itemTotal = cartQty[i] * cartPrice[i];
                                cout << i + 1 << ". " << cartItems[i] << " | Size: "
                                    << cartSize[i] << " | Qty: " << cartQty[i]
                                    << " | RM" << fixed << setprecision(2) << itemTotal << endl;
                                total += itemTotal;
                            }
                            cout << "-------------------------------------------" << endl;
                            cout << "TOTAL = RM" << fixed << setprecision(2) << total << endl;
                        }
                        else {
                            cout << "Your cart is empty.\n";
                        }
                        // let customer continue deleting
                        if (cartCount > 0) {
                            do {
                                cout << "\nDo you want to continue deleting? (y/n): ";
                                cin >> cont;
                                cont = toupper(cont);
                                if (cont == 'Y' || cont == 'N') {
                                    break;
                                }
                                else {
                                    cout << "\nInvalid input. Please type only 'y' or 'n'.\n";
                                }
                            } while (true);

                            if (cont == 'N') {
                                stopDelete = true; // go to delivery
                            }
                        }
                    }
                    // customer cart is empty
                    if (cartCount == 0) {
                        cout << "Cart is now empty.\n";
                        do {
                            // continue or back to main menu
                            cout << "Do you want to continue shopping (y) or go back to main menu (n)? (y/n): ";
                            cin >> ans;
                            ans = toupper(ans);

                            // continue shopping
                            if (ans == 'Y') {
                                continueShopping = true; // active
                                backToMainMenu = false; // no active
                                shopping = true; // active
                                break;
                            }
                            // back to main menu
                            else if (ans == 'N') {
                                backToMainMenu = true; // active
                                continueShopping = false; // no active
                                shopping = false; // no active
                                break;
                            }
                            else {
                                cout << "\nInvalid input! Please type only 'y' or 'n'.\n";
                            }
                        } while (true);

                        if (continueShopping) {
                            continue;
                        }
                        else if (backToMainMenu) {
                            break;
                        }
                    }
                    else {
                        shopping = false;
                    }
                }

            }
            // back to main menu and loop again
            if (backToMainMenu) {
                loadingScreen();
                backToMainMenu = false;  // no active
                continueShopping = true; // active
                stopDelete = true;// active
                shopping = true;// active
                continue;
            }
            //  Check the customer delivery choice they want
            if (cartCount > 0) {
                do {
                    // let customer choose delivery type
                    cout << "\nDo you want delivery (D) or pick up (P)? : ";
                    cin >> deliveryChoice;
                    deliveryChoice = toupper(deliveryChoice);
                    if (deliveryChoice == 'D' || deliveryChoice == 'P') {
                        break;
                    }
                    else {
                        cout << "\nInvalid input! Please enter only D or P.\n";
                    }
                } while (true);

                if (deliveryChoice == 'D') {
                    deliveryType = "Delivery";
                    getDeliveryDetails(address, phone); // check detail from customer typing

                    // Asking the customer if the information is correct or not
                    do {
                        displayDeliveryDetails(address, phone);
                        cout << "\nIs the above information correct? (y/n): ";
                        cin >> confirmChoice;
                        confirmChoice = toupper(confirmChoice);
                        if (confirmChoice == 'Y') {
                            break;
                        }
                        else if (confirmChoice == 'N') {
                            getDeliveryDetails(address, phone); // type again
                        }
                        else {
                            cout << "\nInvalid input. Please type only 'y' or 'n'.\n";
                        }
                    } while (true);
                    fee = 5.0;
                }
                else {
                    deliveryType = "Pick Up";
                    fee = 0.0;
                }

                loadingScreen();

                // check the discount rate for the customer who buys
                if (total > 299) discountRate = 0.25;  // 25%
                else if (total > 249) discountRate = 0.20; // 20%
                else if (total > 199) discountRate = 0.15; // 15%
                else if (total > 149) discountRate = 0.10; // 10%
                else if (total > 99) discountRate = 0.05; // 5%
                else discountRate = 0.0;

                // calulate process
                double discountAmount = total * discountRate;
                double serviceCharge = (total - discountAmount) * 0.04;
                double tax = (total - discountAmount) * 0.03;
                double finalTotal = total - discountAmount + serviceCharge + tax + fee;

                loadingScreen();

                // print invoice
                printInvoice(customer, cartItems, cartSize, cartQty, cartPrice, cartCount,
                    invoiceNo, total, discountAmount, discountRate,
                    serviceCharge, tax, fee, finalTotal,
                    deliveryType, address, phone, totalItems);

                // check payment result and process
                PaymentResult pay = processPayment(finalTotal);

                cout << "------> Discount Applied: " << discountRate * 100 << "%\n";
                cout << "Total Amount after discount: RM " << fixed << setprecision(2) << finalTotal << endl;
                Sleep(2000);

                loadingScreen();

                // print receipt
                printReceipt(customer, cartItems, cartSize, cartQty, cartPrice, cartCount, invoiceNo,
                    pay.method, pay.paid, pay.change, discountAmount, discountRate,
                    serviceCharge, tax, fee, finalTotal, pay.method,
                    deliveryType, address, phone, total, totalItems);

                // all customer record
                CustomerRecord record;
                record.name = customer;
                record.totalPaid = finalTotal;
                record.deliveryType = deliveryType;
                record.paymentMethod = pay.method;
                record.itemCount = cartCount;

                // customer item record
                for (int i = 0; i < cartCount; i++) {
                    record.items[i] = cartItems[i];
                    record.sizes[i] = cartSize[i];
                    record.qty[i] = cartQty[i];
                    record.prices[i] = cartPrice[i];
                }

                allCustomers[customerCount] = record;
                customerCount++;

                // all order record
                OrderSummary order;
                order.customerName = customer;
                order.total = finalTotal;
                order.itemCount = cartCount;

                // order record
                for (int i = 0; i < cartCount; i++) {
                    order.items[i] = cartItems[i];
                    order.sizes[i] = cartSize[i];
                    order.qty[i] = cartQty[i];
                }

                allOrders[orderCount] = order;
                orderCount++;

                // check the company total revenue through the final total
                companyTotalRevenue += finalTotal;

                orderSumQty = 0; // reset order quantity
                for (int i = 0; i < cartCount; i++) {
                    orderSumQty += cartQty[i];
                }

                // check the company total sold through the order sum
                companyTotalSold += orderSumQty;

                totalItems = 0; // reset total item      
                invoiceNo++;

                // count item order record
                for (int i = 0; i < cartCount; i++) {
                    cartItems[i] = "";
                    cartSize[i] = "";
                    cartQty[i] = 0;
                    cartPrice[i] = 0.0;
                }

                cartCount = 0;   // reset cart  
                finalTotal = 0.0; // reset total amount
            }

            // next ccustomer
            do {
                cout << "\nNext customer? (y/n): ";
                cin >> next;
                next = toupper(next);

                if (next != 'Y' && next != 'N') {
                    cout << "\nInvalid input. Please type only 'y' or 'n'.\n";
                }
            } while (next != 'Y' && next != 'N');

            if (next == 'Y') {
                customerNum++;
                loadingScreen();
                displayLogo();
                displayMenu();
            }
            else if (next == 'N') {
                customerNum++;
                loadingScreen();
                displayLogo();
                displayMenu();
            }

        }
        //Check the final detail from the customer report
        else if (choice == 2) {
            system("cls");
            cout << "============================================  CUSTOMER REPORT =========================================\n";

            // no customer recored
            if (customerCount == 0) {
                cout << "No customer records yet.\n";
            }
            else {
                cout << left << setw(5) << "No" << setw(20) << "Customer Name" << setw(20) << "Item(s)"
                    << setw(8) << "Unit" << setw(15) << "Size" << setw(12) << "Paid (RM)"
                    << setw(12) << "Payment" << setw(12) << "Delivery" << endl;
                cout << "------------------------------------------------------------------------------------------------------\n";

                // display customer record
                for (int i = 0; i < customerCount; i++) {
                    CustomerRecord c = allCustomers[i];
                    unitCount = 0; // reset unit

                    // display item quantity record
                    for (int j = 0; j < c.itemCount; j++) {
                        unitCount += c.qty[j];
                    }

                    string itemsStr = "";
                    string sizesStr = "";

                    // display item and size record
                    for (int j = 0; j < c.itemCount; j++) {
                        itemsStr += c.items[j];
                        sizesStr += c.sizes[j];
                        if (j < c.itemCount - 1) {
                            itemsStr += ", ";
                            sizesStr += ", ";
                        }
                    }

                    cout << left << setw(5) << i + 1 << setw(20) << c.name << setw(20) << itemsStr
                        << setw(8) << unitCount << setw(15) << sizesStr << setw(12) << fixed << setprecision(2) << c.totalPaid
                        << setw(12) << c.paymentMethod << setw(12) << c.deliveryType << endl;
                }
                cout << "------------------------------------------------------------------------------------------------------\n";
                cout << "Total Units Sold: " << companyTotalSold << endl;
                cout << "Total Income: RM " << fixed << setprecision(2) << companyTotalRevenue << endl;
                cout << "======================================================================================================\n";
            }

            //Check the company report to see the total sold and the total revenue from the customer report summary
            do {
                cout << "Do you want to check Company report? (y/n): ";
                cin >> ans;
                ans = toupper(ans);
                if (ans == 'Y' || ans == 'N') {
                    break;
                }
                else {
                    cout << "\nInvalid input. Please type only 'y' or 'n'.\n";
                }
            } while (true);

            if (ans == 'Y') {
                printReport();
            }

            // return back main menu
            cout << "Press Enter to return to main menu...";
            cin.ignore();
            cin.get();

            loadingScreen();
            displayLogo();
            displayMenu();
        }
        // leave the shop
        else if (choice == 3) {
            cout << "Thank you for visiting!!" << endl;
            running = false;
        }
    }
    return 0;
}