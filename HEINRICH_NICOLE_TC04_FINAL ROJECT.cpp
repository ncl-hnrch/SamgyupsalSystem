#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;


struct MenuItem {
    string name;
    double price;
};

struct OrderItem {
    string name;
    int quantity;
};

class Table {
private:
    vector<OrderItem> orders;

public:
    void viewMenu(const vector<MenuItem>& menu) const {
        cout << "\nMenu: \n";
        for (const auto& item : menu) {
            cout << item.name << " - $" << item.price << endl;
        }
    }

    void viewOrders() const {
        cout << "Current Orders: \n";
        for (const auto& item : orders) {
            cout << item.name << " x" << item.quantity << endl;
        }
    }

    void addOrder(const string& itemName, int quantity) {
        orders.push_back({ itemName, quantity });
        cout << "Added " << quantity << " " << itemName << " " << "to the order.\n";
    }

    double computeTotal(const vector<MenuItem>& menu) {
        double total = 0.0;
        for (const auto& item : orders) {
            auto menuItem = find_if(menu.begin(), menu.end(),
                [item](const MenuItem& menuitem) {
                    return menuitem.name == item.name;
                });

            if (menuItem != menu.end()) {
                total += item.quantity * menuItem->price;
            }
        }
        return total;
    }
    void clearTotals() {
        orders.clear();
        cout << "\nOrders cleared. \n";
    }
};

class Restaurant {
private:
    vector<MenuItem> menu;
    vector<Table> tables;

public:
    Restaurant(const vector<MenuItem>& initialMenu) : menu(initialMenu) {}

    void viewTables() const {
        cout << "\nReserved Tables: \n";
        for (size_t i = 0; i < tables.size(); ++i) {
            cout << "Table " << (i + 1) << endl;
        }
    }

    Table& reserveTable() {
        tables.emplace_back();
        return tables.back();
    }

    void viewMenu() const {
        for (const auto& item : menu) {
            cout << item.name << " . $" << item.price << endl;
        }
    }

    void addMenuItem(const string& name, double price) {
        menu.push_back({ name, price });
        cout << "\nAdded" << name << " to the menu.\n";
    }

    void viewOrderStatus() const {
        cout << "Order Status. \n";
        for (size_t i = 0; i < tables.size(); ++i) {
            cout << "\nTable " << (i + 1) << ":\n";
            tables[i].viewOrders();
        }
    }
};

int main() {
    vector<MenuItem> initialMenu = {
        {"\nSamgyupsal", 15.99},
        {"Bibimbap", 12.99},
        {"Kimchi Jjigae", 9.99},
        {"Bulgogi", 17.99}
    };

    Restaurant samgyupRestaurant(initialMenu);

    while (true) {
        cout << "\nSamgyup Restaurant Management System\n";
        cout << "1. View Tables\n";
        cout << "2. Reserve Table\n";
        cout << "3. View Menu\n";
        cout << "4. Add Menu Item\n";
        cout << "5. View Order Status\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            samgyupRestaurant.viewTables();
            break;
        }
        case 2: {
            Table& reservedTable = samgyupRestaurant.reserveTable();
            cout << "\nTable reserved. You can now place orders.\n";

            while (true) {
                cout << "\n1. View Menu\n";
                cout << "2. Add to Order\n";
                cout << "3. View Order\n";
                cout << "4. Compute Total\n";
                cout << "5. Clear Orders\n";
                cout << "6. Back to Main Menu\n";
                cout << "Enter your choice: ";

                int tableChoice;
                cin >> tableChoice;

                switch (tableChoice) {
                case 1: {
                    reservedTable.viewMenu(initialMenu);
                    break;
                }
                case 2: {
                    cout << "\nEnter the item name: ";
                    string itemName;
                    cin >> itemName;

                    cout << "Enter the quantity: ";
                    int quantity;
                    cin >> quantity;

                    reservedTable.addOrder(itemName, quantity);
                    break;
                }
                case 3: {
                    reservedTable.viewOrders();
                    break;
                }
                case 4: {
                    double total = reservedTable.computeTotal(initialMenu);
                    cout << "\nTotal Order: $" << total << endl;
                    break;
                }
                case 5: {
                    reservedTable.clearTotals();
                    break;
                }
                case 6: {
                    break;
                }
                default: {
                    cout << "\nInvalid choice. Please try again.\n";
                    break;
                }
                }

                if (tableChoice == 6) {
                    break;
                }
            }

            break;
        }
        case 3: {
            samgyupRestaurant.viewMenu();
            break;
        }
        case 4: {
            cout << "\nEnter the new menu item name: ";
            string itemName;
            cin >> itemName;

            cout << "Enter the price: ";
            double price;
            cin >> price;

            samgyupRestaurant.addMenuItem(itemName, price);
            break;
        }
        case 5: {
            samgyupRestaurant.viewOrderStatus();
            break;
        }
        case 6: {
            cout << "\nExiting Samgyup Restaurant Management System. Goodbye!\n";
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    }

    return 0;
}