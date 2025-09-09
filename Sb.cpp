#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
class Item {
public:
    int id;
    string name;
    double price;
    string details; 
    Item(int i, string n, double p, string d) : id(i), name(n), price(p), details(d) {}  
    virtual void display() {
        cout << "|" << setw(4) << id << "|" << setw(18) << name << "|" 
             << setw(12) << details << "|" << setw(8) << fixed << setprecision(2) << price << "|" << endl;
    }
};
class Grocery : public Item {
public:
    Grocery(int i, string n, double p, string brand) : Item(i, n, p, brand) {}
};

class Electronics : public Item {
public:
    Electronics(int i, string n, double p, int warranty) : Item(i, n, p, to_string(warranty) + "m") {}
};
struct CartItem {
    Item* item;
    int qty;
};
class Billing {
public:
    vector<Item*> items;
    vector<CartItem> cart;
    int billNo;
    Billing() : billNo(1001) {
        items.push_back(new Grocery(1, "Rice 1kg", 45.50, "Basmati"));
        items.push_back(new Grocery(2, "Milk 1L", 55.00, "Amul"));
        items.push_back(new Grocery(3, "Bread", 25.00, "Britannia"));
        items.push_back(new Grocery(4, "Sugar 1kg", 42.00, "Madhur"));
        items.push_back(new Grocery(5, "Oil 1L", 120.00, "Fortune"));
        items.push_back(new Electronics(6, "LED Bulb", 150.00, 24));
        items.push_back(new Electronics(7, "Charger", 299.00, 12));
        items.push_back(new Electronics(8, "Battery 4pc", 180.00, 6));
        items.push_back(new Electronics(9, "Extension", 450.00, 18));
        items.push_back(new Electronics(10, "Torch", 250.00, 12));
    }
    void showItems() {
        cout << "\n===============================================\n";
        cout << "              AVAILABLE ITEMS\n";
        cout << "===============================================\n";
        cout << "| ID | Item Name         | Details     | Price  |\n";
        cout << "|----|--------------------|-------------|--------|\n";
        for (int i = 0; i < items.size(); i++) {
            items[i]->display();
        }
        cout << "===============================================\n";
    }
    Item* findItem(int id) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->id == id) return items[i];
        }
        return NULL;
    }
    void addToCart() {
        int id, qty;
        while (true) {
            cout << "Enter item ID (0 to stop): ";
            cin >> id;
            if (id == 0) break;
            Item* item = findItem(id);
            if (!item) {
                cout << "Item not found!\n";
                continue;
            }
            cout << "Enter quantity: ";
            cin >> qty;
            if (qty <= 0) {
                cout << "Invalid quantity!\n";
                continue;
            }
            bool found = false;
            for (int i = 0; i < cart.size(); i++) {
                if (cart[i].item->id == id) {
                    cart[i].qty += qty;
                    found = true;
                    break;
                }
            }
            if (!found) {
                CartItem newItem = {item, qty};
                cart.push_back(newItem);
            }
            cout << "Added " << qty << " x " << item->name << "\n";
            
            char more;
            cout << "Add more? (y/n): ";
            cin >> more;
            if (more == 'n') break;
        }
    }
    
    void showCart() {
        if (cart.empty()) {
            cout << "Cart is empty!\n";
            return;
        }
        
        cout << "\n===============================================\n";
        cout << "                 YOUR CART\n";
        cout << "===============================================\n";
        cout << "| Item Name         | Price  | Qty | Total  |\n";
        cout << "|-------------------|--------|-----|--------|\n";
        
        for (int i = 0; i < cart.size(); i++) {
            double total = cart[i].item->price * cart[i].qty;
            cout << "|" << setw(18) << cart[i].item->name 
                 << "|" << setw(7) << fixed << setprecision(2) << cart[i].item->price
                 << "|" << setw(4) << cart[i].qty
                 << "|" << setw(7) << total << "|" << endl;
        }
        cout << "===============================================\n";
    }
    
    void generateBill() {
        if (cart.empty()) {
            cout << "Cart is empty!\n";
            return;
        }
         double total = 0;

        // Open a file stream to write the bill
        ofstream billFile("bill.text");

        // Print to console
        cout << "\n===============================================\n";
        cout << "           SUPERMARKET BILL\n";
        cout << "===============================================\n";
        cout << "Bill No: " << billNo << endl;
        cout << "===============================================\n";
        cout << "| Item Name         | Price  | Qty | Total  |\n";
        cout << "|-------------------|--------|-----|--------|\n";
        
        // Print to file
        billFile << "           SUPERMARKET BILL\n";
        billFile << "===============================================\n";
        billFile << "Bill No: " << billNo << endl;
        billFile << "===============================================\n";
        billFile << "| Item Name         | Price  | Qty | Total  |\n";
        billFile << "|-------------------|--------|-----|--------|\n";
        
        for (int i = 0; i < cart.size(); i++) {
            double itemTotal = cart[i].item->price * cart[i].qty;
            total += itemTotal;

            // Print to console
            cout << "|" << setw(18) << cart[i].item->name 
                 << "|" << setw(7) << fixed << setprecision(2) << cart[i].item->price
                 << "|" << setw(4) << cart[i].qty
                 << "|" << setw(7) << itemTotal << "|" << endl;

            // Print to file
            billFile << "|" << setw(18) << cart[i].item->name 
                     << "|" << setw(7) << fixed << setprecision(2) << cart[i].item->price
                     << "|" << setw(4) << cart[i].qty
                     << "|" << setw(7) << itemTotal << "|" << endl;
        }
        
        double tax = total * 0.18;
        double grandTotal = total + tax;
        
        // Print to console
        cout << "===============================================\n";
        cout << "Subtotal: Rs. " << fixed << setprecision(2) << total << endl;
        cout << "Tax (18%): Rs. " << tax << endl;
        cout << "GRAND TOTAL: Rs. " << grandTotal << endl;
        cout << "===============================================\n";
        cout << "Thank you for shopping!\n";
        
        // Print to file
        billFile << "===============================================\n";
        billFile << "Subtotal: Rs. " << fixed << setprecision(2) << total << endl;
        billFile << "Tax (18%): Rs. " << tax << endl;
        billFile << "GRAND TOTAL: Rs. " << grandTotal << endl;
        billFile << "===============================================\n";
        billFile << "Thank you for shopping!\n";

        // Close the file
        billFile.close();
        
        cart.clear();
        billNo++;
    }
    
    void menu() {
        cout << "\n===============================================\n";
        cout << "         SUPERMARKET BILLING SYSTEM\n";
        cout << "===============================================\n";
        cout << "1. View Items\n2. Add to Cart\n3. View Cart\n4. Generate Bill\n5. Exit\n";
        cout << "===============================================\n";
    }
    
    void run() {
        int choice;
        while (true) {
            menu();
            cout << "Enter choice: ";
            cin >> choice;
            
            if (choice == 1) showItems();
            else if (choice == 2) { showItems(); addToCart(); }
            else if (choice == 3) showCart();
            else if (choice == 4) generateBill();
            else if (choice == 5) break;
            else cout << "Invalid choice!\n";
        }
    }
};

int main() {
    Billing shop;
    
    // Read last bill number from a separate file
    ifstream inFile("billnumber.txt");
    if (inFile.is_open()) {
        inFile >> shop.billNo;
        inFile.close();
    }
    
    cout << "Welcome to Supermarket!\n";
    shop.run();
    // Save last bill number to separate file
    ofstream outFile("billnumber.txt");
    if (outFile.is_open()) {
        outFile << shop.billNo << endl;
        outFile.close();
    }
    // Clean up memory
    for (int i = 0; i < shop.items.size(); i++) {
        delete shop.items[i];
    }
    
    return 0;
}
