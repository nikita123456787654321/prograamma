#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream file("../data_ListSmeta.csv");
    string line, cell;

    // Векторы для хранения данных
    vector<string> columnA_data;     // Столбец A (основной текст)
    vector<string> columnB_data;     // Столбец B (единицы измерения)
    vector<string> work_type_data;   // Тип выполняемых работ

    int current_row = 0; // Номер текущей строки

    // Чтение строки за строкой
    while (getline(file, line)) {
        current_row++; // Увеличиваем счетчик строк

        // Обрабатываем строки с 17 по 304
        if (current_row >= 16 && current_row <= 306) {
            stringstream lineStream(line);
            vector<string> row_data; // Для хранения данных текущей строки

            // Разделение строки по символу ';'
            while (getline(lineStream, cell, ';')) {
                row_data.push_back(cell);
            }

            // Проверка, что строка содержит как минимум 2 столбца
            if (row_data.size() >= 2) {
                // Обрабатываем строки с типом выполняемых работ
                if (current_row == 16 || current_row == 96 || current_row == 205 || current_row == 249 || current_row == 273 || current_row == 295) {
                    work_type_data.push_back(row_data[0]); // Сохраняем тип работ (столбец A)
                } else {
                    // Столбец A (индекс 0) — основной текст (длина больше 3 символов)
                    if (row_data[0].length() > 3) {
                        columnA_data.push_back(row_data[0]);
                        
                        // Столбец B (индекс 1) — единицы измерения (текст <= 5 символов)
                        if (row_data[1].length() <= 5) {
                            columnB_data.push_back(row_data[1]);
                        } else {
                            columnB_data.push_back(""); // Если в столбце B данных нет, добавляем пустую строку
                        }
                    }
                }
            }
        }
    }

    // Вывод данных из столбцов A и B
    cout << "Data from columns A and B:\n";
    for (size_t i = 0; i < columnA_data.size(); ++i) {
        cout << columnA_data[i] << "\t" << columnB_data[i] << endl;
    }

    // Вывод данных с типом выполняемых работ
    cout << "\nWork type data (rows 17, 97, 206, 250, 274, 296):\n";
    for (const auto &work_type : work_type_data) {
        cout << work_type << endl;
    }

    return 0;
}
