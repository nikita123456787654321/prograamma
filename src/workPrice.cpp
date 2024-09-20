#include "headers.hpp"
#include "wpClasses.hpp"
#include "area.hpp"
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

string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
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

    // Handle cases where there are no decimal points in the number
    if (str.find('.') == string::npos && str.find(',') == string::npos)
    {
        // If no decimal point is present, ensure that it's represented as double with zero decimal places
        value = static_cast<double>(static_cast<int>(value));
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
vector<WorkItem> loadWorkItems(const string &filename)
{
    ifstream file(filename); // Открываем файл
    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return {}; // Возвращаем пустой вектор, если файл не удалось открыть
    }

    string line;
    vector<WorkItem> workItems;

    // Чтение файла построчно
    while (getline(file, line)) // Читаем строки из файла, а не из filename
    {
        stringstream lineStream(line);
        vector<string> row_data;
        string cell;

        // Разделяем строку на ячейки по разделителю ';'
        while (getline(lineStream, cell, ';'))
        {
            row_data.push_back(cell);
        }

        // Проверяем, что есть как минимум 3 столбца
        if (row_data.size() >= 3)
        {
            string name = row_data[0];
            string unit = trim(row_data[1]); // Первый столбец — это name
            double pricePerUnit = 0.0;

            // Преобразуем третий столбец в double для pricePerUnit
            if (stringToDouble(row_data[2], pricePerUnit))
            {
                workItems.emplace_back(name, unit, pricePerUnit, 0); // Добавляем WorkItem с name и price
            }
            else
            {
                cerr << "Invalid price format in row: " << line << endl;
            }
        }
        else
        {
            cerr << "Invalid row format (not enough columns): " << line << endl;
        }
    }

    return workItems; // Возвращаем вектор WorkItem'ов
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
        cout << item.name << "   " << item.unit << "\t" << item.pricePerUnit << endl; // Assuming WorkItem has a public member 'name'
    }
}
void calc(vector<WorkItem> &items)
{
    double leng, wed;
    int countDoors;
    double DoorsWidth;
    double totalArea;

    // Ввод параметров
    cout << "Введите длину и ширину: ";
    cin >> leng >> wed;
    cout << "Введите количество дверей и ширину дверей: ";
    cin >> countDoors;

    // Расчет общей площади и периметра
    totalArea = calculateFloorArea(leng, wed);

    double metrsPogon = calculatePerimeter(leng, wed) - getTotalDoorArea(countDoors);
    int count = 0;
    string metr = "м2";

    // Проходим по всем элементам вектора items
    for (WorkItem &item : items)
    {
        if (int(item.unit[0]) == -84 && int(item.unit[1]) == 50)
        {
            // Если unit равен "м2", присваиваем totalArea
            item.totalArea = totalArea;
            count++;
        }
        else if (int(item.unit[0]) == -84 && int(item.unit[1]) == 46 && int(item.unit[2]) == -81 && int(item.unit[3]) == 46)
        {
            // Если unit равен "м.п.", присваиваем метры погонные (периметр минус двери)
            item.totalArea = metrsPogon;
            count++;
        }
        else if (int(item.unit[0]) == -24 && int(item.unit[1]) == -30 && int(item.unit[2]) == 46)
        {
            // Если unit равен "шт.", спрашиваем количество штук у пользователя
            int quantity;
            cout << "Введите количество для " << item.name << ": ";
            cin >> quantity;
            item.totalArea = static_cast<double>(quantity); // Сохраняем количество штук как площадь
            count++;
        }
    }

    // for (const auto &item : items)
    // {
    //     cout << "Unit: " << item.unit << " (ASCII codes: ";
    //     for (char c : item.unit)
    //     {
    //         cout << static_cast<int>(c) << " ";
    //     }
    //     cout << ")" << endl;
    // }

    for (auto &item : items)
    {
        item.totalPrice = item.pricePerUnit * item.totalArea;
    }

    // Вывод обновленных объектов WorkItem с новыми значениями
    cout << "\nОбновленные объекты WorkItem:\n";
    for (const WorkItem &item : items)
    {
        cout << "Name: " << item.name << endl;
        cout << "Unit: " << item.unit << endl;
        cout << "Price per Unit: " << item.pricePerUnit << endl;
        cout << "Total Area/Count: " << item.totalArea << endl;
        cout << "Total Price: " << item.totalPrice << endl;
        cout << "--------------------------\n";
    }
    cout << count;
    
}

// Main function
void search()
{
    vector<WorkItem> workItems = loadWorkItems("../walls.csv");
    const char mas[4] = "м2";
    ShoppingCart cart; // Create a ShoppingCart object
    displayWorkItemNames(workItems);
    // cout << endl;
    // calc(workItems);
    // cout << endl;
    // handleUserInput(workItems, cart);
}
