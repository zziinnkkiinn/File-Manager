#include <iostream>
#include "FileManager.h"

int main() {
    int choice;
    std::string path, source, destination, filename, permissions;

    while (true) {
        std::cout << "\n===== Меню =====\n"
                  << "1. Просмотр файлов\n"
                  << "2. Копирование файла\n"
                  << "3. Поиск файла\n"
                  << "4. Удаление файла\n"
                  << "5. Изменение прав доступа\n"
                  << "6. Создание архива\n"
                  << "7. Выход\n"
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
                std::cout << "Введите путь к файлу для удаления: ";
                std::cin >> path;
                deleteFile(path);
                break;

            case 5:
                std::cout << "Введите путь к файлу: ";
                std::cin >> path;
                std::cout << "Введите права доступа (например, 755): ";
                std::cin >> permissions;
                changeFilePermissions(path, permissions);
                break;

            case 6:
                std::cout << "Введите путь к файлу для архивации: ";
                std::cin >> source;
                std::cout << "Введите путь к архиву (например, archive.zip): ";
                std::cin >> destination;
                createArchive(source, destination);
                break;

            case 7:
                std::cout << "Выход...\n";
                return 0;

            case 8:
                std::cout << "Введите путь к исходному файлу для многопоточного копирования: ";
                std::cin >> source;
                std::cout << "Введите путь назначения: ";
                std::cin >> destination;
                copyFileMultithreaded(source, destination);
                break;
            

            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}
