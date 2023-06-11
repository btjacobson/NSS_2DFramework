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

#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{
#if defined(_WIN32)
	WSADATA data;

	if (WSAStartup(MAKEWORD(2, 2), &data))
	{
		printf("Failed to initialize.\n");

		return 1;
	}
#endif

	printf("Configuring local address...\n");
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo* bindAddress;
	getaddrinfo(0, "8080", &hints, &bindAddress);

	printf("Creating socket...\n");
	SOCKET socketListen;
	socketListen = socket(bindAddress->ai_family, bindAddress->ai_socktype, bindAddress->ai_protocol);

	if (!ISVALIDSOCKET(socketListen))
	{
		fprintf(stderr, "Socket() failed. (%d)\n", GETSOCKETERRNO());
		
		return 1;
	}

	printf("Binding socket to local address...\n");
	if (bind(socketListen, bindAddress->ai_addr, bindAddress->ai_addrlen))
	{
		fprintf(stderr, "Bind() failed. (%d)\n", GETSOCKETERRNO());

		return 1;
	}
	freeaddrinfo(bindAddress);

	printf("Listening...\n");
	if (listen(socketListen, 10) < 0)
	{
		fprintf(stderr, "Listen() failed. (%d)\n", GETSOCKETERRNO());

		return 1;
	}
	
	printf("Waiting for connection...\n");
	struct sockaddr_storage clientAddress;
	socklen_t clientLen = sizeof(clientAddress);
	SOCKET socketClient = accept(socketListen, (struct sockaddr*)&clientAddress, &clientLen);

	if (!ISVALIDSOCKET(socketClient))
	{
		fprintf(stderr, "Accept() failed. (%d)\n", GETSOCKETERRNO());

		return 1;
	}

#if defined(_WIN32)
	WSACleanup();
#endif

	return 0;
}