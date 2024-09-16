#include "wpClasses.hpp"
using namespace std;

string replaceCommaWithDot(const string& str);
string toLowerCase(const string& str);
vector<WorkItem> searchInColumn(const vector<WorkItem>& workItems, const string& searchTerm);
vector<WorkItem> loadWorkItems(const string& filename);
bool stringToDouble(const string& str, double& value);
void handleUserInput(vector<WorkItem>& workItems, ShoppingCart& cart);
void search();