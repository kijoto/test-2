#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstdlib>

// Funzione per ottenere la data corrente
std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    return std::string(buffer);
}

int main() {
    std::string consent;
    std::cout << "Do you consent to collect information about your device? (y/n): ";
    std::cin >> consent;

    if (consent != "y") {
        std::cout << "Consent not given. Exiting program." << std::endl;
        return 0;
    }

    std::ofstream outputFile("device_info.txt");

    // Scrivi le informazioni sul dispositivo nel file di testo
    outputFile << "Device Information - " << getCurrentDate() << std::endl;
    outputFile << "---------------------------------------" << std::endl;

    #ifdef _WIN32
        outputFile << "Operating System: Windows" << std::endl;
    #elif __APPLE__
        outputFile << "Operating System: macOS" << std::endl;
    #elif __linux__
        outputFile << "Operating System: Linux" << std::endl;
    #else
        outputFile << "Operating System: Unknown" << std::endl;
    #endif

    #ifdef __cplusplus
        outputFile << "Compiler: C++" << std::endl;
    #else
        outputFile << "Compiler: Unknown" << std::endl;
    #endif

    outputFile << "Hostname: " << std::getenv("COMPUTERNAME") << std::endl;
    outputFile << "Username: " << std::getenv("USERNAME") << std::endl;

    // Chiudi il file di testo
    outputFile.close();
    std::cout << "Device information collected and saved in device_info.txt" << std::endl;

    return 0;
}
