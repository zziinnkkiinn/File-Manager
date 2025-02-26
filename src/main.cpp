#include <iostream>
#include "FileManager.h"

int main() {
    int choice;
    std::string path, source, destination, filename;

    while (true) {
        std::cout << "\n===== Меню =====\n"
                  << "1. Просмотр файлов\n"
                  << "2. Копирование файла\n"
                  << "3. Поиск файла\n"
                  << "4. Выход\n"
                  << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите путь к папке: ";
                std::cin >> path;
                listFiles(path);
                break;

            case 2:
                std::cout << "Введите путь к исходному файлу: ";
                std::cin >> source;
                std::cout << "Введите путь назначения: ";
                std::cin >> destination;
                copyFile(source, destination);
                break;

            case 3:
                std::cout << "Введите путь для поиска: ";
                std::cin >> path;
                std::cout << "Введите имя файла: ";
                std::cin >> filename;
                searchFile(path, filename);
                break;

            case 4:
                std::cout << "Выход...\n";
                return 0;

            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}
