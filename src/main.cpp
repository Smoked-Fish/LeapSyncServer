// LeapSync - Copyright (c) 2023 Jacob Espy. See LICENSE.txt for more details. 

#include "decode.h"
#include "gamepad.h"

#include <vector>
#include <string>
#include <thread>
#include <utility>
#include <cstdint>
#include <iostream>
#include <WS2tcpip.h>
#include <winsock2.h>

// #pragma comment(lib, "ws2_32.lib")

#define PORT 9001

/// Client handler function that processes incoming data from a client
void clientHandler(SOCKET clientSocket) {
    const size_t bufferSize = 1024;
    std::vector<uint8_t> recvBuffer(bufferSize);
    int recvSize;

    // Keep receiving data from the client until there's no more data
    while ((recvSize = recv(clientSocket, reinterpret_cast<char*>(recvBuffer.data()), recvBuffer.size(), 0)) > 0) {
        std::vector<uint8_t> slipData(recvBuffer.begin(), recvBuffer.begin() + recvSize);
        std::vector<std::pair<std::string, int>> result = processData(slipData);

        for (const auto& pair : result) {
            switch (pair.second) {
                case 0:
                case 1:
                    buttonHandler(pair.first, pair.second);
                    break;
                case 2:
                case 3:
                    joystickHandler(pair.first, pair.second);
                    break;
                case 4:
                    touchpadHandler(pair.first);
                    break;
                case 5:
                case 6:
                    motionHandler(pair.first, pair.second);
                    break;
                default:
                    // Handle unknown action code
                    std::cout << "Invalid data received, action code not recognized" << std::endl;
                    break;
            }
        }
    }

    closesocket(clientSocket);
    exit(0);
}

int main() {
    gamepadSession();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed. Error: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Create a new socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed. Error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the server address and listen
    if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << ntohs(serverAddr.sin_port) << std::endl;

    // Accept incoming client connections
    while (1) {
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);

        SOCKET clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed. Error: " << WSAGetLastError() << std::endl;
            continue;
        }
        std::cout << "Client connected from IP: " << inet_ntoa(clientAddr.sin_addr)
                  << ", Port: " << ntohs(clientAddr.sin_port) << std::endl;

        std::thread clientThread(clientHandler, clientSocket);
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
