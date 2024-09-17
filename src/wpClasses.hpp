#include "headers.hpp"

using namespace std;

class WorkItem {
public:
    string name;
    string unit; // New field for the second column
    double pricePerUnit;
    double totalArea; // Optional, depending on your needs

    // Default constructor
    WorkItem() : name(""), unit(""), pricePerUnit(0.0), totalArea(0.0) {}

    // Parameterized constructor
    WorkItem(const string& n, const string& u, double price)
        : name(n), unit(u), pricePerUnit(price), totalArea(0.0) {}

    // Method to display detailed information about the work item
    void display() const {
        cout << "Name: " << name << "\n";
        cout << "Unit: " << unit << "\n"; // Display unit as well
        cout << "Price per unit: " << pricePerUnit << "\n";
        cout << "-------------------------------------\n";
    }
};


class ShoppingCart {
public:
    // Add an item to the cart
    void addItem(const WorkItem& item) {
        items.push_back(item);
    }

    // Display the contents of the cart
    void display() const {
        if (items.empty()) {
            cout << "The cart is empty.\n";
        } else {
            cout << "Items in the cart:\n";
            for (const auto& item : items) {
                item.display();
            }
        }
    }

private:
    vector<WorkItem> items;
};