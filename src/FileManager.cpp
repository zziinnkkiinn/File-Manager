#include "FileManager.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// Просмотр файлов
void listFiles(const std::string& path) {
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ")
                      << entry.path().filename() << '\n';
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }
}

// Копирование файла
void copyFile(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "Файл успешно скопирован в " << destination << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка копирования: " << e.what() << '\n';
    }
}

// Поиск файла
void searchFile(const std::string& path, const std::string& filename) {
    try {
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            if (entry.path().filename() == filename) {
                std::cout << "Найден: " << entry.path() << '\n';
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка поиска: " << e.what() << '\n';
    }
}
