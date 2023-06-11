#ifndef SERVER_H
#define SERVER_H

#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#endif

#if defined(_WIN32)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())
#else
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#endif

#include <unordered_map>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "HeartbeatSocket.h"

#define HEARTBEAT_INTERVAL 10

class Server
{
public:
	Server();
	~Server();

	void Run();

private:
	int Init();
	int Listen();
	
	void HandleConnection();
	void Update();
	void RemoveClient(SOCKET clientToRemove);
	void Shutdown();

	struct addrinfo* bindAddress;
	struct addrinfo hints;

	std::unordered_map<SOCKET, std::chrono::steady_clock::time_point> clients;
	SOCKET listenSocket;

	bool running;
};

#endif
