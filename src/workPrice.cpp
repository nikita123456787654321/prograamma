#include "headers.hpp"
#include "wpClasses.hpp"
//
using namespace std;

// Forward declaration of classes
class WorkItem;
class ShoppingCart;

// Function to replace commas with dots
string replaceCommaWithDot(const string &str)
{
    string result = str;
    replace(result.begin(), result.end(), ',', '.');
    return result;
}

// Function to convert a string to lowercase (for case-insensitive search)
string toLowerCase(const string &str)
{
    string lower_str = str;
    transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

// Function to convert a string to a double using stringstream
bool stringToDouble(const string &str, double &value)
{
    if (str.empty())
    {
        return false; // Empty strings are not valid numbers
    }
    stringstream ss(replaceCommaWithDot(str));
    ss >> value;

    // Check if the conversion succeeded and also if there are extra characters
    if (ss.fail() || !ss.eof())
    {
        return false;
    }

    return true;
}

// Function to search for the most relevant work items
vector<WorkItem> searchInColumn(const vector<WorkItem> &workItems, const string &searchTerm)
{
    vector<WorkItem> results;

    // Convert search term to lowercase for case-insensitive search
    string lowerSearchTerm = toLowerCase(searchTerm);

    // Search for work items that contain the search term in their name
    for (const WorkItem &item : workItems)
    {
        if (toLowerCase(item.name).find(lowerSearchTerm) != string::npos)
        {
            results.push_back(item);
        }
    }

    // Limit results to 5 elements
    if (results.size() > 5)
    {
        results.resize(5);
    }

    return results;
}

// Function to load work items from file
// Function to load work items from file
vector<WorkItem> loadWorkItems(const string &filename) {
    ifstream file(filename);
    string line;
    vector<WorkItem> workItems;

    while (getline(file, line)) {
        stringstream lineStream(line);
        vector<string> row_data;
        string cell;

        while (getline(lineStream, cell, ';')) {
            row_data.push_back(cell);
        }

        if (row_data.size() > 0) {
            string name = row_data[0];
            double pricePerUnit = 0.0;
            double totalArea = 0.0;

            // Only try to convert if there are enough columns for numeric values
            if (row_data.size() > 3) {
                bool validPrice = stringToDouble(row_data[2], pricePerUnit);
                bool validArea = stringToDouble(row_data[3], totalArea);

                if (!validPrice || !validArea) {
                    cerr << "Invalid number format in row: " << line << endl;
                    cerr << "Column C: " << row_data[2] << ", Column D: " << row_data[3] << endl;
                }
            }

            // Always create a WorkItem, even if numbers are invalid
            workItems.emplace_back(name, pricePerUnit, totalArea);
        }
    }

    return workItems;
}


// Function to handle user input and search interactions
void handleUserInput(vector<WorkItem> &workItems, ShoppingCart &cart)
{
    string searchTerm;
    int selectedIndex = 0;
    bool isSearching = true;

    while (isSearching)
    {
        cout << "Enter text to search (press '0' to exit):\n";
        while (true)
        {
            if (_kbhit())
            {
                char input = _getch();
                vector<WorkItem> searchResults = searchInColumn(workItems, searchTerm);

                if (input == '0')
                {
                    break;
                }

                if (input == '\r')
                {
                    if (selectedIndex >= 0 && selectedIndex < searchResults.size())
                    {
                        cart.addItem(searchResults[selectedIndex]);
                        cout << "\nItem added to cart:\n";
                        searchResults[selectedIndex].display();
                    }
                    break;
                }

                if (input == 27)
                { // Escape key to exit search
                    isSearching = false;
                    break;
                }

                if (input == 224)
                { // Arrow keys
                    input = _getch();
                    if (input == 72)
                    { // Up arrow
                        if (selectedIndex > 0)
                        {
                            selectedIndex--;
                        }
                    }
                    else if (input == 80)
                    { // Down arrow
                        if (selectedIndex < searchResults.size() - 1)
                        {
                            selectedIndex++;
                        }
                    }
                }
                else
                {
                    if (input == '\b' || input == 8)
                    {
                        if (!searchTerm.empty())
                        {
                            searchTerm.pop_back();
                        }
                    }
                    else
                    {
                        searchTerm += input;
                    }
                }

                system("CLS");

                cout << "Search query: " << searchTerm << "\n";
                cout << "Search results (up to 5):\n";
                for (size_t i = 0; i < searchResults.size(); ++i)
                {
                    if (i == selectedIndex)
                    {
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
        while (true)
        {
            if (_kbhit())
            {
                if (_getch() == '0')
                {
                    break;
                }
            }
        }
    }
}

// Function to display the name of all work items
void displayWorkItemNames(const vector<WorkItem> &workItems)
{
    for (const WorkItem &item : workItems)
    {
        cout << item.name << endl; // Assuming WorkItem has a public member 'name'
    }
}

// Main function
void search()
{
    vector<WorkItem> workItems = loadWorkItems("../data_ListSmeta.csv");
    ShoppingCart cart; // Create a ShoppingCart object
    displayWorkItemNames(workItems);
    // handleUserInput(workItems, cart);
}
