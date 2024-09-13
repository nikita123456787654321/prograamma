#include <iostream>
using namespace std;


void roomCalculations(double length, double width, double height, 
                      double &S_floor, double &P, double &S_walls) {
    
    S_floor = length * width;

    
    P = 2 * (length + width);


    S_walls = 2 * (length * height + width * height);
}

int main() {

    double length, width, height;

   
    cout << "Vvedite dlinu komnaty (v metrak): ";
    cin >> length;
    cout << "Vvedite shirinu komnaty (v metrak): ";
    cin >> width;
    cout << "Vvedite vysotu komnaty (v metrak): ";
    cin >> height;

    
    double S_floor, P, S_walls;


    roomCalculations(length, width, height, S_floor, P, S_walls);


    int num_doors;
    cout << "Vvedite kolichestvo dverey: ";
    cin >> num_doors;

    double total_door_area = 0;
    double total_door_width = 0; 
    for (int i = 0; i < num_doors; ++i) {
        double door_width, door_height;
        cout << "Vvedite shirinu dveri " << i + 1 << " (v metrak): ";
        cin >> door_width;
        cout << "Vvedite vysotu dveri " << i + 1 << " (v metrak): ";
        cin >> door_height;
        total_door_area += door_width * door_height;
        total_door_width += door_width; 
    }

    
    int num_windows;
    cout << "Vvedite kolichestvo okon: ";
    cin >> num_windows;

    double total_window_area = 0;
    for (int i = 0; i < num_windows; ++i) {
        double window_width, window_height;
        cout << "Vvedite shirinu okna " << i + 1 << " (v metrak): ";
        cin >> window_width;
        cout << "Vvedite vysotu okna " << i + 1 << " (v metrak): ";
        cin >> window_height;
        total_window_area += window_width * window_height;
    }

 
    double S_walls_net = S_walls - total_door_area - total_window_area;

    
    double P_net = P - total_door_width;

 
    cout << "Ploshchad' pola komnaty: " << S_floor << " kv.m." << endl;
    cout << "Perimetr komnaty: " << P << " m." << endl;
    cout << "Perimetr bez ucheta dvernukh proyemov: " << P_net << " m." << endl;
    cout << "Obshchaya ploshchad' sten komnaty: " << S_walls << " kv.m." << endl;
    cout << "Obshchaya ploshchad' dverey: " << total_door_area << " kv.m." << endl;
    cout << "Obshchaya ploshchad' okon: " << total_window_area << " kv.m." << endl;
    cout << "Ploshchad' sten bez ucheta dverey i okon: " << S_walls_net << " kv.m." << endl;

    return 0;
}
