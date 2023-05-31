#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0) {
        std::cerr << "Errore durante l'inizializzazione di Winsock: " << result << std::endl;
        return 1;
    }

    char hostname[256];
    result = gethostname(hostname, sizeof(hostname));
    if (result != 0) {
        std::cerr << "Errore durante la risoluzione del nome host: " << result << std::endl;
        WSACleanup();
        return 1;
    }

    std::cout << "Nome host: " << hostname << std::endl;

    struct addrinfo *resultList = nullptr;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    result = getaddrinfo(hostname, nullptr, &hints, &resultList);
    if (result != 0) {
        std::cerr << "Errore durante la risoluzione degli indirizzi: " << result << std::endl;
        WSACleanup();
        return 1;
    }

    for (auto ptr = resultList; ptr != nullptr; ptr = ptr->ai_next) {
        char ipAddr[INET_ADDRSTRLEN];
        void* addr = &((struct sockaddr_in*)ptr->ai_addr)->sin_addr;
        inet_ntop(AF_INET, addr, ipAddr, INET_ADDRSTRLEN);
        std::cout << "Indirizzo IP: " << ipAddr << std::endl;
    }

    freeaddrinfo(resultList);
    WSACleanup();

    return 0;
}
