#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream file("data_ListSmeta.csv");
    std::string line, cell;

    // Двумерный вектор для хранения отфильтрованных данных
    std::vector<std::vector<std::string>> filtered_data;

    // Чтение строки за строкой
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream lineStream(line);

        // Чтение ячеек строки, разделенных запятой
        while (std::getline(lineStream, cell, ',')) {
            // Проверка, что длина строки больше 3 символов
            if (cell.length() > 3) {
                row.push_back(cell);
            }
        }

        // Если в строке есть отфильтрованные ячейки, добавляем строку в результат
        if (!row.empty()) {
            filtered_data.push_back(row);
        }
    }

    // Вывод отфильтрованных данных из массива
    std::cout << "Filtered data:\n";
    for (const auto& row : filtered_data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
