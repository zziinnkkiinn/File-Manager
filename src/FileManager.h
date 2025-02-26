#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

void listFiles(const std::string& path);
void copyFile(const std::string& source, const std::string& destination);
void copyFileMultithreaded(const std::string& source, const std::string& destination);
void searchFile(const std::string& path, const std::string& filename);
void deleteFile(const std::string& path);
void changeFilePermissions(const std::string& path, const std::string& permissions);
void createArchive(const std::string& source, const std::string& archivePath);

#endif
