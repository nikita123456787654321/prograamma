#include "headers.hpp"

using namespace std;

class WorkItem {
public:
    string name;
    double pricePerUnit;
    double totalArea;

    // Default constructor
    WorkItem() : name(""), pricePerUnit(0.0), totalArea(0.0) {}

    // Parameterized constructor
    WorkItem(const string& n, double price, double area)
        : name(n), pricePerUnit(price), totalArea(area) {}

    // Method to display detailed information about the work item
    void display() const {
        cout << "Name: " << name << "\n";
        cout << "Price per unit: " << pricePerUnit << "\n";
        cout << "Total area: " << totalArea << "\n";
        cout << "-------------------------------------\n";
    }
    string getName(){
        return name;
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