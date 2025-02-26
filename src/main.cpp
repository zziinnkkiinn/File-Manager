#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

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

int main() {
    std::string path;
    std::cout << "Введите путь к директории: ";
    std::cin >> path;

    listFiles(path);

    return 0;
}
