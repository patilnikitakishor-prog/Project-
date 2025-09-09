#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Item {
    string name;
    double price;
    int quantity;
};

int main() {
    int n;
    cout << "Enter number of items purchased: ";
    cin >> n;
    
    Item items[n];
    
    // Input item details
    for(int i = 0; i < n; i++) {
        cout << "\nEnter name of item " << i+1 << ": ";
        cin >> items[i].name;
        cout << "Enter price of " << items[i].name << ": ";
        cin >> items[i].price;
        cout << "Enter quantity of " << items[i].name << ": ";
        cin >> items[i].quantity;
    }
    
    // Print receipt
    double total = 0;
    cout << "\n\n-------- Supermarket Bill --------\n";
    cout << left << setw(15) << "Item"
         << right << setw(10) << "Price"
         << right << setw(10) << "Qty"
         << right << setw(12) << "Total\n";
    cout << "-----------------------------------------\n";
    
    for(int i = 0; i < n; i++) {
        double itemTotal = items[i].price * items[i].quantity;
        total += itemTotal;
        cout << left << setw(15) << items[i].name
             << right << setw(10) << items[i].price
             << right << setw(10) << items[i].quantity
             << right << setw(12) << itemTotal << "\n";
    }
    
    cout << "-----------------------------------------\n";
    cout << left << setw(35) << "Total Amount:" << right << setw(12) << total << "\n";
    cout << "-----------------------------------------\n";

    return 0;
}
