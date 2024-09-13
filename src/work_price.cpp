#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream file("data_ListSmeta.csv");
    string line, cell;

    // Вектор для хранения отфильтрованных данных (строки с текстом > 10 символов)
    vector<string> filtered_data;
    
    // Вектор для хранения строк, которые отвечают за тип выполняемых работ
    vector<string> work_type_data;
    
    int current_row = 0; // Номер текущей строки

    // Чтение строки за строкой
    while (getline(file, line)) {
        current_row++; // Увеличиваем счетчик строк

        // Обрабатываем только строки с 17 по 304
        if (current_row >= 17 && current_row <= 304) {
            stringstream lineStream(line);

            // Чтение только первой ячейки (столбец A)
            if (getline(lineStream, cell, ';')) {
                // Проверка, что это строки с типом выполняемых работ
                if (current_row == 17 || current_row == 97 || current_row == 206 || current_row == 250 || current_row == 274 || current_row == 296) {
                    work_type_data.push_back(cell); // Сохраняем как тип работ
                } else {
                    // Проверка, что длина текста больше 10 символов
                    if (cell.length() > 3) {
                        filtered_data.push_back(cell); // Сохраняем если текст подходит
                    }
                }
            }
        }
    }

    // Вывод отфильтрованных данных
    cout << "Filtered data from column A (rows 18 to 304, with more than 10 characters):\n";
    for (const auto& cell : filtered_data) {
        cout << cell << endl;
    }

    cout << "\nWork type data (rows 17, 97, 206, 250, 274, 296):\n";
    for (const auto& work_type : work_type_data) {
        cout << work_type << endl;
    }

    return 0;
}
