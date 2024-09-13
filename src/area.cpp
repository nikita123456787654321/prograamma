#include <iostream>
#include <cstdlib> // Для функции system()
using namespace std;

// Функция для расчета площади пола
double calculateFloorArea(double length, double width) {
    return length * width;
}

// Функция для расчета периметра комнаты
double calculatePerimeter(double length, double width) {
    return 2 * (length + width);
}

// Функция для расчета площади стен
double calculateWallArea(double length, double width, double height) {
    return 2 * (length * height + width * height);
}

// Функция для ввода размеров дверей
double getTotalDoorArea(int num_doors, double &total_door_width) {
    double total_door_area = 0;
    for (int i = 0; i < num_doors; ++i) {
        double door_width, door_height;
        cout << "Vvedite shirinu dveri " << i + 1 << " (v metrak): ";
        cin >> door_width;
        cout << "Vvedite vysotu dveri " << i + 1 << " (v metrak): ";
        cin >> door_height;
        total_door_area += door_width * door_height;
        total_door_width += door_width;
    }
    return total_door_area;
}

// Функция для ввода размеров окон
double getTotalWindowArea(int num_windows) {
    double total_window_area = 0;
    for (int i = 0; i < num_windows; ++i) {
        double window_width, window_height;
        cout << "Vvedite shirinu okna " << i + 1 << " (v metrak): ";
        cin >> window_width;
        cout << "Vvedite vysotu okna " << i + 1 << " (v metrak): ";
        cin >> window_height;
        total_window_area += window_width * window_height;
    }
    return total_window_area;
}

// Функция для ввода основных данных о комнате
void inputRoomDimensions(double &length, double &width, double &height, int &num_doors, int &num_windows) {
    cout << "Vvedite dlinu komnaty (v metrak): ";
    cin >> length;
    cout << "Vvedite shirinu komnaty (v metrak): ";
    cin >> width;
    cout << "Vvedite vysotu komnaty (v metrak): ";
    cin >> height;
    cout << "Vvedite kolichestvo dverey: ";
    cin >> num_doors;
    cout << "Vvedite kolichestvo okon: ";
    cin >> num_windows;
}

// Функция для очистки консоли
void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Основная программа
int main() {
    // Переменные для размеров комнаты
    double length, width, height;
    int num_doors, num_windows;

    // Ввод данных о комнате
    inputRoomDimensions(length, width, height, num_doors, num_windows);

    // Расчет площади пола, периметра и площади стен
    double S_floor = calculateFloorArea(length, width);
    double P = calculatePerimeter(length, width);
    double S_walls = calculateWallArea(length, width, height);

    // Переменные для дверей и окон
    double total_door_width = 0;
    double total_door_area = getTotalDoorArea(num_doors, total_door_width);
    double total_window_area = getTotalWindowArea(num_windows);

    // Очищаем консоль перед выводом результатов
    clearConsole();

    // Площадь стен без учета окон и дверей
    double S_walls_net = S_walls - total_door_area - total_window_area;

    // Периметр без учета ширины дверей
    double P_net = P - total_door_width;

    // Вывод результатов
    cout << "Rezultaty raschetov:" << endl;
    cout << "Ploshchad' pola komnaty: " << S_floor << " kv.m." << endl;
    cout << "Perimetr komnaty: " << P << " m." << endl;
    cout << "Perimetr bez ucheta dvernukh proyemov: " << P_net << " m." << endl;
    cout << "Obshchaya ploshchad' sten komnaty: " << S_walls << " kv.m." << endl;
    cout << "Obshchaya ploshchad' dverey: " << total_door_area << " kv.m." << endl;
    cout << "Obshchaya ploshchad' okon: " << total_window_area << " kv.m." << endl;
    cout << "Ploshchad' sten bez ucheta dverey i okon: " << S_walls_net << " kv.m." << endl;

    return 0;
}