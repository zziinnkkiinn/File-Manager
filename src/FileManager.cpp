#include "FileManager.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>

namespace fs = std::filesystem;

// Удаление файла
void deleteFile(const std::string& path) {
    try {
        if (fs::remove(path)) {
            std::cout << "Файл успешно удален: " << path << '\n';
        } else {
            std::cout << "Файл не найден: " << path << '\n';
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка удаления: " << e.what() << '\n';
    }
}

// Изменение прав доступа
void changeFilePermissions(const std::string& path, const std::string& permissions) {
    try {
        mode_t mode = 0;

        for (char c : permissions) {
            mode <<= 3;
            mode |= (c - '0');
        }

        if (chmod(path.c_str(), mode) == 0) {
            std::cout << "Права успешно изменены на " << permissions << '\n';
        } else {
            perror("Ошибка изменения прав");
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }
}

// Простое создание архива (ZIP)
void createArchive(const std::string& source, const std::string& archivePath) {
    try {
        std::ifstream src(source, std::ios::binary);
        std::ofstream dest(archivePath, std::ios::binary);

        if (!src || !dest) {
            std::cerr << "Ошибка открытия файла.\n";
            return;
        }

        dest << src.rdbuf();
        std::cout << "Архив создан: " << archivePath << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Ошибка архивирования: " << e.what() << '\n';
    }
}
