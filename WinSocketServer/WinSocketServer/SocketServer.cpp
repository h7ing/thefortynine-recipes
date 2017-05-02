/////////////////////////////////////////////////////////////////////////////////////
// copy from MSDN: Complete Winsock Server Code
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms737593(v=vs.85).aspx
/////////////////////////////////////////////////////////////////////////////////////

#include "SocketServer.h"

//#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "50000"

int handleRecvBuf(SOCKET ClientSocket, char *recvBuf, int bufLen);

int MSDNExample()
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    FD_SET readset;
    FD_SET writeset;

    while (true) {

        FD_ZERO(&readset);
        FD_ZERO(&writeset);

        FD_SET(ListenSocket, &readset);

        iResult = select(0, &readset, &writeset, NULL/* fd_set * exceptfds*/, NULL/*timeout*/);
        if (iResult == SOCKET_ERROR) {
            printf("select failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        if (!FD_ISSET(ListenSocket, &readset))
            return 1;

        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }

        // Receive until the peer shuts down the connection
        std::thread recv_thread([ClientSocket, recvbuflen]()->int{
            char recvbuf[DEFAULT_BUFLEN];
            while (true) {
                int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
                if (iResult > 0) {
                    printf("Bytes received: %d\n", iResult);

                    int iSendResult = handleRecvBuf(ClientSocket, recvbuf, iResult);
                    //iSendResult = send(ClientSocket, recvbuf, iResult, 0);
                    if (iSendResult == SOCKET_ERROR) {
                        printf("send failed with error: %d\n", WSAGetLastError());
                        closesocket(ClientSocket);
                        return 1;
                    }
                    printf("Bytes sent: %d\n", iSendResult);
                }
                else if (iResult == 0) {
                    printf("Connection closing...\n");
                    // cleanup
                    closesocket(ClientSocket);
                    printf("Connection closed\n");
                    return 1;
                }
                else  {
                    printf("recv failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    return 1;
                }
            }
        });
        recv_thread.detach();
    }

    // No longer need server socket
    closesocket(ListenSocket);

    WSACleanup();

    std::cout << "one conversation end\n";

    return 0;
}

int handleTeamInfoReq(SOCKET ClientSocket)
{
    return SOCKET_ERROR;
}

int handleCharacterInfoReq(SOCKET ClientSocket, int uid)
{
    return SOCKET_ERROR;
}

int handleRecvBuf(SOCKET ClientSocket, char *recvBuf, int bufLen)
{
    if (!recvBuf)
        return SOCKET_ERROR;

    return send(ClientSocket, recvBuf, bufLen, 0);
}

void start()
{
    //do {
        MSDNExample();
    //} while (1);
}

void startDebugServer()
{
    std::thread t(start);
    t.detach();
}
