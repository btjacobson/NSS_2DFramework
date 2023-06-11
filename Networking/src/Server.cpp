#include "Server.h"

/*
int main()
{	
	printf("Reading request...\n");
	char request[1024];
	int bytesReceived = recv(socketClient, request, 1024, 0);
	printf("Received %d bytes.\n", bytesReceived);
	printf("%.*s", bytesReceived, request);

	printf("Sending response...\n");
	const char* response =
		"HTTP/1.1 200 OK\r\n"
		"Connection: close\r\n"
		"Content-Type: text/plain\r\n\r\n"
		"Local time is: ";
	int bytesSent = send(socketClient, response, strlen(response), 0);
	printf("Sent %d of %d bytes.\n", bytesSent, (int)strlen(response));

	time_t timer;
	time(&timer);
	char timeMessage[26];
	ctime_s(timeMessage, sizeof(timeMessage), &timer);
	
	bytesSent = send(socketClient, timeMessage, strlen(timeMessage), 0);
	printf("Sent %d of %d bytes.\n", bytesSent, (int)strlen(timeMessage));
}
*/

Server::Server()
{
	running = false;
}

Server::~Server()
{

}

void Server::Run()
{
	Init();

	while (running)
	{
		HandleConnection();
		Update();
	}

	Shutdown();
}

int Server::Init()
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
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(0, "8080", &hints, &bindAddress);

	printf("Creating socket...\n");
	listenSocket = socket(bindAddress->ai_family, bindAddress->ai_socktype, bindAddress->ai_protocol);

	if (!ISVALIDSOCKET(listenSocket))
	{
		fprintf(stderr, "Socket() failed. (%d)\n", GETSOCKETERRNO());

		return 1;
	}

	printf("Binding socket to local address...\n");
	if (bind(listenSocket, bindAddress->ai_addr, bindAddress->ai_addrlen))
	{
		fprintf(stderr, "Bind() failed. (%d)\n", GETSOCKETERRNO());

		return 1;
	}
	freeaddrinfo(bindAddress);

	running = true;
	Listen();
}

int Server::Listen()
{
	printf("Listening...\n");
	if (listen(listenSocket, 10) < 0)
	{
		fprintf(stderr, "Listen() failed. (%d)\n", GETSOCKETERRNO());

		return 1;
	}
}

void Server::HandleConnection()
{
	struct sockaddr_storage clientAddress;
	socklen_t clientLen = sizeof(clientAddress);
	SOCKET socketClient = accept(listenSocket, (struct sockaddr*)&clientAddress, &clientLen);

	if (!ISVALIDSOCKET(socketClient))
	{
		fprintf(stderr, "Accept() failed. (%d)\n", GETSOCKETERRNO());
	}

	printf("Client has connected...\n");

	char addressBuffer[100];
	getnameinfo((struct sockaddr*)&clientAddress, clientLen, addressBuffer, sizeof(addressBuffer), 0, 0, NI_NUMERICHOST);
	printf("%s\n", addressBuffer);

	clients.insert(std::make_pair(socketClient, std::chrono::steady_clock::now()));
}

void Server::Update()
{
	if (clients.size() > 0)
	{
		for (auto client = clients.begin(); client != clients.end(); )
		{
			char buffer[1024];

			if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now()
				- client->second).count() >= HEARTBEAT_INTERVAL)
			{
				send(client->first, "heartbeat", strlen("heartbeat"), 0);
				client->second = std::chrono::steady_clock::now();
			}

			int result = recv(client->first, buffer, sizeof(buffer), 0);
			if (result == 0 || result == SOCKET_ERROR)
			{
				RemoveClient(client->first);
				client = clients.erase(client);

				continue;
			}
		}
	}
}

void Server::RemoveClient(SOCKET clientToRemove)
{
	printf("Client disconnected.\n");
	CLOSESOCKET(clientToRemove);
}

void Server::Shutdown()
{
	printf("Closing connections...\n");
	//for (auto& client : clients)
	//{
	//	//RemoveClient(client.first);
	//}

	printf("Closing listening socket...\n");
	CLOSESOCKET(listenSocket);

#if defined(_WIN32)
	WSACleanup();
#endif
}
