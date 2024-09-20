using namespace std;

void test();
void clearConsole();
void inputRoomDimensions(double &length, double &width, double &height, int &num_doors, int &num_windows);
double getTotalWindowArea(int num_windows);
double getTotalDoorArea(int num_doors);
double calculateWallArea(double length, double width, double height);
double calculatePerimeter(double length, double width);
double calculateFloorArea(double length, double width);