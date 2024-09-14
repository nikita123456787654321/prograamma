#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> // For std::replace and std::transform
#include <conio.h> 
#include <windows.h>  // For _kbhit and _getch

using namespace std;

// Class to represent a work item


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

// Function to replace commas with dots
string replaceCommaWithDot(const string& str) {
    string result = str;
    replace(result.begin(), result.end(), ',', '.');
    return result;
}

// Function to convert a string to lowercase (for case-insensitive search)
string toLowerCase(const string& str) {
    string lower_str = str;
    transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

// Function to convert a string to a double using stringstream
bool stringToDouble(const string& str, double& value) {
    if (str.empty()) {
        return false; // Empty strings are not valid numbers
    }
    stringstream ss(replaceCommaWithDot(str));
    ss >> value;
    
    // Check if the conversion succeeded and also if there are extra characters
    if (ss.fail() || !ss.eof()) {
        return false;
    }
    
    // Handle cases where there are no decimal points in the number
    if (str.find('.') == string::npos && str.find(',') == string::npos) {
        // If no decimal point is present, ensure that it's represented as double with zero decimal places
        value = static_cast<double>(static_cast<int>(value));
    }

    return true;
}

// Function to search for the most relevant work items
vector<WorkItem> searchInColumn(const vector<WorkItem>& workItems, const string& searchTerm) {
    vector<WorkItem> results;

    // Convert search term to lowercase for case-insensitive search
    string lowerSearchTerm = toLowerCase(searchTerm);

    // Search for work items that contain the search term in their name
    for (const WorkItem& item : workItems) {
        if (toLowerCase(item.name).find(lowerSearchTerm) != string::npos) {
            results.push_back(item);
        }
    }

    // Limit results to 5 elements
    if (results.size() > 5) {
        results.resize(5);
    }

    return results;
}

int main() {
    ifstream file("../data_ListSmeta.csv");
    string line;

    vector<WorkItem> workItems;
    string searchTerm;
    ShoppingCart cart; // Create a ShoppingCart object

    while (getline(file, line)) {
        stringstream lineStream(line);
        vector<string> row_data;
        string cell;

        while (getline(lineStream, cell, ';')) {
            row_data.push_back(cell);
        }

        if (row_data.size() > 3) {
            string name = row_data[0];
            double pricePerUnit;
            double totalArea;

            if (stringToDouble(row_data[2], pricePerUnit) && stringToDouble(row_data[3], totalArea)) {
                workItems.emplace_back(name, pricePerUnit, totalArea);
            } else {
                cerr << "Invalid number format in row: " << line << endl;
                cerr << "Column C: " << row_data[2] << ", Column D: " << row_data[3] << endl;
            }
        }
    }

    int selectedIndex = 0;
    bool isSearching = true;

    while (isSearching) {
        cout << "Enter text to search (press '0' to exit):\n";
        while (true) {
            if (_kbhit()) {
                char input = _getch();
                vector<WorkItem> searchResults = searchInColumn(workItems, searchTerm);

                if (input == '0') {
                    return 0;
                }

                if (input == '\r') {
                    if (selectedIndex >= 0 && selectedIndex < searchResults.size()) {
                        cart.addItem(searchResults[selectedIndex]);
                        cout << "\nItem added to cart:\n";
                        searchResults[selectedIndex].display();
                    }
                    break;
                }

                if (input == 27) { // Escape key to exit search
                    isSearching = false;
                    break;
                }

                if (input == 224) { // Arrow keys
                    input = _getch();
                    if (input == 72) { // Up arrow
                        if (selectedIndex > 0) {
                            selectedIndex--;
                        }
                    } else if (input == 80) { // Down arrow
                        if (selectedIndex < searchResults.size() - 1) {
                            selectedIndex++;
                        }
                    }
                } else {
                    if (input == '\b' || input == 8) {
                        if (!searchTerm.empty()) {
                            searchTerm.pop_back();
                        }
                    } else {
                        searchTerm += input;
                    }
                }

                system("CLS");

                cout << "Search query: " << searchTerm << "\n";
                cout << "Search results (up to 5):\n";
                for (size_t i = 0; i < searchResults.size(); ++i) {
                    if (i == selectedIndex) {
                        cout << ">> ";
                    }
                    searchResults[i].display();
                }
            }
        }

        system("CLS");
        cout << "Cart contents:\n";
        cart.display();
        cout << "Press '0' to exit.\n";
        while (true) {
            if (_kbhit()) {
                if (_getch() == '0') {
                    return 0;
                }
            }
        }
    }

    return 0;
}
