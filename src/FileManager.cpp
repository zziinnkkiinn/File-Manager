#include "FileManager.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <sys/stat.h>

namespace fs = std::filesystem;
std::mutex mtx;

// Многопоточность для копирования
void copyChunk(std::ifstream& src, std::ofstream& dest, std::streampos start, std::streamsize size) {
    std::vector<char> buffer(size);
    
    {
        std::lock_guard<std::mutex> lock(mtx);
        src.seekg(start);
        src.read(buffer.data(), size);
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        dest.seekp(start);
        dest.write(buffer.data(), size);
    }
}

void copyFileMultithreaded(const std::string& source, const std::string& destination) {
    try {
        std::ifstream src(source, std::ios::binary);
        std::ofstream dest(destination, std::ios::binary);

        if (!src || !dest) {
            std::cerr << "Ошибка открытия файлов.\n";
            return;
        }

        src.seekg(0, std::ios::end);
        std::streamsize fileSize = src.tellg();
        src.seekg(0);

        const std::streamsize chunkSize = 1024 * 1024;  // 1 MB
        int threadCount = (fileSize + chunkSize - 1) / chunkSize;

        std::vector<std::thread> threads;

        for (int i = 0; i < threadCount; ++i) {
            std::streampos start = i * chunkSize;
            std::streamsize size = std::min(chunkSize, fileSize - start);

            threads.emplace_back(copyChunk, std::ref(src), std::ref(dest), start, size);
        }

        for (auto& t : threads) {
            t.join();
        }

        std::cout << "Файл успешно скопирован многопоточно: " << destination << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }
}

// Улучшенное архивирование (имитация с потоками)
void createArchive(const std::string& source, const std::string& archivePath) {
    try {
        std::ifstream src(source, std::ios::binary);
        std::ofstream dest(archivePath, std::ios::binary);

        if (!src || !dest) {
            std::cerr << "Ошибка открытия файлов.\n";
            return;
        }

        const size_t bufferSize = 1024 * 1024;  // 1 MB
        std::vector<char> buffer(bufferSize);

        while (src.read(buffer.data(), bufferSize) || src.gcount() > 0) {
            dest.write(buffer.data(), src.gcount());
        }

        std::cout << "Файл успешно заархивирован (имитация): " << archivePath << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Ошибка архивирования: " << e.what() << '\n';
    }
}

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
